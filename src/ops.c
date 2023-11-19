#include <ek/ops.h>
#include <ek/scope.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* hopefully not too difficult to follow what's goind on, but to start with we
 * assume we have an effectively infinite amount of virtual registers and we
 * move everything down into them. Typically the top output is used as input in
 * some other step. */

enum loc_kind {
	LOC_NONE, LOC_REG, LOC_MEM
};

struct loc {
	enum loc_kind kind;
	struct loc *next;
	size_t start;
	size_t end;
	size_t reg;
	long long off;
	size_t width;
};

static void set_reg(struct loc *loc, size_t reg)
{
	loc->kind = LOC_REG;
	loc->reg = reg;
}

static void set_mem(struct loc *loc, size_t reg, long long off, size_t width)
{
	loc->kind = LOC_MEM;
	loc->reg = reg;
	loc->off = off;
	loc->width = width;
}

static size_t trivial_type_width(struct ast_node *type)
{
	switch (AST_TYPE(type).kind) {
	case AST_TYPE_POINTER: return 3;
	case AST_TYPE_PRIMITIVE: {
		if (AST_PRIMITIVE_TYPE(type).type == AST_I27)
			return 3;

		if (AST_PRIMITIVE_TYPE(type).type == AST_I9)
			return 1;

		abort();
		break;
	}
	default: abort();
	}
	return 3;
}

enum opcode {
	/* small subset for now */
	OP_LI,
	OP_LA,
	OP_ADD,
	OP_ADDI,
	OP_STT,
	OP_LDT,
	OP_STW,
	OP_LDW,
	OP_MV, /* meta op, will be realized as either load/store or register move */
	OP_LABEL,
	OP_COMMENT,
};

struct op {
	enum opcode opcode;
	struct loc inputs;
	struct loc outputs;
	size_t loc;
	union {
		long long constant;
		const char *string;
	};
	struct op *next;
};

struct ops {
	struct op *base;
	struct op *head;
};

struct ops *create_ops()
{
	struct ops *ops = calloc(1, sizeof(struct ops));

	struct op *op = calloc(1, sizeof(struct op));
	op->opcode = OP_COMMENT;
	op->string = strdup("start");

	ops->base = op;
	ops->head = op;
	return ops;
}

void destroy_ops(struct ops *ops)
{
	if (!ops)
		return;

	struct op *base = ops->base;
	while (base) {
		struct op *prev = base;
		base = base->next;
		free(prev);
	}

	free(ops);
}

static size_t next_virtual_reg()
{
	static size_t reg = 1;
	return reg++;
}

#define HEAD_OUTPUTS(ops) ops->head->outputs

static int lower_op(struct ast_node *n, struct ops *ops);
static struct op *op_head(struct ops *ops)
{
	return ops->head;
}

static struct op *append_op(struct ops *ops, enum opcode opcode)
{
	static size_t i = 1;
	struct op *op = op_head(ops);
	struct op *n = calloc(1, sizeof(struct op));
	n->opcode = opcode;
	op->next = n;
	op->loc = i++;
	ops->head = n;
	return n;
}

static int lower_proc(struct ast_node *n, struct ops *ops)
{
	struct op *op = append_op(ops, OP_LABEL);
	/** @todo name mangling */
	struct ast_node *id = AST_PROC(n).id;
	op->string = strdup(AST_ID(id).id);
	return lower_op(AST_PROC(n).body, ops);
}

static int lower_block(struct ast_node *n, struct ops *ops)
{
	struct ast_node *b = AST_BLOCK(n).body;
	while (b) {
		int ret = lower_op(b, ops);
		if (ret)
			return ret;

		b = b->next;
	}

	return 0;
}

static int lower_var(struct ast_node *n, struct ops *ops)
{
	struct ast_node *d = scope_find_var(n->scope, AST_VAR(n).id);
	/* structs should be handled as well, would it be better to try and fit
	 * them into regs or just dump them on the stack to make sure we don't
	 * immediately run out of registers? */
	struct ast_node *type = d->type;
	if (AST_TYPE(type).kind != AST_TYPE_PRIMITIVE
			&& AST_TYPE(type).kind != AST_TYPE_POINTER) {
		semantic_error(n->scope->fctx, n,
				"only trivial type lowering implemented");
		return -1;
	}

	d->reg = next_virtual_reg();

	if (AST_VAR(n).init) {
		int ret = lower_op(AST_VAR(n).init, ops);
		if (ret)
			return ret;

		struct loc inputs = HEAD_OUTPUTS(ops);
		/* work with only primitive types for now */
		assert(inputs.next == NULL);

		struct op *op = append_op(ops, OP_MV);
		op->inputs = inputs;
		set_reg(&op->outputs, d->reg);
	}

	return 0;
}

static int lower_cast(struct ast_node *n, struct ops *ops)
{
	/** @todo lob off extra trits or something? */
	return lower_op(AST_CAST(n).expr, ops);
}

static int lower_const(struct ast_node *n, struct ops *ops)
{
	if (AST_CONST(n).kind != AST_CONST_INTEGER) {
		semantic_error(n->scope->fctx, n, "only integer constant lowering implemented");
		return -1;
	}

	struct op *op = append_op(ops, OP_LI);
	op->constant = AST_CONST(n).integer;
	set_reg(&op->outputs, next_virtual_reg());
	return 0;
}

static int lower_assign(struct ast_node *n, struct ops *ops)
{
	int ret = lower_op(AST_ASSIGN(n).from, ops);
	if (ret)
		return ret;

	struct loc from = HEAD_OUTPUTS(ops);

	ret = lower_op(AST_ASSIGN(n).to, ops);
	if (ret)
		return ret;

	struct loc to = HEAD_OUTPUTS(ops);
	struct op *op = append_op(ops, OP_MV);
	op->inputs = from;
	op->outputs = to;
	return 0;
}

static int lower_unop(struct ast_node *n, struct ops *ops)
{
	if (AST_UNOP(n).op != AST_DEREF) {
		semantic_error(n->scope->fctx, n, "unop lowering not implemented");
		return -1;
	}

	if (AST_UNOP(n).op == AST_DEREF) {
		int ret = lower_op(AST_UNOP(n).expr, ops);
		if (ret)
			return ret;

		struct loc *l = &HEAD_OUTPUTS(ops);
		if (l->kind == LOC_MEM) {
			/* load value from memory and use it as the next step
			 * location */
			struct op *op = append_op(ops, OP_LDW);
			op->inputs = *l;
			/* hard coded 3 for now, pointer is three trytes */
			set_mem(&op->outputs, next_virtual_reg(), 0, 3);
			return 0;
		}

		/* use the value as if it was a memory location */
		size_t w = trivial_type_width(n->type);
		set_mem(l, l->reg, 0, w);
		return 0;
	}

	return -1;
}

static int lower_id(struct ast_node *n, struct ops *ops)
{
	struct ast_node *d = scope_find_var(n->scope, n);
	assert(d->reg);

	/* feels like a massive hack, but gives fairly readable debug output so
	 * I'll keep it for now. Eventually once I figure out what I'm doing
	 * this whole system will probably have to be rewritten anyway. */
	struct op *op = append_op(ops, OP_COMMENT);
	op->string = strdup(AST_ID(n).id);
	set_reg(&op->outputs, d->reg);
	return 0;
}

static int lower_op(struct ast_node *n, struct ops *ops)
{
	int ret = 0;
	switch (n->node_type) {
	case AST_PROC: ret = lower_proc(n, ops); break;
	case AST_BLOCK: ret = lower_block(n, ops); break;
	case AST_VAR: ret = lower_var(n, ops); break;
	case AST_CAST: ret = lower_cast(n, ops); break;
	case AST_CONST: ret = lower_const(n, ops); break;
	case AST_ASSIGN: ret = lower_assign(n, ops); break;
	case AST_UNOP: ret = lower_unop(n, ops); break;
	case AST_ID: ret = lower_id(n, ops); break;
	default:
		       semantic_error(n->scope->fctx, n, "unimplemented lowering");
		       return -1;
	}

	if (ret)
		return ret;

	return 0;
}

static void print_locs(struct loc *locs)
{
	if (locs->kind == LOC_NONE)
		return;

	printf(" ( ");

	while (locs) {
		if (locs->kind == LOC_MEM)
			printf("%lld(", locs->off);

		printf("r%zd", locs->reg);

		if (locs->kind == LOC_MEM)
			printf(", %zd)", locs->width);

		printf(" ");
		locs = locs->next;
	}

	printf(")");
}

static void print_op(struct op *op)
{
	if (!op)
		return;

	print_locs(&op->outputs);
	putchar(' ');
	switch (op->opcode) {
	case OP_LABEL: printf("%s:", op->string); break;
	case OP_COMMENT: printf("/* %s */", op->string); break;
	case OP_LI: printf("li %lld", op->constant); break;
	case OP_LA: printf("la %s", op->string); break;
	case OP_ADD: printf("add"); break;
	case OP_ADDI: printf("addi %lld", op->constant); break;
	case OP_STT: printf("stt"); break;
	case OP_LDT: printf("ldt"); break;
	case OP_STW: printf("stw"); break;
	case OP_LDW: printf("ldw"); break;
	case OP_MV: printf("mv"); break;
	default: printf("unimp"); break;
	}
	putchar(' ');
	print_locs(&op->inputs);
	printf("\n");
}

static void print_ops(struct ops *ops)
{
	if (!ops)
		return;

	struct op *base = ops->base;
	while (base) {
		print_op(base);
		base = base->next;
	}
}

int lower_ops(struct scope *root, struct ops *ops)
{
	for (struct actual *a = root->actuals; a; a = a->next) {
		assert(a->node);
		int ret = lower_op(a->node, ops);
		if (ret)
			return ret;
	}

	printf("Lowered ops before lifetime analysis:\n");
	print_ops(ops);

	return 0;
}

int analyze_lifetime(struct ops *ops)
{
	return 0;
}

/* this is probably going to balloon up, should probably move this into another
 * file */
int print_asm(struct ops *ops, const char *output)
{
	return 0;
}

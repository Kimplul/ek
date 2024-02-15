/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

/**
 * @file ast.c
 *
 * Abstract syntax tree handling implementations.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <ek/ast.h>
#include <ek/scope.h>

static struct {
	size_t n;
	size_t s;
	struct ast_node **v;
} ast_nodes = {0};

static void destroy_ast_node(struct ast_node *node)
{
	if (!node)
		return;

	switch (node->node_type) {
	case AST_ID: free((void *)AST_ID(node).id); break;
	case AST_CONST:
		if (AST_CONST(node).kind == AST_CONST_STRING)
			free((void *)AST_CONST(node).str);
		break;
	default:
	}

	free(node);
}

void destroy_ast_nodes()
{
	for (size_t i = 0; i < ast_nodes.n; ++i)
		destroy_ast_node(ast_nodes.v[i]);

	free(ast_nodes.v);
}

/* eventually we might want to pass in a context or something */
static struct ast_node *create_ast_node()
{
	if (ast_nodes.s == 0) {
		ast_nodes.s = 1;
		ast_nodes.n = 0;
		ast_nodes.v = calloc(1, sizeof(struct ast_node *));
	}

	else if (ast_nodes.n >= ast_nodes.s) {
		ast_nodes.s *= 2;
		ast_nodes.v =
			realloc(ast_nodes.v,
			        ast_nodes.s * sizeof(struct ast_node *));
	}

	struct ast_node *n = calloc(1, sizeof(struct ast_node));
	ast_nodes.v[ast_nodes.n++] = n;
	return n;
}

/** @todo alloc should maybe also keep track of all nodes in a vector or
 * something and mass free all AST at a time to keep my sanity */
#define ALLOC_NODE(n, type)                                     \
	struct ast_node *n = create_ast_node();                 \
	if (!n) {                                               \
		fprintf(stderr, "failed allocating" type "\n"); \
		return NULL;                                    \
	}

#define DESTROY_LIST(x)                          \
	{                                        \
		struct ast_node *prev = x, *cur; \
		if (prev)                        \
		do {                             \
			cur = prev->next;        \
			destroy_ast_node(prev);  \
		} while ((prev = cur));          \
	}

struct ast_node *gen_arr_access(struct ast_node *base, struct ast_node *idx,
                                struct src_loc loc)
{
	ALLOC_NODE(n, "arr_access");
	n->node_type = AST_ARR_ACCESS;
	AST_ARR_ACCESS(n).base = base;
	AST_ARR_ACCESS(n).idx = idx;
	n->loc = loc;
	return n;
}

struct ast_node *gen_macro_expand(struct ast_node *id, struct ast_node *args,
                                  struct src_loc loc)
{
	ALLOC_NODE(n, "macro_expand");
	n->node_type = AST_MACRO_EXPAND;
	AST_MACRO_EXPAND(n).id = id;
	AST_MACRO_EXPAND(n).args = args;
	n->loc = loc;
	return n;
}

struct ast_node *gen_type_expand(struct ast_node *id,
                                 struct ast_node *args,
                                 struct src_loc loc)
{
	ALLOC_NODE(n, "type_expand");
	n->node_type = AST_TYPE_EXPAND;
	AST_TYPE_EXPAND(n).id = id;
	AST_TYPE_EXPAND(n).args = args;
	n->loc = loc;
	return n;
}

struct ast_node *gen_binop(enum ast_binops op,
                           struct ast_node *left,
                           struct ast_node *right,
                           struct src_loc loc)
{
	ALLOC_NODE(n, "binop");
	n->node_type = AST_BINOP;
	n->binop.op = op;
	n->binop.left = left;
	n->binop.right = right;
	n->loc = loc;
	return n;
}

struct ast_node *gen_unop(enum ast_unops op, struct ast_node *expr)
{
	ALLOC_NODE(n, "unop");
	n->node_type = AST_UNOP;
	n->_unop.op = op;
	n->_unop.expr = expr;
	n->loc = expr->loc;
	return n;
}

struct ast_node *gen_call(struct ast_node *expr, struct ast_node *args,
                          struct src_loc loc)
{
	ALLOC_NODE(n, "call");
	n->node_type = AST_CALL;
	AST_CALL(n).expr = expr;
	AST_CALL(n).args = args;
	n->loc = loc;
	return n;
}

struct ast_node *gen_id(const char *id, struct src_loc loc)
{
	ALLOC_NODE(n, "id");
	n->node_type = AST_ID;
	n->_id.id = id;
	n->loc = loc;
	return n;
}

struct ast_node *gen_assign(struct ast_node *to, struct ast_node *from)
{
	ALLOC_NODE(n, "assign");
	n->node_type = AST_ASSIGN;
	n->_assign.to = to;
	n->_assign.from = from;
	return n;
}

struct ast_node *gen_init(struct ast_node *body)
{
	ALLOC_NODE(n, "struct init");
	n->node_type = AST_INIT;
	n->_init.body = body;
	n->loc = body->loc;
	return n;
}

struct ast_node *gen_int(long long integer)
{
	ALLOC_NODE(n, "int");
	n->node_type = AST_CONST;
	n->_const.kind = AST_CONST_INTEGER;
	n->_const.integer = integer;
	return n;
}

struct ast_node *gen_string(const char *str)
{
	ALLOC_NODE(n, "string");
	n->node_type = AST_CONST;
	n->_const.kind = AST_CONST_STRING;
	n->_const.str = str;
	return n;
}

struct ast_node *gen_while(struct ast_node *cond, struct ast_node *body)
{
	ALLOC_NODE(n, "while");
	n->node_type = AST_WHILE;
	n->_while.cond = cond;
	n->_while.body = body;
	return n;
}

struct ast_node *gen_for(struct ast_node *pre, struct ast_node *cond,
                         struct ast_node *post, struct ast_node *body)
{
	ALLOC_NODE(n, "for");
	n->node_type = AST_FOR;
	n->_for.pre = pre;
	n->_for.cond = cond;
	n->_for.post = post;
	n->_for.body = body;
	return n;
}

struct ast_node *gen_return(struct ast_node *expr)
{
	ALLOC_NODE(n, "return");
	n->node_type = AST_RETURN;
	n->_return.expr = expr;
	if (expr)
		n->loc = expr->loc;
	return n;
}

struct ast_node *gen_goto(struct ast_node *label)
{
	ALLOC_NODE(n, "goto");
	n->node_type = AST_GOTO;
	n->_goto.label = label;
	n->loc = label->loc;
	return n;
}

struct ast_node *gen_dot(struct ast_node *expr, struct ast_node *id, struct src_loc loc)
{
	ALLOC_NODE(n, "dot");
	n->node_type = AST_DOT;
	AST_DOT(n).expr = expr;
	AST_DOT(n).id = id;
	n->loc = loc;
	return n;
}

struct ast_node *gen_label(struct ast_node *id)
{
	ALLOC_NODE(n, "label");
	n->node_type = AST_LABEL;
	n->_label.id = id;
	n->loc = id->loc;
	return n;
}

struct ast_node *gen_ctrl(enum ast_ctrl_kind kind, struct src_loc loc)
{
	ALLOC_NODE(n, "ctrl");
	n->node_type = AST_CTRL;
	n->loc = loc;
	n->_ctrl.kind = kind;
	return n;
}

struct ast_node *gen_fetch(struct ast_node *id, struct ast_node *type)
{
	ALLOC_NODE(n, "fetch");
	n->node_type = AST_FETCH;
	n->_fetch.id = id;
	n->_fetch.type = type;
	n->loc = id->loc;
	return n;
}

struct ast_node *gen_macro_construct(struct ast_node *id,
                                     struct ast_node *params,
                                     struct ast_node *body)
{
	ALLOC_NODE(n, "macro_construct");
	n->node_type = AST_MACRO_CONSTRUCT;
	AST_MACRO_CONSTRUCT(n).id = id;
	AST_MACRO_CONSTRUCT(n).params = params;
	AST_MACRO_CONSTRUCT(n).body = body;
	n->loc = id->loc;
	return n;
}

struct ast_node *gen_if(struct ast_node *cond, struct ast_node *body,
                        struct ast_node *els)
{
	ALLOC_NODE(n, "if");
	n->node_type = AST_IF;
	n->_if.cond = cond;
	n->_if.body = body;
	n->_if.els = els;
	return n;
}

struct ast_node *gen_switch(struct ast_node *cond, struct ast_node *cases)
{
	ALLOC_NODE(n, "switch");
	n->node_type = AST_SWITCH;
	n->_switch.cond = cond;
	n->_switch.cases = cases;
	n->loc = cond->loc;
	return n;
}

struct ast_node *gen_case(struct ast_node *cond, struct ast_node *body)
{
	ALLOC_NODE(n, "case");
	/* TODO: a macro to map proc name to node type would make sure I don't
	 * make any dumb mixups... */
	n->node_type = AST_CASE;
	n->_case.cond = cond;
	n->_case.body = body;
	/* TODO: where should I check the fallthrough flag? In the
	 * actualization stage, I guess */
	n->loc = body->loc;
	return n;
}

struct ast_node *gen_primitive(enum ast_primitive type, struct src_loc loc)
{
	ALLOC_NODE(n, "primitive");
	n->node_type = AST_TYPE;
	AST_TYPE(n).kind = AST_TYPE_PRIMITIVE;
	AST_PRIMITIVE_TYPE(n).type = type;
	n->loc = loc;
	return n;
}

struct ast_node *gen_type(enum ast_type_kind kind,
                          struct ast_node *t0,
                          struct ast_node *t1,
                          struct src_loc loc)
{
	ALLOC_NODE(n, "type");
	n->node_type = AST_TYPE;
	AST_TYPE(n).kind = kind;
	n->loc = loc;

	switch (kind) {
	case AST_TYPE_TRAIT:
		AST_TRAIT_TYPE(n).def = t0;
		break;

	case AST_TYPE_ID:
		AST_ID_TYPE(n).id = t0;
		break;

	case AST_TYPE_CONSTRUCT:
		AST_CONSTRUCT_TYPE(n).id = t0;
		AST_CONSTRUCT_TYPE(n).args = t1;
		break;

	case AST_TYPE_ARR:
		AST_ARR_TYPE(n).size = t0;
		AST_ARR_TYPE(n).base = t1;
		break;

	case AST_TYPE_POINTER:
		AST_PTR_TYPE(n).base = t0;
		break;

	case AST_TYPE_STRUCT:
		AST_STRUCT_TYPE(n).def = t0;
		break;

	case AST_TYPE_ENUM:
		AST_ENUM_TYPE(n).def = t0;
		break;

	case AST_TYPE_SIGN:
		AST_SIGN_TYPE(n).params = t0;
		AST_SIGN_TYPE(n).ret = t1;
		break;

	default: abort();
	}

	return n;
}

struct ast_node *gen_block(struct ast_node *body)
{
	ALLOC_NODE(n, "block");
	n->node_type = AST_BLOCK;
	n->_block.body = body;
	return n;
}

struct ast_node *gen_sizeof(struct ast_node *expr)
{
	ALLOC_NODE(n, "sizeof");
	n->node_type = AST_SIZEOF;
	n->_sizeof.expr = expr;
	n->loc = expr->loc;
	return n;
}

struct ast_node *gen_as(struct ast_node *type)
{
	ALLOC_NODE(n, "as");
	n->node_type = AST_AS;
	n->_as.type = type;
	n->loc = type->loc;
	return n;
}

struct ast_node *gen_defer(struct ast_node *expr)
{
	ALLOC_NODE(n, "defer");
	n->node_type = AST_DEFER;
	n->_defer.expr = expr;
	n->loc = expr->loc;
	return n;
}

void destroy_defer(struct ast_node *defer)
{
	assert(defer->node_type == AST_DEFER);
	destroy_ast_node(defer->_defer.expr);
	free(defer);
}

struct ast_node *gen_var(struct ast_node *id, struct ast_node *type,
                         struct ast_node *init, struct src_loc loc)
{
	ALLOC_NODE(n, "var");
	n->node_type = AST_VAR;
	AST_VAR(n).id = id;
	AST_VAR(n).type = type;
	AST_VAR(n).init = init;
	n->loc = loc;
	return n;
}

struct ast_node *gen_proc(struct ast_node *id, struct ast_node *sign,
                          struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "proc");
	n->node_type = AST_PROC;
	AST_PROC(n).id = id;
	AST_PROC(n).sign = sign;
	AST_PROC(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_struct(struct ast_node *id,
                            struct ast_node *generics, struct ast_node *body)
{
	ALLOC_NODE(n, "struct");
	n->node_type = AST_STRUCT;
	n->_struct.id = id;
	n->_struct.generics = generics;
	n->_struct.body = body;
	if (id)
		n->loc = id->loc;
	else
		n->loc = body->loc;
	return n;
}

struct ast_node *gen_enum(struct ast_node *id, struct ast_node *type,
                          struct ast_node *body)
{
	ALLOC_NODE(n, "enum");
	n->node_type = AST_ENUM;
	n->_enum.id = id;
	n->_enum.type = type;
	n->_enum.body = body;
	if (id)
		n->loc = id->loc;
	return n;
}

struct ast_node *gen_cast(struct ast_node *expr, struct ast_node *type)
{
	ALLOC_NODE(n, "cast");
	n->node_type = AST_CAST;
	n->_cast.expr = expr;
	n->_cast.type = type;
	return n;
}

struct ast_node *gen_val(struct ast_node *id, struct ast_node *val)
{
	ALLOC_NODE(n, "val");
	n->node_type = AST_VAL;
	n->_val.id = id;
	n->_val.val = val;
	n->loc = id->loc;
	return n;
}

struct ast_node *gen_alias(struct ast_node *id, struct ast_node *type)
{
	ALLOC_NODE(n, "alias");
	n->node_type = AST_ALIAS;
	n->_alias.id = id;
	n->_alias.type = type;
	n->loc = id->loc;
	return n;
}

struct ast_node *gen_trait(struct ast_node *id, struct ast_node *params,
                           struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "trait");
	n->node_type = AST_TRAIT;
	AST_TRAIT(n).id = id;
	AST_TRAIT(n).params = params;
	AST_TRAIT(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_import(const char *file)
{
	ALLOC_NODE(n, "import");
	n->node_type = AST_IMPORT;
	n->_import.file = file;
	/* TODO: where to get location */
	return n;
}

struct ast_node *gen_embed(const char *file)
{
	ALLOC_NODE(n, "embed");
	n->node_type = AST_EMBED;
	n->_embed.file = file;
	/* TODO: location */
	return n;
}

struct ast_node *gen_empty()
{
	ALLOC_NODE(n, "empty");
	n->node_type = AST_EMPTY;
	/* TODO: location */
	return n;
}

void ast_set_flags(struct ast_node *node, enum ast_flag flags)
{
	node->flags |= flags;
}

void ast_clear_flags(struct ast_node *node, enum ast_flag flags)
{
	node->flags &= ~(flags);
}

void ast_append(struct ast_node *list, struct ast_node *elem)
{
	struct ast_node *cur = list;
	while (cur->next)
		cur = cur->next;

	cur->next = elem;
}


static const char *binop_symbol(int op)
{
	switch (op) {
	case AST_ADD: return "+";
	case AST_SUB: return "-";
	case AST_MUL: return "*";
	case AST_DIV: return "/";
	case AST_REM: return "%";
	case AST_LOR: return "||";
	case AST_LAND: return "&&";
	case AST_LSHIFT: return "<<";
	case AST_RSHIFT: return ">>";
	case AST_ASSIGN_ADD: return "+=";
	case AST_ASSIGN_SUB: return "-=";
	case AST_ASSIGN_MUL: return "*=";
	case AST_ASSIGN_DIV: return "/=";
	case AST_ASSIGN_REM: return "%=";
	case AST_ASSIGN_LSHIFT: return "<<=";
	case AST_ASSIGN_RSHIFT: return ">>=";
	case AST_LT: return "<";
	case AST_GT: return ">";
	case AST_LE: return "<=";
	case AST_GE: return ">=";
	case AST_NE: return "!=";
	case AST_EQ: return "==";
	}

	return "UNKNOWN";
}

static const char *unop_symbol(int op)
{
	switch (op) {
	case AST_NEG: return "-";
	case AST_LNOT: return "!";
	case AST_REF: return "&";
	case AST_DEREF: return "*";
	}

	return "UNKNOWN";
}

static void dump(int depth, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	for (int i = 0; i < depth; ++i)
		putchar('\t');

	vprintf(fmt, args);

	va_end(args);
}

static void dump_flags(struct ast_node *node)
{
	if (node->scope)
		printf(" %zu:", node->scope->number);

	enum ast_flag flags = node->flags;
	if (flags & AST_FLAG_MUTABLE)
		printf(" MUT");

	if (flags & AST_FLAG_CONST)
		printf(" CONST");

	if (flags & AST_FLAG_EXTERN)
		printf(" EXTERN");

	if (flags & AST_FLAG_VARIADIC)
		printf(" VARIADIC");

	if (flags & AST_FLAG_DELAYED)
		printf(" DELAYED");

	if (flags & AST_FLAG_PUBLIC)
		printf(" PUB");

	if (flags & AST_FLAG_UNTYPED)
		printf(" UNTYPED");

	if (flags & AST_FLAG_FALLTHROUGH)
		printf(" FALLTHROUGH");
}

const char *primitive_str(enum ast_primitive type)
{
	switch (type) {
	case AST_VOID: return "void";
	case AST_I9: return "i9";
	case AST_I27: return "i27";
	default: return "unimp";
	}

	return "unimp";
}

static void __dump_ast(int depth, struct ast_node *node)
{
	switch (node->node_type) {
	case AST_FETCH:
		dump(depth, "{FETCH:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_fetch.id);
		dump_ast(depth + 1, node->_fetch.type);

		dump(depth, "}\n");
		break;

	case AST_ASSIGN:
		dump(depth, "{ASSIGN:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_assign.to);
		dump_ast(depth + 1, node->_assign.from);

		dump(depth, "}\n");
		break;

	case AST_INIT:
		dump(depth, "{INIT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_init.body);

		dump(depth, "}\n");
		break;

	case AST_SIZEOF:
		dump(depth, "{SIZEOF:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_sizeof.expr);

		dump(depth, "}\n");
		break;

	case AST_DOT:
		dump(depth, "{DOT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_dot.expr);
		dump_ast(depth + 1, node->_dot.id);

		dump(depth, "}\n");
		break;

	case AST_GOTO:
		dump(depth, "{GOTO:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_goto.defers);
		dump_ast(depth + 1, node->_goto.label);

		dump(depth, "}\n");
		break;

	case AST_LABEL:
		dump(depth, "{LABEL:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_label.id);

		dump(depth, "}\n");
		break;

	case AST_BINOP:
		dump(depth, "{BINOP:");
		dump_flags(node);
		printf(" %s\n", binop_symbol(node->binop.op));

		dump_ast(depth + 1, node->binop.left);
		dump_ast(depth + 1, node->binop.right);

		dump(depth, "}\n");
		break;

	case AST_UNOP:
		dump(depth, "{UNOP:");
		dump_flags(node);
		printf(" %s\n", unop_symbol(node->_unop.op));

		dump_ast(depth + 1, node->_unop.expr);

		dump(depth, "}\n");
		break;

	case AST_CALL:
		dump(depth, "{CALL:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_CALL(node).expr);
		dump_ast(depth + 1, AST_CALL(node).args);

		dump(depth, "}\n");
		break;

	case AST_DEFER:
		dump(depth, "{DEFER:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_defer.expr);

		dump(depth, "}\n");
		break;

	case AST_CAST:
		dump(depth, "{CAST:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_cast.expr);
		dump_ast(depth + 1, node->_cast.type);

		dump(depth, "}\n");
		break;

	case AST_MACRO_CONSTRUCT:
		dump(depth, "{MACRO_CONSTRUCT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_MACRO_CONSTRUCT(node).id);
		dump_ast(depth + 1, AST_MACRO_CONSTRUCT(node).params);
		dump_ast(depth + 1, AST_MACRO_CONSTRUCT(node).body);

		dump(depth, "}\n");
		break;

	case AST_MACRO_EXPAND:
		dump(depth, "{MACRO_EXPAND:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_macro_expand.id);
		dump_ast(depth + 1, node->_macro_expand.args);

		dump(depth, "}\n");
		break;

	case AST_PROC:
		dump(depth, "{PROC:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_proc.id);
		dump_ast(depth + 1, node->_proc.sign);
		dump_ast(depth + 1, node->_proc.body);

		dump(depth, "}\n");
		break;

	case AST_VAR:
		dump(depth, "{VAR:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_var.id);
		dump_ast(depth + 1, node->_var.type);
		dump_ast(depth + 1, node->_var.init);

		dump(depth, "}\n");
		break;

	case AST_ID:
		dump(depth, "{ID:");
		dump_flags(node);
		printf(" %s}\n", node->_id.id);
		break;

	case AST_AS:
		dump(depth, "{AS:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_as.type);
		dump(depth, "}\n");
		break;

	case AST_BLOCK:
		dump(depth, "{BLOCK:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_block.body);
		dump_ast(depth + 1, node->_block.defers);

		dump(depth, "}\n");
		break;

	case AST_RETURN:
		dump(depth, "{RETURN:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_return.defers);
		dump_ast(depth + 1, node->_return.expr);

		dump(depth, "}\n");
		break;

	case AST_TYPE:
		dump(depth, "{TYPE:");
		dump_flags(node);

		switch (node->_type.kind) {
		case AST_TYPE_PRIMITIVE:
			printf(" PRIMITIVE %s\n",
			       primitive_str(AST_PRIMITIVE_TYPE(node).type));
			break;

		case AST_TYPE_TRAIT:
			printf(" TRAIT\n");
			/* might be a bit overkill? */
			dump_ast(depth + 1, AST_TRAIT_TYPE(node).def);
			break;

		case AST_TYPE_ID:
			printf(" ID\n");
			dump_ast(depth + 1, AST_ID_TYPE(node).id);
			break;

		case AST_TYPE_ARR:
			printf(" ARR\n");
			dump_ast(depth + 1, AST_ARR_TYPE(node).size);
			dump_ast(depth + 1, AST_ARR_TYPE(node).base);
			break;

		case AST_TYPE_POINTER:
			printf(" PTR\n");
			dump_ast(depth + 1, AST_PTR_TYPE(node).base);
			break;

		case AST_TYPE_STRUCT:
			printf(" STRUCT\n");
			/* oh yeah, struc is at least right now just an ID that
			 * we can use to fetch the actual struct with. */
			dump_ast(depth + 1, AST_STRUCT_TYPE(node).def);
			break;

		case AST_TYPE_ENUM:
			printf(" ENUM\n");
			dump_ast(depth + 1, AST_ENUM_TYPE(node).def);
			break;

		case AST_TYPE_SIGN:
			printf(" SIGN\n");
			dump_ast(depth + 1, AST_SIGN_TYPE(node).params);
			dump_ast(depth + 1, AST_SIGN_TYPE(node).ret);
			break;
		}

		dump_ast(depth + 1, AST_TYPE(node).next);

		dump(depth, "}\n");
		break;

	case AST_EMPTY:
		dump(depth, "{EMPTY:");
		dump_flags(node);
		printf("}\n");
		break;

	case AST_FOR:
		dump(depth, "{FOR:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_for.pre);
		dump_ast(depth + 1, node->_for.cond);
		dump_ast(depth + 1, node->_for.post);
		dump_ast(depth + 1, node->_for.body);

		dump(depth, "}\n");
		break;

	case AST_WHILE:
		dump(depth, "{WHILE:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_while.cond);
		dump_ast(depth + 1, node->_while.body);

		dump(depth, "}\n");
		break;

	case AST_CTRL:
		dump(depth, "{CTRL:");
		dump_flags(node);
		switch(node->_ctrl.kind) {
		case AST_CTRL_BREAK: printf(" BREAK"); break;
		case AST_CTRL_CONTINUE: printf(" CONTINUE"); break;
		}
		printf("}\n");
		break;

	case AST_IF:
		dump(depth, "{IF:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_if.cond);
		dump_ast(depth + 1, node->_if.body);
		dump_ast(depth + 1, node->_if.els);

		dump(depth, "}\n");
		break;

	case AST_IMPORT:
		dump(depth, "{IMPORT:");
		dump_flags(node);
		printf(" %s}\n", node->_import.file);
		break;

	case AST_EMBED:
		dump(depth, "{EMBED:");
		dump_flags(node);
		printf(" %s}\n", node->_import.file);
		break;

	case AST_ENUM:
		dump(depth, "{ENUM:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_enum.id);
		dump_ast(depth + 1, node->_enum.type);
		dump_ast(depth + 1, node->_enum.body);

		dump(depth, "}\n");
		break;

	case AST_STRUCT:
		dump(depth, "{STRUCT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_struct.id);
		dump_ast(depth + 1, node->_struct.generics);
		dump_ast(depth + 1, node->_struct.body);

		dump(depth, "}\n");
		break;

	case AST_VAL:
		dump(depth, "{VAL:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_val.id);
		dump_ast(depth + 1, node->_val.val);

		dump(depth, "}\n");
		break;

	case AST_SWITCH:
		dump(depth, "{SWITCH:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_switch.cond);
		dump_ast(depth + 1, node->_switch.cases);

		dump(depth, "}\n");
		break;

	case AST_CASE:
		dump(depth, "{CASE:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_case.cond);
		dump_ast(depth + 1, node->_case.body);

		dump(depth, "}\n");
		break;

	case AST_CONST:
		dump(depth, "{CONST:");
		dump_flags(node);
		switch (node->_const.kind) {
		case AST_CONST_INTEGER: printf(" %lli",
			                       AST_CONST(node).integer);
			break;
		case AST_CONST_STRING: printf(" \"%s\"", AST_CONST(node).str);
			break;
		}
		printf("}\n");
		break;

	case AST_ALIAS:
		dump(depth, "{ALIAS:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_alias.id);
		dump_ast(depth + 1, node->_alias.type);

		dump(depth, "}\n");
		break;

	case AST_TRAIT:
		dump(depth, "{TRAIT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_trait.id);
		dump_ast(depth + 1, node->_trait.body);

		dump(depth, "}\n");
		break;

	default:
		dump(depth, "{UNIMP}\n");
	}
}

void dump_ast(int depth, struct ast_node *root)
{
	if (!root) {
		dump(depth, "{NULL}\n");
		return;
	}

	struct ast_node *n = root;
	do {
		__dump_ast(depth, n);
	} while ((n = n->next));
}

struct ast_node *clone_ast_node(struct ast_node *node)
{
	if (!node)
		return NULL;

	assert(node->node_type);
	struct ast_node *new = NULL;
	switch (node->node_type) {
	case AST_ARR_ACCESS:
		new = gen_arr_access(
			clone_ast_node(AST_ARR_ACCESS(node).base),
			clone_ast_node(AST_ARR_ACCESS(node).idx),
			node->loc);
		break;

	case AST_TYPE_EXPAND:
		new = gen_type_expand(
			clone_ast_node(AST_TYPE_EXPAND(node).id),
			clone_ast_node(AST_TYPE_EXPAND(node).args),
			node->loc);
		break;

	case AST_FETCH:
		new = gen_fetch(clone_ast_node(node->_fetch.id),
		                clone_ast_node(node->_fetch.type));
		break;

	case AST_ASSIGN:
		new = gen_assign(clone_ast_node(node->_assign.to),
		                 clone_ast_node(node->_assign.from));
		break;

	case AST_INIT: new = gen_init(clone_ast_node(node->_init.body));
		break;

	case AST_SIZEOF: new = gen_sizeof(clone_ast_node(node->_sizeof.expr));
		break;

	case AST_DOT: new = gen_dot(clone_ast_node(AST_DOT(node).expr),
		                    clone_ast_node(AST_DOT(node).id),
				    node->loc);
		break;

	case AST_AS: new = gen_as(clone_ast_node(node->_as.type));
		break;

	case AST_GOTO: new = gen_goto(clone_ast_node(node->_goto.label));
		break;

	case AST_LABEL: new = gen_label(clone_ast_node(node->_label.id));
		break;

	case AST_BINOP: new = gen_binop(node->binop.op,
		                        clone_ast_node(node->binop.left),
		                        clone_ast_node(node->binop.right),
		                        node->loc);
		break;

	case AST_UNOP: new = gen_unop(node->_unop.op,
		                      clone_ast_node(node->_unop.expr));
		break;

	case AST_CALL: new = gen_call(clone_ast_node(AST_CALL(node).expr),
		                      clone_ast_node(AST_CALL(node).args),
		                      node->loc);
		break;

	case AST_DEFER: new = gen_defer(clone_ast_node(node->_defer.expr));
		break;

	case AST_MACRO_CONSTRUCT: new = gen_macro_construct(
			clone_ast_node(AST_MACRO_CONSTRUCT(node).id),
			clone_ast_node(AST_MACRO_CONSTRUCT(node).params),
			clone_ast_node(AST_MACRO_CONSTRUCT(node).body));
		break;

	case AST_MACRO_EXPAND: new = gen_macro_expand(
			clone_ast_node(AST_MACRO_EXPAND(node).id),
			clone_ast_node(AST_MACRO_EXPAND(node).args),
			node->loc);
		break;

	case AST_CAST: new = gen_cast(clone_ast_node(node->_cast.expr),
		                      clone_ast_node(node->_cast.type));
		break;

	case AST_PROC: new = gen_proc(clone_ast_node(node->_proc.id),
		                      clone_ast_node(node->_proc.sign),
		                      clone_ast_node(node->_proc.body),
		                      node->loc);
		break;

	case AST_VAR: new = gen_var(clone_ast_node(AST_VAR(node).id),
		              clone_ast_node(AST_VAR(node).type),
		              clone_ast_node(AST_VAR(node).init),
			      node->loc);
		break;

	case AST_FOR: new = gen_for(clone_ast_node(node->_for.pre),
		                    clone_ast_node(node->_for.cond),
		                    clone_ast_node(node->_for.post),
		                    clone_ast_node(node->_for.body));
		break;

	case AST_WHILE: new = gen_while(clone_ast_node(node->_while.cond),
		                        clone_ast_node(node->_while.body));
		break;

	case AST_CTRL: new = gen_ctrl(node->_ctrl.kind, node->loc);
		break;

	case AST_RETURN: new = gen_return(clone_ast_node(node->_return.expr));
		break;

	case AST_TYPE:
		/* oh, if a node has a ->type it probably isn't cloned
		 * correctly... */
		switch (node->_type.kind) {
		case AST_TYPE_PRIMITIVE:
			new = gen_primitive(AST_PRIMITIVE_TYPE(
						    node).type, node->loc);
			break;

		case AST_TYPE_TRAIT:
			new = gen_type(AST_TYPE_TRAIT,
			               AST_TRAIT_TYPE(node).def,
			               NULL,
			               node->loc);
			break;

		case AST_TYPE_ID:
			new = gen_type(AST_TYPE_ID,
			               clone_ast_node(AST_ID_TYPE(node).id),
			               NULL,
			               node->loc);
			break;

		case AST_TYPE_ARR:
			new = gen_type(AST_TYPE_ARR,
			               clone_ast_node(AST_ARR_TYPE(node).size),
			               clone_ast_node(AST_ARR_TYPE(node).base),
			               node->loc);
			break;

		case AST_TYPE_POINTER:
			new = gen_type(AST_TYPE_POINTER, AST_PTR_TYPE(node).base,
				NULL,
			               node->loc);
			break;

		case AST_TYPE_STRUCT:
			new = gen_type(AST_TYPE_STRUCT,
			               clone_ast_node(AST_STRUCT_TYPE(node).def),
			               NULL, node->loc);
			break;

		case AST_TYPE_ENUM:
			new = gen_type(AST_TYPE_ENUM,
			               clone_ast_node(AST_ENUM_TYPE(node).def),
			               NULL,
			               node->loc);
			break;

		case AST_TYPE_SIGN:
			new = gen_type(AST_TYPE_SIGN,
			               clone_ast_node(AST_SIGN_TYPE(node).params),
			               clone_ast_node(AST_SIGN_TYPE(node).ret),
			               node->loc);
			break;

		}

		assert(new);
		new->_type.next = clone_ast_node(node->_type.next);
		break;

	case AST_BLOCK:
		/* TODO: should defers also be cloned? Probably? */
		new = gen_block(clone_ast_node(node->_block.body));
		break;

	case AST_IMPORT:
		new = gen_import(strdup(node->_import.file));
		break;

	case AST_EMBED:
		new = gen_embed(strdup(node->_import.file));
		break;

	case AST_ENUM:
		new = gen_enum(clone_ast_node(node->_enum.id),
		               clone_ast_node(node->_enum.type),
		               clone_ast_node(node->_enum.body));
		break;

	case AST_STRUCT:
		new = gen_struct(clone_ast_node(node->_struct.id),
		                 clone_ast_node(node->_struct.generics),
		                 clone_ast_node(node->_struct.body));
		break;

	case AST_VAL:
		new = gen_val(clone_ast_node(node->_val.id),
		              clone_ast_node(node->_val.val));
		break;

	case AST_SWITCH:
		new = gen_switch(clone_ast_node(node->_switch.cond),
		                 clone_ast_node(node->_switch.cases));
		break;

	case AST_CASE:
		new = gen_case(clone_ast_node(node->_case.cond),
		               clone_ast_node(node->_case.body));
		break;

	case AST_CONST:
		switch (node->_const.kind) {
		case AST_CONST_INTEGER:
			new = gen_int(node->_const.integer);
			break;

		case AST_CONST_STRING:
			new = gen_string(strdup(node->_const.str));
			break;
		}
		break;

	case AST_ID:
		new = gen_id(strdup(node->_id.id), node->loc);
		break;

	case AST_EMPTY:
		new = gen_empty();
		break;

	case AST_ALIAS:
		new = gen_alias(clone_ast_node(node->_alias.id),
		                clone_ast_node(node->_alias.type));
		break;

	case AST_TRAIT:
		new = gen_trait(clone_ast_node(AST_TRAIT(node).id),
		                clone_ast_node(AST_TRAIT(node).params),
		                clone_ast_node(AST_TRAIT(node).body),
		                node->loc);
		break;

	case AST_IF:
		new = gen_if(clone_ast_node(node->_if.cond),
		             clone_ast_node(node->_if.body),
		             clone_ast_node(node->_if.els));
		break;
	}

	/* if we run out of memory, this assert is likely a bit dumb... */
	assert(new);
	new->scope = node->scope;
	new->flags = node->flags;
	new->loc = node->loc;
	new->next = clone_ast_node(node->next);

	/* some special case handled type references for us */
	if (!new->type)
		new->type = node->type;

	return new;
}

/* here we could do a memcmp... */
static int identical_loc(struct src_loc left, struct src_loc right)
{
	return left.first_line == right.first_line
	       && left.last_line == right.last_line
	       && left.first_col == right.first_col
	       && left.last_col == right.last_col;
}

static int identical_flags(enum ast_flag left, enum ast_flag right)
{
	return left == right;
}

/* TODO: remember to update this if I decide to not mess aroung with this void*
 * nonsense */
static int identical_scope(void *left, void *right)
{
	return left == right;
}

static int identical_assign(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_assign.to, a->_assign.to))
		return 0;

	if (!identical_ast_nodes(exact, b->_assign.from, b->_assign.from))
		return 0;

	return 1;
}

static int identical_init(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_init.body, b->_init.body);
}

static int identical_sizeof(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_sizeof.expr, b->_sizeof.expr);
}

static int identical_dot(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_dot.expr, b->_dot.expr))
		return 0;

	if (!identical_ast_nodes(exact, a->_dot.id, b->_dot.id))
		return 0;

	return 1;
}

static int identical_as(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_as.type, b->_as.type);
}

static int identical_goto(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_goto.label, b->_goto.label);
}

static int identical_label(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_label.id, b->_label.id);
}

static int identical_binop(int exact, struct ast_node *a, struct ast_node *b)
{
	if (a->binop.op != b->binop.op)
		return 0;

	if (!identical_ast_nodes(exact, a->binop.left, b->binop.left))
		return 0;

	if (!identical_ast_nodes(exact, a->binop.right, b->binop.right))
		return 0;

	return 1;
}

static int identical_unop(int exact, struct ast_node *a, struct ast_node *b)
{
	if (a->_unop.op != b->_unop.op)
		return 0;

	if (!identical_ast_nodes(exact, a->_unop.expr, b->_unop.expr))
		return 0;

	return 1;
}

static int identical_call(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, AST_CALL(a).expr, AST_CALL(b).expr))
		return 0;

	if (!identical_ast_nodes(exact, AST_CALL(a).args, AST_CALL(b).args))
		return 0;

	return 1;
}

static int identical_cast(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_cast.expr, b->_cast.expr))
		return 0;

	if (!identical_ast_nodes(exact, a->_cast.type, b->_cast.type))
		return 0;

	return 1;
}

static int identical_defer(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_defer.expr, b->_defer.expr);
}

static int identical_macro_construct(int exact, struct ast_node *a,
                                     struct ast_node *b)
{
	if (!identical_ast_nodes(exact, AST_MACRO_CONSTRUCT(a).id,
	                         AST_MACRO_CONSTRUCT(b).id))
		return 0;

	if (!identical_ast_nodes(exact, AST_MACRO_CONSTRUCT(a).params,
	                         AST_MACRO_CONSTRUCT(b).params))
		return 0;

	return identical_ast_nodes(exact, AST_MACRO_CONSTRUCT(
					   a).body,
	                           AST_MACRO_CONSTRUCT(b).body);
}

static int identical_macro_expand(int exact, struct ast_node *a,
                                  struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_macro_expand.id,
	                         b->_macro_expand.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_macro_expand.args,
	                         b->_macro_expand.args))
		return 0;

	return 1;
}

static int identical_proc(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_proc.id, b->_proc.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_proc.sign, b->_proc.sign))
		return 0;

	if (!identical_ast_nodes(exact, a->_proc.body, b->_proc.body))
		return 0;

	return 1;
}

static int identical_var(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_var.id, b->_var.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_var.type, b->_var.type))
		return 0;

	if (!identical_ast_nodes(exact, a->_var.init, b->_var.init))
		return 0;

	return 1;
}

static int identical_for(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_for.pre, b->_for.pre))
		return 0;

	if (!identical_ast_nodes(exact, a->_for.cond, b->_for.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_for.post, b->_for.post))
		return 0;

	if (!identical_ast_nodes(exact, a->_for.body, b->_for.body))
		return 0;

	return 1;
}

static int identical_while(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_while.cond, b->_while.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_while.body, b->_while.body))
		return 0;

	return 1;
}

static int identical_ctrl(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	return a->_ctrl.kind == b->_ctrl.kind;
}

static int identical_return(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_return.expr, b->_return.expr);
}

static int identical_type_id(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, AST_ID_TYPE(a).id, AST_ID_TYPE(b).id);
}

static int identical_type_arr(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, AST_ARR_TYPE(a).size,
	                         AST_ARR_TYPE(b).size))
		return 0;

	return identical_ast_nodes(exact, AST_ARR_TYPE(a).base, AST_ARR_TYPE(
					   b).base);
}

static int identical_type_trait(int exact, struct ast_node *a,
                                struct ast_node *b)
{
	return identical_ast_nodes(exact, AST_TRAIT_TYPE(a).def,
	                           AST_TRAIT_TYPE(b).def);
}

static int identical_type_primitive(int exact, struct ast_node *a,
                                    struct ast_node *b)
{
	return AST_PRIMITIVE_TYPE(a).type == AST_PRIMITIVE_TYPE(b).type;
}

static int identical_type_sign(int exact, struct ast_node *a,
                               struct ast_node *b)
{
	if (!identical_ast_nodes(exact, AST_SIGN_TYPE(a).params,
	                         AST_SIGN_TYPE(b).params))
		return 0;

	return identical_ast_nodes(exact, AST_SIGN_TYPE(a).ret, AST_SIGN_TYPE(
					   b).ret);
}

static int identical_type_struct(int exact, struct ast_node *a,
                                 struct ast_node *b)
{
	return identical_ast_nodes(exact, AST_STRUCT_TYPE(
					   a).def, AST_STRUCT_TYPE(b).def);
}

static int identical_type_enum(int exact, struct ast_node *a,
                               struct ast_node *b)
{
	return identical_ast_nodes(exact, AST_ENUM_TYPE(a).def, AST_ENUM_TYPE(
					   b).def);
}

static int identical_type(int exact, struct ast_node *a, struct ast_node *b)
{
	if (a->_type.kind != b->_type.kind)
		return 0;

	int ret = 0;
	switch (a->_type.kind) {
	case AST_TYPE_PRIMITIVE: ret = identical_type_primitive(exact, a, b);
		break;
	case AST_TYPE_ENUM: ret = identical_type_enum(exact, a, b); break;
	case AST_TYPE_TRAIT: ret = identical_type_trait(exact, a, b); break;
	case AST_TYPE_ID: ret = identical_type_id(exact, a, b); break;
	case AST_TYPE_ARR: ret = identical_type_arr(exact, a, b); break;
	case AST_TYPE_SIGN: ret = identical_type_sign(exact, a, b); break;
	case AST_TYPE_STRUCT: ret = identical_type_struct(exact, a, b); break;
	case AST_TYPE_POINTER: break;
	}

	return ret;
}

static int identical_block(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_block.body, b->_block.body);
}

static int identical_import(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	return strcmp(a->_import.file, b->_import.file) == 0;
}

static int identical_embed(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	return strcmp(a->_embed.file, b->_embed.file) == 0;
}

static int identical_enum(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_enum.id, b->_enum.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_enum.type, b->_enum.type))
		return 0;

	if (!identical_ast_nodes(exact, a->_enum.body, b->_enum.body))
		return 0;

	return 1;
}

static int identical_struct(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_struct.id, b->_struct.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_struct.generics,
	                         b->_struct.generics))
		return 0;

	if (!identical_ast_nodes(exact, a->_struct.body, b->_struct.body))
		return 0;

	return 1;
}

static int identical_val(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_val.id, b->_val.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_val.val, b->_val.val))
		return 0;

	return 1;
}

static int identical_switch(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_switch.cond, b->_switch.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_switch.cases, b->_switch.cases))
		return 0;

	return 1;
}

static int identical_case(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_case.cond, b->_switch.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_case.body, b->_case.body))
		return 0;

	return 1;
}

static int identical_const(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	if (a->_const.kind != b->_const.kind)
		return 0;

	/* these could potentially also be broken out to their own
	 * procedures, but I don't think it's that important */
	switch (a->_const.kind) {
	case AST_CONST_INTEGER:
		if (a->_const.integer != b->_const.integer)
			return 0;

		break;

	case AST_CONST_STRING:
		if (strcmp(a->_const.str, b->_const.str) != 0)
			return 0;

		break;
	}

	return 1;
}

static int identical_id(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	return strcmp(a->_id.id, b->_id.id) == 0;
}

static int identical_alias(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_alias.id, b->_alias.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_alias.type, b->_alias.type))
		return 0;

	return 1;
}

static int identical_trait(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_trait.id, b->_trait.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_trait.body, b->_trait.body))
		return 0;

	return 1;
}

static int identical_if(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_if.cond, b->_if.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_if.body, b->_if.body))
		return 0;

	if (!identical_ast_nodes(exact, a->_if.els, b->_if.els))
		return 0;

	return 1;
}

static int identical_fetch(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_fetch.id, b->_fetch.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_fetch.type, b->_fetch.type))
		return 0;

	return 1;
}

static int identical_type_expand(int exact, struct ast_node *a,
                                 struct ast_node *b)
{
	if (!identical_ast_nodes(exact, AST_TYPE_EXPAND(a).id,
	                         AST_TYPE_EXPAND(b).id))
		return 0;

	return identical_ast_nodes(exact, AST_TYPE_EXPAND(
					   a).args, AST_TYPE_EXPAND(b).args);
}

static int identical_arr_access(int exact, struct ast_node *a,
                                struct ast_node *b)
{
	if (!identical_ast_nodes(exact, AST_ARR_ACCESS(a).base,
	                         AST_ARR_ACCESS(b).base))
		return 0;

	if (!identical_ast_nodes(exact, AST_ARR_ACCESS(a).idx,
	                         AST_ARR_ACCESS(b).idx))
		return 0;

	return 1;
}

/* sort of unfortnate that we can't just do a direct memcmp... */
int identical_ast_nodes(int exact, struct ast_node *a, struct ast_node *b)
{
	/* both being NULL counts as identical */
	if (!a && !b)
		return 1;

	/* the same node must be the same */
	if (a == b)
		return 1;

	/* either one being null means not identical */
	if (!a)
		return 0;

	if (!b)
		return 0;

	if (a->node_type != b->node_type)
		return 0;

	if (exact && !identical_flags(a->flags, b->flags))
		return 0;

	if (exact && !identical_loc(a->loc, b->loc))
		return 0;

	if (exact && !identical_scope(a->scope, b->scope))
		return 0;

	int ret = 0;
	switch (a->node_type) {
	case AST_ARR_ACCESS: ret = identical_arr_access(exact, a, b); break;
	case AST_TYPE_EXPAND: ret = identical_type_expand(exact, a, b); break;
	case AST_FETCH: ret = identical_fetch(exact, a, b); break;
	case AST_ASSIGN: ret = identical_assign(exact, a, b); break;
	case AST_INIT: ret = identical_init(exact, a, b); break;
	case AST_SIZEOF: ret = identical_sizeof(exact, a, b); break;
	case AST_DOT: ret = identical_dot(exact, a, b); break;
	case AST_AS: ret = identical_as(exact, a, b); break;
	case AST_GOTO: ret = identical_goto(exact, a, b); break;
	case AST_LABEL: ret = identical_label(exact, a, b); break;
	case AST_BINOP: ret = identical_binop(exact, a, b); break;
	case AST_UNOP: ret = identical_unop(exact, a, b); break;
	case AST_CALL: ret = identical_call(exact, a, b); break;
	case AST_CAST: ret = identical_cast(exact, a, b); break;
	case AST_DEFER: ret = identical_defer(exact, a, b); break;
	case AST_MACRO_CONSTRUCT: ret = identical_macro_construct(exact, a, b);
		break;
	case AST_MACRO_EXPAND: ret = identical_macro_expand(exact, a, b); break;
	case AST_PROC: ret = identical_proc(exact, a, b); break;
	case AST_VAR: ret = identical_var(exact, a, b); break;
	case AST_FOR: ret = identical_for(exact, a, b); break;
	case AST_WHILE: ret = identical_while(exact, a, b); break;
	case AST_CTRL: ret = identical_ctrl(exact, a, b); break;
	case AST_RETURN: ret = identical_return(exact, a, b); break;
	case AST_TYPE: ret = identical_type(exact, a, b); break;
	case AST_BLOCK: ret = identical_block(exact, a, b); break;
	case AST_IMPORT: ret = identical_import(exact, a, b); break;
	case AST_EMBED: ret = identical_embed(exact, a, b); break;
	case AST_ENUM: ret = identical_enum(exact, a, b); break;
	case AST_STRUCT: ret = identical_struct(exact, a, b); break;
	case AST_VAL: ret = identical_val(exact, a, b); break;
	case AST_SWITCH: ret = identical_switch(exact, a, b); break;
	case AST_CASE: ret = identical_case(exact, a, b); break;
	case AST_CONST: ret = identical_const(exact, a, b); break;
	case AST_ID: ret = identical_id(exact, a, b); break;
	case AST_ALIAS: ret = identical_alias(exact, a, b); break;
	case AST_TRAIT: ret = identical_trait(exact, a, b); break;
	case AST_IF: ret = identical_if(exact, a, b); break;
	case AST_EMPTY: break;
	}

	if (ret == 0)
		return 0;

	/* Unsure if exact should be more of a flag or what,
	 * but at least right now the issue is that the analyzer in some cases
	 * has nodes that follow each other, i.e. next is populated, but we're
	 * only interested in the current node. Calls, mainly. */
	if (exact)
		return identical_ast_nodes(exact, a->next, b->next);

	return 1;
}

int ast_flags(struct ast_node *node, enum ast_flag flags)
{
	return node->flags & flags;
}

static int call_on_assign(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_assign.to, data);
	ret |= call(node->_assign.from, data);
	return ret;
}

static int call_on_init(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	return call(node->_init.body, data);
}

static int call_on_sizeof(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	return call(node->_sizeof.expr, data);
}

static int call_on_dot(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_dot.expr, data);
	ret |= call(node->_dot.id, data);
	return ret;
}

static int call_on_as(int (*call)(struct ast_node *,
                                  void *), struct ast_node *node, void *data)
{
	return call(node->_as.type, data);
}

static int call_on_cast(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_cast.expr, data);
	ret |= call(node->_cast.type, data);
	return ret;
}

static int call_on_defer(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	return call(node->_defer.expr, data);
}

static int call_on_var(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_var.id, data);
	ret |= call(node->_var.type, data);
	ret |= call(node->_var.init, data);
	return ret;
}

static int call_on_for(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_for.pre, data);
	ret |= call(node->_for.cond, data);
	ret |= call(node->_for.post, data);
	ret |= call(node->_for.body, data);
	return ret;
}

static int call_on_while(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_while.cond, data);
	ret |= call(node->_while.body, data);
	return ret;
}

static int call_on_return(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	return call(node->_return.expr, data);
}

static int call_on_alias(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_alias.id, data);
	ret |= call(node->_alias.type, data);
	return ret;
}

static int call_on_trait(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_trait.id, data);
	ret |= call(node->_trait.body, data);
	return ret;
}

static int call_on_if(int (*call)(struct ast_node *,
                                  void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_if.cond, data);
	ret |= call(node->_if.body, data);
	ret |= call(node->_if.els, data);
	return ret;
}

static int call_on_enum(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_enum.id, data);
	ret |= call(node->_enum.type, data);
	ret |= call(node->_enum.body, data);
	return ret;
}

static int call_on_struct(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_struct.id, data);
	ret |= call(node->_struct.generics, data);
	ret |= call(node->_struct.body, data);
	return ret;
}

static int call_on_val(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_val.id, data);
	ret |= call(node->_val.val, data);
	return ret;
}

static int call_on_switch(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_switch.cond, data);
	ret |= call(node->_switch.cases, data);
	return ret;
}

static int call_on_case(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_case.cond, data);
	ret |= call(node->_case.body, data);
	return ret;
}

static int call_on_type_trait(int (*call)(struct ast_node *,
                                          void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_TRAIT_TYPE(node).def, data);
	return ret;
}

static int call_on_type_id(int (*call)(struct ast_node *,
                                       void *), struct ast_node *node, void *data)
{
	return call(AST_ID_TYPE(node).id, data);
}

static int call_on_type_arr(int (*call)(struct ast_node *,
                                        void *), struct ast_node *node, void *data)
{
	return call(AST_ARR_TYPE(node).size, data);
}

static int call_on_type_struct(int (*call)(struct ast_node *,
                                           void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_STRUCT_TYPE(node).def, data);
	return ret;
}

static int call_on_type_sign(int (*call)(struct ast_node *,
                                         void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_SIGN_TYPE(node).params, data);
	ret |= call(AST_SIGN_TYPE(node).ret, data);
	return ret;
}

static int call_on_type_enum(int (*call)(struct ast_node *,
                                         void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_ENUM_TYPE(node).def, data);
	return ret;
}

static int call_on_type(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	switch (node->_type.kind) {
	case AST_TYPE_ENUM: ret = call_on_type_enum(call, node, data); break;
	case AST_TYPE_TRAIT: ret = call_on_type_trait(call, node, data); break;
	case AST_TYPE_ID: ret = call_on_type_id(call, node, data); break;
	case AST_TYPE_ARR: ret = call_on_type_arr(call, node, data); break;
	case AST_TYPE_STRUCT: ret = call_on_type_struct(call, node, data);
		break;
	case AST_TYPE_SIGN: ret = call_on_type_sign(call, node, data); break;
	case AST_TYPE_POINTER: break;
	case AST_TYPE_PRIMITIVE: break;
	}

	return ret;
}

static int call_on_goto(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	return call(node->_goto.label, data);
}

static int call_on_label(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	return call(node->_label.id, data);
}

static int call_on_binop(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->binop.left, data);
	ret |= call(node->binop.right, data);
	return ret;
}

static int call_on_unop(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	return call(node->_unop.expr, data);
}

static int call_on_call(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_CALL(node).expr, data);
	ret |= call(AST_CALL(node).args, data);
	return ret;
}

static int call_on_macro_construct(int (*call)(struct ast_node *,
                                               void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_MACRO_CONSTRUCT(node).id, data);
	ret |= call(AST_MACRO_CONSTRUCT(node).params, data);
	ret |= call(AST_MACRO_CONSTRUCT(node).body, data);
	return ret;
}

static int call_on_proc(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_proc.id, data);
	ret |= call(node->_proc.sign, data);
	ret |= call(node->_proc.body, data);
	return ret;
}

static int call_on_block(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	return call(node->_block.body, data);
}

static int call_on_fetch(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_fetch.id, data);
	ret |= call(node->_fetch.type, data);
	return ret;
}

static int call_on_macro_expand(int (*call)(struct ast_node *,
                                            void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_macro_expand.id, data);
	ret |= call(node->_macro_expand.args, data);
	return ret;
}

static int call_on_type_expand(int (*call)(struct ast_node *,
                                           void *), struct ast_node *type_expand, void *data)
{
	int ret = 0;
	ret |= call(AST_TYPE_EXPAND(type_expand).id, data);
	ret |= call(AST_TYPE_EXPAND(type_expand).args, data);
	return ret;
}

/* I guess this works, but it's not exactly optimal as the caller sort of has to
 * know when to continue to call on, and when it would cause an infinite loop.
 * I.e. a call on an ID that is forwarded results in an infinite loop.
 *
 * Maybe add in something like ast_continue_call_on() that can check for the
 * user if there's any point in continuing?
 */
int ast_call_on(int (*call)(struct ast_node *,
                            void *), struct ast_node *node, void *data)
{
	int ret = 0;
	if (!node)
		return ret;

	switch (node->node_type) {
	case AST_ARR_ACCESS:
	case AST_TYPE_EXPAND: ret = call_on_type_expand(call, node, data);
		break;
	case AST_FETCH: ret = call_on_fetch(call, node, data); break;
	case AST_ASSIGN: ret = call_on_assign(call, node, data); break;
	case AST_INIT: ret = call_on_init(call, node, data); break;
	case AST_SIZEOF: ret = call_on_sizeof(call, node, data); break;
	case AST_DOT: ret = call_on_dot(call, node, data); break;
	case AST_AS: ret = call_on_as(call, node, data); break;
	case AST_CAST: ret = call_on_cast(call, node, data); break;
	case AST_DEFER: ret = call_on_defer(call, node, data); break;
	case AST_VAR: ret = call_on_var(call, node, data); break;
	case AST_FOR: ret = call_on_for(call, node, data); break;
	case AST_WHILE: ret = call_on_while(call, node, data); break;
	case AST_RETURN: ret = call_on_return(call, node, data); break;
	case AST_ALIAS: ret = call_on_alias(call, node, data); break;
	case AST_TRAIT: ret = call_on_trait(call, node, data); break;
	case AST_IF: ret = call_on_if(call, node, data); break;
	case AST_ENUM: ret = call_on_enum(call, node, data); break;
	case AST_STRUCT: ret = call_on_struct(call, node, data); break;
	case AST_VAL: ret = call_on_val(call, node, data); break;
	case AST_SWITCH: ret = call_on_switch(call, node, data); break;
	case AST_CASE: ret = call_on_case(call, node, data); break;
	case AST_TYPE: ret = call_on_type(call, node, data); break;
	case AST_GOTO: ret = call_on_goto(call, node, data); break;
	case AST_LABEL: ret = call_on_label(call, node, data); break;
	case AST_BINOP: ret = call_on_binop(call, node, data); break;
	case AST_UNOP: ret = call_on_unop(call, node, data); break;
	case AST_CALL: ret = call_on_call(call, node, data); break;
	case AST_MACRO_CONSTRUCT: ret =
		call_on_macro_construct(call, node, data); break;
	case AST_MACRO_EXPAND: ret = call_on_macro_expand(call, node, data);
		break;
	case AST_PROC: ret = call_on_proc(call, node, data); break;
	case AST_BLOCK: ret = call_on_block(call, node, data); break;
	case AST_EMBED: break;
	case AST_CTRL: break;
	case AST_IMPORT: break;
	case AST_CONST: break;
	case AST_ID: break;
	case AST_EMPTY: break;
	}

	ret |= call(node->next, data);
	return ret;
}

size_t ast_list_len(struct ast_node *node)
{
	size_t count = 0;
	while (node) {
		count++;
		node = node->next;
	}

	return count;
}

struct ast_node *ast_last_node(struct ast_node *list)
{
	if (!list)
		return NULL;

	while (list->next)
		list = list->next;

	return list;
}

struct ast_node *ast_block_last(struct ast_node *block)
{
	struct ast_node *b = ast_last_node(block);
	if (b && b->node_type == AST_BLOCK)
		return ast_block_last(b->_block.body);

	return b;
}

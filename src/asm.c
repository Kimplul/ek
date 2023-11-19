#include <ek/ops.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* I guess using the zero register might be okay in some scenarios, but for now
 * I'll just keep it an illegal register */
#define ASSERT_REG(x) {assert(x->kind == LOC_REG); assert(x->reg > 0 && x->reg < 81);}
#define ASSERT_MEM(x) {assert(x->kind == LOC_MEM); assert(x->reg > 0 && x->reg < 81);}

static int print_comment(struct op *op, FILE *f)
{
	fprintf(f, "/* %s */\n", op->string);
	return 0;
}

static int print_label(struct op *op, FILE *f)
{
	fprintf(f, "%s:\n", op->string);
	return 0;
}

static int print_li(struct op *op, FILE *f)
{
	struct loc *o = &op->outputs;
	assert(o->next == NULL);
	/* unsure if this will always hold, but for now */
	ASSERT_REG(o);

	fprintf(f, "li x%zd, %lld\n", o->reg, op->constant);
	return 0;
}

static int print_mv(struct op *op, FILE *f)
{
	struct loc *i = &op->inputs;
	struct loc *o = &op->outputs;
	assert(i->next == NULL);
	assert(o->next == NULL);
	ASSERT_REG(i);
	ASSERT_REG(o);

	fprintf(f, "mv x%zd, x%zd\n", o->reg, i->reg);
	return 0;
}

static int print_stt(struct op *op, FILE *f)
{
	struct loc *i = &op->inputs;
	struct loc *o = &op->outputs;
	assert(i->next == NULL);
	assert(o->next == NULL);
	ASSERT_REG(i);
	ASSERT_MEM(o);

	fprintf(f, "st t, x%zd, %lld(x%zd)\n", i->reg, o->off, o->reg);
	return 0;
}

static int print_op(struct op *op, FILE *f)
{
	int ret = 0;
	switch (op->opcode) {
	case OP_COMMENT: ret = print_comment(op, f); break;
	case OP_LABEL: ret = print_label(op, f); break;
	case OP_LI: ret = print_li(op, f); break;
	case OP_MV: ret = print_mv(op, f); break;
	case OP_STT: ret = print_stt(op, f); break;
	default: abort();
	}

	return ret;
}

int print_asm(struct ops *ops, const char *output)
{
	FILE *f = fopen(output, "w");

	/* main should probably be mangled here as well */
	fprintf(f, "jal x0, main\n");
	int ret = 0;
	struct op *op = ops->base;
	while (op) {
		if ((ret = print_op(op, f)))
			break;

		op = op->next;
	}

	/* tell simulator to turn off (very much temp) */
	fprintf(f, "li x1, 3\n");
	fprintf(f, "csrrw mpower, x0, x1\n");

	fclose(f);
	return ret;
}

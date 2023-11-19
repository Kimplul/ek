#ifndef EK_OPS_H
#define EK_OPS_H

#include <ek/ast.h>

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
	OP_MV, /* kind of meta op, will be realized as either load/store or register move */
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

struct ops *create_ops();
void destroy_ops(struct ops *ops);
int lower_ops(struct scope *root, struct ops *ops);
int alloc_regs(struct ops *ops);
int print_asm(struct ops *ops, const char *output);

#endif /* EK_OPS_H */

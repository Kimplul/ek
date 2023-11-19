#ifndef EK_OPS_H
#define EK_OPS_H

#include <ek/ast.h>

struct ops;

struct ops *create_ops();
void destroy_ops(struct ops *ops);
int lower_ops(struct scope *root, struct ops *ops);
int analyze_lifetime(struct ops *ops);
int print_asm(struct ops *ops, const char *output);

#endif /* EK_OPS_H */

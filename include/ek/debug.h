/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_DEBUG_H
#define EK_DEBUG_H

#include <stdio.h>

#include <ek/ast.h>

#if DEBUG
#define debug(x, ...) \
	do {fprintf(stderr, "debug: " x "\n",##__VA_ARGS__);} while(0)
#else
#define debug(x, ...)
#endif

#define error(x, ...) \
	do {fprintf(stderr, "error: " x "\n",##__VA_ARGS__);} while(0)

#define warn(x, ...) \
	do {fprintf(stderr, "warn: " x "\n",##__VA_ARGS__);} while(0)

#define info(x, ...) \
	do {fprintf(stderr, "info: " x "\n",##__VA_ARGS__);} while(0)


struct file_ctx {
	const char *fname;
	const char *fbuf;
};

char *type_str(struct ast_node *type);
char *call_str(struct ast_node *call);
void semantic_info(struct file_ctx ctx, struct ast_node *node, const char *fmt,
                   ...);
void semantic_warn(struct file_ctx ctx, struct ast_node *node, const char *fmt,
                   ...);
void semantic_error(struct file_ctx ctx, struct ast_node *node, const char *fmt,
                    ...);
void internal_error(const char *fmt, ...);

enum issue_level {
	SRC_INFO,
	SRC_WARN,
	SRC_ERROR
};

struct src_issue {
	enum issue_level level;
	struct src_loc loc;
	struct file_ctx fctx;
	size_t offset;
};

void src_issue(struct src_issue issue, const char *err_msg, ...);
#endif /* EK_DEBUG_H */

/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_DEBUG_H
#define EK_DEBUG_H

/**
 * @file debug.h
 *
 * Debugging and general information printing helpers.
 */

#include <stdio.h>

#include <ek/ast.h>

#if DEBUG
/**
 * Print debugging message. Only active if \c DEBUG is defined,
 *
 * @param x Format string. Follows standard printf() formatting.
 */
#define debug(x, ...) \
	do {fprintf(stderr, "debug: " x "\n",##__VA_ARGS__);} while(0)
#else
#define debug(x, ...)
#endif

/**
 * Print error message.
 *
 * @param x Format string. Follows standard printf() formatting.
 */
#define error(x, ...) \
	do {fprintf(stderr, "error: " x "\n",##__VA_ARGS__);} while(0)

/**
 * Print warning message.
 *
 * @param x Format string. Follows standard printf() formatting.
 */
#define warn(x, ...) \
	do {fprintf(stderr, "warn: " x "\n",##__VA_ARGS__);} while(0)

/**
 * Print info message.
 *
 * @param x Format string. Follows standard printf() formatting.
 */
#define info(x, ...) \
	do {fprintf(stderr, "info: " x "\n",##__VA_ARGS__);} while(0)


/** Keeps track of file name and file buffer. */
struct file_ctx {
	/** File name. */
	const char *fname;
	/** File buffer. */
	const char *fbuf;
};

/**
 * Generate string representation of type.
 *
 * @param type Type to generate string representation of.
 * @return \p type as string.
 */
char *type_str(struct ast_node *type);

/**
 * Generate string representation of call.
 *
 * @param call Call to generate string representation of.
 * @return \p call as string.
 */
char *call_str(struct ast_node *call);

/**
 * Print info that relates to a specific AST node.
 * Recommended for situations where it may be useful to clarify some
 * previous error or warning.
 *
 * @param ctx File context \p node was generated from.
 * @param node AST node to print message with.
 * @param fmt Format string. Follows standard printf() formatting.
 */
void semantic_info(struct file_ctx ctx, struct ast_node *node, const char *fmt,
                   ...);

/**
 * Print warning that relates to a specific AST node.
 * Recommended for situations where the user wrote some shady code
 * and it might be unclear what was meant.
 *
 * The language itself tries to avoid such situations, and as such warnings
 * should probably be avoided in favor of errors. Still, I can imagine that
 * there are situations where warnings can be useful, so it's provided.
 *
 * @param ctx File context \p node was generated from.
 * @param node AST node to print message with.
 * @param fmt Format string. Follows standard printf() formatting.
 */
void semantic_warn(struct file_ctx ctx, struct ast_node *node, const char *fmt,
                   ...);

/**
 * Print warning that relates to a specific AST node.
 * Recommended for situations where the user messed up.
 *
 * @param ctx File context \p node was generated from.
 * @param node AST node to print message with.
 * @param fmt Format string. Follows standard printf() formatting.
 */
void semantic_error(struct file_ctx ctx, struct ast_node *node, const char *fmt,
                    ...);

/**
 * Print internal error.
 * Recommended for situations where the developer (probably me) messed up.
 *
 * @param fmt Format string. Follows standard printf() formatting.
 */
void internal_error(const char *fmt, ...);
void internal_warn(const char *fmt, ...);

/** Issue categorization. */
enum issue_level {
	/** Information. */
	SRC_INFO,
	/** Warning. */
	SRC_WARN,
	/** Error. */
	SRC_ERROR
};

/** Context for issue in user code. */
struct src_issue {
	/** How bad the issue is. */
	enum issue_level level;
	/** Where the issue happened relative to file buffer. */
	struct src_loc loc;
	/** File context issue happened in. */
	struct file_ctx fctx;
};

/**
 * Print a source issue.
 *
 * @param issue Context for issue.
 * @param err_msg Format string. Follows standard printf() formatting.
 */
void src_issue(struct src_issue issue, const char *err_msg, ...);

#endif /* EK_DEBUG_H */

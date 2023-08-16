/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef PARSER_H
#define PARSER_H

/**
 * @file parser.h
 *
 * Glue file to get lexer and parser to play nice.
 */

#include <stddef.h>
#include <stdbool.h>
#include <ek/ast.h>

/** Stuff the parser needs to do its job. */
struct parser {
	/** Whether parsing failed or succeeded. */
	bool failed;
	/** Lexer. Parser owns the lexer and is responsible for initializing
	 * and destroyint the lexer.
	 */
	void *lexer;

	/** File content in memory. */
	const char *buf;
	/** Filename. */
	const char *fname;
	/** How deeply we've nested comments. */
	size_t comment_nesting;
	/** Raw AST. */
	struct ast_node *tree;
};

/**
 * Create new parser.
 *
 * @return Created parser.
 */
struct parser *create_parser();

/**
 * Destroy parser.
 *
 * @param p Parser to destroy.
 */
void destroy_parser(struct parser *p);

/**
 * Run parser on buffer \p buf with name \p fname.
 *
 * @param p Parser to run.
 * @param fname Name of file \p buf was read from.
 * @param buf Contents of \p fname.
 */
void parse(struct parser *p, const char *fname, const char *buf);

#endif /* PARSER_H */

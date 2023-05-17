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

/** Modifies the signature of yylex to fit our parser better. */
#define YY_DECL int yylex(YYSTYPE *yylval, YYLTYPE *yylloc, \
	                  yyscan_t yyscanner, struct parser *parser)

#include <../gen/gen_parser.h>
#ifndef FROM_LEXER
#include <../gen/gen_lexer.h>
#endif

/**
 * Declare yylex.
 *
 * @param yylval Bison current value.
 * @param yylloc Bison location info.
 * @param yyscanner Flex scanner.
 * @param parser Current parser state.
 * @return \c 0 when succesful, \c 1 otherwise.
 * More info on yylex() can be found in the flex manual.
 */
YY_DECL;

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

/**
 * Gobble tokens until we reach the next interesting feature.
 * Interesting features are generally new statements.
 * Mainly intended for trying to get to a sensible
 * location to continue parser after an error has occured.
 *
 * @param yylval Current parser value.
 * @param yylloc Parser location info.
 * @param scanner Lex scanner.
 * @param parser Current parser.
 * @return \c 0 on success, non-zero otherwise.
 */
int next_interesting_feature(YYSTYPE *yylval, YYLTYPE *yylloc,
                             void *scanner, struct parser *parser);

/**
 * Convert bison location info to our own source location info.
 *
 * @param yylloc Bison location info.
 * @return Internal location info.
 */
struct src_loc to_src_loc(YYLTYPE *yylloc);

/**
 * Print parsing error.
 * Automatically called by bison.
 *
 * @param yylloc Location of error.
 * @param lexer Lexer.
 * @param parser Parser state.
 * @param msg Message to print.
 */
void yyerror(YYLTYPE *yylloc, void *lexer, struct parser *parser,
             const char *msg);

/**
 * Try to convert escape code to its actual value.
 * I.e. '\n' -> 0x0a.
 *
 * @param c Escape character without backslash.
 * @return Corresponding value.
 */
long long match_escape(char c);

/**
 * Similar to strdup() but skips quotation marks that would
 * otherwise be included.
 * I.e. "something" -> something.
 *
 * @param s String to clone, with quotation marks surrounding it.
 * @return Identical string but without quotation marks around it.
 */
const char *clone_string(const char *s);

#endif /* PARSER_H */

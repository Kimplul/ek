/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdbool.h>
#include <ek/ast.h>

struct parser {
	bool failed;
	void *lexer;
	size_t buf_offset;
	const char *buf;
	const char *fname;
	size_t comment_nesting;
	struct ast_node *tree;
};

#define YY_DECL int yylex(YYSTYPE *yylval, YYLTYPE *yylloc, \
	                  yyscan_t yyscanner, struct parser *parser)

#include <../gen/gen_parser.h>
#ifndef FROM_LEXER
#include <../gen/gen_lexer.h>
#endif

YY_DECL;

struct parser *create_parser();
void destroy_parser(struct parser *p);
void parse(struct parser *p, const char *fname, const char *buf);
int next_interesting_feature(YYSTYPE *yylval, YYLTYPE *yylloc,
                             void *scanner, struct parser *parser);

struct src_loc to_src_loc(YYLTYPE *yylloc);

void yyerror(YYLTYPE *yylloc, void *lexer, struct parser *parser,
             const char *msg);

long long match_escape(char c);
const char *clone_string(const char *s);

#endif /* PARSER_H */

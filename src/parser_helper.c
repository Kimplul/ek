/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#include <stdarg.h>

#include <ek/parser.h>
#include <ek/debug.h>

struct parser *create_parser()
{
	return calloc(1, sizeof(struct parser));
}

void destroy_parser(struct parser *p)
{
	yylex_destroy(p->lexer);
	free(p);
}

void parse(struct parser *p, const char *fname, const char *buf)
{
	p->fname = fname;
	p->buf = buf;

	p->buf_offset = 0;
	p->comment_nesting = 0;

	p->failed = false;

	yylex_init(&p->lexer);
	yy_scan_string(buf, p->lexer);
	yyparse(p->lexer, p);
}

/* I'm not convinced this is foolproof quite yet, more testing would be nice. */
int next_interesting_feature(YYSTYPE *yylval, YYLTYPE *yylloc, void *scanner,
                             struct parser *parser)
{
	size_t depth = 0;
	while (1) {
		int ret = yylex(yylval, yylloc, scanner, parser);
		if (ret == LBRACE) {
			depth++;
			continue;
		}

		if (ret == RBRACE && depth > 0)
			depth--;

		if (ret == RBRACE && depth == 0)
			return 0;

		if (ret == SEMICOLON && depth == 0)
			return 0;

		/* return fatal error and parser should abort */
		if (ret == YYEOF)
			/* some error for unmatched braces would be cool I think */
			return 1;
	}
}


struct src_loc to_src_loc(YYLTYPE *yylloc)
{
	struct src_loc loc;
	loc.first_line = yylloc->first_line;
	loc.last_line = yylloc->last_line;
	loc.first_col = yylloc->first_column;
	loc.last_col = yylloc->last_column;
	return loc;
}

void yyerror(YYLTYPE *yylloc, void *lexer, struct parser *parser,
             const char *msg)
{
	(void)lexer;

	struct src_issue issue;
	issue.level = SRC_ERROR;
	issue.loc = to_src_loc(yylloc);
	issue.fctx.fbuf = parser->buf;
	issue.fctx.fname = parser->fname;
	issue.offset = parser->buf_offset;
	src_issue(issue, msg);
}

long long match_escape(char c)
{
	switch (c) {
	case '\'': return '\'';
	case '\\': return '\\';
	case 'a': return '\a';
	case 'b': return '\b';
	case 'f': return '\f';
	case 'n': return '\n';
	case 'r': return '\r';
	case 't': return '\t';
	case 'v': return '\v';
	}

	return c;
}

const char *clone_string(const char *str)
{
	const size_t len = strlen(str) + 1;
	char *buf = malloc(len);
	if (!buf) {
		/* should probably try to handle the error in some way... */
		internal_error("failed allocating buffer for string clone");
		return NULL;
	}

	/* skip quotation marks */
	size_t j = 0;
	for (size_t i = 1; i < len - 2; ++i) {
		char c = str[i];

		if (c == '\\')
			c = match_escape(str[++i]);

		buf[j++] = c;
	}

	buf[j] = 0;
	return buf;

}

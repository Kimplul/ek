/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

%option reentrant noyywrap nounput noinput nodefault
%{
#define FROM_LEXER
#include <ek/parser.h>
#include <ek/debug.h>

static void update_yylloc(struct parser *parser, YYLTYPE *lloc, const char *text)
{
	lloc->first_line = lloc->last_line;
	lloc->first_column = lloc->last_column;

	for (size_t i = 0; text[i] != 0; ++i) {
		parser->buf_offset++;
		if (text[i] == '\n') {
			lloc->last_line++;
			/* flex uses 1 based indexing */
			lloc->last_column = 1;
		} else {
			lloc->last_column++;
		}
	}
}

#define YY_USER_ACTION update_yylloc(parser, yylloc, yytext);
%}

HEX		0[xX][0-9a-fA-F]+
DEC		-?[0-9]+
OCT		0[0-8]+
BIN		0b[0-1]+

INT		{HEX}|{DEC}|{OCT}|{BIN}

HEXF		[+-]?0[xX][0-9a-fA-F]+([pP][+-]?[0-9]+)
DECF		[+-]?[0-9]+[.]([eE]?[+-]?[0-9]+)?[fF]?
FLOAT		{HEXF}|{DECF}|inf|nan

ID		[_a-zA-Z][_a-zA-Z0-9]*

STRING		\"(\\.|[^"\\])*\"

%x SC_COMMENT

%%
"//".* {/* skip line comments */}

"/*"	{BEGIN(SC_COMMENT);}
<SC_COMMENT>{
	"/*"	{++parser->comment_nesting;}
	"*"+"/"	{
		if (parser->comment_nesting)
			--parser->comment_nesting;
		else
			BEGIN(INITIAL);
	}

	"*"+ {}
	[^/*\n]+ {}
	    [/] {}
	    \n {}
}

"::"		{return SCOPE;}
"("		{return LPAREN;}
")"		{return RPAREN;}
"{"		{return LBRACE;}
"}"		{return RBRACE;}
"["		{return LBRACKET;}
"]"		{return RBRACKET;}
"."		{return DOT;}
","		{return COMMA;}
";"		{return SEMICOLON;}
":"		{return COLON;}
"!"		{return BANG;}
"##"		{return PASTE;}
"@"		{return AT;}

"+"		{return PLUS;}
"-"		{return MINUS;}
"*"		{return STAR;}
"/"		{return DIV;}
"%"		{return REM;}
"^"		{return XOR;}
"^^"		{return POW;}

'[^'\\]'	{
	/* regular character constant, 'a' */
	yylval->integer = yytext[1];
	return INT;
}

'\\x[0-9a-fA-F]+' {
	/* hex character constant, '\xef' */
	/* handling is slightly different from C, here it's more or less just
	 * another way to specify a hex integer */
	yylval->integer = strtoll(yytext + 3, NULL, 16);
	return INT;
}

'\\[0-8]+' {
	/* octal character constant, '\033' */
	yylval->integer = strtoll(yytext + 2, NULL, 8);
	return INT;
}

'\\b[01]+' {
	/* binary character constant, '\b101' */
	yylval->integer = strtoll(yytext + 3, NULL, 2);
	return INT;
}

'\\.' {
	/* escaped character constant */
	yylval->integer = match_escape(yytext[2]);
	return INT;
}

"'"		{return SQUOTE;}

"&"		{return AND;}
"&&"		{return LAND;}
"|"		{return OR;}
"||"		{return LOR;}

"~"		{return TILDE;}
"="		{return TO;}
"<"		{return LT;}
">"		{return GT;}
"<="		{return LE;}
">="		{return GE;}
"!="		{return NE;}
"=="		{return EQ;}

"=>"		{return FATARROW;}

"<<"		{return LSHIFT;}
">>"		{return RSHIFT;}

"+="		{return PLUSSELF;}
"-="		{return MINUSSELF;}
"/="		{return DIVSELF;}
"%="		{return REMSELF;}
"^="		{return XORSELF;}
"^^="		{return POWSELF;}
"&="		{return ORSELF;}
"|="		{return ORSELF;}
"<<="		{return LSHIFTSELF;}
">>="		{return RSHIFTSELF;}
"..."		{return ELLIPSIS;}

"as"		{return AS;}
"pub"		{return PUB;}
"defer"		{return DEFER;}
"union"		{return UNION;}
"struct"	{return STRUCT;}
"typedef"	{return TYPEDEF;}
"import"	{return IMPORT;}
"typeof"	{return TYPEOF;}
"sizeof"	{return SIZEOF;}
"embed"		{return EMBED;}
"if"		{return IF;}
"goto"		{return GOTO;}
"else"		{return ELSE;}
"switch"	{return SWITCH;}
"case"		{return CASE;}
"for"		{return FOR;}
"while"		{return WHILE;}
"do"		{return DO;}
"mut"		{return MUT;}
"const"		{return CONST;}
"return"	{return RETURN;}
"extern"	{return EXTERN;}
"enum"		{return ENUM;}
"define"	{return DEFINE;}
"break"		{return BREAK;}
"continue"	{return CONTINUE;}

{STRING} {
	/* seems risky, I know, but letting the parser choose when to allocate a
	 * new string seems to help with syntax error cleanup */
	yylval->str = yytext;
	return STRING;
}

{INT} {
	yylval->integer = strtoll(yytext, 0, 0);
	return INT;
}

{FLOAT}	{
	yylval->dbl = strtod(yytext, 0);
	return FLOAT;
}

{ID} {
	yylval->str = yytext;
	return ID;
}


[[:space:]]+	{/* skip whitespace */}

. {
	struct src_issue issue;
	issue.level = SRC_ERROR;
	issue.loc = to_src_loc(yylloc);
	issue.fctx.fbuf = parser->buf;
	issue.fctx.fname = parser->fname;
	issue.offset = parser->buf_offset;
	src_issue(issue, "Unexpected token: %s", yytext);
	parser->failed = true;
}
%%

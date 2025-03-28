/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

%{

/* TODO: clean up this mess and I guess fix location tracking, it works for the
 * parser but each ast node should also get some location data
 * I'm trying something over in ast.c, but I'm not sure about it
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <ek/parser.h>

%}

%locations

%define parse.trace
%define parse.error verbose
%define api.pure full
%define lr.type ielr

%lex-param {void *scanner} {struct parser *parser}
%parse-param {void *scanner} {struct parser* parser}

%union {
	struct ast *node;
	struct type *type;
	long long integer;
	char *str;
};

%token <integer> INT
%token <integer> CHAR
%token <integer> BOOL
%token <dbl> FLOAT
%token <str> STRING
%token <str> ID
%token <str> APPLY

%token QUESTION "?"
%token SQUOTE "'"
%token TO "="
%token ELLIPSIS "..."
%token SEMICOLON ";"
%token COLON ":"
%token BANG "!"
%token SIZEOF "sizeof"
%token STAR "*"
%token DIV "/"
%token REM "%"
%token MINUS "-"
%token PLUS "+"
%token XOR "^"
%token AND "&"
%token TILDE "~"
%token LT "<"
%token GT ">"
%token LE "<="
%token GE ">="
%token NE "!="
%token EQ "=="
%token LSHIFT "<<"
%token RSHIFT ">>"
%token PLUSSELF "+="
%token MINUSSELF "-="
%token STARSELF "*="
%token DIVSELF "/="
%token REMSELF "%="
%token LSHIFTSELF "<<="
%token RSHIFTSELF ">>="
%token COMMA ","
%token PUB "pub"
%token UNION "union"
%token TYPEDEF "typedef"
%token IMPORT "import"
%token DEFER "defer"
%token GOTO "goto"
%token EMBED "embed"
%token IF "if"
%token ELSE "else"
%token BREAK "break"
%token CONTINUE "continue"
%token DEFAULT "default"
%token SWITCH "switch"
%token CASE "case"
%token FOR "for"
%token WHILE "while"
%token DO "do"
%token MUT "mut"
%token RETURN "return"
%token CONST "const"
%token LET "let"
%token EXTERN "extern"
%token ENUM "enum"
%token DEFINE "define"
%token LPAREN "("
%token RPAREN ")"
%token LBRACE "{"
%token RBRACE "}"
%token LBRACKET "["
%token RBRACKET "]"
%token AS "as"
%token DOT "."
%token SCOPE "::"
%token FATARROW "=>"

%right "[" "]"
/* precedence */
%left ","
%right "=" "+=" "-=" "*=" "/=" "%=" "<<=" ">>="
%left "==" "!="
%left "<" ">" "<=" ">="
%left "^"
%left "&"
%left "<<" ">>"
%left "+" "-"
%left "*" "/" "%"
%left "as" "sizeof"
%right "'" "!" "~"
%left "." "=>" "(" ")"
%left "::"

/* why doesn't bison allow <*> for %nterm? would be so much easier */
%nterm <node> import binop unop decls opt_decls expr
%nterm <node> while do_while statement statements body references macro
%nterm <node> exprs if for case cases switch const
%nterm <node> var_decl var
%nterm <node> var_init proc
%nterm <node> alias trait enum_val enums enum top unit id
%nterm <node> embed param_decl members
%nterm <node> top_if const_if const_for goto assign
%nterm <node> construct construct_args construct_arg
%nterm <node> statelet

%nterm <type> types type opt_type

%nterm <node> struct struct_cont expr_if

/* constant operations */
%nterm <node> const_expr const_unop const_binop

%nterm <node> macro_expand type_expand

%nterm <node> type_params opt_type_params type_param opt_for_inits for_inits for_init

/* array stuff */
%nterm <node> arr arr_inits arr_init

/* optional stuff */
%nterm <node> opt_exprs proc_decl member opt_members
%nterm <type> opt_types opt_sign_decls sign_decls sign_decl sign_var_decl
%nterm <node> opt_construct_args
%nterm <node> opt_behaviours behaviours behaviour
%nterm <node> opt_deferred_statement

/* reverse lists */
%nterm <type> rev_sign_decls;
%nterm <node> rev_construct_args;
%nterm <node> rev_statements;
%nterm <node> rev_references;
%nterm <node> rev_arr_inits;
%nterm <node> rev_for_inits;
%nterm <node> rev_cases;
%nterm <node> rev_exprs;
%nterm <node> rev_decls;

%{

/** Modifies the signature of yylex to fit our parser better. */
#define YY_DECL int yylex(YYSTYPE *yylval, YYLTYPE *yylloc, \
	                  void *yyscanner, struct parser *parser)

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
static int next_interesting_feature(YYSTYPE *yylval, YYLTYPE *yylloc,
                             void *scanner, struct parser *parser);

/**
 * Convert bison location info to our own source location info.
 *
 * @param yylloc Bison location info.
 * @return Internal location info.
 */
static struct src_loc src_loc(YYLTYPE yylloc);

/**
 * Print parsing error.
 * Automatically called by bison.
 *
 * @param yylloc Location of error.
 * @param lexer Lexer.
 * @param parser Parser state.
 * @param msg Message to print.
 */
static void yyerror(YYLTYPE *yylloc, void *lexer,
		struct parser *parser, const char *msg);

/**
 * Try to convert escape code to its actual value.
 * I.e. '\n' -> 0x0a.
 *
 * @param c Escape character without backslash.
 * @return Corresponding value.
 */
static char match_escape(char c);

/**
 * Similar to strdup() but skips quotation marks that would
 * otherwise be included.
 * I.e. "something" -> something.
 *
 * @param s String to clone, with quotation marks surrounding it.
 * @return Identical string but without quotation marks around it.
 */
static char *strip(const char *s);

%}

%start input;
%%
id
	: ID {$$ = gen_id($1, src_loc(@$));}

var
	: var_init

embed
	: "embed" STRING { $$ = gen_embed(strip($2), src_loc(@$));  }

import
	: "import" STRING { $$ = gen_import(strip($2), src_loc(@$));  }

assign
	: expr "=" expr { $$ = gen_assign($1, $3, src_loc(@$)); }

binop
	: expr "+" expr { $$ = gen_binop(AST_ADD, $1, $3, src_loc(@$));  }
	| expr "-" expr { $$ = gen_binop(AST_SUB, $1, $3, src_loc(@$));  }
	| expr "*" expr { $$ = gen_binop(AST_MUL, $1, $3, src_loc(@$));  }
	| expr "/" expr { $$ = gen_binop(AST_DIV, $1, $3, src_loc(@$));  }
	| expr "%" expr { $$ = gen_binop(AST_REM, $1, $3, src_loc(@$));  }
	| expr "<<" expr { $$ = gen_binop(AST_LSHIFT, $1, $3, src_loc(@$));  }
	| expr ">>" expr { $$ = gen_binop(AST_RSHIFT, $1, $3, src_loc(@$));  }
	| expr "+=" expr { $$ = gen_binop(AST_ASSIGN_ADD, $1, $3, src_loc(@$));  }
	| expr "-=" expr { $$ = gen_binop(AST_ASSIGN_SUB, $1, $3, src_loc(@$));  }
	| expr "*=" expr { $$ = gen_binop(AST_ASSIGN_MUL, $1, $3, src_loc(@$));  }
	| expr "/=" expr { $$ = gen_binop(AST_ASSIGN_DIV, $1, $3, src_loc(@$));  }
	| expr "%=" expr { $$ = gen_binop(AST_ASSIGN_REM, $1, $3, src_loc(@$));  }
	| expr "<<=" expr {
		$$ = gen_binop(AST_ASSIGN_LSHIFT, $1, $3, src_loc(@$));
	}
	| expr ">>=" expr {
		$$ = gen_binop(AST_ASSIGN_RSHIFT, $1, $3, src_loc(@$));
	}
	| expr "<" expr { $$ = gen_comparison(AST_LT, $1, $3, src_loc(@$));  }
	| expr ">" expr { $$ = gen_comparison(AST_GT, $1, $3, src_loc(@$));  }
	| expr "<=" expr { $$ = gen_comparison(AST_LE, $1, $3, src_loc(@$));  }
	| expr ">=" expr { $$ = gen_comparison(AST_GE, $1, $3, src_loc(@$));  }
	| expr "!=" expr { $$ = gen_comparison(AST_NE, $1, $3, src_loc(@$));  }
	| expr "==" expr { $$ = gen_comparison(AST_EQ, $1, $3, src_loc(@$));  }

unop
	: "-" expr { $$ = gen_unop(AST_NEG, $2, src_loc(@$));  }
	| "!" expr { $$ = gen_unop(AST_LNOT, $2, src_loc(@$));  }
	| expr "&" { $$ = gen_unop(AST_REF, $1, src_loc(@$));  }
	| expr "*" { $$ = gen_unop(AST_DEREF, $1, src_loc(@$));  }

arr_init
	: "=>" const_expr "..." const_expr "=" expr {
		assert(0 && "range array init is unimplemented");
		abort();
	}
	| "=>" const_expr "=" expr {
		assert(0 && "range array init is unimplemented");
		abort();
	}
	| expr

rev_arr_inits
	: rev_arr_inits "," arr_init { $$ = $3; $1->n = $1; }
	| arr_init

arr_inits
	: rev_arr_inits { $$ = reverse_ast_list($1); }

arr
	: "!" "[" arr_inits "]" { $$ = $3; }

param_decl
	: type { $$ = gen_var(NULL, $1, NULL, src_loc(@$));  }
	| var_decl

sign_decl
	: type
	| sign_var_decl

rev_decls
	: rev_decls "," param_decl { $$ = $3; $$->n = $1; }
	| param_decl

decls
	: rev_decls { $$ = reverse_ast_list($1); }
	| rev_decls "," { $$ = reverse_ast_list($1); }

rev_sign_decls
	: rev_sign_decls "," sign_decl { $$ = $3; $1->n = $1; }
	| sign_decl

sign_decls
	: rev_sign_decls { $$ = reverse_type_list($1); }
	| rev_sign_decls "," { $$ = reverse_type_list($1); }

opt_decls
	: decls
	| {$$ = NULL;}

const_binop
	: const_expr "+" const_expr {
		$$ = gen_binop(AST_ADD, $1, $3, src_loc(@$));
	}
	| const_expr "-" const_expr {
		$$ = gen_binop(AST_SUB, $1, $3, src_loc(@$));
	}
	| const_expr "*" const_expr {
		$$ = gen_binop(AST_MUL, $1, $3, src_loc(@$));
	}
	| const_expr "/" const_expr {
		$$ = gen_binop(AST_DIV, $1, $3, src_loc(@$));
	}
	| const_expr "%" const_expr {
		$$ = gen_binop(AST_REM, $1, $3, src_loc(@$));
	}
	| const_expr "<<" const_expr {
		$$ = gen_binop(AST_LSHIFT, $1, $3, src_loc(@$));
	}
	| const_expr ">>" const_expr {
		$$ = gen_binop(AST_RSHIFT, $1, $3, src_loc(@$));
	}
	| const_expr "<" const_expr {
		$$ = gen_binop(AST_LT, $1, $3, src_loc(@$));
	}
	| const_expr ">" const_expr {
		$$ = gen_binop(AST_GT, $1, $3, src_loc(@$));
	}
	| const_expr "<=" const_expr {
		$$ = gen_binop(AST_LE, $1, $3, src_loc(@$));
	}
	| const_expr ">=" const_expr {
		$$ = gen_binop(AST_GE, $1, $3, src_loc(@$));
	}
	| const_expr "!=" const_expr {
		$$ = gen_binop(AST_NE, $1, $3, src_loc(@$));
	}
	| const_expr "==" const_expr {
		$$ = gen_binop(AST_EQ, $1, $3, src_loc(@$));
	}

const_unop
	: "-" const_expr { $$ = gen_unop(AST_NEG, $2, src_loc(@$));  }
	| "!" const_expr { $$ = gen_unop(AST_LNOT, $2, src_loc(@$));  }

const_expr
	: "(" const_expr ")" { $$ = $2; }
	| INT { $$ = gen_const_int($1, src_loc(@$)); }
	| CHAR { $$ = gen_const_char($1, src_loc(@$)); }
	| BOOL { $$ = gen_const_bool($1, src_loc(@$)); }
	| const_binop
	| const_unop
	| id

/* TODO: concatenate multiple strings together? Or is that the lexer's job? */
expr
	: expr "." ID { $$ = gen_dot($3, $1, src_loc(@$)); }
	| INT { $$ = gen_const_int($1, src_loc(@$)); }
	| CHAR { $$ = gen_const_char($1, src_loc(@$)); }
	| BOOL { $$ = gen_const_bool($1, src_loc(@$)); }
	| STRING {$$ = gen_const_str(strip($1), src_loc(@$));}
	| "(" expr ")" { $$ = $2; }
	/* special rule, user is allowed to define new variables in if
	 * statements etc but it should stand out, which is why we require
	 * parentheses. Also because otherwise the parser craps itself lol */
	| "(" var ")" { $$ = $2; }
	/* by adding "do" some statement-like things become expressions. It was
	 * either this or adding parentheses around them, I personally think
	 * "do" looks a bit cleaner. There is the slight annoyance that a very
	 * long do {} ... might have a 'while'; at the end, not sure if do ...
	 * while should be removed from the language altogether or what */
	| "do" body { $$ = $2; ast_set_flags($$, AST_FLAG_DOEXPR); }
	| "do" expr_if { $$ = $2; ast_set_flags($$, AST_FLAG_DOEXPR); }
	| "do" "const" expr_if { $$ = $3; ast_set_flags($$, AST_FLAG_DOEXPR); }
	| "do" switch { $$ = $2; ast_set_flags($$, AST_FLAG_DOEXPR); }
	| "do" "const" switch { $$ = $3; ast_set_flags($$, AST_FLAG_DOEXPR); }
	| expr "(" opt_exprs ")" { $$ = gen_call($1, $3, src_loc(@$)); }
	| expr "[" expr "]" { $$ = gen_arr($1, $3, src_loc(@$)); }
	| "sizeof" expr { $$ = gen_sizeof($2, src_loc(@$)); }
	| expr "as" type { $$ = gen_cast($1, $3, src_loc(@$));  }
	| ID "::" type { $$ = gen_fetch($1, $3, src_loc(@$)); }
	| "..." ID { $$ = gen_unpack($2, src_loc(@$)); }
	| macro_expand
	| construct
	| assign
	| embed
	| binop
	| unop
	| arr
	| id

while
	: "while" expr body { $$ = gen_while($2, $3, src_loc(@$));  }

do_while
	: "do" body "while" expr ";" { $$ = gen_do_while($2, $4, src_loc(@$)); }

goto
	: "goto" ID { $$ = gen_goto($[ID], NULL, src_loc(@$));  }

statelet
	: "return" exprs { $$ = gen_return($2, NULL, src_loc(@$));  }
	| "return" { $$ = gen_return(NULL, NULL, src_loc(@$)); }
	| "break" { $$ = gen_break(NULL, src_loc(@$)); }
	| "continue" { $$ = gen_continue(NULL, src_loc(@$)); }
	| trait
	| import
	| alias
	| exprs
	| goto
	| var
	| error {
	    /* TODO: figure out how to destroy any and all possible ast nodes we
	     * may have generated up until the error */
	    $$ = gen_empty(src_loc(@$));
	    parser->failed = true;
	    /* If we're failing to parse a statement in a block, continue by trying to
	     * parse the next statement in the block */
	    if (next_interesting_feature(&yylval, &yylloc, scanner, parser)) {
		YYABORT;
	    }
	    yyclearin;
	    yyerrok;
	}

statement
	: statelet ";"
	| switch
	| while
	| do_while
	| body
	| struct
	| struct_cont
	| for
	| if
	| const
	| macro
	| ID ":" { $$ = gen_label($[ID], NULL, src_loc(@$));  }

opt_deferred_statement
	: statement
	| "defer" statement { $$ = gen_defer($2, src_loc(@$)); }

rev_statements
	: rev_statements opt_deferred_statement { $$ = $2; $2->n = $1; }
	| opt_deferred_statement

statements
	: rev_statements { $$ = reverse_ast_list($1); }
	| rev_statements ";" { $$ = reverse_ast_list($1); }

body
	: "{" statements "}" { $$ = gen_block($2, NULL, src_loc(@$));  }
	| "{" "}" { $$ = gen_block(gen_empty(src_loc(@$)), NULL, src_loc(@$)); }

rev_references
	: rev_references "," id { $$ = $3; $$->n = $1; }
	| id

references
	: rev_references { $$ = reverse_ast_list($1); }
	| rev_references "," { $$ = reverse_ast_list($1); }

macro
	: "define" ID "(" references ")" body {
		$$ = gen_macro_def($[ID], $[references], $[body], src_loc(@$));
		ast_set_flags($6, AST_FLAG_UNHYGIENIC);
	}
	| "define" ID "(" references "..." id ")" body {
		ast_append(&$4, $6);
		$$ = gen_macro_def($[ID], $4, $8, src_loc(@$));
		ast_set_flags($$, AST_FLAG_VARIADIC);
		ast_set_flags($8, AST_FLAG_UNHYGIENIC);
	}
	| "define" ID "(" ")" body {
		$$ = gen_macro_def($[ID], NULL, $5, src_loc(@$));
		ast_set_flags($5, AST_FLAG_UNHYGIENIC);
	}

rev_exprs
	: rev_exprs "," expr { $$ = $3; $$->n = $1; }
	| expr

exprs
	: rev_exprs { $$ = reverse_ast_list($1); }
	| rev_exprs "," { $$ = reverse_ast_list($1); }

construct_arg
	: "." ID "=" expr {
		$$ = gen_var($2, NULL, $4, src_loc(@$));
		ast_set_flags($$, AST_FLAG_MEMBER);
	}

rev_construct_args
	: rev_construct_args "," construct_arg { $$ = $3; $3->n = $1; }
	| construct_arg

construct_args
	: rev_construct_args { $$ = reverse_ast_list($1); }
	| rev_construct_args "," { $$ = reverse_ast_list($1); }

opt_construct_args
	: construct_args
	| { $$ = NULL; }

construct
	: APPLY "{" opt_construct_args "}" {
		/** @todo add type info? */
		$$ = gen_init($1, NULL, $3, src_loc(@$));
	}
	| APPLY "[" opt_types "]" "{" opt_construct_args "}" {
		$$ = gen_init($1, $3, $6, src_loc(@$));
	}

if
	: "if" expr body { $$ = gen_if($2, $3, NULL, src_loc(@$));  }
	| "if" expr body "else" body { $$ = gen_if($2, $3, $5, src_loc(@$));  }
	| "if" expr body "else" if { $$ = gen_if($2, $3, $5, src_loc(@$));  }

expr_if
	: "if" expr body "else" body { $$ = gen_if($2, $3, $5, src_loc(@$)); }
	| "if" expr body "else" expr_if { $$ = gen_if($2, $3, $5, src_loc(@$)); }

opt_exprs
	: exprs
	| {$$ = NULL;}

for_init
	: expr
	| var_init

rev_for_inits
	: rev_for_inits "," for_init { $$ = $3; $$->n = $1; }
	| for_init

for_inits
	: rev_for_inits { $$ = reverse_ast_list($1); }
	| rev_for_inits "," { $$ = reverse_ast_list($1); }

opt_for_inits
	: for_inits
	| {$$ = NULL;}

for
	: "for" opt_for_inits ";" opt_exprs ";" opt_exprs body {
		$$ = gen_for($2, $4, $6, $7, src_loc(@$));
	}

case
	: "case" const_expr ":" statements {
		$$ = gen_case($2, $4, src_loc(@$));  }
	| "default" ":" statements {
		/* default seems like it would be useful as something other than
		 * a keyword... */
		$$ = gen_case(NULL, $3, src_loc(@$));
	}

rev_cases
	: rev_cases case { $$ = $2; $1->n = $1; }
	| case

cases
	: rev_cases { $$ = reverse_ast_list($1); }

switch
	: "switch" expr "{" cases "}" { $$ = gen_switch($2, $4, src_loc(@$)); }

/* could there be a use case for number based iteration? */
const_for
	: "for" id ":" exprs body {
		/* TODO: should id be a separate rule? */
		$$ = gen_for($2, NULL, $4, $5, src_loc(@$));
		ast_set_flags($5, AST_FLAG_UNHYGIENIC);
	}

const_if
	: "if" const_expr body {
		$$ = gen_if($2, $3, NULL, src_loc(@$));
		ast_set_flags($3, AST_FLAG_UNHYGIENIC);
	}
	| "if" const_expr body "else" body {
		$$ = gen_if($2, $3, $5, src_loc(@$));
		ast_set_flags($3, AST_FLAG_UNHYGIENIC);
		ast_set_flags($5, AST_FLAG_UNHYGIENIC);
	}
	| "if" const_expr body "else" const_if {
		$$ = gen_if($2, $3, $5, src_loc(@$));
		ast_set_flags($3, AST_FLAG_UNHYGIENIC);
	}

/* maybe I should add a separate gen_iter_for or something and just support
 * iterator for? */
const
	: "const" const_if { $$ = $2; ast_set_flags($$, AST_FLAG_CONST); }
	| "const" const_for { $$ = $2; ast_set_flags($$, AST_FLAG_CONST); }

opt_sign_decls
	: sign_decls
	| {$$ = NULL;}

type
	: ID { $$ = tgen_id($1, src_loc(@$)); }
	| "*" "(" opt_sign_decls "=>" opt_type ")" {
		/* still not entirely sold on this signature, but it's not terrible I
		 * guess */
		$$ = tgen_callable($[opt_sign_decls], $[opt_type], src_loc(@$));
		$$ = tgen_ptr($$, src_loc(@$));
	}
	| "*" "(" opt_sign_decls ")" {
		$$ = tgen_callable($[opt_sign_decls], NULL, src_loc(@$));
		$$ = tgen_ptr($$, src_loc(@$));
	}
	| "*" type {
		$$ = tgen_ptr($2, src_loc(@$));
	}
	| "[" const_expr "]" type {
		assert(0 && "arrays unimplemented");
		abort();
	}
	| "const" type {
		$$ = $2;
	}
	| "mut" type {
		$$ = $2; /* ignored for now */
	}
	| APPLY "[" opt_types "]" {
		$$ = tgen_construct($[APPLY], $[opt_types], src_loc(@$));
	}

opt_type
	: type
	| {$$ = NULL;}

types
	: type "," types { $$ = $1; $$->n = $3; }
	| type

opt_types
	: types
	| { $$ = NULL; }

type_expand
	: APPLY { $$ = gen_type_expand($1, NULL, src_loc(@$)); }

var_decl
	: type ID { $$ = gen_var($2, $1, NULL, src_loc(@$));  }

sign_var_decl
	: type ID { $$ = $1; free((void *)$[ID]);}

var_init
	: var_decl "=" expr { $$ = $1; var_init($$) = $3; }
	| "const" ID "=" expr { $$ = gen_var($2, NULL, $4, src_loc(@$)); }
	| "mut" ID "=" expr {
		$$ = gen_var($2, NULL, $4, src_loc(@$));
		ast_set_flags($$, AST_FLAG_MUTABLE);
	}

proc_decl
	: ID "(" opt_decls "=>" opt_type ")" {
		$$ = gen_proc($[ID],
				$[opt_decls],
				$[opt_type],
				NULL,
				src_loc(@$));
	}
	| ID "(" opt_decls ")" {
		$$ = gen_proc($[ID], $[opt_decls], NULL, NULL, src_loc(@$));
	}

proc
	: ID "(" opt_decls "=>" opt_type ")" body {
		$$ = gen_proc($[ID],
				$[opt_decls],
				$[opt_type],
				$[body],
				src_loc(@$));
	}
	| ID "(" opt_decls ")" body {
		$$ = gen_proc($[ID], $[opt_decls], NULL, $[body], src_loc(@$));
	}
	| "extern" ID "(" opt_decls "=>" opt_type ")" {
		$$ = gen_proc($[ID],
				$[opt_decls],
				$[opt_type],
				NULL,
				src_loc(@$));

		ast_set_flags($$, AST_FLAG_EXTERN | AST_FLAG_NOMANGLE);
	}
	| "extern" ID "(" opt_decls ")" {
		$$ = gen_proc($[ID], $[opt_decls], NULL, NULL, src_loc(@$));
		ast_set_flags($$, AST_FLAG_EXTERN | AST_FLAG_NOMANGLE);
	}
	| "extern" ID "(" opt_decls ")" body {
		$$ = gen_proc($[ID], $[opt_decls], NULL, $[body], src_loc(@$));
		ast_set_flags($$, AST_FLAG_NOMANGLE);
	}
	| "extern" ID "(" opt_decls "=>" opt_type ")" body {
		$$ = gen_proc($[ID], $[opt_decls], $[opt_type], $[body], src_loc(@$));
		ast_set_flags($$, AST_FLAG_NOMANGLE);
	}

behaviour
	: type_expand ";"
	| proc_decl ";"
	| proc

member
	: var_decl ";"
	| behaviour
	;

members
	: member members { $$ = $1; $1->n = $2; ast_set_flags($$, AST_FLAG_MEMBER); }
	| member { $$ = $1; ast_set_flags($$, AST_FLAG_MEMBER); }

opt_members
	: members
	| {$$ = NULL;}

behaviours
	: behaviours behaviour {
		$$ = $1; $1->n = $2;
		ast_set_flags($$, AST_FLAG_MEMBER);
	}
	| behaviour { $$ = $1; ast_set_flags($$, AST_FLAG_MEMBER); }

opt_behaviours
	: behaviours
	| {$$ = NULL;}

macro_expand
	: APPLY "(" opt_exprs ")" {
		$$ = gen_macro_expand($1, $3, src_loc(@$));
	}

struct
	: "typedef" ID "[" opt_type_params "]" "{" opt_members "}" {
		$$ = gen_struct($2, $4, $7, src_loc(@$));
	}
	| "typedef" ID "{" opt_members "}" {
		$$ = gen_struct($2, NULL, $4, src_loc(@$));
	}

struct_cont
	: "continue" ID "[" opt_type_params "]" "{" opt_behaviours "}" {
		/* abbrev 2 */
		$$ = gen_struct_cont($2, $4, $7, src_loc(@$));
	}
	| "continue" ID "{" opt_behaviours "}" {
		/* abbrev 3 */
		$$ = gen_struct_cont($2, NULL, $4, src_loc(@$));
	}

alias
	: "typedef" ID type {
		$$ = gen_alias($2, $3, src_loc(@$));
	}

type_param
	: ID ID {
		struct type *t = tgen_id($1, src_loc(@1));
		$$ = gen_var($2, t, NULL, src_loc(@$));
	}

type_params
	: type_param "," type_params {
		$$ = $1; $1->n = $3; /** @todo this could be left recursive */
	}
	| type_param

opt_type_params
	: type_params
	| { $$ = NULL; }

trait
	: "define" ID "{" opt_behaviours "}" {
		$$ = gen_trait($2, NULL, $4, src_loc(@$));
	}

enum_val
	: ID {
		$$ = gen_val($1, NULL, src_loc(@$));
	}
	| ID "=" expr {
		$$ = gen_val($1, $3, src_loc(@$));
	}

enums
	: enum_val "," enums { $$ = $1; $1->n = $3; }
	| enum_val "," { $$ = $1; }
	| enum_val { $$ = $1; }

enum
	: "enum" ID ":" type "{" enums "}" {
		$$ = gen_enum($2, $4, $6, src_loc(@$));
	}
	| "enum" ID "{" enums "}" {
		$$ = gen_enum($2, NULL, $4, src_loc(@$));
		ast_set_flags($$, AST_FLAG_UNTYPED);
	}

top_if
	: "if" const_expr "{" unit "}" {
		$$ = gen_if($2, $4, NULL, src_loc(@$));
		ast_set_flags($$, AST_FLAG_UNHYGIENIC);
	}
	| "if" const_expr "{" unit "}" "else" "{" unit "}" {
		$$ = gen_if($2, $4, $8, src_loc(@$));
		ast_set_flags($$, AST_FLAG_UNHYGIENIC);
	}
	| "if" const_expr "{" unit "}" "else" top_if {
		$$ = gen_if($2, $4, $7, src_loc(@$));
		ast_set_flags($$, AST_FLAG_UNHYGIENIC);
	}

/* slightly silly to allow stray semicolons at a top level, but seems to help
 * with recovering from certain syntax errors */
top
	: enum
	| proc
	| struct
	| struct_cont { $$ = $1; }
	| macro { $$ = $1; }
	| top_if { $$ = $1; ast_set_flags($$, AST_FLAG_CONST); }
	| import { $$ = $1; }
	| alias { $$ = $1; }
	| trait { $$ = $1; }
	| "pub" enum { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" struct { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" struct_cont { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" proc { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" macro { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" import { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" alias { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" trait { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| ";" { $$ = gen_empty(src_loc(@$)); }
	| error {
	    $$ = gen_empty(src_loc(@$));
	    parser->failed = true;
	    /* ignore any content inside a top level thing and just move onto
	     * the next one */
	    if (next_interesting_feature(&yylval, &yylloc, scanner, parser)) {
		YYABORT;
	    }
	    yyclearin;
	    yyerrok;
	}

unit
	: top { $$ = $1; }
	| unit top { $$ = $2; $2->n = $1; }

input
	: unit { parser->tree = reverse_ast_list($1); }
	| /* empty */

%%

#include "gen_lexer.inc"

/* I'm not convinced this is foolproof quite yet, more testing would be nice. */
static int next_interesting_feature(YYSTYPE *yylval, YYLTYPE *yylloc,
				void *scanner, struct parser *parser)
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


static struct src_loc src_loc(YYLTYPE yylloc)
{
	struct src_loc loc;
	loc.first_line = yylloc.first_line;
	loc.last_line = yylloc.last_line;
	loc.first_col = yylloc.first_column;
	loc.last_col = yylloc.last_column;
	return loc;
}

static void yyerror(YYLTYPE *yylloc, void *lexer,
		struct parser *parser, const char *msg)
{
	(void)lexer;

	struct src_issue issue;
	issue.level = SRC_ERROR;
	issue.loc = src_loc(*yylloc);
	issue.fctx.fbuf = parser->buf;
	issue.fctx.fname = parser->fname;
	src_issue(issue, msg);
}

static char match_escape(char c)
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

static char *strip(const char *str)
{
	const size_t len = strlen(str) + 1;
	char *buf = malloc(len);
	if (!buf) {
		/* should probably try to handle the error in some way... */
		internal_error("failed allocating buffer for string clone");
		free((void *)str);
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
	free((void *)str);
	return buf;

}

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

	p->comment_nesting = 0;

	p->failed = false;

	yylex_init(&p->lexer);
	yy_scan_string(buf, p->lexer);
	yyparse(p->lexer, p);
}

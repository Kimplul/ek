/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

%{

/* TODO: clean up this mess and I guess fix location tracking, it works for the
 * parser but each ast node should also get some location data
 * I'm trying something over in ast.c, but I'm not sure about it
 */

#include <stdio.h>
#include <stdlib.h>
#include <ek/parser.h>
#include <ek/ast.h>

%}

%locations

%define parse.trace
%define parse.error verbose
%define api.pure full
%define lr.type ielr

%lex-param {void *scanner} {struct parser *parser}
%parse-param {void *scanner} {struct parser* parser}

%union {
	struct ast_node *node;
	long long integer;
	double dbl;
	char *str;
};

%token <integer> INT
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
/* still not sure if this should be just typeof, would be slower to type I guess */
%token TYPEOF "typeof"
/* typeof does sort of fit into sizeof, hmmm */
%token SIZEOF "sizeof"
%token PASTE "##"
%token STAR "*"
%token DIV "/"
%token REM "%"
%token MINUS "-"
%token PLUS "+"
%token POW "^^"
%token XOR "^"
%token AND "&"
%token OR "|"
%token LAND "&&"
%token LOR "||"
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
%token XORSELF "^="
%token POWSELF "^^="
%token ANDSELF "&="
%token ORSELF "|="
%token LSHIFTSELF "<<="
%token RSHIFTSELF ">>="
%token AT "@"
%token COMMA ","
%token PUB "pub"
%token STRUCT "struct"
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
%right "=" "+=" "-=" "*=" "/=" "%=" "<<=" ">>=" "&=" "^=" "|=" "^^="
%left "^^"
%left "||"
%left "&&"
%left "==" "!="
%left "<" ">" "<=" ">="
%left "|"
%left "^"
%left "&"
%left "<<" ">>"
%left "+" "-"
%left "*" "/" "%"
%left "as" "sizeof" "typeof"
%right "'" "!" "~"
%left "." "=>" "(" ")"
%left "::"

/* why doesn't bison allow <*> for %nterm? would be so much easier */
%nterm <node> import binop unop arg args decls expr
%nterm <node> while do_while statement statements body references macro
%nterm <node> exprs if for case cases switch const
%nterm <node> func_sign type var_decl var captures
%nterm <node> var_init proc lambda template_elem template_elems types
%nterm <node> alias template enum_val enums enum top unit id
%nterm <node> embed param_decl union struct members struct_elem
%nterm <node> top_if const_if const_for defer goto assign
%nterm <node> construct construct_args construct_arg
%nterm <node> generic generics statelet apply

/* special handling for top level variables */
%nterm <node> top_var_decl top_var_init top_var

/* constant operations */
%nterm <node> const_expr const_unop const_binop

%destructor {} FLOAT INT STRING ID APPLY
%destructor { destroy_ast_tree($$); } <*>

%start input;
%%
id
	: ID {
		$$ = gen_id(strdup($1));
		$$->loc = to_src_loc(&yylloc);
	}

apply
	: APPLY {
		$$ = gen_id(strdup($1));
		$$->loc = to_src_loc(&yylloc);
	}

var
	: var_decl { $$ = $1; }
	| var_init { $$ = $1; }

embed
	: "embed" "(" STRING ")" { $$ = gen_embed(clone_string($3));  }

import
	: "import" STRING { $$ = gen_import(clone_string($2));  }

assign
	: expr "=" expr { $$ = gen_assign($1, $3); }

binop
	: expr "+" expr { $$ = gen_binop(AST_ADD, $1, $3);  }
	| expr "-" expr { $$ = gen_binop(AST_SUB, $1, $3);  }
	| expr "*" expr { $$ = gen_binop(AST_MUL, $1, $3);  }
	| expr "/" expr { $$ = gen_binop(AST_DIV, $1, $3);  }
	| expr "%" expr { $$ = gen_binop(AST_REM, $1, $3);  }
	| expr "^" expr { $$ = gen_binop(AST_XOR, $1, $3);  }
	| expr "^^" expr { $$ = gen_binop(AST_POW, $1, $3);  }
	| expr "&" expr { $$ = gen_binop(AST_AND, $1, $3);  }
	| expr "&&" expr { $$ = gen_binop(AST_LAND, $1, $3);  }
	| expr "|" expr { $$ = gen_binop(AST_OR, $1, $3);  }
	| expr "||" expr { $$ = gen_binop(AST_LOR, $1, $3);  }
	| expr "<<" expr { $$ = gen_binop(AST_LSHIFT, $1, $3);  }
	| expr ">>" expr { $$ = gen_binop(AST_RSHIFT, $1, $3);  }
	| expr "+=" expr { $$ = gen_binop(AST_ASSIGN_ADD, $1, $3);  }
	| expr "-=" expr { $$ = gen_binop(AST_ASSIGN_SUB, $1, $3);  }
	| expr "*=" expr { $$ = gen_binop(AST_ASSIGN_MUL, $1, $3);  }
	| expr "/=" expr { $$ = gen_binop(AST_ASSIGN_DIV, $1, $3);  }
	| expr "%=" expr { $$ = gen_binop(AST_ASSIGN_REM, $1, $3);  }
	| expr "&=" expr { $$ = gen_binop(AST_ASSIGN_AND, $1, $3);  }
	| expr "|=" expr { $$ = gen_binop(AST_ASSIGN_OR, $1, $3);  }
	| expr "^=" expr { $$ = gen_binop(AST_ASSIGN_XOR, $1, $3);  }
	| expr "<<=" expr {
		$$ = gen_binop(AST_ASSIGN_LSHIFT, $1, $3);
	}
	| expr ">>=" expr {
		$$ = gen_binop(AST_ASSIGN_RSHIFT, $1, $3);
	}
	| expr "<" expr { $$ = gen_binop(AST_LT, $1, $3);  }
	| expr ">" expr { $$ = gen_binop(AST_GT, $1, $3);  }
	| expr "<=" expr { $$ = gen_binop(AST_LE, $1, $3);  }
	| expr ">=" expr { $$ = gen_binop(AST_GE, $1, $3);  }
	| expr "!=" expr { $$ = gen_binop(AST_NE, $1, $3);  }
	| expr "==" expr { $$ = gen_binop(AST_EQ, $1, $3);  }

unop
	: "-" expr { $$ = gen_unop(AST_NEG, $2);  }
	| "!" expr { $$ = gen_unop(AST_LNOT, $2);  }
	| "&" expr { $$ = gen_unop(AST_REF, $2);  }
	| "'" expr { $$ = gen_unop(AST_DEREF, $2);  }
	| "~" expr { $$ = gen_unop(AST_NOT, $2);  }

arg
	: "&" var_decl { $$ = gen_unop(AST_REF, $2);  }
	| var_decl { $$ = $1; }
	| expr { $$ = $1; }

args
	: arg "," args { $$ = $1; $1->next = $3; }
	| arg { $$ = $1; }

param_decl
	: type { $$ = gen_var(NULL, $1, NULL);  }

decls
	: var_decl "," decls { $$ = $1; $1->next = $3; }
	| param_decl "," decls { $$ = $1; $1->next = $3; }
	| var_decl { $$ = $1; }
	| param_decl { $$ = $1; }
	| "..." id { $$ = $2; ast_set_flags($$, AST_FLAG_VARIADIC); }

defer
	: "defer" expr { $$ = gen_defer($2);  }

const_binop
	: const_expr "+" const_expr { $$ = gen_binop(AST_ADD, $1, $3);  }
	| const_expr "-" const_expr { $$ = gen_binop(AST_SUB, $1, $3);  }
	| const_expr "*" const_expr { $$ = gen_binop(AST_MUL, $1, $3);  }
	| const_expr "/" const_expr { $$ = gen_binop(AST_DIV, $1, $3);  }
	| const_expr "%" const_expr { $$ = gen_binop(AST_REM, $1, $3);  }
	| const_expr "^" const_expr { $$ = gen_binop(AST_XOR, $1, $3);  }
	| const_expr "^^" const_expr { $$ = gen_binop(AST_POW, $1, $3);  }
	| const_expr "&" const_expr { $$ = gen_binop(AST_AND, $1, $3);  }
	| const_expr "&&" const_expr { $$ = gen_binop(AST_LAND, $1, $3);  }
	| const_expr "|" const_expr { $$ = gen_binop(AST_OR, $1, $3);  }
	| const_expr "||" const_expr { $$ = gen_binop(AST_LOR, $1, $3);  }
	| const_expr "<<" const_expr { $$ = gen_binop(AST_LSHIFT, $1, $3);  }
	| const_expr ">>" const_expr { $$ = gen_binop(AST_RSHIFT, $1, $3);  }
	| const_expr "<" const_expr { $$ = gen_binop(AST_LT, $1, $3);  }
	| const_expr ">" const_expr { $$ = gen_binop(AST_GT, $1, $3);  }
	| const_expr "<=" const_expr { $$ = gen_binop(AST_LE, $1, $3);  }
	| const_expr ">=" const_expr { $$ = gen_binop(AST_GE, $1, $3);  }
	| const_expr "!=" const_expr { $$ = gen_binop(AST_NE, $1, $3);  }
	| const_expr "==" const_expr { $$ = gen_binop(AST_EQ, $1, $3);  }

const_unop
	: "-" const_expr { $$ = gen_unop(AST_NEG, $2);  }
	| "!" const_expr { $$ = gen_unop(AST_LNOT, $2);  }
	| "~" const_expr { $$ = gen_unop(AST_NOT, $2);  }

const_expr
	: "(" const_expr ")" { $$ = $2; }
	| id { $$ = $1; }
	| INT { $$ = gen_int($1); }
	| FLOAT { $$ = gen_float($1); }
	| const_binop { $$ = $1; }
	| const_unop { $$ = $1; }

/* TODO: concatenate multiple strings together? Or is that the lexer's job? */
expr
	: id { $$ = $1; }
	| expr "." id { $$ = gen_dot($1, $3); }
	| "..." id { $$ = $2; }
	| INT { $$ = gen_int($1); $$->loc = to_src_loc(&yylloc); }
	| FLOAT { $$ = gen_float($1); $$->loc = to_src_loc(&yylloc);  }
	| STRING {
		$$ = gen_string(clone_string($1));
		$$->loc = to_src_loc(&yylloc);
	}
	| "(" expr ")" { $$ = $2; }
	| assign { $$ = $1; }
	| expr "(" args ")" { $$ = gen_call($1, $3); }
	| expr "(" ")" { $$ = gen_call($1, NULL); }
	| expr "[" expr "]" { $$ = gen_call($1, $3); /** @todo add arr access */}
	| apply "(" args ")" { $$ = gen_call($1, $3); /* macro call */}
	| apply "(" ")" { $$ = gen_call($1, NULL); /* macro call */}
	| binop { $$ = $1; }
	| unop { $$ = $1; }
	| "(" var_init ")" { $$ = $2; }
	| "sizeof" expr { $$ = gen_sizeof($2); }
	| expr "as" type { $$ = gen_cast($1, $3);  }
	| id "::" type { $$ = gen_fetch($1, $3); }
	| "as" type { $$ = gen_as($2); }
	| embed { $$ = $1; }
	| lambda { $$ = $1; }
	| if { $$ = $1; }
	| switch { $$ = $1; }
	| construct { $$ = $1; }
	| "(" body ")" { $$ = $2; }

while
	: "while" expr body { $$ = gen_while($2, $3);  }

do_while
	: "do" body "while" expr ";" {
		$$ = gen_while($2, $4);
		ast_set_flags($$, AST_FLAG_DELAYED);
	}

goto
	: "goto" id { $$ = gen_goto(gen_label($2));  }

statelet
	: expr { $$ = $1; }
	| "return" expr { $$ = gen_return($2);  }
	| "return" { $$ = gen_return(NULL); }
	| "break" { $$ = gen_ctrl(AST_CTRL_BREAK, to_src_loc(&yylloc)); }
	| "continue" { $$ = gen_ctrl(AST_CTRL_CONTINUE, to_src_loc(&yylloc)); }
	| import { $$ = $1; }
	| var { $$ = $1; }
	| goto { $$ = $1; }
	| id ":" { $$ = gen_label($1);  }
	| for { $$ = $1; }
	| const { $$ = $1; }
	| while { $$ = $1; }
	| do_while { $$ = $1; }
	| macro { $$ = $1; }
	| struct { $$ = $1; }
	| alias { $$ = $1; }
	| template { $$ = $1; }
	| defer { $$ = $1; }
	| enum { $$ = $1; }
	| body { $$ = $1; }
	| ";" { $$ = gen_empty();  }
	| error {
	    /* TODO: figure out how to destroy any and all possible ast nodes we
	     * may have generated up until the error */
	    $$ = gen_empty();
	    parser->failed = true;
	    /* If we're failing to parse a statement in a block, continue by trying to
	     * parse the next statement in the block */
	    if (next_interesting_feature(&yylval, &yylloc, scanner, parser)) {
		destroy_ast_node($$);
		YYABORT;
	    }
	    yyclearin;
	    yyerrok;
	    }

statement
	: statelet ";" { $$ = $1; }

statements
	: statement statements { $$ = $1; $1->next = $2; }
	| statement { $$ = $1; }
	| statelet { $$ = $1; }

body
	: "{" statements "}" { $$ = gen_block($2);  }
	| "{" "}" { $$ = gen_block(gen_empty());  }

references
	: id "," references { $$ = $1; $$->next = $3; }
	| id { $$ = $1; }
	| "..." id { $$ = $2; ast_set_flags($$, AST_FLAG_VARIADIC); }

/* TODO: rethink how macros play into everyting */
macro
	: "define" id "(" references ")" body {
		$$ = gen_macro($2, $4, $6);
		ast_set_flags($6, AST_FLAG_UNHYGIENIC);
	}
	| "define" id "(" references "..." id ")" body {
		/* TODO: the location data of the variadic ID is way off */
		ast_append($4, $6);
		$$ = gen_macro($2, $4, $8);
		ast_set_flags($$, AST_FLAG_VARIADIC);
		ast_set_flags($8, AST_FLAG_UNHYGIENIC);
	}
	| "define" id "(" ")" body {
		$$ = gen_macro($2, NULL, $5);
		ast_set_flags($5, AST_FLAG_UNHYGIENIC);
	}

exprs
	: expr "," exprs { $$ = $1; $1->next = $3; }
	| expr { $$ = $1; }

construct_arg
	: expr { $$ = $1; }
	| "." id "=" expr {
		$$ = gen_var($2, NULL, $4);
		ast_set_flags($$, AST_FLAG_MEMBER);
	}

construct_args
	: construct_arg "," construct_args { $$ = $1; $1->next = $3; }
	| construct_arg { $$ = $1; }

construct
	: "!" "{" construct_args "}" { $$ = gen_init($3); }

if
	: "if" expr body { $$ = gen_if($2, $3, NULL);  }
	| "if" expr body "else" body { $$ = gen_if($2, $3, $5);  }
	| "if" expr body "else" if { $$ = gen_if($2, $3, $5);  }

/* todo how about leaving out some parts? */
for
	: "for" arg ";" expr ";" expr body { $$ = gen_for($2, $4, $6, $7); }

case
	: "case" const_expr ":" statements {
		$$ = gen_case($2, $4);  }
	| "default" ":" statements {
		$$ = gen_case(NULL, $3);
	}

cases
	: case cases { $$ = $1; $1->next = $2; }
	| case { $$ = $1; }

switch
	: "switch" expr "{" cases "}" { $$ = gen_switch($2, $4); }

/* could there be a use case for number based iteration? */
const_for
	: "for" id ":" exprs body {
		/* TODO: should id be a separate rule? */
		$$ = gen_for($2, NULL, $4, $5);
		ast_set_flags($5, AST_FLAG_UNHYGIENIC);
	}

const_if
	: "if" const_expr body {
		$$ = gen_if($2, $3, NULL);
		ast_set_flags($3, AST_FLAG_UNHYGIENIC);
	}
	| "if" const_expr body "else" body {
		$$ = gen_if($2, $3, $5);
		ast_set_flags($3, AST_FLAG_UNHYGIENIC);
		ast_set_flags($5, AST_FLAG_UNHYGIENIC);
	}
	| "if" const_expr body "else" const_if {
		$$ = gen_if($2, $3, $5);
		ast_set_flags($3, AST_FLAG_UNHYGIENIC);
	}

/* maybe I should add a separate gen_iter_for or something and just support
 * iterator for? */
const
	: "const" const_if { $$ = $2; ast_set_flags($$, AST_FLAG_CONST); }
	| "const" const_for { $$ = $2; ast_set_flags($$, AST_FLAG_CONST); }

func_sign
	: "(" decls "=>" type ")" {
		$$ = gen_type(AST_TYPE_SIGN, NULL, $2, $4);
	}
	| "(" decls ")" { $$ = gen_type(AST_TYPE_SIGN, NULL, $2, NULL); }
	| "(" decls "=>" ")" { $$ = gen_type(AST_TYPE_SIGN, NULL, $2, NULL); }
	| "(" "=>" type ")" { $$ = gen_type(AST_TYPE_SIGN, NULL, NULL, $3); }
	| "(" ")" { $$ = gen_type(AST_TYPE_SIGN, NULL, NULL, NULL); }

type
	: id { $$ = gen_type(AST_TYPE_ID, $1, NULL, NULL); }
	| "@" func_sign {
		$$ = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		$$->_type.next = $2;
	}
	| apply "[" types "]" {
		$$ = gen_type(AST_TYPE_GENERIC, $1, $3, NULL);
	}
	| "'" type {
		$$ = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		$$->_type.next = $2;
	}
	| "'" "[" const_expr "]" type {
		$$ = gen_type(AST_TYPE_ARR, NULL, $3, NULL);
		$$->_type.next = $5;
	}
	| "typeof" expr {
		$$ = gen_type(AST_TYPE_TYPEOF, NULL, $2, NULL);
	}
	| id "::" type {
		$$ = gen_type(AST_TYPE_MEMBER, $1, $3, NULL);
	}

var_decl
	: id "mut" type {
		$$ = gen_var($1, $3, NULL);
		ast_set_flags($$, AST_FLAG_MUTABLE);
	}
	| id "const" type { $$ = gen_var($1, $3, NULL);  }
	| id type { $$ = gen_var($1, $2, NULL);  }

var_init
	: var_decl "=" expr { $$ = $1; $1->_var.init = $3; }
	| id "mut" "=" expr {
		$$ = gen_var($1, NULL, $4);
		ast_set_flags($$, AST_FLAG_UNTYPED | AST_FLAG_MUTABLE);
	}
	| id "const" "=" expr {
		$$ = gen_var($1, NULL, $4);
		ast_set_flags($$, AST_FLAG_UNTYPED);
	}

proc
	: id func_sign body {
		$$ = gen_proc($1, $2, $3);
		ast_set_flags($$, $2->flags);
	}
	| "extern" id func_sign {
		/* todo check that we don't have a variadic function */
		$$ = gen_proc($2, $3, NULL);
		ast_set_flags($$, AST_FLAG_EXTERN);
	}

captures
	: id "," captures { $$ = $1; $1->next = $3; }
	| id { $$ = $1; }

lambda
	: "[" captures "]" func_sign body { $$ = gen_lambda($2, $4, $5); }
	| "[" captures "]" body { $$ = gen_lambda($2, NULL, $4); }

struct_elem
	: var_decl { $$ = $1; }

members
	: struct_elem ";" members { $$ = $1; $1->next = $3; }
	| struct_elem ";" { $$ = $1; }

union
	: "union" id "{" members "}" {
		$$ = gen_union($2, NULL, $4);
	}
	| "union" id "(" generics ")" "{" members "}" {
		$$ = gen_union($2, $4, $7);
	}

generic
	: id type { $$ = gen_alias($1, $2); }

generics
	: generic "," generics { $$ = $1; $$->next = $3; }
	| generic { $$ = $1; }

struct
	: "struct" id "{" members "}" {
		$$ = gen_struct($2, NULL, $4);
	}
	| "struct" id "(" generics ")" "{" members "}" {
		$$ = gen_struct($2, $4, $7);
	}

/* since traits aren't generic, they don't have to implement anything, meaning
 * we can keep a pretty clean separation between procs and supertraits */
template_elem
	: id ";" { $$ = $1; }
	| id func_sign ";" { $$ = gen_proc($1, $2, NULL);  }
	| var_decl ";" { $$ = $1; }
	| union { $$ = $1; }

template_elems
	: template_elem template_elems { $$ = $1; $1->next = $2; }
	| template_elem { $$ = $1; }

types
	: type "," types { $$ = $1; $1->next = $3; }
	| type { $$ = $1; }

alias
	: "typedef" id type { $$ = gen_alias($2, $3);  }

/* we'll parse the arg list later in the AST and check that each node is of some
 * specific type */
template
	: "typedef" id "{" template_elems "}" {
		$$ = gen_template($2, $4);
	}
	| "typedef" id "{" "}" {
		/* should match anything, but doesn't implement anything */
		$$ = gen_template($2, NULL);
	}

enum_val
	: id { $$ = gen_val($1, NULL);  }
	| id "=" expr { $$ = gen_val($1, $3);  }

enums
	: enum_val "," enums { $$ = $1; $1->next = $3; }
	| enum_val "," { $$ = $1; }
	| enum_val { $$ = $1; }

enum
	: "enum" id ":" type "{" enums "}" { $$ = gen_enum($2, $4, $6); }
	| "enum" id "{" enums "}" {
		$$ = gen_enum($2, NULL, $4);
		ast_set_flags($$, AST_FLAG_UNTYPED);
	}

top_if
	: "if" const_expr "{" unit "}" {
		$$ = gen_if($2, $4, NULL);
		ast_set_flags($$, AST_FLAG_UNHYGIENIC);
	}
	| "if" const_expr "{" unit "}" "else" "{" unit "}" {
		$$ = gen_if($2, $4, $8);
		ast_set_flags($$, AST_FLAG_UNHYGIENIC);
	}
	| "if" const_expr "{" unit "}" "else" top_if {
		$$ = gen_if($2, $4, $7);
		ast_set_flags($$, AST_FLAG_UNHYGIENIC);
	}

top_var_decl
	: id "mut" type {
		$$ = gen_var($1, $3, NULL);
		ast_set_flags($$, AST_FLAG_MUTABLE);
	}
	| id "const" type { $$ = gen_var($1, $3, NULL); }
	| id type { $$ = gen_var($1, $2, NULL); }

top_var_init
	: top_var_decl "=" const_expr { $$ = $1; $1->_var.init = $3; }
	| id "mut" "=" const_expr { $$ = $1; $1->_var.init = $4; }
	| id "const" "=" const_expr { $$ = $1; $1->_var.init = $4; }

top_var
	: top_var_decl { $$ = $1; }
	| top_var_init { $$ = $1; }

/* slightly silly to allow stray semicolons at a top level, but seems to help
 * with recovering from certain syntax errors */
top
	: enum { $$ = $1; }
	| proc { $$ = $1; }
	| struct { $$ = $1; }
	| union { $$ = $1; }
	| macro { $$ = $1; }
	| top_if { $$ = $1; ast_set_flags($$, AST_FLAG_CONST); }
	| top_var { $$ = $1; ast_set_flags($$, AST_FLAG_CONST); }
	| import { $$ = $1; }
	| alias { $$ = $1; }
	| template { $$ = $1; }
	| "pub" enum { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" struct { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" union { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" proc { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" macro { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" import { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" alias { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" template { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" top_var {
		$$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC);
		ast_set_flags($$, AST_FLAG_CONST);
	}
	| ";" { $$ = gen_empty(); }
	| error {
	    $$ = gen_empty();
	    parser->failed = true;
	    /* ignore any content inside a top level thing and just move onto
	     * the next one */
	    if (next_interesting_feature(&yylval, &yylloc, scanner, parser)) {
		/* remove previously allocated node if we're out of input */
		destroy_ast_node($$);
		YYABORT;
	    }
	    yyclearin;
	    yyerrok;
	}

unit
	: top { $$ = $1; }
	| top unit { $$ = $1; $1->next = $2; }

input
	: unit { parser->tree = $1; }
	| /* empty */

%%

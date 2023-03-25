%{

/* TODO: clean up this mess and I guess fix location tracking, it works for the
 * parser but each ast node should also get some location data
 * I'm trying something over in ast.c, but I'm not sure about it
 */

#include <stdio.h>
#include <stdlib.h>
#include <cu/parser.h>
#include <cu/ast.h>

%}

%locations

%define parse.trace
%define parse.error verbose
%define api.pure full

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
%token TYPEDEF "type"
%token IMPORT "import"
%token DEFER "defer"
%token GOTO "goto"
%token EMBED "embed"
%token IF "if"
%token ELSE "else"
%token BREAK "break"
%token CONTINUE "continue"
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
%token FATARROW "=>"

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

/* why doesn't bison allow <*> for %nterm? would be so much easier */
%nterm <node> import binary_op unary_op arg arg_list decl_list call expr
%nterm <node> while do_while statement statement_list body macro_list macro
%nterm <node> expr_list init_expr expr_if if for case case_list switch const
%nterm <node> func_sign variadic_sign type var_decl var
%nterm <node> var_init proc lambda template_elem template_list type_list
%nterm <node> type_alias type_template enum_val enum_list enum top unit id
%nterm <node> embed param_decl union struct struct_list struct_elem
%nterm <node> top_if const_if const_for defer goto assign
%nterm <node> struct_construct struct_inits struct_init cond
%nterm <node> generic generic_list union_struct

%destructor {} FLOAT INT STRING ID
%destructor { destroy_ast_tree($$); } <*>

%start input;
%%
id: ID {
		$$ = gen_id(strdup($1));
		$$->loc = to_src_loc(&yylloc);
	}
	;

var: var_decl { $$ = $1; }
	| var_init { $$ = $1; }
	;

embed: "embed" "(" STRING ")" { $$ = gen_embed(clone_string($3));  }
	;

import: "import" STRING { $$ = gen_import(clone_string($2));  }
	;

assign: expr "=" expr { $$ = gen_assign($1, $3); }
	| expr "=" struct_construct { $$ = gen_assign($1, $3); }
	;

binary_op: expr "+" expr { $$ = gen_binop(AST_ADD, $1, $3);  }
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
	;

unary_op: "-" expr { $$ = gen_unop(AST_NEG, $2);  }
	| "!" expr { $$ = gen_unop(AST_LNOT, $2);  }
	| "&" expr { $$ = gen_unop(AST_REF, $2);  }
	| "'" expr { $$ = gen_unop(AST_DEREF, $2);  }
	| "~" expr { $$ = gen_unop(AST_NOT, $2);  }
	;

arg: "&" var_decl { $$ = gen_unop(AST_REF, $2);  }
	| var_decl { $$ = $1; }
	| init_expr { $$ = $1; }
	;

arg_list: arg "," arg_list { $$ = $1; $1->next = $3; }
	| arg { $$ = $1; }
	;

param_decl: type { $$ = gen_var(NULL, $1, NULL);  }

decl_list: var_decl "," decl_list { $$ = $1; $1->next = $3; }
	| param_decl "," decl_list { $$ = $1; $1->next = $3; }
	| var_decl { $$ = $1; }
	| param_decl { $$ = $1; }
	;

/* call also works for arrays in this case */
call: id "(" arg_list ")" { $$ = gen_call($1, $3);  }
	| id "(" ")" { $$ = gen_call($1, NULL);  }
	;

defer: "defer" "(" expr ")" { $$ = gen_defer($3);  }
	;

/* TODO: concatenate multiple strings together */
expr: id { $$ = $1; }
	| expr "." id { $$ = gen_dot($1, $3); }
	| id "##" id { $$ = gen_paste($1, $3);  }
	| "..." id { $$ = $2; }
	| "@" { $$ = gen_last();  }
	| INT { $$ = gen_int($1); $$->loc = to_src_loc(&yylloc); }
	| FLOAT { $$ = gen_float($1); $$->loc = to_src_loc(&yylloc);  }
	| STRING {
		$$ = gen_string(clone_string($1));
		$$->loc = to_src_loc(&yylloc);
	}
	| "(" expr ")" { $$ = $2; }
	| assign { $$ = $1; }
	| call { $$ = $1; }
	| defer { $$ = $1; }
	| binary_op { $$ = $1; }
	| unary_op { $$ = $1; }
	| "(" var_init ")" { $$ = $2; }
	| "sizeof" expr { $$ = gen_sizeof($2); }
	| expr "as" type { $$ = gen_cast($1, $3);  }
	| "as" type { $$ = gen_as($2); }
	| embed { $$ = $1; }
	| lambda { $$ = $1; }
	;

while: "while" expr body { $$ = gen_while($2, $3);  }
	;

do_while: "do" body "while" expr ";" {
		$$ = gen_while($2, $4);
		ast_set_flags($$, AST_FLAG_DELAYED);
	}
	;

goto: "goto" id { $$ = gen_goto(gen_label($2));  }

statement: expr ";" { $$ = $1; }
	| "return" init_expr ";" { $$ = gen_return($2);  }
	| "return" ";" { $$ = gen_return(NULL); }
	| "break" ";" { $$ = gen_ctrl(AST_CTRL_BREAK, to_src_loc(&yylloc)); }
	| "continue" ";" { $$ = gen_ctrl(AST_CTRL_CONTINUE,
	to_src_loc(&yylloc));  }
	| import ";" { $$ = $1; }
	| var ";" { $$ = $1; }
	| if { $$ = $1; }
	| goto ";"{ $$ = $1; }
	| id ":" { $$ = gen_label($1);  }
	| for { $$ = $1; }
	| const { $$ = $1; }
	| while { $$ = $1; }
	| do_while { $$ = $1; }
	| switch { $$ = $1; }
	| macro { $$ = $1; }
	| struct { $$ = $1; }
	| type_alias ";" { $$ = $1; }
	| type_template { $$ = $1; }
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
	 ;

statement_list: statement statement_list { $$ = $1; $1->next = $2; }
	| statement { $$ = $1; }
	;

body: "{" statement_list "}" { $$ = gen_block($2);  }
	| "{" "}" { $$ = gen_block(gen_empty());  }
	;

macro_list: id "," macro_list { $$ = $1; $$->next = $3; }
	| id { $$ = $1; }
	;

macro: "define" id "(" macro_list ")" body {
		$$ = gen_macro($2, $4, $6);
		ast_set_flags($6, AST_FLAG_UNHYGIENIC);
	}
	| "define" id "(" macro_list "..." id ")" body {
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
	;

expr_list: expr "," expr_list { $$ = $1; $1->next = $3; }
	| expr { $$ = $1; }
	;

struct_init: init_expr { $$ = $1; }
	| "." id "=" init_expr {
		$$ = gen_var($2, NULL, $4);
		ast_set_flags($$, AST_FLAG_MEMBER);
	}
	;

struct_inits: struct_init "," struct_inits { $$ = $1; $1->next = $3; }
	| struct_init { $$ = $1; }
	;

struct_construct: "{" struct_inits "}" { $$ = gen_init($2); }
	;

init_expr: expr { $$ = $1; }
	| expr_if { $$ = $1; }
	| struct_construct { $$ = $1; }
	| struct_construct "as" type { $$ = gen_cast($1, $3); }
	;

cond: expr { $$ = $1; }
	| "(" expr_if ")" { $$ = $2; }
	/* note no struct construct */
	;

expr_if: "if" cond body "else" body { $$ = gen_if($2, $3, $5);  }
	| "if" cond body "else" expr_if { $$ = gen_if($2, $3, $5);  }
	;

if: "if" cond body { $$ = gen_if($2, $3, NULL);  }
	| "if" cond body "else" body { $$ = gen_if($2, $3, $5);  }
	| "if" cond body "else" if { $$ = gen_if($2, $3, $5);  }
	;

for: "for" arg ";" expr ";" expr body { $$ = gen_for($2, $4, $6, $7); }
	;

case: "case" expr ":" statement_list { $$ = gen_case($2, $4);  }
	;

case_list: case case_list { $$ = $1; $1->next = $2; }
	| case { $$ = $1; }
	;

switch: "switch" expr "{" case_list "}" { $$ = gen_switch($2, $4);  }
	;

const_for: "for" id ":" expr_list body {
		/* TODO: should id be a separate rule? */
		$$ = gen_for($2, NULL, $4, $5);
		ast_set_flags($5, AST_FLAG_UNHYGIENIC);
	}
	;

const_if: "if" expr body {
		$$ = gen_if($2, $3, NULL);
		ast_set_flags($3, AST_FLAG_UNHYGIENIC);
	}
	| "if" expr body "else" body {
		$$ = gen_if($2, $3, $5);
		ast_set_flags($3, AST_FLAG_UNHYGIENIC);
		ast_set_flags($5, AST_FLAG_UNHYGIENIC);
	}
	| "if" expr body "else" const_if {
		$$ = gen_if($2, $3, $5);
		ast_set_flags($3, AST_FLAG_UNHYGIENIC);
	}
	;

/* maybe I should add a separate gen_iter_for or something and just support
 * iterator for? */
const: "const" const_if { $$ = $2; ast_set_flags($$, AST_FLAG_CONST);
      }
	| "const" const_for { $$ = $2; ast_set_flags($$, AST_FLAG_CONST);
	 }
	;

func_sign: "(" decl_list "=>" type ")" {
		$$ = gen_type(AST_TYPE_SIGN, NULL, $2, $4);
	}
	| "(" decl_list ")" { $$ = gen_type(AST_TYPE_SIGN, NULL, $2, NULL);
	 }
	| "(" decl_list "=>" ")" { $$ = gen_type(AST_TYPE_SIGN, NULL, $2, NULL);
	 }
	| "(" "=>" type ")" { $$ = gen_type(AST_TYPE_SIGN, NULL, NULL, $3);
	 }
	| "(" ")" { $$ = gen_type(AST_TYPE_SIGN, NULL, NULL, NULL);
	 }
	;

variadic_sign: func_sign { $$ = $1; }
	| "(" decl_list "..." id "=>" type ")" {
		ast_append($2, $4);
		$$ = gen_type(AST_TYPE_SIGN, NULL, $2, $6);
		ast_set_flags($$, AST_FLAG_VARIADIC);
	}
	;

type: id { $$ = gen_type(AST_TYPE_ID, $1, NULL, NULL); }
	| "'" func_sign {
		$$ = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		$$->next = $2;
	}
	| id "(" type_list ")" {
		$$ = gen_type(AST_TYPE_STRUCT, $1, $3, NULL);
	}
	| "'" type {
		$$ = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		$$->_type.next = $2;
	}
	| "[" "]" type {
		$$ = gen_type(AST_TYPE_ARR, NULL, NULL, NULL);
		$$->_type.next = $3;
	}
	| "[" expr "]" type {
		$$ = gen_type(AST_TYPE_ARR, NULL, $2, NULL);
		$$->_type.next = $4;
	}
	| "typeof" expr {
		$$ = gen_type(AST_TYPE_TYPEOF, NULL, $2, NULL);
	}
	;

var_decl: id "mut" type {
		$$ = gen_var($1, $3, NULL);
		ast_set_flags($$, AST_FLAG_MUTABLE);
	}
	| id "const" type { $$ = gen_var($1, $3, NULL);  }
	| id type { $$ = gen_var($1, $2, NULL);  }
	;

var_init: var_decl "=" init_expr { $$ = $1; $1->_var.init = $3; }
	| id "mut" "=" init_expr {
		$$ = gen_var($1, NULL, $4);
		ast_set_flags($$, AST_FLAG_UNTYPED | AST_FLAG_MUTABLE);
	}
	| id "const" "=" init_expr {
		$$ = gen_var($1, NULL, $4);
		ast_set_flags($$, AST_FLAG_UNTYPED);
	}
	;

proc: id variadic_sign body {
		$$ = gen_proc($1, $2, $3);
		ast_set_flags($$, $2->flags);
	}
	| "extern" id func_sign {
		$$ = gen_proc($2, $3, NULL);
		ast_set_flags($$, AST_FLAG_EXTERN);
	}
	;

lambda: "[" macro_list "]" func_sign body { $$ = gen_lambda($2, $4, $5); }
	;

struct_elem: var_decl { $$ = $1; }
	;

struct_list: struct_elem ";" struct_list { $$ = $1; $1->next = $3; }
	| struct_elem ";" { $$ = $1; }
	;

union: "union" id "{" struct_list "}" {
		$$ = gen_union($2, NULL, $4);
	}
	| "union" id "(" generic_list ")" "{" struct_list "}" {
		$$ = gen_union($2, $4, $7);
	}
	;

generic: id type { $$ = gen_alias($1, $2); }
generic_list: generic "," generic_list { $$ = $1; $$->next = $3; }
	| generic { $$ = $1; }
	;

struct: "struct" id "{" struct_list "}" {
		$$ = gen_struct($2, NULL, $4);
	}
	| "struct" id "(" generic_list ")" "{" struct_list "}" {
		$$ = gen_struct($2, $4, $7);
	}
	;

/* since traits aren't generic, they don't have to implement anything, meaning
 * we can keep a pretty clean separation between procs and supertraits */
template_elem: id ";" { $$ = $1; }
	| id func_sign ";" { $$ = gen_proc($1, $2, NULL);  }
	| var_decl ";" { $$ = $1; }
	| union { $$ = $1; }
	;

template_list: template_elem template_list { $$ = $1; $1->next = $2; }
	 | template_elem { $$ = $1; }
	 ;

type_list: type "," type_list { $$ = $1; $1->next = $3; }
	| type { $$ = $1; }
	;

type_alias: "type" id type { $$ = gen_alias($2, $3);  }
	;

/* we'll parse the arg list later in the AST and check that each node is of some
 * specific type */
type_template: "type" id "{" template_list "}" {
		$$ = gen_template($2, $4);
	}
	| "type" id "{" "}" {
		/* should match anything, but doesn't implement anything */
		$$ = gen_template($2, NULL);
	}
	;

enum_val: id { $$ = gen_val($1, gen_int(0));  }
	| id "=" expr { $$ = gen_val($1, $3);  }
	;

enum_list: enum_val "," enum_list { $$ = $1; $1->next = $3; }
	| enum_val "," { $$ = $1; }
	| enum_val { $$ = $1; }
	;

enum: "enum" id ":" type "{" enum_list "}" { $$ = gen_enum($2, $4, $6); }
	| "enum" id "{" enum_list "}" {
		$$ = gen_enum($2, NULL, $4);
		ast_set_flags($$, AST_FLAG_UNTYPED);
	}
	;

top_if: "if" expr "{" unit "}" {
		$$ = gen_if($2, $4, NULL);
		ast_set_flags($$, AST_FLAG_UNHYGIENIC);
	}
	| "if" expr "{" unit "}" "else" "{" unit "}" {
		$$ = gen_if($2, $4, $8);
		ast_set_flags($$, AST_FLAG_UNHYGIENIC);
	}
	| "if" expr "{" unit "}" "else" top_if {
		$$ = gen_if($2, $4, $7);
		ast_set_flags($$, AST_FLAG_UNHYGIENIC);
	}
	;

/* slightly silly to allow stray semicolons at a top level, but seems to help
 * with recovering from certain syntax errors */
top: ";" { $$ = gen_empty(); }
	| enum { $$ = $1; }
	| proc { $$ = $1; }
	| struct { $$ = $1; }
	| macro { $$ = $1; }
	| "const" top_if { $$ = $2; ast_set_flags($$, AST_FLAG_CONST); }
	| import ";" { $$ = $1; }
	| type_alias ";" { $$ = $1; }
	| type_template { $$ = $1; }
	| "pub" enum { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" struct { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" proc { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" macro { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" import ";" { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" type_alias ";" { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| "pub" type_template { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
	| var ";" { $$ = $1; }
	| "pub" var ";" { $$ = $2; ast_set_flags($2, AST_FLAG_PUBLIC); }
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
	;

unit: top { $$ = $1; }
	| top unit { $$ = $1; $1->next = $2; }
	;

input: unit { parser->tree = $1; }
	| /* empty */
	;
%%

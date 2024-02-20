/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

/**
 * @file ast.c
 *
 * Abstract syntax tree handling implementations.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <ek/ast.h>
#include <ek/scope.h>

static struct {
	size_t n;
	size_t s;
	struct ast_node **v;
} ast_nodes = {0};

static void destroy_ast_node(struct ast_node *node)
{
	if (!node)
		return;

	switch (node->node_type) {
	case AST_ID: free((void *)AST_ID(node).id); break;
	case AST_CONST:
		if (AST_CONST(node).kind == AST_CONST_STRING)
			free((void *)AST_CONST(node).str);
		break;
	default:
	}

	free(node);
}

void destroy_ast_nodes()
{
	for (size_t i = 0; i < ast_nodes.n; ++i)
		destroy_ast_node(ast_nodes.v[i]);

	free(ast_nodes.v);
}

/* eventually we might want to pass in a context or something */
static struct ast_node *create_ast_node()
{
	if (ast_nodes.s == 0) {
		ast_nodes.s = 1;
		ast_nodes.n = 0;
		ast_nodes.v = calloc(1, sizeof(struct ast_node *));
	}

	else if (ast_nodes.n >= ast_nodes.s) {
		ast_nodes.s *= 2;
		ast_nodes.v =
			realloc(ast_nodes.v,
			        ast_nodes.s * sizeof(struct ast_node *));
	}

	struct ast_node *n = calloc(1, sizeof(struct ast_node));
	ast_nodes.v[ast_nodes.n++] = n;
	return n;
}

/** @todo alloc should maybe also keep track of all nodes in a vector or
 * something and mass free all AST at a time to keep my sanity */
#define ALLOC_NODE(n, type)                                     \
	struct ast_node *n = create_ast_node();                 \
	if (!n) {                                               \
		fprintf(stderr, "failed allocating" type "\n"); \
		return NULL;                                    \
	}

#define DESTROY_LIST(x)                          \
	{                                        \
		struct ast_node *prev = x, *cur; \
		if (prev)                        \
		do {                             \
			cur = prev->next;        \
			destroy_ast_node(prev);  \
		} while ((prev = cur));          \
	}

struct ast_node *gen_arr_access(struct ast_node *base, struct ast_node *idx,
                                struct src_loc loc)
{
	ALLOC_NODE(n, "arr_access");
	n->node_type = AST_ARR_ACCESS;
	AST_ARR_ACCESS(n).base = base;
	AST_ARR_ACCESS(n).idx = idx;
	n->loc = loc;
	return n;
}

struct ast_node *gen_macro_expand(struct ast_node *id, struct ast_node *args,
                                  struct src_loc loc)
{
	ALLOC_NODE(n, "macro_expand");
	n->node_type = AST_MACRO_EXPAND;
	AST_MACRO_EXPAND(n).id = id;
	AST_MACRO_EXPAND(n).args = args;
	n->loc = loc;
	return n;
}

struct ast_node *gen_type_expand(struct ast_node *id,
                                 struct ast_node *args,
                                 struct src_loc loc)
{
	ALLOC_NODE(n, "type_expand");
	n->node_type = AST_TYPE_EXPAND;
	AST_TYPE_EXPAND(n).id = id;
	AST_TYPE_EXPAND(n).args = args;
	n->loc = loc;
	return n;
}

struct ast_node *gen_binop(enum ast_binops op,
                           struct ast_node *left,
                           struct ast_node *right,
                           struct src_loc loc)
{
	ALLOC_NODE(n, "binop");
	n->node_type = AST_BINOP;
	AST_BINOP(n).op = op;
	AST_BINOP(n).left = left;
	AST_BINOP(n).right = right;
	n->loc = loc;
	return n;
}

struct ast_node *gen_unop(enum ast_unops op, struct ast_node *expr, struct src_loc loc)
{
	ALLOC_NODE(n, "unop");
	n->node_type = AST_UNOP;
	AST_UNOP(n).op = op;
	AST_UNOP(n).expr = expr;
	n->loc = loc;
	return n;
}

struct ast_node *gen_call(struct ast_node *expr, struct ast_node *args,
                          struct src_loc loc)
{
	ALLOC_NODE(n, "call");
	n->node_type = AST_CALL;
	AST_CALL(n).expr = expr;
	AST_CALL(n).args = args;
	n->loc = loc;
	return n;
}

struct ast_node *gen_id(const char *id, struct src_loc loc)
{
	ALLOC_NODE(n, "id");
	n->node_type = AST_ID;
	AST_ID(n).id = id;
	n->loc = loc;
	return n;
}

struct ast_node *gen_assign(struct ast_node *to, struct ast_node *from, struct src_loc loc)
{
	ALLOC_NODE(n, "assign");
	n->node_type = AST_ASSIGN;
	AST_ASSIGN(n).to = to;
	AST_ASSIGN(n).from = from;
	n->loc = loc;
	return n;
}

struct ast_node *gen_init(struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "struct init");
	n->node_type = AST_INIT;
	AST_INIT(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_int(long long integer, struct src_loc loc)
{
	ALLOC_NODE(n, "int");
	n->node_type = AST_CONST;
	AST_CONST(n).kind = AST_CONST_INTEGER;
	AST_CONST(n).integer = integer;
	n->loc = loc;
	return n;
}

struct ast_node *gen_string(const char *str, struct src_loc loc)
{
	ALLOC_NODE(n, "string");
	n->node_type = AST_CONST;
	AST_CONST(n).kind = AST_CONST_STRING;
	AST_CONST(n).str = str;
	n->loc = loc;
	return n;
}

struct ast_node *gen_while(struct ast_node *cond, struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "while");
	n->node_type = AST_WHILE;
	AST_WHILE(n).cond = cond;
	AST_WHILE(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_for(struct ast_node *pre, struct ast_node *cond,
                         struct ast_node *post, struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "for");
	n->node_type = AST_FOR;
	AST_FOR(n).pre = pre;
	AST_FOR(n).cond = cond;
	AST_FOR(n).post = post;
	AST_FOR(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_return(struct ast_node *expr, struct src_loc loc)
{
	ALLOC_NODE(n, "return");
	n->node_type = AST_RETURN;
	AST_RETURN(n).expr = expr;
	n->loc = loc;
	return n;
}

struct ast_node *gen_goto(struct ast_node *label, struct src_loc loc)
{
	ALLOC_NODE(n, "goto");
	n->node_type = AST_GOTO;
	AST_GOTO(n).label = label;
	n->loc = loc;
	return n;
}

struct ast_node *gen_dot(struct ast_node *expr, struct ast_node *id, struct src_loc loc)
{
	ALLOC_NODE(n, "dot");
	n->node_type = AST_DOT;
	AST_DOT(n).expr = expr;
	AST_DOT(n).id = id;
	n->loc = loc;
	return n;
}

struct ast_node *gen_label(struct ast_node *id, struct src_loc loc)
{
	ALLOC_NODE(n, "label");
	n->node_type = AST_LABEL;
	AST_LABEL(n).id = id;
	n->loc = loc;
	return n;
}

struct ast_node *gen_ctrl(enum ast_ctrl_kind kind, struct src_loc loc)
{
	ALLOC_NODE(n, "ctrl");
	n->node_type = AST_CTRL;
	AST_CTRL(n).kind = kind;
	n->loc = loc;
	return n;
}

struct ast_node *gen_fetch(struct ast_node *id, struct ast_node *type, struct src_loc loc)
{
	ALLOC_NODE(n, "fetch");
	n->node_type = AST_FETCH;
	AST_FETCH(n).id = id;
	AST_FETCH(n).type = type;
	n->loc = loc;
	return n;
}

struct ast_node *gen_macro_construct(struct ast_node *id,
                                     struct ast_node *params,
                                     struct ast_node *body,
				     struct src_loc loc)
{
	ALLOC_NODE(n, "macro_construct");
	n->node_type = AST_MACRO_CONSTRUCT;
	AST_MACRO_CONSTRUCT(n).id = id;
	AST_MACRO_CONSTRUCT(n).params = params;
	AST_MACRO_CONSTRUCT(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_if(struct ast_node *cond, struct ast_node *body,
                        struct ast_node *els, struct src_loc loc)
{
	ALLOC_NODE(n, "if");
	n->node_type = AST_IF;
	AST_IF(n).cond = cond;
	AST_IF(n).body = body;
	AST_IF(n).els = els;
	n->loc = loc;
	return n;
}

struct ast_node *gen_switch(struct ast_node *cond, struct ast_node *cases, struct src_loc loc)
{
	ALLOC_NODE(n, "switch");
	n->node_type = AST_SWITCH;
	AST_SWITCH(n).cond = cond;
	AST_SWITCH(n).cases = cases;
	n->loc = loc;
	return n;
}

struct ast_node *gen_case(struct ast_node *cond, struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "case");
	/* TODO: a macro to map proc name to node type would make sure I don't
	 * make any dumb mixups... */
	n->node_type = AST_CASE;
	AST_CASE(n).cond = cond;
	AST_CASE(n).body = body;
	/* TODO: where should I check the fallthrough flag? In the
	 * actualization stage, I guess */
	n->loc = loc;
	return n;
}

struct ast_node *gen_primitive(enum ast_primitive type, struct ast_node *def, struct src_loc loc)
{
	ALLOC_NODE(n, "primitive");
	n->node_type = AST_TYPE;
	AST_TYPE(n).kind = AST_TYPE_PRIMITIVE;
	AST_PRIMITIVE_TYPE(n).type = type;
	AST_PRIMITIVE_TYPE(n).def = def;
	n->loc = loc;
	return n;
}

struct ast_node *gen_type(enum ast_type_kind kind,
                          struct ast_node *t0,
                          struct ast_node *t1,
                          struct src_loc loc)
{
	ALLOC_NODE(n, "type");
	n->node_type = AST_TYPE;
	AST_TYPE(n).kind = kind;
	n->loc = loc;

	switch (kind) {
	case AST_TYPE_TRAIT:
		AST_TRAIT_TYPE(n).def = t0;
		break;

	case AST_TYPE_ID:
		AST_ID_TYPE(n).id = t0;
		break;

	case AST_TYPE_CONSTRUCT:
		AST_CONSTRUCT_TYPE(n).id = t0;
		AST_CONSTRUCT_TYPE(n).args = t1;
		break;

	case AST_TYPE_ARR:
		AST_ARR_TYPE(n).size = t0;
		AST_ARR_TYPE(n).base = t1;
		break;

	case AST_TYPE_POINTER:
		AST_PTR_TYPE(n).base = t0;
		break;

	case AST_TYPE_STRUCT:
		AST_STRUCT_TYPE(n).def = t0;
		break;

	case AST_TYPE_ENUM:
		AST_ENUM_TYPE(n).def = t0;
		break;

	case AST_TYPE_SIGN:
		AST_SIGN_TYPE(n).params = t0;
		AST_SIGN_TYPE(n).ret = t1;
		break;

	default: abort();
	}

	return n;
}

struct ast_node *gen_block(struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "block");
	n->node_type = AST_BLOCK;
	AST_BLOCK(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_sizeof(struct ast_node *expr, struct src_loc loc)
{
	ALLOC_NODE(n, "sizeof");
	n->node_type = AST_SIZEOF;
	AST_SIZEOF(n).expr = expr;
	n->loc = loc;
	return n;
}

struct ast_node *gen_as(struct ast_node *type, struct src_loc loc)
{
	ALLOC_NODE(n, "as");
	n->node_type = AST_AS;
	AST_AS(n).type = type;
	n->loc = loc;
	return n;
}

struct ast_node *gen_defer(struct ast_node *expr, struct src_loc loc)
{
	ALLOC_NODE(n, "defer");
	n->node_type = AST_DEFER;
	AST_DEFER(n).expr = expr;
	n->loc = loc;
	return n;
}

void destroy_defer(struct ast_node *defer)
{
	assert(defer->node_type == AST_DEFER);
	destroy_ast_node(AST_DEFER(defer).expr);
	free(defer);
}

struct ast_node *gen_var(struct ast_node *id, struct ast_node *type,
                         struct ast_node *init, struct src_loc loc)
{
	ALLOC_NODE(n, "var");
	n->node_type = AST_VAR;
	AST_VAR(n).id = id;
	AST_VAR(n).type = type;
	AST_VAR(n).init = init;
	n->loc = loc;
	return n;
}

struct ast_node *gen_proc(struct ast_node *id, struct ast_node *sign,
                          struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "proc");
	n->node_type = AST_PROC;
	AST_PROC(n).id = id;
	AST_PROC(n).sign = sign;
	AST_PROC(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_struct(struct ast_node *id,
                            struct ast_node *generics, struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "struct");
	n->node_type = AST_STRUCT;
	AST_STRUCT(n).id = id;
	AST_STRUCT(n).generics = generics;
	AST_STRUCT(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_enum(struct ast_node *id, struct ast_node *type,
                          struct ast_node *body, struct src_loc loc)
{
	ALLOC_NODE(n, "enum");
	n->node_type = AST_ENUM;
	AST_ENUM(n).id = id;
	AST_ENUM(n).type = type;
	AST_ENUM(n).body = body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_cast(struct ast_node *expr, struct ast_node *type, struct src_loc loc)
{
	ALLOC_NODE(n, "cast");
	n->node_type = AST_CAST;
	AST_CAST(n).expr = expr;
	AST_CAST(n).type = type;
	n->loc = loc;
	return n;
}

struct ast_node *gen_val(struct ast_node *id, struct ast_node *val, struct src_loc loc)
{
	ALLOC_NODE(n, "val");
	n->node_type = AST_VAL;
	AST_VAL(n).id = id;
	AST_VAL(n).val = val;
	n->loc = loc;
	return n;
}

struct ast_node *gen_alias(struct ast_node *id, struct ast_node *type, struct src_loc loc)
{
	ALLOC_NODE(n, "alias");
	n->node_type = AST_ALIAS;
	AST_ALIAS(n).id = id;
	AST_ALIAS(n).type = type;
	n->loc = loc;
	return n;
}

struct ast_node *gen_trait(struct ast_node *id,
			struct ast_node *params,
                           struct ast_node *raw_body,
			   struct ast_node *body,
			   struct src_loc loc)
{
	ALLOC_NODE(n, "trait");
	n->node_type = AST_TRAIT;
	AST_TRAIT(n).id = id;
	AST_TRAIT(n).params = params;
	AST_TRAIT(n).body = body;
	AST_TRAIT(n).raw_body = raw_body;
	n->loc = loc;
	return n;
}

struct ast_node *gen_import(const char *file, struct src_loc loc)
{
	ALLOC_NODE(n, "import");
	n->node_type = AST_IMPORT;
	AST_IMPORT(n).file = file;
	n->loc = loc;
	return n;
}

struct ast_node *gen_embed(const char *file, struct src_loc loc)
{
	ALLOC_NODE(n, "embed");
	n->node_type = AST_EMBED;
	AST_EMBED(n).file = file;
	n->loc = loc;
	return n;
}

struct ast_node *gen_empty()
{
	ALLOC_NODE(n, "empty");
	n->node_type = AST_EMPTY;
	/* TODO: location? */
	return n;
}

void ast_set_flags(struct ast_node *node, enum ast_flag flags)
{
	node->flags |= flags;
}

void ast_clear_flags(struct ast_node *node, enum ast_flag flags)
{
	node->flags &= ~(flags);
}

void ast_append(struct ast_node *list, struct ast_node *elem)
{
	struct ast_node *cur = list;
	while (cur->next)
		cur = cur->next;

	cur->next = elem;
}


static const char *binop_symbol(int op)
{
	switch (op) {
	case AST_ADD: return "+";
	case AST_SUB: return "-";
	case AST_MUL: return "*";
	case AST_DIV: return "/";
	case AST_REM: return "%";
	case AST_LOR: return "||";
	case AST_LAND: return "&&";
	case AST_LSHIFT: return "<<";
	case AST_RSHIFT: return ">>";
	case AST_ASSIGN_ADD: return "+=";
	case AST_ASSIGN_SUB: return "-=";
	case AST_ASSIGN_MUL: return "*=";
	case AST_ASSIGN_DIV: return "/=";
	case AST_ASSIGN_REM: return "%=";
	case AST_ASSIGN_LSHIFT: return "<<=";
	case AST_ASSIGN_RSHIFT: return ">>=";
	case AST_LT: return "<";
	case AST_GT: return ">";
	case AST_LE: return "<=";
	case AST_GE: return ">=";
	case AST_NE: return "!=";
	case AST_EQ: return "==";
	}

	return "UNKNOWN";
}

static const char *unop_symbol(int op)
{
	switch (op) {
	case AST_NEG: return "-";
	case AST_LNOT: return "!";
	case AST_REF: return "&";
	case AST_DEREF: return "*";
	}

	return "UNKNOWN";
}

static void dump(int depth, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	for (int i = 0; i < depth; ++i)
		putchar('\t');

	vprintf(fmt, args);

	va_end(args);
}

static void dump_flags(struct ast_node *node)
{
	if (node->scope)
		printf(" %zu:", node->scope->number);

	enum ast_flag flags = node->flags;
	if (flags & AST_FLAG_MUTABLE)
		printf(" MUT");

	if (flags & AST_FLAG_CONST)
		printf(" CONST");

	if (flags & AST_FLAG_EXTERN)
		printf(" EXTERN");

	if (flags & AST_FLAG_VARIADIC)
		printf(" VARIADIC");

	if (flags & AST_FLAG_DELAYED)
		printf(" DELAYED");

	if (flags & AST_FLAG_PUBLIC)
		printf(" PUB");

	if (flags & AST_FLAG_UNTYPED)
		printf(" UNTYPED");

	if (flags & AST_FLAG_FALLTHROUGH)
		printf(" FALLTHROUGH");
}

const char *primitive_str(enum ast_primitive type)
{
	switch (type) {
	case AST_VOID: return "void";
	case AST_I9: return "i9";
	case AST_I27: return "i27";
	case AST_BOOL: return "bool";
	default: return "unimp";
	}

	return "unimp";
}

static void __dump_ast(int depth, struct ast_node *node)
{
	switch (node->node_type) {
	case AST_FETCH:
		dump(depth, "{FETCH:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_FETCH(node).id);
		dump_ast(depth + 1, AST_FETCH(node).type);

		dump(depth, "}\n");
		break;

	case AST_ASSIGN:
		dump(depth, "{ASSIGN:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_ASSIGN(node).to);
		dump_ast(depth + 1, AST_ASSIGN(node).from);

		dump(depth, "}\n");
		break;

	case AST_INIT:
		dump(depth, "{INIT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_INIT(node).body);

		dump(depth, "}\n");
		break;

	case AST_SIZEOF:
		dump(depth, "{SIZEOF:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_SIZEOF(node).expr);

		dump(depth, "}\n");
		break;

	case AST_DOT:
		dump(depth, "{DOT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_DOT(node).expr);
		dump_ast(depth + 1, AST_DOT(node).id);

		dump(depth, "}\n");
		break;

	case AST_GOTO:
		dump(depth, "{GOTO:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_GOTO(node).defers);
		dump_ast(depth + 1, AST_GOTO(node).label);

		dump(depth, "}\n");
		break;

	case AST_LABEL:
		dump(depth, "{LABEL:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_LABEL(node).id);

		dump(depth, "}\n");
		break;

	case AST_BINOP:
		dump(depth, "{BINOP:");
		dump_flags(node);
		printf(" %s\n", binop_symbol(AST_BINOP(node).op));

		dump_ast(depth + 1, AST_BINOP(node).left);
		dump_ast(depth + 1, AST_BINOP(node).right);

		dump(depth, "}\n");
		break;

	case AST_UNOP:
		dump(depth, "{UNOP:");
		dump_flags(node);
		printf(" %s\n", unop_symbol(AST_UNOP(node).op));

		dump_ast(depth + 1, AST_UNOP(node).expr);

		dump(depth, "}\n");
		break;

	case AST_CALL:
		dump(depth, "{CALL:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_CALL(node).expr);
		dump_ast(depth + 1, AST_CALL(node).args);

		dump(depth, "}\n");
		break;

	case AST_DEFER:
		dump(depth, "{DEFER:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_DEFER(node).expr);

		dump(depth, "}\n");
		break;

	case AST_CAST:
		dump(depth, "{CAST:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_CAST(node).expr);
		dump_ast(depth + 1, AST_CAST(node).type);

		dump(depth, "}\n");
		break;

	case AST_MACRO_CONSTRUCT:
		dump(depth, "{MACRO_CONSTRUCT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_MACRO_CONSTRUCT(node).id);
		dump_ast(depth + 1, AST_MACRO_CONSTRUCT(node).params);
		dump_ast(depth + 1, AST_MACRO_CONSTRUCT(node).body);

		dump(depth, "}\n");
		break;

	case AST_MACRO_EXPAND:
		dump(depth, "{MACRO_EXPAND:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_MACRO_EXPAND(node).id);
		dump_ast(depth + 1, AST_MACRO_EXPAND(node).args);

		dump(depth, "}\n");
		break;

	case AST_PROC:
		dump(depth, "{PROC:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_PROC(node).id);
		dump_ast(depth + 1, AST_PROC(node).sign);
		dump_ast(depth + 1, AST_PROC(node).body);

		dump(depth, "}\n");
		break;

	case AST_VAR:
		dump(depth, "{VAR:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_VAR(node).id);
		dump_ast(depth + 1, AST_VAR(node).type);
		dump_ast(depth + 1, AST_VAR(node).init);

		dump(depth, "}\n");
		break;

	case AST_ID:
		dump(depth, "{ID:");
		dump_flags(node);
		printf(" %s}\n", AST_ID(node).id);
		break;

	case AST_AS:
		dump(depth, "{AS:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_AS(node).type);
		dump(depth, "}\n");
		break;

	case AST_BLOCK:
		dump(depth, "{BLOCK:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_BLOCK(node).body);
		dump_ast(depth + 1, AST_BLOCK(node).defers);

		dump(depth, "}\n");
		break;

	case AST_RETURN:
		dump(depth, "{RETURN:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_RETURN(node).defers);
		dump_ast(depth + 1, AST_RETURN(node).expr);

		dump(depth, "}\n");
		break;

	case AST_TYPE:
		dump(depth, "{TYPE:");
		dump_flags(node);

		switch (node->_type.kind) {
		case AST_TYPE_PRIMITIVE:
			printf(" PRIMITIVE %s\n",
			       primitive_str(AST_PRIMITIVE_TYPE(node).type));
			break;

		case AST_TYPE_TRAIT: {
			printf(" TRAIT\n");
			struct ast_node *def = AST_TRAIT_TYPE(node).def;
			/* this should be enough, avoid print loops */
			dump_ast(depth + 1, AST_TRAIT(def).id);
			break;
		}

		case AST_TYPE_CONSTRUCT: {
			printf(" CONSTRUCT\n");
			dump_ast(depth + 1, AST_CONSTRUCT_TYPE(node).id);
			dump_ast(depth + 1, AST_CONSTRUCT_TYPE(node).args);
			break;
		}

		case AST_TYPE_ID:
			printf(" ID\n");
			dump_ast(depth + 1, AST_ID_TYPE(node).id);
			break;

		case AST_TYPE_ARR:
			printf(" ARR\n");
			dump_ast(depth + 1, AST_ARR_TYPE(node).size);
			dump_ast(depth + 1, AST_ARR_TYPE(node).base);
			break;

		case AST_TYPE_POINTER:
			printf(" PTR\n");
			dump_ast(depth + 1, AST_PTR_TYPE(node).base);
			break;

		case AST_TYPE_STRUCT: {
			printf(" STRUCT\n");
			struct ast_node *def = AST_STRUCT_TYPE(node).def;
			/* oh yeah, struc is at least right now just an ID that
			 * we can use to fetch the actual struct with. */
			dump_ast(depth + 1, AST_STRUCT(def).id);
			break;
		}

		case AST_TYPE_ENUM: {
			printf(" ENUM\n");
			struct ast_node *def = AST_ENUM_TYPE(node).def;
			dump_ast(depth + 1, AST_ENUM(def).id);
			break;
		}

		case AST_TYPE_SIGN:
			printf(" SIGN\n");
			dump_ast(depth + 1, AST_SIGN_TYPE(node).params);
			dump_ast(depth + 1, AST_SIGN_TYPE(node).ret);
			break;
		}

		dump_ast(depth + 1, AST_TYPE(node).next);

		dump(depth, "}\n");
		break;

	case AST_EMPTY:
		dump(depth, "{EMPTY:");
		dump_flags(node);
		printf("}\n");
		break;

	case AST_FOR:
		dump(depth, "{FOR:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_FOR(node).pre);
		dump_ast(depth + 1, AST_FOR(node).cond);
		dump_ast(depth + 1, AST_FOR(node).post);
		dump_ast(depth + 1, AST_FOR(node).body);

		dump(depth, "}\n");
		break;

	case AST_WHILE:
		dump(depth, "{WHILE:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_WHILE(node).cond);
		dump_ast(depth + 1, AST_WHILE(node).body);

		dump(depth, "}\n");
		break;

	case AST_CTRL:
		dump(depth, "{CTRL:");
		dump_flags(node);
		switch(AST_CTRL(node).kind) {
		case AST_CTRL_BREAK: printf(" BREAK"); break;
		case AST_CTRL_CONTINUE: printf(" CONTINUE"); break;
		}
		printf("}\n");
		break;

	case AST_IF:
		dump(depth, "{IF:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_IF(node).cond);
		dump_ast(depth + 1, AST_IF(node).body);
		dump_ast(depth + 1, AST_IF(node).els);

		dump(depth, "}\n");
		break;

	case AST_IMPORT:
		dump(depth, "{IMPORT:");
		dump_flags(node);
		printf(" %s}\n", AST_IMPORT(node).file);
		break;

	case AST_EMBED:
		dump(depth, "{EMBED:");
		dump_flags(node);
		printf(" %s}\n", AST_EMBED(node).file);
		break;

	case AST_ENUM:
		dump(depth, "{ENUM:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_ENUM(node).id);
		dump_ast(depth + 1, AST_ENUM(node).type);
		dump_ast(depth + 1, AST_ENUM(node).body);

		dump(depth, "}\n");
		break;

	case AST_STRUCT:
		dump(depth, "{STRUCT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_STRUCT(node).id);
		dump_ast(depth + 1, AST_STRUCT(node).generics);
		dump_ast(depth + 1, AST_STRUCT(node).body);

		dump(depth, "}\n");
		break;

	case AST_VAL:
		dump(depth, "{VAL:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_VAL(node).id);
		dump_ast(depth + 1, AST_VAL(node).val);

		dump(depth, "}\n");
		break;

	case AST_SWITCH:
		dump(depth, "{SWITCH:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_SWITCH(node).cond);
		dump_ast(depth + 1, AST_SWITCH(node).cases);

		dump(depth, "}\n");
		break;

	case AST_CASE:
		dump(depth, "{CASE:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_CASE(node).cond);
		dump_ast(depth + 1, AST_CASE(node).body);

		dump(depth, "}\n");
		break;

	case AST_CONST:
		dump(depth, "{CONST:");
		dump_flags(node);
		switch (node->_const.kind) {
		case AST_CONST_INTEGER:
			printf(" %lli", AST_CONST(node).integer);
			break;
		case AST_CONST_STRING:
			printf(" \"%s\"", AST_CONST(node).str);
			break;
		}
		printf("}\n");
		break;

	case AST_ALIAS:
		dump(depth, "{ALIAS:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_ALIAS(node).id);
		dump_ast(depth + 1, AST_ALIAS(node).type);

		dump(depth, "}\n");
		break;

	case AST_TRAIT:
		dump(depth, "{TRAIT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, AST_TRAIT(node).id);
		dump_ast(depth + 1, AST_TRAIT(node).body);

		dump(depth, "}\n");
		break;

	default:
		dump(depth, "{UNIMP}\n");
	}
}

void dump_ast_node(int depth, struct ast_node *n)
{
	if (!n) {
		dump(depth, "{NULL}\n");
		return;
	}

	__dump_ast(depth, n);
}

void dump_ast(int depth, struct ast_node *root)
{
	if (!root) {
		dump(depth, "{NULL}\n");
		return;
	}

	struct ast_node *n = root;
	do {
		dump_ast_node(depth, n);
	} while ((n = n->next));
}

struct ast_node *clone_ast_node(struct ast_node *node)
{
	if (!node)
		return NULL;

	assert(node->node_type);
	struct ast_node *new = NULL;
	switch (node->node_type) {
	case AST_ARR_ACCESS:
		new = gen_arr_access(
			clone_ast_node(AST_ARR_ACCESS(node).base),
			clone_ast_node(AST_ARR_ACCESS(node).idx),
			node->loc);
		break;

	case AST_TYPE_EXPAND:
		new = gen_type_expand(
			clone_ast_node(AST_TYPE_EXPAND(node).id),
			clone_ast_node(AST_TYPE_EXPAND(node).args),
			node->loc);
		break;

	case AST_FETCH:
		new = gen_fetch(clone_ast_node(AST_FETCH(node).id),
		                clone_ast_node(AST_FETCH(node).type),
				node->loc);
		break;

	case AST_ASSIGN:
		new = gen_assign(clone_ast_node(AST_ASSIGN(node).to),
		                 clone_ast_node(AST_ASSIGN(node).from),
				 node->loc);
		break;

	case AST_INIT: new = gen_init(clone_ast_node(AST_INIT(node).body), node->loc);
		break;

	case AST_SIZEOF: new = gen_sizeof(clone_ast_node(AST_SIZEOF(node).expr), node->loc);
		break;

	case AST_DOT: new = gen_dot(clone_ast_node(AST_DOT(node).expr),
		                    clone_ast_node(AST_DOT(node).id),
				    node->loc);
		break;

	case AST_AS: new = gen_as(clone_ast_node(AST_AS(node).type), node->loc);
		break;

	case AST_GOTO: new = gen_goto(clone_ast_node(AST_GOTO(node).label), node->loc);
		break;

	case AST_LABEL: new = gen_label(clone_ast_node(AST_LABEL(node).id), node->loc);
		break;

	case AST_BINOP: new = gen_binop(AST_BINOP(node).op,
		                        clone_ast_node(AST_BINOP(node).left),
		                        clone_ast_node(AST_BINOP(node).right),
		                        node->loc);
		break;

	case AST_UNOP: new = gen_unop(AST_UNOP(node).op,
		                      clone_ast_node(AST_UNOP(node).expr),
				      node->loc);
		break;

	case AST_CALL: new = gen_call(clone_ast_node(AST_CALL(node).expr),
		                      clone_ast_node(AST_CALL(node).args),
		                      node->loc);
		break;

	case AST_DEFER: new = gen_defer(clone_ast_node(AST_DEFER(node).expr), node->loc);
		break;

	case AST_MACRO_CONSTRUCT: new = gen_macro_construct(
			clone_ast_node(AST_MACRO_CONSTRUCT(node).id),
			clone_ast_node(AST_MACRO_CONSTRUCT(node).params),
			clone_ast_node(AST_MACRO_CONSTRUCT(node).body),
			node->loc);
		break;

	case AST_MACRO_EXPAND: new = gen_macro_expand(
			clone_ast_node(AST_MACRO_EXPAND(node).id),
			clone_ast_node(AST_MACRO_EXPAND(node).args),
			node->loc);
		break;

	case AST_CAST: new = gen_cast(clone_ast_node(AST_CAST(node).expr),
		                      clone_ast_node(AST_CAST(node).type),
				      node->loc);
		break;

	case AST_PROC: new = gen_proc(clone_ast_node(AST_PROC(node).id),
		                      clone_ast_node(AST_PROC(node).sign),
		                      clone_ast_node(AST_PROC(node).body),
		                      node->loc);
		break;

	case AST_VAR: new = gen_var(clone_ast_node(AST_VAR(node).id),
		              clone_ast_node(AST_VAR(node).type),
		              clone_ast_node(AST_VAR(node).init),
			      node->loc);
		break;

	case AST_FOR: new = gen_for(clone_ast_node(AST_FOR(node).pre),
		                    clone_ast_node(AST_FOR(node).cond),
		                    clone_ast_node(AST_FOR(node).post),
		                    clone_ast_node(AST_FOR(node).body),
				    node->loc);
		break;

	case AST_WHILE: new = gen_while(clone_ast_node(AST_WHILE(node).cond),
		                        clone_ast_node(AST_WHILE(node).body),
					node->loc);
		break;

	case AST_CTRL: new = gen_ctrl(AST_CTRL(node).kind, node->loc);
		break;

	case AST_RETURN: new = gen_return(clone_ast_node(AST_RETURN(node).expr), node->loc);
		break;

	case AST_TYPE:
		/* oh, if a node has a ->type it probably isn't cloned
		 * correctly... */
		switch (node->_type.kind) {
		case AST_TYPE_PRIMITIVE:
			new = gen_primitive(AST_PRIMITIVE_TYPE(node).type,
					AST_PRIMITIVE_TYPE(node).def, node->loc);
			break;

		case AST_TYPE_TRAIT:
			new = gen_type(AST_TYPE_TRAIT,
			               AST_TRAIT_TYPE(node).def,
			               NULL,
			               node->loc);
			break;

		case AST_TYPE_CONSTRUCT:
			new = gen_type(AST_TYPE_CONSTRUCT,
					clone_ast_node(AST_CONSTRUCT_TYPE(node).id),
					clone_ast_node(AST_CONSTRUCT_TYPE(node).args),
					node->loc);
			break;

		case AST_TYPE_ID:
			new = gen_type(AST_TYPE_ID,
			               clone_ast_node(AST_ID_TYPE(node).id),
			               NULL,
			               node->loc);
			break;

		case AST_TYPE_ARR:
			new = gen_type(AST_TYPE_ARR,
			               clone_ast_node(AST_ARR_TYPE(node).size),
			               clone_ast_node(AST_ARR_TYPE(node).base),
			               node->loc);
			break;

		case AST_TYPE_POINTER:
			new = gen_type(AST_TYPE_POINTER,
					clone_ast_node(AST_PTR_TYPE(node).base),
					NULL,
					node->loc);
			break;

		case AST_TYPE_STRUCT:
			new = gen_type(AST_TYPE_STRUCT,
			               AST_STRUCT_TYPE(node).def,
			               NULL, node->loc);
			break;

		case AST_TYPE_ENUM:
			new = gen_type(AST_TYPE_ENUM,
			               AST_ENUM_TYPE(node).def,
			               NULL,
			               node->loc);
			break;

		case AST_TYPE_SIGN:
			new = gen_type(AST_TYPE_SIGN,
			               clone_ast_node(AST_SIGN_TYPE(node).params),
			               clone_ast_node(AST_SIGN_TYPE(node).ret),
			               node->loc);
			break;

		}

		assert(new);
		AST_TYPE(new).next = clone_ast_node(AST_TYPE(node).next);
		break;

	case AST_BLOCK:
		/* TODO: should defers also be cloned? Probably? */
		new = gen_block(clone_ast_node(AST_BLOCK(node).body), node->loc);
		break;

	case AST_IMPORT:
		new = gen_import(strdup(AST_IMPORT(node).file), node->loc);
		break;

	case AST_EMBED:
		new = gen_embed(strdup(AST_EMBED(node).file), node->loc);
		break;

	case AST_ENUM:
		new = gen_enum(clone_ast_node(AST_ENUM(node).id),
		               clone_ast_node(AST_ENUM(node).type),
		               clone_ast_node(AST_ENUM(node).body),
			       node->loc);
		break;

	case AST_STRUCT:
		new = gen_struct(clone_ast_node(AST_STRUCT(node).id),
		                 clone_ast_node(AST_STRUCT(node).generics),
		                 clone_ast_node(AST_STRUCT(node).body),
				 node->loc);
		break;

	case AST_VAL:
		new = gen_val(clone_ast_node(AST_VAL(node).id),
		              clone_ast_node(AST_VAL(node).val),
			      node->loc);
		break;

	case AST_SWITCH:
		new = gen_switch(clone_ast_node(AST_SWITCH(node).cond),
		                 clone_ast_node(AST_SWITCH(node).cases),
				 node->loc);
		break;

	case AST_CASE:
		new = gen_case(clone_ast_node(AST_CASE(node).cond),
		               clone_ast_node(AST_CASE(node).body),
			       node->loc);
		break;

	case AST_CONST:
		switch (node->_const.kind) {
		case AST_CONST_INTEGER:
			new = gen_int(AST_CONST(node).integer, node->loc);
			break;

		case AST_CONST_STRING:
			new = gen_string(strdup(AST_CONST(node).str), node->loc);
			break;
		}
		break;

	case AST_ID:
		new = gen_id(strdup(AST_ID(node).id), node->loc);
		break;

	case AST_EMPTY:
		new = gen_empty();
		break;

	case AST_ALIAS:
		new = gen_alias(clone_ast_node(AST_ALIAS(node).id),
		                clone_ast_node(AST_ALIAS(node).type),
				node->loc);
		break;

	case AST_TRAIT:
		new = gen_trait(clone_ast_node(AST_TRAIT(node).id),
		                clone_ast_node(AST_TRAIT(node).params),
				clone_ast_node(AST_TRAIT(node).raw_body),
		                clone_ast_node(AST_TRAIT(node).body),
		                node->loc);
		break;

	case AST_IF:
		new = gen_if(clone_ast_node(AST_IF(node).cond),
		             clone_ast_node(AST_IF(node).body),
		             clone_ast_node(AST_IF(node).els),
			     node->loc);
		break;
	}

	/* if we run out of memory, this assert is likely a bit dumb... */
	assert(new);
	new->scope = node->scope;
	new->flags = node->flags;
	new->loc = node->loc;
	new->next = clone_ast_node(node->next);

	/* some special case handled type references for us */
	if (!new->type)
		new->type = node->type;

	return new;
}

int ast_flags(struct ast_node *node, enum ast_flag flags)
{
	return node->flags & flags;
}

static int call_on_assign(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_ASSIGN(node).to, data);
	ret |= call(AST_ASSIGN(node).from, data);
	return ret;
}

static int call_on_init(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	return call(AST_INIT(node).body, data);
}

static int call_on_sizeof(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	return call(AST_SIZEOF(node).expr, data);
}

static int call_on_dot(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_DOT(node).expr, data);
	ret |= call(AST_DOT(node).id, data);
	return ret;
}

static int call_on_as(int (*call)(struct ast_node *,
                                  void *), struct ast_node *node, void *data)
{
	return call(AST_AS(node).type, data);
}

static int call_on_cast(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_CAST(node).expr, data);
	ret |= call(AST_CAST(node).type, data);
	return ret;
}

static int call_on_defer(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	return call(AST_DEFER(node).expr, data);
}

static int call_on_var(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_VAR(node).id, data);
	ret |= call(AST_VAR(node).type, data);
	ret |= call(AST_VAR(node).init, data);
	return ret;
}

static int call_on_for(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_for.pre, data);
	ret |= call(node->_for.cond, data);
	ret |= call(node->_for.post, data);
	ret |= call(node->_for.body, data);
	return ret;
}

static int call_on_while(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_while.cond, data);
	ret |= call(node->_while.body, data);
	return ret;
}

static int call_on_return(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	return call(node->_return.expr, data);
}

static int call_on_alias(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_alias.id, data);
	ret |= call(node->_alias.type, data);
	return ret;
}

static int call_on_trait(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_trait.id, data);
	ret |= call(node->_trait.body, data);
	return ret;
}

static int call_on_if(int (*call)(struct ast_node *,
                                  void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_if.cond, data);
	ret |= call(node->_if.body, data);
	ret |= call(node->_if.els, data);
	return ret;
}

static int call_on_enum(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_enum.id, data);
	ret |= call(node->_enum.type, data);
	ret |= call(node->_enum.body, data);
	return ret;
}

static int call_on_struct(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_struct.id, data);
	ret |= call(node->_struct.generics, data);
	ret |= call(node->_struct.body, data);
	return ret;
}

static int call_on_val(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_val.id, data);
	ret |= call(node->_val.val, data);
	return ret;
}

static int call_on_switch(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_switch.cond, data);
	ret |= call(node->_switch.cases, data);
	return ret;
}

static int call_on_case(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_case.cond, data);
	ret |= call(node->_case.body, data);
	return ret;
}

static int call_on_type_id(int (*call)(struct ast_node *,
                                       void *), struct ast_node *node, void *data)
{
	return call(AST_ID_TYPE(node).id, data);
}

static int call_on_type_arr(int (*call)(struct ast_node *,
                                        void *), struct ast_node *node, void *data)
{
	return call(AST_ARR_TYPE(node).size, data);
}

static int call_on_type_sign(int (*call)(struct ast_node *,
                                         void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_SIGN_TYPE(node).params, data);
	ret |= call(AST_SIGN_TYPE(node).ret, data);
	return ret;
}

static int call_on_type_construct(int (*call)(struct ast_node *, void *),
		struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_CONSTRUCT_TYPE(node).id, data);
	ret |= call(AST_CONSTRUCT_TYPE(node).args, data);
	return ret;
}

static int call_on_type_pointer(int (*call)(struct ast_node *, void *),
		struct ast_node *node, void *data)
{
	return call(AST_PTR_TYPE(node).base, data);
}

static int call_on_type(int (*call)(struct ast_node *, void *),
		struct ast_node *node, void *data)
{
	int ret = 0;
	switch (AST_TYPE(node).kind) {
	case AST_TYPE_ENUM: break;
	case AST_TYPE_TRAIT: break;
	case AST_TYPE_ID: ret = call_on_type_id(call, node, data); break;
	case AST_TYPE_ARR: ret = call_on_type_arr(call, node, data); break;
	case AST_TYPE_STRUCT: break;
	case AST_TYPE_SIGN: ret = call_on_type_sign(call, node, data); break;
	case AST_TYPE_CONSTRUCT: ret = call_on_type_construct(call, node, data); break;
	case AST_TYPE_POINTER: ret = call_on_type_pointer(call, node, data); break;
	case AST_TYPE_PRIMITIVE: break;
	}

	return ret;
}

static int call_on_goto(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	return call(AST_GOTO(node).label, data);
}

static int call_on_label(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	return call(AST_LABEL(node).id, data);
}

static int call_on_binop(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_BINOP(node).left, data);
	ret |= call(AST_BINOP(node).right, data);
	return ret;
}

static int call_on_unop(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	return call(AST_UNOP(node).expr, data);
}

static int call_on_call(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_CALL(node).expr, data);
	ret |= call(AST_CALL(node).args, data);
	return ret;
}

static int call_on_macro_construct(int (*call)(struct ast_node *,
                                               void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(AST_MACRO_CONSTRUCT(node).id, data);
	ret |= call(AST_MACRO_CONSTRUCT(node).params, data);
	ret |= call(AST_MACRO_CONSTRUCT(node).body, data);
	return ret;
}

static int call_on_proc(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_proc.id, data);
	ret |= call(node->_proc.sign, data);
	ret |= call(node->_proc.body, data);
	return ret;
}

static int call_on_block(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	return call(node->_block.body, data);
}

static int call_on_fetch(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_fetch.id, data);
	ret |= call(node->_fetch.type, data);
	return ret;
}

static int call_on_macro_expand(int (*call)(struct ast_node *,
                                            void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_macro_expand.id, data);
	ret |= call(node->_macro_expand.args, data);
	return ret;
}

static int call_on_type_expand(int (*call)(struct ast_node *,
                                           void *), struct ast_node *type_expand, void *data)
{
	int ret = 0;
	ret |= call(AST_TYPE_EXPAND(type_expand).id, data);
	ret |= call(AST_TYPE_EXPAND(type_expand).args, data);
	return ret;
}

/* I guess this works, but it's not exactly optimal as the caller sort of has to
 * know when to continue to call on, and when it would cause an infinite loop.
 * I.e. a call on an ID that is forwarded results in an infinite loop.
 *
 * Maybe add in something like ast_continue_call_on() that can check for the
 * user if there's any point in continuing?
 */
int ast_call_on(int (*call)(struct ast_node *,
                            void *), struct ast_node *node, void *data)
{
	int ret = 0;
	if (!node)
		return ret;

	switch (node->node_type) {
	case AST_ARR_ACCESS:
	case AST_TYPE_EXPAND: ret = call_on_type_expand(call, node, data);
		break;
	case AST_FETCH: ret = call_on_fetch(call, node, data); break;
	case AST_ASSIGN: ret = call_on_assign(call, node, data); break;
	case AST_INIT: ret = call_on_init(call, node, data); break;
	case AST_SIZEOF: ret = call_on_sizeof(call, node, data); break;
	case AST_DOT: ret = call_on_dot(call, node, data); break;
	case AST_AS: ret = call_on_as(call, node, data); break;
	case AST_CAST: ret = call_on_cast(call, node, data); break;
	case AST_DEFER: ret = call_on_defer(call, node, data); break;
	case AST_VAR: ret = call_on_var(call, node, data); break;
	case AST_FOR: ret = call_on_for(call, node, data); break;
	case AST_WHILE: ret = call_on_while(call, node, data); break;
	case AST_RETURN: ret = call_on_return(call, node, data); break;
	case AST_ALIAS: ret = call_on_alias(call, node, data); break;
	case AST_TRAIT: ret = call_on_trait(call, node, data); break;
	case AST_IF: ret = call_on_if(call, node, data); break;
	case AST_ENUM: ret = call_on_enum(call, node, data); break;
	case AST_STRUCT: ret = call_on_struct(call, node, data); break;
	case AST_VAL: ret = call_on_val(call, node, data); break;
	case AST_SWITCH: ret = call_on_switch(call, node, data); break;
	case AST_CASE: ret = call_on_case(call, node, data); break;
	case AST_TYPE: ret = call_on_type(call, node, data); break;
	case AST_GOTO: ret = call_on_goto(call, node, data); break;
	case AST_LABEL: ret = call_on_label(call, node, data); break;
	case AST_BINOP: ret = call_on_binop(call, node, data); break;
	case AST_UNOP: ret = call_on_unop(call, node, data); break;
	case AST_CALL: ret = call_on_call(call, node, data); break;
	case AST_MACRO_CONSTRUCT: ret =
		call_on_macro_construct(call, node, data); break;
	case AST_MACRO_EXPAND: ret = call_on_macro_expand(call, node, data);
		break;
	case AST_PROC: ret = call_on_proc(call, node, data); break;
	case AST_BLOCK: ret = call_on_block(call, node, data); break;
	case AST_EMBED: break;
	case AST_CTRL: break;
	case AST_IMPORT: break;
	case AST_CONST: break;
	case AST_ID: break;
	case AST_EMPTY: break;
	}

	ret |= call(node->next, data);
	return ret;
}

size_t ast_list_len(struct ast_node *node)
{
	size_t count = 0;
	while (node) {
		count++;
		node = node->next;
	}

	return count;
}

struct ast_node *ast_last_node(struct ast_node *list)
{
	if (!list)
		return NULL;

	while (list->next)
		list = list->next;

	return list;
}

struct ast_node *ast_block_last(struct ast_node *block)
{
	struct ast_node *b = ast_last_node(block);
	if (b && b->node_type == AST_BLOCK)
		return ast_block_last(b->_block.body);

	return b;
}

int same_id(struct ast_node *id1, struct ast_node *id2)
{
	assert(id1->node_type == AST_ID);
	assert(id2->node_type == AST_ID);
	return equiv_nodes(id1, id2);
}

int equiv_nodes(struct ast_node *n1, struct ast_node *n2)
{
	if (n1->node_type != n2->node_type)
		return 0;

	switch (n1->node_type) {
		case AST_ID:
			if (strcmp(AST_ID(n1).id, AST_ID(n2).id) != 0)
				return 0;

			break;
		default:
			internal_error("unimplemented equivalency");
			return 0;
	}

	return 1;
}

int equiv_node_chains(struct ast_node *c1, struct ast_node *c2)
{
	if (c1 && !c2)
		return 0;
	if (!c1 && c2)
		return 0;

	if (!c1 && !c2)
		return 1;

	do {
		if (!equiv_nodes(c1, c2))
			return 0;

		c1 = c1->next;
		c2 = c2->next;

	} while (c1 && c2);

	return 1;
}

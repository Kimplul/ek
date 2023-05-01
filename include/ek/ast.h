/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef AST_H
#define AST_H

enum ast_binops {
	AST_ADD,
	AST_SUB,
	AST_MUL,
	AST_DIV,
	AST_REM,
	AST_XOR,
	AST_POW,
	AST_AND,
	AST_LAND,
	AST_OR,
	AST_LOR,
	AST_LSHIFT,
	AST_RSHIFT,
	AST_ASSIGN_ADD,
	AST_ASSIGN_SUB,
	AST_ASSIGN_MUL,
	AST_ASSIGN_DIV,
	AST_ASSIGN_REM,
	AST_ASSIGN_AND,
	AST_ASSIGN_OR,
	AST_ASSIGN_XOR,
	AST_ASSIGN_LSHIFT,
	AST_ASSIGN_RSHIFT,
	AST_LT,
	AST_GT,
	AST_LE,
	AST_GE,
	AST_NE,
	AST_EQ,
};

enum ast_unops {
	AST_NEG,
	AST_LNOT,
	AST_REF,
	AST_DEREF,
	AST_NOT
};

/* should this also have file name? Probably? */
struct src_loc {
	int first_line;
	int last_line;
	int first_col;
	int last_col;
};

enum ast_node_type {
	AST_BINOP = 1,
	AST_UNOP,
	AST_FETCH,
	AST_INIT,
	AST_ASSIGN,
	AST_CALL,
	AST_SIZEOF,
	AST_CAST,
	AST_DEFER,
	AST_MACRO,
	AST_LAST,
	AST_PROC,
	AST_GOTO,
	AST_LABEL,
	AST_VAR,
	AST_LAMBDA,
	AST_FOR,
	AST_EMBED,
	AST_DOT,
	AST_WHILE,
	AST_CTRL,
	AST_RETURN,
	AST_ALIAS,
	AST_TEMPLATE,
	AST_STRUCT,
	AST_IF,
	AST_TYPE,
	AST_BLOCK,
	AST_IMPORT,
	AST_ENUM,
	AST_UNION,
	AST_VAL,
	AST_SWITCH,
	AST_CASE,
	AST_CONST,
	AST_ID,
	AST_AS,
	AST_EMPTY,
};

enum ast_ctrl_kind {
	AST_CTRL_BREAK,
	AST_CTRL_CONTINUE
};

enum ast_const_kind {
	AST_CONST_INTEGER,
	AST_CONST_STRING,
	AST_CONST_FLOAT,
};

enum ast_type_kind {
	AST_TYPE_ID,
	AST_TYPE_ARR,
	AST_TYPE_TYPEOF,
	AST_TYPE_TEMPLATE,
	AST_TYPE_ALIAS,
	AST_TYPE_MEMBER,
	AST_TYPE_POINTER,
	AST_TYPE_UNION,
	AST_TYPE_LAMBDA,
	AST_TYPE_PROC,
	AST_TYPE_STRUCT,
	AST_TYPE_GENERIC,
	AST_TYPE_ENUM,
	AST_TYPE_SIGN,
};

enum ast_typedef_kind {
	AST_TYPEDEF_ALIAS,
	AST_TYPEDEF_TEMPLATE,
};

enum ast_flag {
	AST_FLAG_MUTABLE = (1 << 0),
	AST_FLAG_CONST = (1 << 1),
	AST_FLAG_EXTERN = (1 << 2),
	AST_FLAG_VARIADIC = (1 << 3),
	AST_FLAG_DELAYED = (1 << 4),
	AST_FLAG_PUBLIC = (1 << 5),
	/* Is untyped necessary? It's fairly easy to just look at the type of an
	 * expression... */
	AST_FLAG_UNTYPED = (1 << 6),
	AST_FLAG_FALLTHROUGH = (1 << 7),
	AST_FLAG_UNHYGIENIC = (1 << 8),
	AST_FLAG_ACTUAL = (1 << 9),
	AST_FLAG_INIT = (1 << 10),
	AST_FLAG_MEMBER = (1 << 11),
	AST_FLAG_SHARED = (1 << 12),
	AST_FLAG_GENERIC = (1 << 13),
};

struct ast_node;

struct ast_if {
	struct ast_node *cond;
	struct ast_node *body;
	struct ast_node *els;
};

struct ast_fetch {
	struct ast_node *id;
	struct ast_node *type;
};

struct ast_label {
	struct ast_node *id;
	struct ast_node *defers;
};

struct ast_goto {
	struct ast_node *label;
	struct ast_node *defers;
};

struct ast_alias {
	struct ast_node *id;
	struct ast_node *type;
};

struct template_implemented {
	struct ast_node *type;
	struct template_implemented *next;
};

/* should templates take decls or should it just be for structures? */
struct ast_template {
	struct ast_node *id;
	struct ast_node *body;

	struct template_implemented *impl_by;
};

struct ast_cast {
	struct ast_node *expr;
	struct ast_node *type;
};

struct ast_binop {
	enum ast_binops op;
	struct ast_node *left;
	struct ast_node *right;
};

struct ast_unop {
	enum ast_unops op;
	struct ast_node *expr;
};

struct ast_call {
	struct ast_node *id;
	struct ast_node *args;
};

struct ast_defer {
	struct ast_node *expr;
};

struct ast_macro {
	struct ast_node *id;
	struct ast_node *params;
	struct ast_node *body;
};

struct ast_proc {
	struct ast_node *id;
	struct ast_node *sign;
	struct ast_node *body;
};

struct ast_dot {
	struct ast_node *expr;
	struct ast_node *id;
};

struct ast_as {
	struct ast_node *type;
};

struct ast_sizeof {
	struct ast_node *expr;
};

struct ast_var {
	struct ast_node *id;
	struct ast_node *type;
	struct ast_node *init;
};

struct ast_lambda {
	struct ast_node *captures;
	struct ast_node *sign;
	struct ast_node *body;
};

struct ast_for {
	struct ast_node *pre;
	struct ast_node *cond;
	struct ast_node *post;
	struct ast_node *body;
};

struct ast_while {
	struct ast_node *cond;
	struct ast_node *body;
};

struct ast_ctrl {
	enum ast_ctrl_kind kind;
	struct ast_node *defers;
};

struct ast_return {
	struct ast_node *expr;
	struct ast_node *defers;
};

struct ast_type {
	enum ast_type_kind kind;
	struct ast_node *next;
	union {
		struct ast_node *id;

		struct {
			struct ast_node *size;
		} arr;

		struct {
			struct ast_node *expr;
			struct ast_node *actual;
		} typeo;

		struct {
			struct ast_node *id;
			struct ast_node *params;
			struct ast_node *ret;
		} proc;

		struct {
			struct ast_node *alias;
			struct ast_node *actual;
		} alias;

		struct {
			struct ast_node *id;
			struct ast_node *expr;
		} member;

		struct {
			struct ast_node *template;
			struct ast_node *actual;
		} template;

		struct {
			struct ast_node *params;
			struct ast_node *ret;
		} lambda;

		struct {
			struct ast_node *id;
			struct ast_node *args;
		} generic;

		struct {
			struct ast_node *id;
			struct ast_node *impls;
		} struc;

		struct {
			struct ast_node *id;
			struct ast_node *type;
		} enu;

		struct {
			struct ast_node *id;
			struct ast_node *impls;
		} unio;

		/* a signature can be either a procedure or a lambda, to be
		 * determined later. */
		struct {
			struct ast_node *params;
			struct ast_node *ret;
		} sign;

		struct {
			struct ast_node *id;
			struct ast_node *types;
		} impl;
	};
};

struct ast_block {
	struct ast_node *body;
	struct ast_node *defers;
};

struct ast_import {
	const char *file;
};

struct ast_embed {
	const char *file;
};

struct ast_paste {
	struct ast_node *id1;
	struct ast_node *id2;
};

struct ast_enum {
	struct ast_node *id;
	struct ast_node *type;
	struct ast_node *body;
};

struct ast_struct {
	struct ast_node *id;
	struct ast_node *generics;
	struct ast_node *body;
};

struct ast_union {
	struct ast_node *id;
	struct ast_node *generics;
	struct ast_node *body;
};

struct ast_val {
	struct ast_node *id;
	struct ast_node *val;
};

struct ast_switch {
	struct ast_node *cond;
	struct ast_node *cases;
};

struct ast_case {
	struct ast_node *cond;
	struct ast_node *body;
};

struct ast_const {
	enum ast_const_kind kind;
	union {
		long long integer;
		const char *str;
		double dbl;
	};
};

struct ast_init {
	struct ast_node *body;
};

struct ast_assign {
	struct ast_node *to;
	struct ast_node *from;
};

struct ast_id {
	const char *id;
};

struct ast_empty {
};

struct ast_node {
	enum ast_node_type node_type;
	enum ast_flag flags;
	struct ast_node *next;

	struct src_loc loc;

	/* scope ast node belongs to */
	struct scope *scope;
	/* type of ast node */
	struct ast_node *type;

	union {
		struct ast_binop _binop;
		struct ast_unop _unop;
		struct ast_call _call;
		struct ast_cast _cast;
		struct ast_macro _macro;
		struct ast_proc _proc;
		struct ast_goto _goto;
		struct ast_label _label;
		struct ast_var _var;
		struct ast_lambda _lambda;
		struct ast_if _if;
		struct ast_for _for;
		struct ast_while _while;
		struct ast_ctrl _ctrl;
		struct ast_defer _defer;
		struct ast_type _type;
		struct ast_dot _dot;
		struct ast_block _block;
		struct ast_import _import;
		struct ast_embed _embed;
		struct ast_return _return;
		struct ast_switch _switch;
		struct ast_paste _paste;
		struct ast_alias _alias;
		struct ast_template _template;
		struct ast_enum _enum;
		struct ast_struct _struct;
		struct ast_union _union;
		struct ast_val _val;
		struct ast_case _case;
		struct ast_const _const;
		struct ast_init _init;
		struct ast_assign _assign;
		struct ast_id _id;
		struct ast_as _as;
		struct ast_sizeof _sizeof;
		struct ast_fetch _fetch;
		struct ast_empty _empty;
	};
};

struct ast_node *gen_binop(enum ast_binops op,
                           struct ast_node *left, struct ast_node *right);

struct ast_node *gen_unop(enum ast_unops op, struct ast_node *expr);

struct ast_node *gen_call(struct ast_node *id, struct ast_node *args);

struct ast_node *gen_id(const char *id);

struct ast_node *gen_int(long long integer);
struct ast_node *gen_string(const char *str);
struct ast_node *gen_float(double dbl);

struct ast_node *gen_assign(struct ast_node *to, struct ast_node *from);
struct ast_node *gen_init(struct ast_node *body);

struct ast_node *gen_while(struct ast_node *cond, struct ast_node *body);

struct ast_node *gen_for(struct ast_node *pre, struct ast_node *cond,
                         struct ast_node *post, struct ast_node *body);

struct ast_node *gen_return(struct ast_node *expr);

struct ast_node *gen_ctrl(enum ast_ctrl_kind kind, struct src_loc loc);

struct ast_node *gen_macro(struct ast_node *id, struct ast_node *params,
                           struct ast_node *body);

struct ast_node *gen_if(struct ast_node *cond, struct ast_node *body,
                        struct ast_node *els);

struct ast_node *gen_switch(struct ast_node *cond, struct ast_node *cases);

struct ast_node *gen_case(struct ast_node *expr, struct ast_node *body);

struct ast_node *gen_type(enum ast_type_kind kind, struct ast_node *id,
                          struct ast_node *decl, struct ast_node *rets);

struct ast_node *gen_block(struct ast_node *body);

struct ast_node *gen_var(struct ast_node *id, struct ast_node *type,
                         struct ast_node *init);

struct ast_node *gen_lambda(struct ast_node *captures,
                            struct ast_node *type, struct ast_node * body);

struct ast_node *gen_proc(struct ast_node *id, struct ast_node *type,
                          struct ast_node *body);

struct ast_node *gen_dot(struct ast_node *expr, struct ast_node *id);

struct ast_node *gen_enum(struct ast_node *id, struct ast_node *type,
                          struct ast_node *body);

struct ast_node *gen_val(struct ast_node *id, struct ast_node *val);

struct ast_node *gen_alias(struct ast_node *id, struct ast_node *type);

struct ast_node *gen_template(struct ast_node *id, struct ast_node *body);

struct ast_node *gen_import(const char *file);

struct ast_node *gen_cast(struct ast_node *expr, struct ast_node *type);

struct ast_node *gen_embed(const char *file);

struct ast_node *gen_goto(struct ast_node *label);

struct ast_node *gen_label(struct ast_node *id);

struct ast_node *gen_defer(struct ast_node *expr);

struct ast_node *gen_as(struct ast_node *type);

struct ast_node *gen_sizeof(struct ast_node *expr);

struct ast_node *gen_struct(struct ast_node *id, struct ast_node *generics,
                            struct ast_node *body);

struct ast_node *gen_union(struct ast_node *id, struct ast_node *generics,
                           struct ast_node *body);

struct ast_node *gen_fetch(struct ast_node *id, struct ast_node *type);

/* might have to come up with a better name for this */
struct ast_node *gen_last();

struct ast_node *gen_empty();

struct ast_node *clone_ast_node(struct ast_node *node);
int identical_ast_nodes(int exact, struct ast_node *left,
                        struct ast_node *right);

void destroy_ast_node(struct ast_node *node);
void destroy_ast_tree(struct ast_node *root);

void dump_ast(int depth, struct ast_node *root);
void ast_append(struct ast_node *list, struct ast_node *elem);
void ast_set_flags(struct ast_node *node, enum ast_flag flags);
void ast_clear_flags(struct ast_node *node, enum ast_flag flags);
int ast_flags(struct ast_node *node, enum ast_flag flags);

int ast_call_on(int (*call)(struct ast_node *node, void *data),
                struct ast_node *node, void *data);

size_t ast_list_len(struct ast_node *list);
struct ast_node *ast_last_node(struct ast_node *node);
struct ast_node *ast_block_last(struct ast_node *node);

#endif /* AST_H */

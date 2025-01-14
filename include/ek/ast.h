/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef AST_H
#define AST_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @file ast.h
 *
 * Abstract syntax tree handling.
 */

#define NULL_LOC() ((struct src_loc){0, 0, 0, 0})

/** Represents a source location, spanning over some bit of code. */
struct src_loc {
	/** First line of interesting text. */
	int first_line;
	/** Last line of interesting text. */
	int last_line;
	/** First column in first line of interesting text. */
	int first_col;
	/** Last column in last line of interesting text. */
	int last_col;
};

/** Possible AST node types. We reserve node 0 as an illegal value. */
enum ast_kind {
	/** Fetch enum constant. */
	AST_FETCH = 1,
	/** Value initialization. */
	AST_INIT,
	/** Assignment. */
	AST_ASSIGN,
	/** Call procedure. */
	AST_CALL,
	AST_ARR,
	/** Sizeof. */
	AST_SIZEOF,
	/** Cast. */
	AST_CAST,
	/** Defer. */
	AST_DEFER,
	/** Macro definition. */
	AST_MACRO_DEF,
	AST_MACRO_EXPAND,
	AST_TYPE_EXPAND,
	/** Procedure definition. */
	AST_PROC_DEF,
	/** Goto. */
	AST_GOTO,
	/** Goto label. */
	AST_LABEL,
	/** Variable declaration/definition. */
	AST_VAR_DEF,
	/** For loop. */
	AST_FOR,
	/** Embed file contents. */
	AST_EMBED,
	/** Dot. \c a.b; */
	AST_DOT,
	/**
	 * While loop, both \c do and \c while.
	 * \c AST_DELAYED is active for \c do loops.
	 */
	AST_WHILE,
	AST_DO_WHILE,
	/** Control statement, \c break or \c continue. */
	AST_BREAK,
	AST_CONTINUE,
	/** Return. */
	AST_RETURN,
	/** Alias definition. */
	AST_ALIAS_DEF,
	/** More like trait. @todo really come up with consistent naming. */
	AST_TRAIT_DEF,
	/** Structure definition. */
	AST_STRUCT_DEF,
	/** Structure continuation, kind of like impl in Rust. */
	AST_STRUCT_CONT_DEF,
	/** If. */
	AST_IF,
	/** Block. E.g. \c {} */
	AST_BLOCK,
	/** Import. */
	AST_IMPORT,
	/** Enum definition. */
	AST_ENUM_DEF,
	/** Enum constant value. */
	AST_VAL,
	/** Switch. */
	AST_SWITCH,
	/** Switch case. */
	AST_CASE,
	/** Any ID, variable or whatever. */
	AST_ID,
	/** As statement, used to determine types. */
	AST_AS,
	/** Empty. Essentially noop. */
	AST_EMPTY,
	/** Add, \c + */
	AST_ADD,
	/** Subtract, \c - */
	AST_SUB,
	/** Multiply, \ * */
	AST_MUL,
	/** Divide, \c \ */
	AST_DIV,
	/** Remainder, \c % */
	AST_REM,
	/** Logical and, \c && */
	AST_LAND,
	/** Logical or, \c ||*/
	AST_LOR,
	/** Left shift (logical), \c << @todo add arithmetic shifts? */
	AST_LSHIFT,
	/** Right shift (logical), \c >> */
	AST_RSHIFT,
	/** Assigning add, \c += */
	AST_ASSIGN_ADD,
	/** Assigning subtraction, \c -= */
	AST_ASSIGN_SUB,
	/** Assigning multiplication, \c *= */
	AST_ASSIGN_MUL,
	/** Assigning division, \c /= */
	AST_ASSIGN_DIV,
	/** Assigning remainder, \c %= */
	AST_ASSIGN_REM,
	/** Assigning logical left shift, \c >>= */
	AST_ASSIGN_LSHIFT,
	/** Assigning logical right shift, \c <<= */
	AST_ASSIGN_RSHIFT,
	/** Less than, \c < */
	AST_LT,
	/** Greater than, \c > */
	AST_GT,
	/** Less than or equal, \c <= */
	AST_LE,
	/** Greater than or equal, \c >= */
	AST_GE,
	/** Not equal, \c != */
	AST_NE,
	/** Equal, \c == */
	AST_EQ,
	/** Negation, \c - */
	AST_NEG,
	/** Logical negation, \c ! */
	AST_LNOT,
	AST_NOT,
	/** Referencing, \c & */
	AST_REF,
	/** Dereferencing, \c ' */
	AST_DEREF,
	AST_CONST_INT,
	AST_CONST_CHAR,
	AST_CONST_BOOL,
	AST_CONST_STR,
	AST_UNPACK,
};

/** Flags an AST node can have. */
enum ast_flags {
	/** Node is mutable. Mostly used for variables. */
	AST_FLAG_MUTABLE = (1 << 0),
	/** Value is constant. Constant if, for, etc. */
	AST_FLAG_CONST = (1 << 1),
	/** External definition. Disables generic support. */
	AST_FLAG_EXTERN = (1 << 2),
	/** Variadic macros. */
	AST_FLAG_VARIADIC = (1 << 3),
	/** Public node, should be propagated to parent scopes. */
	AST_FLAG_PUBLIC = (1 << 5),
	/**
	 * Untyped node.
	 * @todo Is untyped necessary? It's fairly easy to just look at the type of an
	 * expression...
	 */
	AST_FLAG_UNTYPED = (1 << 6),
	/** Switch case should fall through. */
	AST_FLAG_FALLTHROUGH = (1 << 7),
	/** Block is unhygienic. */
	AST_FLAG_UNHYGIENIC = (1 << 8),
	/** Node has been actualized, types expanded etc. */
	AST_FLAG_ACTUAL = (1 << 9),
	/** Actualization has been initialized. Used to detect type loops. */
	AST_FLAG_INIT = (1 << 10),
	/** Whether a struct/union initialization is index or name based. */
	AST_FLAG_MEMBER = (1 << 11),
	/** Struct/union is generic. */
	AST_FLAG_NOMANGLE = (1 << 14),
	AST_FLAG_DOEXPR = (1 << 15),
	AST_FLAG_LOWERED = (1 << 16),
};

struct ast;

enum type_kind {
	TYPE_VOID = 1, TYPE_BOOL, TYPE_I9, TYPE_I27, TYPE_STR, TYPE_PTR,
	TYPE_ID, TYPE_CONSTRUCT, TYPE_STRUCT, TYPE_ENUM, TYPE_CALLABLE,
	TYPE_TRAIT,
};

struct compound_entry {
	struct ast *def;
	struct type *type;
};

#define MAP_KEY char *
#define MAP_TYPE struct compound_entry
#define MAP_CMP(a, b) strcmp((a), (b))
#define MAP_NAME compound_map
#include "map.h"

#define SPTREE_TYPE char *
#define SPTREE_CMP(a, b) strcmp((a), (b))
#define SPTREE_NAME trait_set
#include "sptree.h"

struct compound_type {
	enum type_kind k;
	struct ast *def;
	struct compound_map map;
	struct trait_set set;
};

struct type {
	enum type_kind k;

	/* arg */
	struct type *t0;
	struct type *t1;

	/* struct members etc */
	struct compound_type *d;

	/* id */
	char *id;
	/* next */
	struct type *n;

	long long size;
	struct src_loc loc;
	struct scope *scope;
};

struct ast {
	enum ast_kind k;
	struct type *t;
	long long v;
	char *s;
	struct ast *a0;
	struct ast *a1;
	struct ast *a2;
	struct ast *a3;
	struct type *t2;
	enum ast_flags f;

	struct ast *n;
	struct ast *chain;
	struct src_loc loc;
	struct scope *scope;
};

struct ast *gen_ast(enum ast_kind kind,
                    struct ast *a0,
                    struct ast *a1,
                    struct ast *a2,
                    struct ast *a3,
                    struct type *t1,
                    char *s,
                    long long v,
                    struct src_loc loc);

struct type *tgen_type(enum type_kind kind,
                       struct type *t0,
                       struct type *t1,
                       struct ast *d,
                       struct ast *a,
                       char *id,
                       struct src_loc loc);

size_t align3k(size_t o);
size_t type_size(struct type *t);
size_t type_offsetof(struct type *t, char *m);

#define tgen_primitive(kind, id, def, loc) \
	tgen_type(kind, NULL, NULL, def, NULL, id, loc)

#define tgen_id(id, loc) \
	tgen_type(TYPE_ID, NULL, NULL, NULL, NULL, id, loc)

#define tgen_struct(id, def, loc) \
	tgen_type(TYPE_STRUCT, NULL, NULL, def, NULL, id, loc)

#define tgen_trait(id, def, loc) \
	tgen_type(TYPE_TRAIT, NULL, NULL, def, NULL, id, loc)

#define tgen_enum(id, def, loc) \
	tgen_type(TYPE_ENUM, NULL, NULL, def, NULL, id, loc)

static inline bool is_binop(struct ast *x)
{
	switch (x->k) {
	case AST_ADD:
	case AST_SUB:
	case AST_MUL:
	case AST_DIV:
	case AST_REM:
	case AST_LSHIFT:
	case AST_RSHIFT:
		return true;
	default:
		break;
	};

	return false;
}

static inline bool is_opassign(struct ast *x)
{
	switch (x->k) {
	case AST_ASSIGN_ADD:
	case AST_ASSIGN_SUB:
	case AST_ASSIGN_MUL:
	case AST_ASSIGN_DIV:
	case AST_ASSIGN_REM:
	case AST_ASSIGN_LSHIFT:
	case AST_ASSIGN_RSHIFT:
		return true;
	default:
		break;
	};
	return false;
}

static inline bool is_unop(struct ast *x)
{
	switch (x->k) {
	case AST_REF:
	case AST_DEREF:
	case AST_NOT:
	case AST_NEG:
		return true;
	default:
		break;
	}

	return false;
}

static inline bool is_comparison(struct ast *x)
{
	switch (x->k) {
	case AST_LT:
	case AST_GT:
	case AST_LE:
	case AST_GE:
	case AST_NE:
	case AST_EQ:
		return true;
	default:
		break;
	}

	return false;
}

static inline bool is_const(struct ast *x)
{
	/* note that const strings are sort of their own entity */
	switch (x->k) {
	case AST_CONST_INT:
	case AST_CONST_CHAR:
	case AST_CONST_BOOL:
		return true;
	default:
		break;
	}

	return false;
}

static inline bool is_primitive(struct type *t)
{
	switch (t->k) {
	case TYPE_I27:
	case TYPE_I9:
	case TYPE_BOOL:
	case TYPE_PTR:
		return true;
	default:
		break;
	}

	return false;
}

#define gen_str_type1(k, s, t, a, loc) gen_ast(k, a, NULL, NULL, NULL, t, s, -1, \
					       loc)
#define gen_str_type(k, s, t, loc) gen_str_type1(k, s, t, NULL, loc)
#define gen_type(k, a, type, loc) gen_ast(k, a, NULL, NULL, NULL, type, NULL, \
					  -1,                                 \
					  loc)
#define gen_str3(k, s, a, b, c, loc) gen_ast(k, a, b, c, NULL, NULL, s, -1, loc)
#define gen_str2(k, s, a, b, loc) gen_str3(k, s, a, b, NULL, loc)
#define gen_str1(k, s, a, loc) gen_str2(k, s, a, NULL, loc)
#define gen_str(k, s, loc) gen_ast(k, NULL, NULL, NULL, NULL, NULL, s, -1, loc)


#define gen4(k, a, b, c, d, loc) gen_ast(k, a, b, c, d, NULL, NULL, -1, loc)
#define gen3(k, a, b, c, loc) gen4(k, a, b, c, NULL, loc)
#define gen2(k, a, b, loc) gen3(k, a, b, NULL, loc)
#define gen1(k, a, loc) gen2(k, a, NULL, loc)

#define tgen2(k, a, b, loc) tgen_type(k, a, b, NULL, NULL, NULL, loc)
#define tgen1(k, a, loc) tgen2(k, a, NULL, loc)

#define tgen_str1(k, s, a, loc) tgen_type(k, a, NULL, NULL, NULL, s, loc)

/* kind of hacky but I guess it works, and allows us to check that the type is
 * correct every time */
#define return_s(x, kind) *({assert((x)->k == kind); &(x)->s;})
#define return_a0(x, kind) *({assert((x)->k == kind); &(x)->a0;})
#define return_a1(x, kind) *({assert((x)->k == kind); &(x)->a1;})
#define return_a2(x, kind) *({assert((x)->k == kind); &(x)->a2;})
#define return_a3(x, kind) *({assert((x)->k == kind); &(x)->a3;})

#define return_id(x, kind) *({assert((x)->k == kind); &(x)->id;})
#define return_t0(x, kind) *({assert((x)->k == kind); &(x)->t0;})
#define return_t1(x, kind) *({assert((x)->k == kind); &(x)->t1;})
/* note that this one is in ast, the other two are in type */
#define return_t2(x, kind) *({assert((x)->k == kind); &(x)->t2;})

#define if_cond(x) return_a0(x, AST_IF)
#define if_body(x) return_a1(x, AST_IF)
#define if_else(x) return_a2(x, AST_IF)
#define gen_if(cond, body, els, loc) \
	gen3(AST_IF, cond, body, els, loc)

#define fetch_id(x) return_s(x, AST_FETCH)
#define fetch_type(x) return_t2(x, AST_FETCH)
#define gen_fetch(id, type, loc) \
	gen_str_type(AST_FETCH, id, type, loc)

#define label_id(x) return_s(x, AST_LABEL)
#define label_defers(x) return_a0(x, AST_LABEL)
#define gen_label(id, defers, loc) \
	gen_str1(AST_LABEL, id, defers, loc)

#define arr_base(x) return_a0(x, AST_ARR)
#define arr_idx(x) return_a1(x, AST_ARR)
#define gen_arr(base, idx, loc) \
	gen2(AST_ARR, base, idx, loc)

#define goto_label(x) return_s(x, AST_GOTO)
#define goto_defers(x) return_a0(x, AST_GOTO)
#define goto_label_ref(x) return_a1(x, AST_GOTO)
#define gen_goto(label, defers, loc) \
	gen_str1(AST_GOTO, label, defers, loc)

#define alias_id(x) return_s(x, AST_ALIAS_DEF)
#define alias_type(x) return_t2(x, AST_ALIAS_DEF)
#define gen_alias(id, type, loc) \
	gen_str_type(AST_ALIAS_DEF, id, type, loc)

#define trait_id(x) return_s(x, AST_TRAIT_DEF)
#define trait_params(x) return_a0(x, AST_TRAIT_DEF)
#define trait_raw_body(x) return_a1(x, AST_TRAIT_DEF)
#define trait_body(x) return_a2(x, AST_TRAIT_DEF)
#define gen_trait(id, params, body, loc) \
	gen_str2(AST_TRAIT_DEF, id, params, body, loc)

#define cast_expr(x) return_a0(x, AST_CAST)
#define cast_type(x) return_t2(x, AST_CAST)
#define gen_cast(expr, type, loc) \
	gen_type(AST_CAST, expr, type, loc)

#define opassign_left(x) ({assert(is_opassign(x)); x->a0;})
#define opassign_right(x) ({assert(is_opassign(x)); x->a1;})
#define gen_opassign(op, left, right, loc) \
	gen2(op, left, right, loc)

#define binop_left(x) ({assert(is_binop(x)); x->a0;})
#define binop_right(x) ({assert(is_binop(x)); x->a1;})
#define gen_binop(op, left, right, loc) \
	gen2(op, left, right, loc)

#define comparison_left(x) ({assert(is_comparison(x)); x->a0;})
#define comparison_right(x) ({assert(is_comparison(x)); x->a1;})
#define gen_comparison(op, left, right, loc) \
	gen2(op, left, right, loc)

#define unop_expr(x) ({assert(is_unop(x)); x->a0;})
#define gen_unop(op, expr, loc) \
	gen1(op, expr, loc)

#define call_expr(x) return_a0(x, AST_CALL)
#define call_args(x) return_a1(x, AST_CALL)
#define gen_call(expr, args, loc) \
	gen2(AST_CALL, expr, args, loc)

#define defer_expr(x) return_a0(x, AST_DEFER)
#define gen_defer(expr, loc) \
	gen1(AST_DEFER, expr, loc)

#define macro_def_id(x) return_s(x, AST_MACRO_DEF)
#define macro_def_params(x) return_a0(x, AST_MACRO_DEF)
#define macro_def_body(x) return_a1(x, AST_MACRO_DEF)
#define gen_macro_def(id, params, body, loc) \
	gen_str2(AST_MACRO_DEF, id, params, body, loc)

#define macro_expand_id(x) return_s(x, AST_MACRO_EXPAND)
#define macro_expand_args(x) return_a0(x, AST_MACRO_EXPAND)
#define gen_macro_expand(id, args, loc) \
	gen_str1(AST_MACRO_EXPAND, id, args, loc)

#define type_expand_id(x) return_s(x, AST_TYPE_EXPAND)
#define type_expand_args(x) return_t2(x, AST_TYPE_EXPAND)
#define gen_type_expand(id, args, loc) \
	gen_str_type(AST_TYPE_EXPAND, id, args, loc)

#define proc_id(x) return_s(x, AST_PROC_DEF)
#define proc_params(x) return_a0(x, AST_PROC_DEF)
#define proc_rtype(x) return_t2(x, AST_PROC_DEF)
#define proc_body(x) return_a1(x, AST_PROC_DEF)
#define gen_proc(id, params, rtype, body, loc) \
	gen_ast(AST_PROC_DEF, params, body, NULL, NULL, rtype, id, 0, loc)

#define dot_id(x) return_s(x, AST_DOT)
#define dot_expr(x) return_a0(x, AST_DOT)
#define gen_dot(id, expr, loc) \
	gen_str1(AST_DOT, id, expr, loc)

#define as_type(x) return_t2(x, AST_AS)
#define gen_as(type, loc) \
	gen_type(NULL, type, loc)

#define sizeof_expr(x) return_a0(x, AST_SIZEOF)
#define gen_sizeof(expr, loc) \
	gen1(AST_SIZEOF, expr, loc)

#define var_id(x) return_s(x, AST_VAR_DEF)
#define var_type(x) return_t2(x, AST_VAR_DEF)
#define var_init(x) return_a0(x, AST_VAR_DEF)
#define gen_var(id, type, init, loc) \
	gen_ast(AST_VAR_DEF, init, NULL, NULL, NULL, type, id, 1, loc)

#define for_pre(x) return_a0(x, AST_FOR)
#define for_cond(x) return_a1(x, AST_FOR)
#define for_post(x) return_a2(x, AST_FOR)
#define for_body(x) return_a3(x, AST_FOR)
#define gen_for(pre, cond, post, body, loc) \
	gen4(AST_FOR, pre, cond, post, body, loc)

#define while_cond(x) return_a0(x, AST_WHILE)
#define while_body(x) return_a1(x, AST_WHILE)
#define gen_while(cond, body, loc) \
	gen2(AST_WHILE, cond, body, loc)

#define do_while_cond(x) return_a0(x, AST_DO_WHILE)
#define do_while_body(x) return_a1(x, AST_DO_WHILE)
#define gen_do_while(cond, body, loc) \
	gen2(AST_DO_WHILE, cond, body, loc)

#define continue_defers(x) return_a0(x, AST_CONTINUE)
#define gen_continue(defers, loc) \
	gen1(AST_CONTINUE, defers, loc)

#define break_defers(x) return_a0(x, AST_BREAK)
#define gen_break(defers, loc) \
	gen1(AST_BREAK, defers, loc)

#define return_expr(x) return_a0(x, AST_RETURN)
#define return_defers(x) return_a1(x, AST_RETURN)
#define gen_return(expr, defers, loc) \
	gen2(AST_RETURN, expr, defers, loc)

#define block_body(x) return_a0(x, AST_BLOCK)
#define block_defers(x) return_a1(x, AST_BLOCK)
#define gen_block(body, defers, loc) \
	gen2(AST_BLOCK, body, defers, loc)

#define import_file(x) return_s(x, AST_IMPORT)
#define gen_import(f, loc) \
	gen_str(AST_IMPORT, f, loc)

#define embed_file(x) return_s(x, AST_EMBED)
#define gen_embed(f, loc) \
	gen_str(AST_EMBED, f, loc)

#define enum_id(x) return_s(x, AST_ENUM_DEF)
#define enum_type(x) return_t2(x, AST_ENUM_DEF)
#define enum_body(x) return_a0(x, AST_ENUM_DEF)
#define gen_enum(id, type, body, loc) \
	gen_ast(AST_ENUM_DEF, body, NULL, NULL, NULL, type, id, 0, loc)

#define struct_id(x) return_s(x, AST_STRUCT_DEF)
#define struct_params(x) return_a0(x, AST_STRUCT_DEF)
#define struct_body(x) return_a1(x, AST_STRUCT_DEF)
#define gen_struct(id, params, body, loc) \
	gen_str2(AST_STRUCT_DEF, id, params, body, loc)

#define struct_cont_id(x) return_s(x, AST_STRUCT_CONT_DEF)
#define struct_cont_params(x) return_a0(x, AST_STRUCT_CONT_DEF)
#define struct_cont_body(x) return_a1(x, AST_STRUCT_CONT_DEF)
#define gen_struct_cont(id, params, body, loc)                              \
	gen_ast(AST_STRUCT_CONT_DEF, params, body, NULL, NULL, NULL, id, 0, \
		loc)

#define val_id(x) return_s(x, AST_VAL)
#define val_val(x) return_a0(x, AST_VAL)
#define gen_val(id, val, loc) \
	gen_str1(AST_VAL, id, val, loc)

#define switch_cond(x) return_a0(x, AST_SWITCH)
#define switch_cases(x) return_a1(x, AST_SWITCH)
#define gen_switch(cond, cases, loc) \
	gen2(AST_SWITCH, cond, cases, loc)

#define case_cond(x) return_a0(x, AST_CASE)
#define case_body(x) return_a1(x, AST_CASE)
#define gen_case(cond, body, loc) \
	gen2(AST_CASE, cond, body, loc)

#define str_val(x) return_s(x, AST_CONST_STR)
#define gen_const_str(s, loc) \
	gen_ast(AST_CONST_STR, NULL, NULL, NULL, NULL, NULL, s, 0, loc)

#define int_val(x) *({assert(x->k == AST_CONST_INT); &x->v;})
#define gen_const_int(i, loc) \
	gen_ast(AST_CONST_INT, NULL, NULL, NULL, NULL, NULL, NULL, i, loc)

#define char_val(x) *({assert(x->k == AST_CONST_CHAR); &x->v;})
#define gen_const_char(i, loc) \
	gen_ast(AST_CONST_CHAR, NULL, NULL, NULL, NULL, NULL, NULL, i, loc)

#define bool_val(x) *({assert(x->k == AST_CONST_CHAR); &x->v;})
#define gen_const_bool(i, loc) \
	gen_ast(AST_CONST_BOOL, NULL, NULL, NULL, NULL, NULL, NULL, i, loc)

#define init_args(x) return_t2(x, AST_INIT)
#define init_body(x) return_a0(x, AST_INIT)
#define init_id(x) return_s(x, AST_INIT)
#define gen_init(id, targs, body, loc) \
	gen_str_type1(AST_INIT, id, targs, body, loc)

#define assign_to(x) return_a0(x, AST_ASSIGN)
#define assign_from(x) return_a1(x, AST_ASSIGN)
#define gen_assign(from, to, loc) \
	gen2(AST_ASSIGN, from, to, loc)

#define id_str(x) return_s(x, AST_ID)
#define gen_id(id, loc) \
	gen_str(AST_ID, id, loc)

#define gen_unpack(id, loc) \
	gen_str(AST_UNPACK, id, loc)

#define gen_empty(loc) \
	gen1(AST_EMPTY, NULL, loc)

/* types */
#define callable_ptypes(x) return_t0(x, TYPE_CALLABLE)
#define callable_rtype(x) return_t1(x, TYPE_CALLABLE)
#define tgen_callable(ptypes, rtype, loc) \
	tgen2(TYPE_CALLABLE, ptypes, rtype, loc)

#define ptr_base(x) return_t0(x, TYPE_PTR)
#define tgen_ptr(base, loc) \
	tgen1(TYPE_PTR, base, loc)

#define construct_id(x) return_id(x, TYPE_CONSTRUCT)
#define construct_atypes(x) return_t0(x, TYPE_CONSTRUCT)
#define tgen_construct(id, atypes, loc) \
	tgen_str1(TYPE_CONSTRUCT, id, atypes, loc)

#define tstruct_params(x) return_t0(x, TYPE_STRUCT)
#define ttrait_params(x) return_t0(x, TYPE_TRAIT)

struct ast *clone_ast(struct ast *n);
struct ast *clone_ast_list(struct ast *l);

struct type *clone_type(struct type *n);
struct type *clone_type_list(struct type *l);

#if defined(DEBUG)
void ast_dump_list(int depth, struct ast *root);
void ast_dump(int depth, struct ast *node);

void type_dump_list(struct type *root);
void type_dump(struct type *node);
#else
#define ast_dump_list(depth, root)
#define ast_dump(depth, root)

#define type_dump_list(root)
#define type_dump(root)
#endif /* DEBUG */

void ast_append(struct ast **list, struct ast *elem);
void type_append(struct type **list, struct type *elem);

struct ast *ast_prepend(struct ast *list, struct ast *elem);
struct type *type_prepend(struct type *list, struct type *elem);

void ast_set_flags(struct ast *node, enum ast_flags flags);
void ast_clear_flags(struct ast *node, enum ast_flags flags);
unsigned ast_flags(struct ast *node, enum ast_flags flags);

typedef int (*ast_callback_t)(struct ast *, void *);
typedef int (*type_callback_t)(struct type *, void *);
int ast_visit(ast_callback_t before, ast_callback_t after, struct ast *node,
              void *data);
int ast_visit_list(ast_callback_t before, ast_callback_t after,
                   struct ast *node, void *data);

int type_visit(type_callback_t before, type_callback_t after, struct type *node,
               void *data);
int type_visit_list(type_callback_t before, type_callback_t after,
                    struct type *node, void *data);

/**
 * Number of elements in AST list.
 *
 * @param list List whose elements to count.
 * @return Number of elements in \p list.
 */
size_t ast_list_len(struct ast *list);
size_t type_list_len(struct type *list);

/**
 * Get last nose in ASt list.
 *
 * @param list List whose last element to get.
 * @return Last node in \p list.
 */
struct ast *ast_last(struct ast *list);

/**
 * Get last element in block.
 *
 * @param block Block whose last element to get.
 * @return Last node in block.
 */
struct ast *ast_block_last(struct ast *block);

void destroy_allocs();
const char *primitive_str(struct type *kind);

int same_id(char *id1, char *id2);
int equiv_nodes(struct ast *n1, struct ast *n2);
int equiv_node_lists(struct ast *c1, struct ast *c2);

int equiv_types(struct type *t1, struct type *t2);
int equiv_type_lists(struct type *t1, struct type *t2);

struct ast *reverse_ast_list(struct ast *root);
struct type *reverse_type_list(struct type *root);

#define foreach_node(iter, nodes) \
	for (struct ast *iter = nodes; iter; iter = iter->n)

#define foreach_type(iter, nodes) \
	for (struct type *iter = nodes; iter; iter = iter->n)

struct ast *chain_base(struct ast *node);
int type_cmp(struct type *a, struct type *b);

#endif /* AST_H */

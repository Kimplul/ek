/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef AST_H
#define AST_H

#include <stddef.h>

/**
 * @file ast.h
 *
 * Abstract syntax tree handling.
 */

#define AST_ID(x) x->_id
#define AST_AS(x) x->_as
#define AST_DOT(x) x->_dot
#define AST_UNOP(x) x->_unop
#define AST_IMPORT(x) x->_import
#define AST_ALIAS(x) x->_alias
#define AST_TRAIT(x) x->_trait
#define AST_CAST(x) x->_cast
#define AST_PROC(x) x->_proc
#define AST_VAR(x) x->_var
#define AST_RETURN(x) x->_return
#define AST_STRUCT(x) x->_struct
#define AST_ENUM(x) x->_enum
#define AST_CALL(x) x->_call
#define AST_CONST(x) x->_const
#define AST_ASSIGN(x) x->_assign
#define AST_BLOCK(x) x->_block
#define AST_ARR_ACCESS(x) x->_arr_access
#define AST_MACRO_CONSTRUCT(x) x->_macro_construct
#define AST_MACRO_EXPAND(x) x->_macro_expand
#define AST_TYPE_EXPAND(x) x->_type_expand
#define AST_IF(x) x->_if
#define AST_CASE(x) x->_case
#define AST_SWITCH(x) x->_switch
#define AST_VAL(x) x->_val
#define AST_EMBED(x) x->_embed
#define AST_CTRL(x) x->_ctrl
#define AST_WHILE(x) x->_while
#define AST_FOR(x) x->_for
#define AST_DEFER(x) x->_defer
#define AST_BINOP(x) x->_binop
#define AST_LABEL(x) x->_label
#define AST_GOTO(x) x->_goto
#define AST_INIT(x) x->_init
#define AST_SIZEOF(x) x->_sizeof
#define AST_FETCH(x) x->_fetch

#define AST_TYPE(x) x->_type
#define AST_ID_TYPE(x) x->_type._id
#define AST_CONSTRUCT_TYPE(x) x->_type._construct
#define AST_TRAIT_TYPE(x) x->_type._trait
/** @todo is sign and proc type the same ? */
#define AST_PROC_TYPE(x) x->_type._proc
#define AST_ARR_TYPE(x) x->_type._arr
#define AST_SIGN_TYPE(x) x->_type._sign
#define AST_ENUM_TYPE(x) x->_type._enum
#define AST_UNION_TYPE(x) x->_type._union
#define AST_STRUCT_TYPE(x) x->_type._struct
/* might rename primitive to something else */
#define AST_PRIMITIVE_TYPE(x) x->_type._primitive
#define AST_PTR_TYPE(x) x->_type._ptr

/** Binary operands, that is they take two arguments and produce a result. */
enum ast_binops {
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
};

/** Unary operations, that is they take one argument and produce a result. */
enum ast_unops {
	/** Negation, \c - */
	AST_NEG,
	/** Logical negation, \c ! */
	AST_LNOT,
	/** Referencing, \c & */
	AST_REF,
	/** Dereferencing, \c ' */
	AST_DEREF,
};

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
enum ast_node_type {
	/** Binary operation. */
	AST_BINOP = 1,
	/** Unary operation. */
	AST_UNOP,
	/** Fetch enum constant. */
	AST_FETCH,
	/** Value initialization. */
	AST_INIT,
	/** Assignment. */
	AST_ASSIGN,
	/** Call procedure. */
	AST_CALL,
	AST_ARR_ACCESS,
	/** Sizeof. */
	AST_SIZEOF,
	/** Cast. */
	AST_CAST,
	/** Defer. */
	AST_DEFER,
	/** Macro definition. */
	AST_MACRO_CONSTRUCT,
	AST_MACRO_EXPAND,
	AST_TYPE_EXPAND,
	/** Procedure definition. */
	AST_PROC,
	/** Goto. */
	AST_GOTO,
	/** Goto label. */
	AST_LABEL,
	/** Variable declaration/definition. */
	AST_VAR,
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
	/** Control statement, \c break or \c continue. */
	AST_CTRL,
	/** Return. */
	AST_RETURN,
	/** Alias definition. */
	AST_ALIAS,
	/** More like trait. @todo really come up with consistent naming. */
	AST_TRAIT,
	/** Structure definition. */
	AST_STRUCT,
	/** If. */
	AST_IF,
	/** Special 'meta' node that represents a type. */
	AST_TYPE,
	/** Block. E.g. \c {} */
	AST_BLOCK,
	/** Import. */
	AST_IMPORT,
	/** Enum definition. */
	AST_ENUM,
	/** Enum constant value. */
	AST_VAL,
	/** Switch. */
	AST_SWITCH,
	/** Switch case. */
	AST_CASE,
	/** Constant value. */
	AST_CONST,
	/** Any ID, variable or whatever. */
	AST_ID,
	/** As statement, used to determine types. */
	AST_AS,
	/** Empty. Essentially noop. */
	AST_EMPTY,
};

/** Whether \c AST_CTRL is break or continue. */
enum ast_ctrl_kind {
	/** Break. */
	AST_CTRL_BREAK,
	/** Continue. */
	AST_CTRL_CONTINUE
};

/** Constant value kind. */
enum ast_const_kind {
	/** Integer, i27 */
	AST_CONST_INTEGER,
	/** String. */
	AST_CONST_STRING,
};

/** Type representation. */
enum ast_type_kind {
	/** ID, can refer to pretty much anything. */
	AST_TYPE_ID,
	AST_TYPE_PRIMITIVE,
	/** Array. */
	AST_TYPE_ARR,
	AST_TYPE_CONSTRUCT,
	/** Trait. */
	AST_TYPE_TRAIT,
	/** Pointer to a type. */
	AST_TYPE_POINTER,
	/** Structure. */
	AST_TYPE_STRUCT,
	/** Enum. */
	AST_TYPE_ENUM,
	/** Signature, i.e. procedure signature. */
	AST_TYPE_SIGN,
};

/** Whether typedef makes an alias on trait. */
enum ast_typedef_kind {
	/** Alias. */
	AST_TYPEDEF_ALIAS,
	/** Trait. */
	AST_TYPEDEF_TRAIT,
};

/** Flags an AST node can have. */
enum ast_flag {
	/** Node is mutable. Mostly used for variables. */
	AST_FLAG_MUTABLE = (1 << 0),
	/** Value is constant. Constant if, for, etc. */
	AST_FLAG_CONST = (1 << 1),
	/** External definition. Disables generic support. */
	AST_FLAG_EXTERN = (1 << 2),
	/** Variadic procedures and macros. */
	AST_FLAG_VARIADIC = (1 << 3),
	/** Delayed execution. Mainly \c do loops. */
	AST_FLAG_DELAYED = (1 << 4),
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
	/** AST node has several owners, requires special destruction handling. */
	AST_FLAG_SHARED = (1 << 12),
	/** Struct/union is generic. */
	AST_FLAG_GENERIC = (1 << 13),
};

struct ast_node;

/**
 * AST if node.
 *
 * \verbatim
 * if cond {body} [els]
 * \endverbatim
 */
struct ast_if {
	/** Conditional block. */
	struct ast_node *cond;
	/** Body. */
	struct ast_node *body;
	/** Else block. */
	struct ast_node *els;
};

/** AST fetch enum member node. */
struct ast_fetch {
	/** Name of member to fetch. */
	struct ast_node *id;
	/** Enum type to fetch from. */
	struct ast_node *type;
};

/** Goto label. */
struct ast_label {
	/** Label name. */
	struct ast_node *id;
	/**
	 * List of active defers.
	 * Used to determine which defer statements should be executed
	 * when a goto jumps to this label.
	 */
	struct ast_node *defers;
};

struct ast_arr_access {
	struct ast_node *base;
	struct ast_node *idx;
};

/** Goto node. */
struct ast_goto {
	/** Name of label to jump to. */
	struct ast_node *label;
	/**
	 * List of active defers.
	 * With the list in the corresponding label, we can detect which
	 * defers should be triggered and which ones shouldn't.
	 * See actualize_goto_defers().
	 */
	struct ast_node *defers;
};

/** Alias definition. */
struct ast_alias {
	/** Name of alias. */
	struct ast_node *id;
	/** Type to alias. */
	struct ast_node *type;
};

/** List of types that implements the template list belongs to. */
struct trait_implemented {
	/** A type that implements the template. */
	struct ast_node *type;
	/** Next type that implements the template. */
	struct trait_implemented *next;
};

/** A trait definition. */
struct ast_trait {
	/** Name of trait. */
	struct ast_node *id;
	/** Parameters to construct concrete type from trait. */
	struct ast_node *params;
	/** Raw body before expansion. */
	struct ast_node *raw_body;
	/** Body of trait. */
	struct ast_node *body;
};

/** Cast. */
struct ast_cast {
	/** Expression. */
	struct ast_node *expr;
	/** Type to cast expression result to. */
	struct ast_node *type;
};

/** Binary operation. */
struct ast_binop {
	/** Which operation. */
	enum ast_binops op;
	/** Left operand. */
	struct ast_node *left;
	/** Right operand. */
	struct ast_node *right;
};

/** Unary operation. */
struct ast_unop {
	/** Which operation. */
	enum ast_unops op;
	/** Expression. */
	struct ast_node *expr;
};

/** A call. */
struct ast_call {
	/** Name to call, whatever it may be. */
	struct ast_node *expr;
	/** List of arguments to call. */
	struct ast_node *args;
};

/** Defer. */
struct ast_defer {
	/** Expression to defer. */
	struct ast_node *expr;
};

/** Macro definition. */
struct ast_macro_construct {
	/** Name of macro. */
	struct ast_node *id;
	/** Parameters macro takes. */
	struct ast_node *params;
	/** Macro body. */
	struct ast_node *body;
};

struct ast_macro_expand {
	struct ast_node *id;
	struct ast_node *args;
};

struct ast_type_expand {
	struct ast_node *id;
	struct ast_node *args;
};

/** Procedure definition. */
struct ast_proc {
	/** Procedure name. */
	struct ast_node *id;
	/** Procedure signature. */
	struct ast_node *sign;
	/** Procedure body. */
	struct ast_node *body;
};

/** Dot. */
struct ast_dot {
	/** Expression to do dot operation on. */
	struct ast_node *expr;
	/** Name to dot. */
	struct ast_node *id;
};

/** As. */
struct ast_as {
	/** Type to use for resolution. */
	struct ast_node *type;
};

/** Sizeof. */
struct ast_sizeof {
	/** Expression to get type of. */
	struct ast_node *expr;
};

/** Variable declaration. */
struct ast_var {
	/** Name of variable. */
	struct ast_node *id;
	/** Type of variable. */
	struct ast_node *type;
	/** Initialization expression. */
	struct ast_node *init;
};

/** Lambda definition. */
struct ast_lambda {
	/** Which variables to capture from the context. */
	struct ast_node *captures;
	/** Signature of lambda. */
	struct ast_node *sign;
	/** Body of lambda. */
	struct ast_node *body;
};

/**
 * For loop.
 *
 * \verbatim
 * for (pre; cond; post) {body}
 * \endverbatim
 */
struct ast_for {
	/** Initialization. */
	struct ast_node *pre;
	/** Condition. */
	struct ast_node *cond;
	/** Iteration. */
	struct ast_node *post;
	/** Body. */
	struct ast_node *body;
};

/**  While loop. */
struct ast_while {
	/** Condition. */
	struct ast_node *cond;
	/** Body. */
	struct ast_node *body;
};

/** Control. */
struct ast_ctrl {
	/** Break or continue. */
	enum ast_ctrl_kind kind;
	/**
	 * List of active defers.
	 * Similarly to goto, used to figure out which defers to trigger.
	 */
	struct ast_node *defers;
};

/** Return. */
struct ast_return {
	/** Expression to return. */
	struct ast_node *expr;
	/** List of active defers. */
	struct ast_node *defers;
};

enum ast_primitive {
	AST_VOID, AST_BOOL, AST_I9, AST_I27, AST_STR
};

/**
 * Type.
 * I'm not entirely happy with the current type system, for one
 * some parts are only used until they get initialized, which makes it
 * sort of difficult to follow what each kind means.
 *
 * @todo Could be better to have separate type nodes instead of co-opting
 * AST nodes.
 */
struct ast_type {
	/** Type kind. */
	enum ast_type_kind kind;
	/**
	 * Next type element in whole type. I.e. *i9 is two elements, one
	 * AST_TYPE_POINTER and one AST_TYPE_ID.
	 */
	struct ast_node *next;
	struct ast_node *as;
	struct ast_node *aliased;

	/** Data relevant to kind. */
	union {
		/** Name of a type, to be converted later. */
		struct {
			struct ast_node *id;
		} _id;

		struct {
			struct ast_node *id;
			struct ast_node *args;
		} _construct;

		struct {
			enum ast_primitive type;
			struct ast_node *def; // for possible user defined
					      // member functions
		} _primitive;

		/** Array type. */
		struct {
			struct ast_node *size;
			struct ast_node *base;
		} _arr;

		struct {
			struct ast_node *base;
		} _ptr;

		/** Procedure. */
		struct {
			/** Name. */
			struct ast_node *id;
			/** Parameters. */
			struct ast_node *params;
			/** Return type. */
			struct ast_node *ret;
		} _proc;

		/** Trait. */
		struct {
			/** Trait definition. */
			struct ast_node *def;
		} _trait;

		/** Structure. */
		struct {
			/** Structure definition. */
			struct ast_node *def;
		} _struct;

		/** Enumeration. */
		struct {
			/** Enum definition. */
			struct ast_node *def;
		} _enum;

		/** Union. */
		struct {
			/** Name of union. */
			struct ast_node *id;
			/** Arguments for type parameters. */
			struct ast_node *impls;
		} _union;

		struct {
			/** Parameter types. */
			struct ast_node *params;
			/** Return type. */
			struct ast_node *ret;
		} _sign;
	};
};

/** Block. */
struct ast_block {
	/** Body of block. */
	struct ast_node *body;
	/** List of defers. */
	struct ast_node *defers;
};

/** Import. */
struct ast_import {
	/** File to import. */
	const char *file;
};

/** Embed. @todo figure out how embedding should be done, just *u8? */
struct ast_embed {
	/** File to embed. */
	const char *file;
};

/** Enum definition. */
struct ast_enum {
	/** Name of enum. */
	struct ast_node *id;
	/** Type enum is convertible to/from. */
	struct ast_node *type;
	/** Body. */
	struct ast_node *body;
};

/** Structure definition. */
struct ast_struct {
	/** Name of structure. */
	struct ast_node *id;
	/** List of type parameters, if any. */
	struct ast_node *generics;
	/** Body. */
	struct ast_node *body;
	struct trait_implemented *implemented_by;
};

/** Enum member constant value. */
struct ast_val {
	/** Name of member. */
	struct ast_node *id;
	/** Constant value of member. */
	struct ast_node *val;
};

/** Switch. */
struct ast_switch {
	/** Condition. */
	struct ast_node *cond;
	/** List of cases. */
	struct ast_node *cases;
};

/** Switch case. */
struct ast_case {
	/** Condition. */
	struct ast_node *cond;
	/** Body. */
	struct ast_node *body;
};

/** Constant value. */
struct ast_const {
	/** Constant kind. */
	enum ast_const_kind kind;
	union {
		/** Integer. */
		long long integer;
		/** String. */
		const char *str;
	};
};

/** Value initialization. */
struct ast_init {
	/** Body. @todo maybe come up with a better name? */
	struct ast_node *body;
};

/** Assignment. */
struct ast_assign {
	/** Where to assign to. */
	struct ast_node *to;
	/** What to assign from. */
	struct ast_node *from;
};

/**
 * An ID.
 * @todo One optimization would be to reduce number of ast_ids,
 * replacing them with raw strings.
 */
struct ast_id {
	/** Actual ID. */
	const char *id;
};

/** Empty node. */
struct ast_empty {
};

/** AST node. */
struct ast_node {
	/** Node type. */
	enum ast_node_type node_type;
	/** Node flags. */
	enum ast_flag flags;
	/** Next node, when applicable. I.e. body statements. */
	struct ast_node *next;
	/** Source location. */
	struct src_loc loc;
	/** Scope node belongs to. */
	struct scope *scope;
	/** Ek type. */
	struct ast_node *type;

	size_t reg;

	/** Data relevant to kind. */
	union {
		struct ast_arr_access _arr_access;
		/** Binary operation. */
		struct ast_binop _binop;
		/** Unary operation. */
		struct ast_unop _unop;
		/** Call. */
		struct ast_call _call;
		/** Cast. */
		struct ast_cast _cast;
		/** Macro definition. */
		struct ast_macro_construct _macro_construct;
		struct ast_macro_expand _macro_expand;
		struct ast_type_expand _type_expand;
		/** Procedure definition. */
		struct ast_proc _proc;
		/** Goto. */
		struct ast_goto _goto;
		/** Goto label. */
		struct ast_label _label;
		/** Variable. */
		struct ast_var _var;
		/** Lambda. */
		struct ast_lambda _lambda;
		/** If. */
		struct ast_if _if;
		/** For. */
		struct ast_for _for;
		/** While. */
		struct ast_while _while;
		/** Break/continue. */
		struct ast_ctrl _ctrl;
		/** Defer. */
		struct ast_defer _defer;
		/** Type. */
		struct ast_type _type;
		/** Dot. */
		struct ast_dot _dot;
		/** Block. */
		struct ast_block _block;
		/** Import. */
		struct ast_import _import;
		/** Embed. */
		struct ast_embed _embed;
		/** Return. */
		struct ast_return _return;
		/** Switch. */
		struct ast_switch _switch;
		/** Alias. */
		struct ast_alias _alias;
		/** Trait definition. */
		struct ast_trait _trait;
		/** Enum definition. */
		struct ast_enum _enum;
		/** Structure definition. */
		struct ast_struct _struct;
		/** Enum value. */
		struct ast_val _val;
		/** Switch case. */
		struct ast_case _case;
		/** Constant value. */
		struct ast_const _const;
		/** Initialization. */
		struct ast_init _init;
		/** Assignment. */
		struct ast_assign _assign;
		/** ID. */
		struct ast_id _id;
		/** As type. */
		struct ast_as _as;
		/** Sizeof. */
		struct ast_sizeof _sizeof;
		/** Fetch enum member. */
		struct ast_fetch _fetch;
		/** Empty. */
		struct ast_empty _empty;
	};
};

struct ast_node *gen_arr_access(struct ast_node *base, struct ast_node *idx,
                                struct src_loc loc);

/**
 * Generate binary operation node.
 *
 * @param op Which operation.
 * @param left Left operand.
 * @param right Right operand.
 * @return Corresponding AST node.
 */
struct ast_node *gen_binop(enum ast_binops op,
                           struct ast_node *left,
                           struct ast_node *right,
                           struct src_loc loc);

/**
 * Generate unary operation.
 *
 * @param op Which operation.
 * @param expr Expression.
 * @return Corresponding AST node.
 */
struct ast_node *gen_unop(enum ast_unops op, struct ast_node *expr, struct src_loc loc);

/**
 * Generate call.
 *
 * @param id ID to call.
 * @param args Arguments to call.
 * @return Corresponding AST node.
 */
struct ast_node *gen_call(struct ast_node *id, struct ast_node *args,
                          struct src_loc loc);

/**
 * Generate ID.
 *
 * @param id ID.
 * @return Corresponding AST node.
 */
struct ast_node *gen_id(const char *id, struct src_loc loc);

/**
 * Generate constant integer.
 *
 * @param integer Integer.
 * @return Corresponding AST node.
 */
struct ast_node *gen_int(long long integer, struct src_loc loc);

/**
 * Generate constant string.
 *
 * @param str String.
 * @return Corresponding AST node.
 */
struct ast_node *gen_string(const char *str, struct src_loc loc);

/**
 * Generate constant float.
 *
 * @param dbl Double.
 * @return Corresponding AST node.
 */
struct ast_node *gen_float(double dbl, struct src_loc loc);

/**
 * Generate assignment.
 *
 * @param to Where to assign to.
 * @param from Where to assign from.
 * @return Corresponding AST node.
 */
struct ast_node *gen_assign(struct ast_node *to, struct ast_node *from, struct src_loc loc);

/**
 * Generate initialization.
 *
 * @param body Body of initialization.
 * @return Corresponding AST node.
 */
struct ast_node *gen_init(struct ast_node *body, struct src_loc loc);

/**
 * Generate while loop.
 *
 * @param cond Condition.
 * @param body Body.
 * @return Corresponding AST node.
 */
struct ast_node *gen_while(struct ast_node *cond, struct ast_node *body, struct src_loc loc);

/**
 * Generate for loop.
 *
 * @param pre Pre condition.
 * @param cond Condition.
 * @param post Post condition.
 * @param body Loop body.
 * @return Corresponding AST node.
 */
struct ast_node *gen_for(struct ast_node *pre, struct ast_node *cond,
                         struct ast_node *post, struct ast_node *body, struct src_loc loc);

/**
 * Generate return.
 *
 * @param expr Expression.
 * @return Corresponding AST node.
 */
struct ast_node *gen_return(struct ast_node *expr, struct src_loc loc);

/**
 * Generate control statement.
 * @note Some generators take source location info, which is then
 * propagated to higher level nodes.
 *
 * @todo not sure where to best place the note about location
 *
 * @param kind Break or continue.
 * @param loc Source location.
 * @return Corresponding AST node.
 */
struct ast_node *gen_ctrl(enum ast_ctrl_kind kind, struct src_loc loc);

/**
 * Generate macro definition.
 *
 * @param id Macro name.
 * @param params Macro parameters.
 * @param body Macro body.
 * @return Corresponding AST node.
 */
struct ast_node *gen_macro_construct(struct ast_node *id,
                                     struct ast_node *params,
                                     struct ast_node *body, struct src_loc loc);

struct ast_node *gen_macro_expand(struct ast_node *id, struct ast_node *args,
                                  struct src_loc loc);

/** @todo change args to type type when I figure out how it should be
 * constructed */
struct ast_node *gen_type_expand(struct ast_node *id,
                                 struct ast_node *args,
                                 struct src_loc loc);

/**
 * Generate if.
 *
 * @param cond Condition.
 * @param body Body.
 * @param els Else.
 * @return Corresponding AST node.
 */
struct ast_node *gen_if(struct ast_node *cond, struct ast_node *body,
                        struct ast_node *els, struct src_loc loc);

/**
 * Generate switch.
 *
 * @param cond Condition.
 * @param cases List of cases.
 * @return Corresponding AST node.
 */
struct ast_node *gen_switch(struct ast_node *cond, struct ast_node *cases, struct src_loc loc);

/**
 * Generate switch case.
 *
 * @param expr Condition.
 * @param body Body.
 * @return Corresponding AST node.
 */
struct ast_node *gen_case(struct ast_node *expr, struct ast_node *body, struct src_loc loc);

struct ast_node *gen_primitive(enum ast_primitive type, struct ast_node *def, struct src_loc loc);
/**
 * Generate Ek type (besides primitive).
 *
 * @param kind Type kind.
 * @param id Name of type.
 * @param decl List of parameters, when applicable.
 * @param rets Return type, when applicable.
 * @return Corresponding AST node.
 */
struct ast_node *gen_type(enum ast_type_kind kind, struct ast_node *t2,
                          struct ast_node *t1,
                          struct src_loc loc);

/**
 * Generate block.
 *
 * @param body Body.
 * @return Corresponding AST node.
 */
struct ast_node *gen_block(struct ast_node *body, struct src_loc loc);

/**
 * Generate variable.
 *
 * @param id Name of variable.
 * @param type Type of varibable.
 * @param init Initialization, when applicable.
 * @return Corresponding AST node.
 */
struct ast_node *gen_var(struct ast_node *id, struct ast_node *type,
                         struct ast_node *init, struct src_loc loc);

/**
 * Generate lambda.
 *
 * @param captures List of captures.
 * @param type Signature of lambda.
 * @param body Body.
 * @return Corresponding AST node.
 */
struct ast_node *gen_lambda(struct ast_node *captures,
                            struct ast_node *type, struct ast_node *body, struct src_loc loc);

/**
 * Generate procedure definition.
 *
 * @param id Name of procedure.
 * @param type Signature of procedure.
 * @param body Body.
 * @return Corresponding AST node.
 */
struct ast_node *gen_proc(struct ast_node *id, struct ast_node *type,
                          struct ast_node *body, struct src_loc loc);

/**
 * Generate dot operation.
 *
 * @param expr Expression to do dot operation to.
 * @param id Name to do dot with.
 * @return Corresponding AST node.
 */
struct ast_node *gen_dot(struct ast_node *expr, struct ast_node *id, struct src_loc loc);

/**
 * Generate enum definition.
 *
 * @param id Name of enumeration type.
 * @param type Type of enum.
 * @param body Body.
 * @return Corresponding AST node.
 */
struct ast_node *gen_enum(struct ast_node *id, struct ast_node *type,
                          struct ast_node *body, struct src_loc loc);

/**
 * Generate enum member value.
 *
 * @param id Name of enumeration member.
 * @param val Value of enumeration member.
 * @return Corresponding AST node.
 */
struct ast_node *gen_val(struct ast_node *id, struct ast_node *val, struct src_loc loc);

/**
 * Generate alias definition.
 *
 * @param id Name of alias.
 * @param type Type to alias.
 * @return Corresponding AST node.
 */
struct ast_node *gen_alias(struct ast_node *id, struct ast_node *type, struct src_loc loc);

/**
 * Generate trait definition.
 *
 * @param id Name of trait.
 * @param body Body.
 * @return Corresponding AST node.
 */
struct ast_node *gen_trait(struct ast_node *id, struct ast_node *params,
                           struct ast_node *raw_body, struct ast_node *body, struct src_loc loc);

/**
 * Generate import;
 *
 * @param file File to import.
 * @return Corresponding AST node.
 */
struct ast_node *gen_import(const char *file, struct src_loc loc);

/**
 * Generate cast.
 *
 * @param expr Expression.
 * @param type Type to cast expression result to.
 * @return Corresponding AST node.
 */
struct ast_node *gen_cast(struct ast_node *expr, struct ast_node *type, struct src_loc loc);

/**
 * Generate embed.
 *
 * @param file File to embed.
 * @return Corresponding AST node.
 */
struct ast_node *gen_embed(const char *file, struct src_loc loc);

/**
 * Generate goto.
 *
 * @param label Name of label to jump to.
 * @return Corresponding AST node.
 */
struct ast_node *gen_goto(struct ast_node *label, struct src_loc loc);

/**
 * Generate goto label.
 *
 * @param id Name of label.
 * @return Corresponding AST node.
 */
struct ast_node *gen_label(struct ast_node *id, struct src_loc loc);

/**
 * Generate defer.
 *
 * @param expr Expression to defer.
 * @return Corresponding AST node.
 */
struct ast_node *gen_defer(struct ast_node *expr, struct src_loc loc);

/**
 * Generate as.
 *
 * @param type Type to resolve with.
 * @return Corresponding AST node.
 */
struct ast_node *gen_as(struct ast_node *type, struct src_loc loc);

/**
 * Generate sizeof.
 *
 * @param expr Expression to take type of.
 * @return Corresponding AST node.
 */
struct ast_node *gen_sizeof(struct ast_node *expr, struct src_loc loc);

/**
 * Generate structure definition.
 *
 * @param id Name of structure.
 * @param generics List of type parameters.
 * @param body Body of structure.
 * @return Corresponding AST node.
 */
struct ast_node *gen_struct(struct ast_node *id, struct ast_node *generics,
                            struct ast_node *body, struct src_loc loc);

/**
 * Generate enum member fetch.
 *
 * @param id Name of enum member to fetch.
 * @param type Enum type to fetch from.
 * @return Corresponding AST node.
 */
struct ast_node *gen_fetch(struct ast_node *id, struct ast_node *type, struct src_loc loc);

/**
 * Generate empty AST node.
 *
 * @return Corresponding AST node.
 */
struct ast_node *gen_empty();

/**
 * Clone AST node.
 *
 * @param node Node to clone.
 * @return A clone of \p node.
 */
struct ast_node *clone_ast_node(struct ast_node *node);

/**
 * Check if two nodes are identical.
 *
 * @param exact Ignore some less important checks, such as flags, location and
 * scope.
 * @param left One AST node to compare.
 * @param right Other AST node to compare.
 * @return \c 0 if nodes aren't identical, \c 1 otherwise.
 */
int identical_ast_nodes(int exact, struct ast_node *left,
                        struct ast_node *right);

/**
 * Dump textual representation of AST to stdout.
 *
 * @param depth How many spaces to prepend.
 * @param root AST node to dump.
 */
void dump_ast(int depth, struct ast_node *root);

/**
 * Add \p elem to end of \p list.
 *
 * @param list List of AST nodes.
 * @param elem Add to end of \p list.
 */
void ast_append(struct ast_node *list, struct ast_node *elem);

/**
 * Set AST node flags.
 *
 * @param node Node to set flags for.
 * @param flags Flags to set.
 */
void ast_set_flags(struct ast_node *node, enum ast_flag flags);

/**
 * Clear AST node flags.
 *
 * @param node Node to clear flags for.
 * @param flags Flags to set.
 */
void ast_clear_flags(struct ast_node *node, enum ast_flag flags);

/**
 * Check if \p node has \p flags set.
 * All flags have to be set.
 *
 * @param node Node to check flags for.
 * @param flags Flags to check.
 * @return \c 1 if all \p flags are set, \c 0 othewise.
 */
int ast_flags(struct ast_node *node, enum ast_flag flags);

/**
 * Call external callback on all nodes in tree.
 *
 * @param call Callback to call.
 * @param node Node whose all subnodes should be passed to \p call.
 * @param data Extra data to pass to \p call.
 * @return Whatever \p call returns.
 */
int ast_call_on(int (*call)(struct ast_node *, void *),
                struct ast_node *node, void *data);

int ast_call_on_chain(int (*call)(struct ast_node *, void *),
		struct ast_node *node, void *data);

/**
 * Number of elements in AST list.
 *
 * @param list List whose elements to count.
 * @return Number of elements in \p list.
 */
size_t ast_list_len(struct ast_node *list);

/**
 * Get last nose in ASt list.
 *
 * @param list List whose last element to get.
 * @return Last node in \p list.
 */
struct ast_node *ast_last_node(struct ast_node *list);

/**
 * Get last element in block.
 *
 * @param block Block whose last element to get.
 * @return Last node in block.
 */
struct ast_node *ast_block_last(struct ast_node *block);

void destroy_ast_nodes();
const char *primitive_str(enum ast_primitive type);

int same_id(struct ast_node *id1, struct ast_node *id2);
int equiv_nodes(struct ast_node *n1, struct ast_node *n2);
int equiv_node_chains(struct ast_node *c1, struct ast_node *c2);

#define foreach_node(iter, nodes)\
	for (struct ast_node *iter = nodes; iter; iter = iter->next)

#endif /* AST_H */

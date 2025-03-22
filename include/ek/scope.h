/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef SCOPE_H
#define SCOPE_H

/**
 * @file scope.h
 *
 * Scope handling stuff.
 */

#include <string.h>
#include <stdint.h>

#include "ast.h"
#include "debug.h"

/** Flags a scope can have. */
enum scope_flags {
	/** Scope is public, i.e. stuff defined in this scope should be made
	 * visible to parent file scopes. */
	SCOPE_PUBLIC = (1 << 0),
	/** Scope is file scope. */
	SCOPE_FILE = (1 << 1),
	SCOPE_ROOT = (1 << 2)
};

#define MAP_KEY char *
#define MAP_TYPE struct ast *
#define MAP_CMP(a, b) strcmp((a), (b))
#define MAP_HASH(a) CONTS_MAP_STR_HASH(a)
#define MAP_NAME visible
#include <conts/map.h>

struct expanded_key {
	struct ast *def;
	struct type *types;
};

static inline int expanded_key_cmp(struct expanded_key a, struct expanded_key b)
{
	uintptr_t na = (uintptr_t)a.def;
	uintptr_t nb = (uintptr_t)b.def;
	if (na != nb)
		return na - nb;

	return !type_lists_match(a.types, b.types);
}

static inline size_t expanded_key_hash(struct expanded_key a)
{
	return (uintptr_t)a.def;
}

#define MAP_KEY struct expanded_key
#define MAP_TYPE struct ast *
#define MAP_CMP(a, b) expanded_key_cmp((a), (b))
#define MAP_HASH(a) expanded_key_hash(a)
#define MAP_NAME expanded
#include <conts/map.h>

/* use map like set, could maybe be added to conts directly with some
 * convenience wrappers? */
#define MAP_KEY struct ast *
#define MAP_TYPE struct ast *
#define MAP_CMP(a, b) ((uintptr_t)(a) - (uintptr_t)(b))
#define MAP_HASH(a) ((uintptr_t)(a))
#define MAP_NAME exported
#include <conts/map.h>

/**
 * Scope.
 * Responsible for keeping track of visibilities and
 * file context.
 */
struct scope {
	/** Parent scope, NULL if top scope. */
	struct scope *parent;
	/** Scope flags. */
	enum scope_flags flags;
	/** Unique scope ID. Mostly used for debugging. */
	size_t number;

	/**
	 * File context of scope. Accurate debugging output relies
	 * on keeping track of which file and buffer a context is in.
	 */
	struct file_ctx fctx;

	/**
	 * Next child node.
	 * Used by the parent scope to keep track of all its children.
	 */
	struct scope *next;
	/** List of child scopes. */
	struct scope *children;

	struct expanded expanded;

	struct visible symbols;
	struct visible macros;
	struct visible types;

	struct exported exported_symbols;
	struct exported exported_macros;
	struct exported exported_types;
};

/**
 * Create scope.
 *
 * @return New, empty scope.
 */
struct scope *create_scope();

/**
 * Destroy scope.
 * Destroys all lists the scope owns and frees the scope.
 *
 * @param scope Scope to destroy.
 */
void destroy_scope(struct scope *scope);

/**
 * Set scope flags.
 *
 * @param scope Scope to set flags for.
 * @param flags Flags to set in scope.
 */
void scope_set_flags(struct scope *scope, enum scope_flags flags);

/**
 * Check if scope has flags active.
 *
 * @param scope Scope to check flags in.
 * @param flags Flags to check for.
 * @return \c 1 if flags are set, \c 0 if flags are unset.
 * @note All flags have to be set for the result to be \c 1.
 */
unsigned scope_flags(struct scope *scope, enum scope_flags flags);

/**
 * Add child scope to \p parent.
 *
 * @param parent Scope to add scope to.
 * @param child Scope to add to scope.
 */
void scope_add_scope(struct scope *parent, struct scope *child);

/**
 * Add variable to scope.
 * Propagates public variables up the file scope chain as references.
 *
 * @param scope Scope to add variable to.
 * @param var Variable to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_var(struct scope *scope, struct ast *var);

/**
 * Add type to scope.
 * Propagates public types up the file scope chain as references.
 *
 * @param scope Scope to add type to.
 * @param type Type to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_type(struct scope *scope, char *id, struct ast *type);

int scope_add_chain(struct scope *scope, char *id, struct ast *node);

/**
 * Add procedure to scope.
 * Propagates public procedures up the file scope chain as references.
 *
 * @param scope Scope to add procedure to.
 * @param proc Procedure to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_proc(struct scope *scope, struct ast *proc);

/**
 * Add macro to scope.
 * Propagates public macros up the file scope chain as references.
 *
 * @param scope Scope to add macro to.
 * @param macro Macro to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_macro(struct scope *scope, struct ast *macro);

/**
 * Add template to scope.
 * Propagates public templates up the file scope chain as references.
 *
 * @param scope Scope to add template to.
 * @param type_template Template to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_trait(struct scope *scope, struct ast *trait);

int scope_add_expd_struct(struct scope *scope, struct ast *def,
                          struct type *types, struct ast *expanded);

int scope_add_expd_chain(struct scope *scope, struct ast *def,
                         struct type *types, struct ast *expanded);

/**
 * Find a variable with ID in \p scope.
 * @note Only looks in the current scope, so doesn't see anything outside
 * of it. See file_scope_find_var().
 *
 * @param scope Scope to look in.
 * @param id ID of variable to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *scope_find_var(struct scope *scope, char *id);
struct ast *scope_find_symbol(struct scope *scope, char *id);

/**
 * Find a type with ID in \p scope.
 * @note Only looks in the current scope, so doesn't see anything outside
 * of it. See file_scope_find_type().
 *
 * @param scope Scope to look in.
 * @param id ID of type to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *scope_find_type(struct scope *scope, char *id);

/**
 * Find a procedure with ID in \p scope.
 * @note Only looks in the current scope, so doesn't see anything outside
 * of it. See file_scope_find_proc().
 *
 * @param scope Scope to look in.
 * @param id ID of procedure to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *scope_find_proc(struct scope *scope, char *id);

/**
 * Find a  macro with ID in \p scope.
 * @note Only looks in the current scope, so doesn't see anything outside
 * of it. See file_scope_find_macro().
 *
 * @param scope Scope to look in.
 * @param id ID of macro to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *scope_find_macro(struct scope *scope, char *id);

/**
 * Find an alias with ID in \p scope.
 * @note Only looks in the current scope, so doesn't see anything outside
 * of it. See file_scope_find_alias().
 *
 * @param scope Scope to look in.
 * @param id ID of alias to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *scope_find_alias(struct scope *scope, char *id);

/**
 * Find a template with ID in \p scope.
 * @note Only looks in the current scope, so doesn't see anything outside
 * of it. See file_scope_find_template().
 *
 * @param scope Scope to look in.
 * @param id ID of template to fetch.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *scope_find_trait(struct scope *scope, char *id);

struct ast *scope_find_expd_struct(struct scope *scope, struct ast *def,
                                   struct type *types);

/**
 * Find a variable with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of variable to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *file_scope_find_var(struct scope *scope, char *id);
struct ast *file_scope_find_symbol(struct scope *scope, char *id);

/**
 * Find a type with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of variable to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *file_scope_find_type(struct scope *scope, char *id);

/**
 * Find a procedure with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of procedure to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *file_scope_find_proc(struct scope *scope, char *id);

/**
 * Find a macro with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of macro to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *file_scope_find_macro(struct scope *scope, char *id);
/**
 * Find a alias with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of alias to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *file_scope_find_alias(struct scope *scope, char *id);

/**
 * Find a template with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of template to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast *file_scope_find_trait(struct scope *scope, char *id);

struct ast *file_scope_find_expd_struct(struct scope *scope, struct ast *def,
                                        struct type *types);

bool is_exported_type(struct scope *scope, struct ast *def);
bool is_exported_symbol(struct scope *scope, struct ast *def);
bool is_exported_macro(struct scope *scope, struct ast *def);

int scope_add_exported_symbol(struct scope *scope, struct ast *def);
int scope_add_exported_type(struct scope *scope, struct ast *def);
int scope_add_exported_chain(struct scope *scope, struct ast *def);
int scope_add_exported_macro(struct scope *scope, struct ast *def);

#endif /* SCOPE_H */

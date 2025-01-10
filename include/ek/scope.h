/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef SCOPE_H
#define SCOPE_H

/**
 * @file scope.h
 *
 * Scope handling stuff.
 */

#include "ast.h"
#include "debug.h"

/** Flags a scope can have. */
enum scope_flags {
	/** Scope is public, i.e. stuff defined in this scope should be made
	 * visible to parent file scopes. */
	SCOPE_PUBLIC = (1 << 0),
	/** Scope is file scope. */
	SCOPE_FILE = (1 << 1),
};

/**
 * An AST node visible to the scope we're in.
 * The same AST node can be referenced by multiple visible nodes,
 * but only the owning scope is allowed to destroy the node.
 * Check that \p owner is identical to the scope the visible node
 * belongs to.
 *
 * Basic linked list for now, can probably be optimized into some kind of hash
 * table later.
 */
struct visible {
	/** Name of the visible node. */
	char *id;
	/** AST node that is visible. */
	struct ast *node;
	/** Next visible object in the scope we're in. */
	struct visible *next;
};

struct expanded {
	struct ast *node;
	struct type *types;
	struct ast *expd;
	struct expanded *next;
};

struct type_defs {
	char *id;
	struct ast *type_def;
	struct type_defs *next;
};

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

	struct expanded *expanded;

	struct visible *symbols;
	struct visible *macros;
	struct visible *types;

	struct visible *type_constructs;
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
 * Add default stuff to scope, mainly builtin types.
 *
 * @param root Scope to add default stuff to.
 * @note Only has to be called on the file scope, all child scopes will
 * look up stuff from the file scope anyway.
 * @return \c 0 if succesful, non-zero otherwise.
 */
int scope_add_defaults(struct scope *root);

/**
 * Destroy defaults in scope that might otherwise not be freed.
 *
 * @param root Scope to destroy added defaults in.
 * @todo not sure if this should be private.
 */
void scope_destroy_defaults(struct scope *root);

/**
 * Add a scratch AST node.
 *
 * @param scope Scope to add scratch AST node to.
 * @param scratch Scratch node to add to \p scope.
 * @return \c 0 when successful, non-zero otherwise.
 */
int scope_add_scratch(struct scope *scope, struct ast *scratch);

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

#define foreach_visible(iter, init) \
	for (struct visible *iter = init; iter; iter = iter->next)

#define foreach_expanded(iter, init) \
	for (struct expanded *iter = init; iter; iter = iter->next)

#endif /* SCOPE_H */

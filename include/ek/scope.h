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
	struct ast_node *id;
	/** AST node that is visible. */
	struct ast_node *node;
	/** Next visible object in the scope we're in. */
	struct visible *next;
};

/** Actualized nodes visible to scope. */
struct actual {
	/** Actualized AST node. */
	struct ast_node *node;
	/** Next actual node. */
	struct actual *next;
};

/**
 * Callable nodes visible to scope.
 *
 * Each callable consists of an ID and
 * a resolution tree built from parameters the
 * callable can take.
 * Parameters passed to the callable are
 * matched against this resolution tree to know
 * which callable to choose.
 */
struct resolve {
	/** Resolve tree of resolve. */
	struct resolve_node *root;
	/** AST node ID of resolve. */
	struct ast_node *id;
	/** Next resolve node. */
	struct resolve *next;
};

/** A parameter node in the procedure resolution tree. */
struct param_node {
	/** Parameter type. */
	struct ast_node *type;
	/** Fully resolved procedure if there is no next node. */
	struct resolve_node *resolved;
	/** Next parameter node in current parameter slot. */
	struct param_node *next;
};

/**
 * A procedure node in the resolution tree.
 *
 * A resolution tree is how Ek chooses which overloaded callable
 * to choose from. For example,
 *
 * @verbatim
 * do_stuff(u8, f32){}
 * do_stuff(u8, f64){}
 * do_stuff(u16, f32){}
 * @endverbatim
 *
 * generates a resolution tree of the form
 * @verbatim
 * callable:
 * do_stuff -> u8  -> f32
 *                 -> f64
 *             u16 -> f32
 * @endverbatim
 *
 * When a callable is called with some arguments, the argument's types
 * are actualized and using the resolve tree, the correct do_stuff is chosen.
 *
 * Additionally, interfaces are allowed, but only as a 'fallback'. That is, if
 * no trivial parameter type matches the argument type, the fallback is checked,
 * and if the argument type doesn't implement the fallback, the resolution
 * is considered to have failed.
 *
 * Self-refential parameter types are similarly checked after primitive types.
 *
 * @note Generic structures without type arguments are considered primitive,
 * as are fully qualified generic structures, anything between is disallowed.
 * Eg.
 * @verbatim
 * struct some_struct (a A, b B) {...}
 * do_stuff(some_struct){...} // OK
 * do_stuff(some_struct(u8, u16)){} // OK
 * do_stuff(some_struct(u8)){} // ERR
 * @endverbatim
 */
struct resolve_node {
	/** List of parameters of the current parameter slot. */
	struct param_node *params;

	/** Next procedure with parameter slot. */
	struct ast_node *resolved;
};

struct types {
	struct ast_node *id;
	struct ast_node *type;
	struct ast_node *next;
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

	/**
	 * List of actualized functions,
	 * shared between all scopes in the file.
	 */
	struct actual *actuals;

	/** { types */

	struct visible *types;

	/** } */

	struct visible *type_constructs;

	/**
	 * Variables visible in scope.
	 * @note Only some variables are callable, namely array variables.
	 * @todo Could maybe add separate array list instead of a variable list?
	 */
	struct visible *vars;

	struct resolve *proc_resolve;
	struct resolve *macro_resolve;
	struct resolve *type_construct_resolve;
};

/** Flags for matching objects during search. */
enum match_flags {
	/** Search globally, not just in current scope. */
	MATCH_GLOBAL = (1 << 0),
	/**
	 * Match call arguments to parameters.
	 * If this flag is not present, only the name is matched.
	 */
	MATCH_CALL = (1 << 1),
};

/**
 * Create scope.
 *
 * @return New, empty scope.
 */
struct scope *create_scope();

/**
 * Create actuals list.
 * Since actuals are shared in the file scope, many scopes may share the actuals
 * list. Only the file scope is allowed to destroy the actual list.
 *
 * @return Empty actual list.
 */
struct actual *create_actuals();

/**
 * Destroy the list of actuals and actuals in list.
 *
 * @param actuals List of actuals to destroy.
 */
void destroy_actuals(struct actual *actuals);

/**
 * Destroy list of visibles.
 *
 * @param scope Scope list belongs to.
 * @param visible List of visibles to destroy.
 */
void destroy_visible(struct scope *scope, struct visible *visible);

/**
 * Destroy scope.
 * Destroys all lists the scope owns and frees the scope.
 *
 * @param scope Scope to destroy.
 */
void destroy_scope(struct scope *scope);

/**
 * Create temporary scope.
 * Adds \p parent as the parent of the scope, but doesn't add the new scope
 * to the list of children \p parent has.
 * Caller is responsible for destroying the temporary scope.
 *
 * @param parent The temporary scope's parent.
 * @return New temporary scope.
 */
struct scope *create_temp_scope(struct scope *parent);

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
int scope_add_scratch(struct scope *scope, struct ast_node *scratch);

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
int scope_flags(struct scope *scope, enum scope_flags flags);

/**
 * Add child scope to \p parent.
 *
 * @param parent Scope to add scope to.
 * @param child Scope to add to scope.
 */
void scope_add_scope(struct scope *parent, struct scope *child);

/**
 * Add actualized AST node to scope.
 * Will make the actualized node visible to all scopes in the file scope.
 *
 * @param scope Scope to add \p node to.
 * @param node Actualized AST node.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_actual(struct scope *scope, struct ast_node *node);

/**
 * Add variable to scope.
 * Propagates public variables up the file scope chain as references.
 *
 * @param scope Scope to add variable to.
 * @param var Variable to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_var(struct scope *scope, struct ast_node *var);

/**
 * Add type to scope.
 * Propagates public types up the file scope chain as references.
 *
 * @param scope Scope to add type to.
 * @param type Type to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_type(struct scope *scope, struct ast_node *id, struct ast_node *type);

/**
 * Add procedure to scope.
 * Propagates public procedures up the file scope chain as references.
 *
 * @param scope Scope to add procedure to.
 * @param proc Procedure to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_proc(struct scope *scope, struct ast_node *proc);

/**
 * Add macro to scope.
 * Propagates public macros up the file scope chain as references.
 *
 * @param scope Scope to add macro to.
 * @param macro Macro to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_macro(struct scope *scope, struct ast_node *macro);

/**
 * Add template to scope.
 * Propagates public templates up the file scope chain as references.
 *
 * @param scope Scope to add template to.
 * @param type_template Template to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_trait(struct scope *scope, struct ast_node *trait);

int scope_add_type_construct(struct scope *scope, struct ast_node *type_construct);

/**
 * Add an already allocated visible variable node to scope.
 * After initial analysis, preallocated variable nodes are actualized
 * and added back into the scope to build up the resolution tree.
 *
 * @param scope Scope to add variable node to.
 * @param var Variable to to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_existing_var(struct scope *scope, struct visible *var);

/**
 * Add an already allocated visible procedure node to scope.
 * After initial analysis, preallocated procedure nodes are (partially)
 * actualized and added back into the scope to build up the resolution tree.
 *
 * @param scope SCope to add procedure node to.
 * @param proc Procedure to add to scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int scope_add_existing_proc(struct scope *scope, struct visible *proc);

/**
 * Find an actualized AST node with ID in \p scope.
 * Since actuals are file global, technically no need for a file_*
 * @note Doesn't do any resolution. See scope_resolve_actual().
 *
 * @param scope Scope to look in.
 * @param id ID of actual to find.
 * @return Pointer to the actualized AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast_node *scope_find_actual(struct scope *scope, struct ast_node *id);

/**
 * Find anything with ID in \p scope.
 * @note Only looks in the current scope, so doesn't see anything outside
 * of it. See file_scope_find().
 *
 * @param scope Scope to look in.
 * @param id ID of whatever to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast_node *scope_find(struct scope *scope, struct ast_node *id);

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
struct ast_node *scope_find_var(struct scope *scope, struct ast_node *id);

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
struct ast_node *scope_find_type(struct scope *scope, struct ast_node *id);

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
struct ast_node *scope_find_proc(struct scope *scope, struct ast_node *id);

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
struct ast_node *scope_find_macro(struct scope *scope, struct ast_node *id);

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
struct ast_node *scope_find_alias(struct scope *scope, struct ast_node *id);

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
struct ast_node *scope_find_trait(struct scope *scope, struct ast_node *id);

/**
 * Find anything with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of whatever to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast_node *file_scope_find(struct scope *scope, struct ast_node *id);

/**
 * Find a variable with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of variable to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast_node *file_scope_find_var(struct scope *scope, struct ast_node *id);

/**
 * Find a type with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of variable to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast_node *file_scope_find_type(struct scope *scope, struct ast_node *id);

/**
 * Find a procedure with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of procedure to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast_node *file_scope_find_proc(struct scope *scope, struct ast_node *id);

/**
 * Find a macro with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of macro to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast_node *file_scope_find_macro(struct scope *scope,
                                       struct ast_node *id);
/**
 * Find a alias with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of alias to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast_node *file_scope_find_alias(struct scope *scope,
                                       struct ast_node *id);

/**
 * Find a template with ID visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param id ID of template to find.
 * @return Pointer to the AST node corresponding to \p id if found,
 * otherwise \c NULL.
 */
struct ast_node *file_scope_find_trait(struct scope *scope,
                                          struct ast_node *id);

/**
 * Try to resolve a call to an array in \p scope.
 *
 * @param scope Scope to look in.
 * @param call AST call node to try and match to an array.
 * @return Pointer to the AST node corresponding to \p call if found,
 * otherwise \c NULL.
 */
struct ast_node *scope_resolve_arr(struct scope *scope, struct ast_node *call);

/**
 * Try to resolve a call to a macro in \p scope.
 *
 * @param scope Scope to look in.
 * @param call AST call node to try and match to a macro.
 * @return Pointer to the AST node corresponding to \p call if found,
 * otherwise \c NULL.
 */
struct ast_node *scope_resolve_macro(struct scope *scope,
                                     struct ast_node *call);

/**
 * Try to resolve a call to an actualized node in \p scope.
 *
 * @param scope Scope to look in.
 * @param call AST call node to try and match to an actualized node.
 * @return Pointer to the AST node corresponding to \p call if found,
 * otherwise \c NULL.
 */
struct ast_node *scope_resolve_actual(struct scope *scope,
                                      struct ast_node *call);

/**
 * Try to resolve a call to a procedure in \p scope.
 *
 * @param scope Scope to look in.
 * @param call AST call node to try and match to a procedure.
 * @return Pointer to the AST node corresponding to \p call if found,
 * otherwise \c NULL.
 */
struct ast_node *scope_resolve_proc(struct scope *scope, struct ast_node *call);

/**
 * Try to resolve a call to an AST node in \p scope.
 *
 * @param scope Scope to look in.
 * @param call AST call node to try and match to an AST node.
 * @return Pointer to the AST node corresponding to \p call if found,
 * otherwise \c NULL.
 */
struct ast_node *scope_resolve_call(struct scope *scope, struct ast_node *call);

/**
 * Try to resolve a call to an AST node visible to \p scope.
 *
 * @param scope Scope to look in.
 * @param call AST call node to try and match to an AST node.
 * @return Pointer to the AST node corresponding to \p call if found,
 * otherwise \c NULL.
 */
struct ast_node *file_scope_resolve_call(struct scope *scope,
                                         struct ast_node *call);

struct ast_node *file_scope_resolve_macro(struct scope *scope,
		struct ast_node *macro);

/**
 * Check if \p arg_type implements \p param_type.
 *
 * A type implement another type if
 * a) They resolve to the same primitive type after alias and expression substitutions
 * b) One type is a trait and the other type has all members and
 * procedures specified in the trait.
 *
 * \p arg_type should never be a trait, so I suppose it's undefined if a trait
 * implements another trait.
 *
 * @param flags Flags for resolution.
 * @param scope Scope to check types in.
 * @param arg_type Argument type.
 * @param param_type Parameter type.
 * @return \c 1 if \p arg_type implements \p param_type, \c 0 otherwise.
 */
int implements(enum match_flags flags, struct scope *scope,
               struct ast_node *arg_type,
               struct ast_node *param_type);

/**
 * Check if type is primitive.
 *
 * @param type Type to check.
 * @return \c 1 if \p type is primitive, \c 0 otherwise.
 */
int primitive_type(struct ast_node *type);

/**
 * Check if type is fully qualified.
 * A fully qualified type is a struct or union with all type parameters filled.
 *
 * @param type Type to check.
 * @return \c 1 if \p type is fully qualified, \c 0 otherwise.
 */
int fully_qualified(struct ast_node *type);

#endif /* SCOPE_H */

/* SPDX-License-Identifier: GPL-3.0-or-later */

#ifndef SCOPE_H
#define SCOPE_H

#include "ast.h"
#include "debug.h"

enum scope_flags {
	SCOPE_PUBLIC = (1 << 0),
	SCOPE_FILE = (1 << 1),
};

/* basic linked list for now, can probably be optimized into some kind of hash
 * table later */
struct visible {
	struct ast_node *node;
	struct scope *owner;
	struct visible *next;
};

struct scratch {
	struct ast_node *node;
	struct scratch *next;
};

struct actual {
	struct ast_node *node;
	struct actual *next;
};

struct callable {
	struct proc_node *root;
	struct ast_node *id;
	struct callable *next;
};

struct param_node {
	struct ast_node *type;
	struct proc_node *proc;
	struct param_node *next;
};

struct proc_node {
	struct param_node *primitives;

	struct param_node *referential;
	struct param_node *fallback;

	struct ast_node *proc;
};


struct scope {
	struct scope *parent;
	enum scope_flags flags;
	size_t number;

	struct file_ctx fctx;

	/* used by the parent to keep track of all its children */
	struct scope *next;
	struct scope *children;

	/* list of actualized functions, shared between all scopes in the
	 * compilation unit */
	struct actual *actuals;

	/* for temp stuff */
	struct scratch *scratch;

	/* types */
	/* TODO: add actualized types maybe? */
	struct visible *enums;
	struct visible *structs;
	struct visible *aliases;
	struct visible *builtins;
	struct visible *templates;

	/* basic variables */
	struct visible *vars;
	struct visible *macros;

	/* collect procedures */
	struct visible *procs;

	/* callables */
	struct callable *callable;
};

enum match_flags {
	MATCH_GLOBAL = (1 << 0),
	MATCH_CALL = (1 << 1),
};

struct scope *create_scope();
struct actual *create_actuals();
void destroy_actuals(struct actual *actuals);
void destroy_visible(struct scope *scope, struct visible *visible);
void destroy_scope(struct scope *scope);

struct scope *create_temp_scope(struct scope *parent);

int scope_add_defaults(struct scope *root);
/* not sure if this should be public */
void scope_destroy_defaults(struct scope *root);

int scope_add_scratch(struct scope *scope, struct ast_node *scratch);

void scope_set_flags(struct scope *scope, enum scope_flags flags);
int scope_flags(struct scope *scope, enum scope_flags flags);

void scope_add_scope(struct scope *parent, struct scope *child);

int scope_add_actual(struct scope *scope, struct ast_node *node);
/* sets a node's owner as scope, and as needed propagates references to public
 * things up the file scope chain. */
int scope_add_var(struct scope *scope, struct ast_node *var);
int scope_add_type(struct scope *scope, struct ast_node *type);
int scope_add_proc(struct scope *scope, struct ast_node *proc);
int scope_add_macro(struct scope *scope, struct ast_node *macro);
int scope_add_alias(struct scope *scope, struct ast_node *alias);
int scope_add_template(struct scope *scope, struct ast_node *type_template);

int scope_add_existing_var(struct scope *scope, struct visible *var);
int scope_add_existing_proc(struct scope *scope, struct visible *proc);

/* actuals are global, so technically no need for a file_* */
struct ast_node *scope_find_actual(struct scope *scope, struct ast_node *id);

struct ast_node *scope_find(struct scope *scope, struct ast_node *id);
struct ast_node *scope_find_var(struct scope *scope, struct ast_node *id);
struct ast_node *scope_find_type(struct scope *scope, struct ast_node *id);
struct ast_node *scope_find_proc(struct scope *scope, struct ast_node *id);
struct ast_node *scope_find_macro(struct scope *scope, struct ast_node *id);
struct ast_node *scope_find_alias(struct scope *scope, struct ast_node *id);
struct ast_node *scope_find_template(struct scope *scope, struct ast_node *id);

struct ast_node *file_scope_find(struct scope *scope, struct ast_node *id);
struct ast_node *file_scope_find_var(struct scope *scope, struct ast_node *id);
struct ast_node *file_scope_find_type(struct scope *scope, struct ast_node *id);
struct ast_node *file_scope_find_proc(struct scope *scope, struct ast_node *id);
struct ast_node *file_scope_find_macro(struct scope *scope,
                                       struct ast_node *id);
struct ast_node *file_scope_find_alias(struct scope *scope,
                                       struct ast_node *id);
struct ast_node *file_scope_find_override(struct scope *scope,
                                          struct ast_node *id);
struct ast_node *file_scope_find_template(struct scope *scope,
                                          struct ast_node *id);

struct ast_node *scope_resolve_arr(struct scope *scope, struct ast_node *call);
struct ast_node *scope_resolve_macro(struct scope *scope,
                                     struct ast_node *call);
struct ast_node *scope_resolve_actual(struct scope *scope,
                                      struct ast_node *call);
struct ast_node *scope_resolve_proc(struct scope *scope, struct ast_node *call);
struct ast_node *scope_resolve_call(struct scope *scope, struct ast_node *call);

struct ast_node *scope_resolve_type(struct scope *scope, struct ast_node *type);
struct ast_node *file_scope_resolve_type(struct scope *scope,
                                         struct ast_node *type);

struct ast_node *file_scope_resolve_call(struct scope *scope,
                                         struct ast_node *call);
int implements(enum match_flags flags, struct scope *scope,
               struct ast_node *arg_type,
               struct ast_node *param_type);
#endif /* SCOPE_H */

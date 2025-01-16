/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

/** @file scope.c
 *
 * Implementations for scope handling stuff.
 */

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

#include <ek/debug.h>
#include <ek/scope.h>
#include <ek/actualize.h>

static bool same_src_scope(struct scope *a, struct scope *b)
{
	/** @todo a bit ridiculous, is there a less hacky way? */
	return a->fctx.fbuf == b->fctx.fbuf;
}

struct scope *create_scope()
{
	/* if I ever try making the parser multithreaded, this should be atomic. */
	static size_t counter = 0;

	struct scope *scope = calloc(1, sizeof(struct scope));
	if (!scope) {
		internal_error("ran out of memory allocating scope");
		return NULL;
	}

	scope->expanded = expanded_create();
	scope->symbols = visible_create();
	scope->macros = visible_create();
	scope->types = visible_create();

	scope->number = counter++;
	return scope;
}

void destroy_scope(struct scope *scope)
{
	if (!scope)
		return;

	if (scope_flags(scope, SCOPE_FILE)) {
		free((void *)scope->fctx.fbuf);
		free((void *)scope->fctx.fname);
	}

	visible_destroy(&scope->symbols);
	visible_destroy(&scope->macros);
	visible_destroy(&scope->types);

	expanded_destroy(&scope->expanded);

	struct scope *prev = scope->children, *cur;
	if (prev)
		do {
			cur = prev->next;
			destroy_scope(prev);
		} while ((prev = cur));

	free(scope);
}

void scope_set_flags(struct scope *scope, enum scope_flags flags)
{
	assert(scope);
	scope->flags |= flags;
}

unsigned scope_flags(struct scope *scope, enum scope_flags flags)
{
	assert(scope);
	return (scope->flags & flags) == flags;
}

struct ast **create_type(struct scope *scope, char *id, struct ast *type)
{
	return visible_insert(&scope->types, id, type);
}

struct ast **create_expanded(struct scope *scope, struct ast *def,
                                 struct type *types, struct ast *expd)
{
	struct expanded_key key = {.def = def, .types = types};
	return expanded_insert(&scope->expanded, key, expd);
}

struct ast **create_var(struct scope *scope, char *id, struct ast *var)
{
	return visible_insert(&scope->symbols, id, var);
}

struct ast **create_macro(struct scope *scope, char *id, struct ast *macro)
{
	return visible_insert(&scope->macros, id, macro);
}

struct ast **create_proc(struct scope *scope, char *id, struct ast *proc)
{
	return visible_insert(&scope->symbols, id, proc);
}

static bool scope_add_recurse(struct scope *scope, struct ast *node)
{
	if (!scope->parent)
		return false;

	if (!ast_flags(node, AST_FLAG_PUBLIC))
		return false;

	if (same_src_scope(scope, node->scope))
		return true;

	return scope_flags(scope, SCOPE_PUBLIC);
}

int scope_add_var(struct scope *scope, struct ast *var)
{
	struct ast *exists = scope_find_symbol(scope, var_id(var));
	if (exists) {
		semantic_error(scope->fctx, var, "var redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	create_var(scope, var_id(var), var);
	if (scope_add_recurse(scope, var))
		return scope_add_var(scope->parent, var);

	return 0;
}

int scope_add_type(struct scope *scope, char *id, struct ast *type)
{
	struct ast *exists = scope_find_type(scope, id);
	if (exists) {
		semantic_error(scope->fctx, type, "type redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	create_type(scope, id, type);
	if (scope_add_recurse(scope, type))
		return scope_add_type(scope->parent, id, type);

	return 0;
}

static void insert_chain(struct scope *scope, char *id, struct ast *type)
{
	struct ast **v = visible_find(&scope->types, id);
	assert(v);

	struct ast *n = *v;

	if (ast_flags(n, AST_FLAG_PUBLIC)
	    || !ast_flags(type, AST_FLAG_PUBLIC)) {
		type->chain = n;
		*v = type;
		return;
	}

	/* find first public continuation in chain and insert just before it */
	struct ast *next = n->chain;
	while (next->k == AST_STRUCT_CONT_DEF && !ast_flags(next,
	                                                    AST_FLAG_PUBLIC)) {
		n = next;
		next = n->chain;
	}

	n->chain = type;
	type->chain = next;
}

int scope_add_chain(struct scope *scope, char *id, struct ast *type)
{
	struct ast *exists = file_scope_find_type(scope, id);
	if (!exists) {
		semantic_error(scope->fctx, type, "no previous definition");
		return -1;
	}

	insert_chain(scope, id, type);

	if (scope_add_recurse(scope, type))
		return scope_add_chain(scope->parent, id, type);

	return 0;
}

int scope_add_macro(struct scope *scope, struct ast *macro)
{
	assert(macro->k == AST_MACRO_DEF);
	struct ast *exists = file_scope_find_macro(scope, macro_def_id(macro));
	if (exists) {
		semantic_error(scope->fctx, macro, "macro redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	/* always add to scope, do resolve checking later */
	create_macro(scope, macro_def_id(macro), macro);
	if (scope_add_recurse(scope, macro))
		return scope_add_macro(scope->parent, macro);

	return 0;
}

int scope_add_proc(struct scope *scope, struct ast *proc)
{
	assert(proc->k == AST_PROC_DEF);
	struct ast *exists = file_scope_find_symbol(scope, proc_id(proc));
	if (exists && proc_body(exists) == proc_body(proc)) {
		semantic_error(proc->scope->fctx, proc, "proc redefined");
		semantic_info(exists->scope->fctx, exists, "previously here");
		return -1;
	}

	/* always add to scope, do resolve checking later */
	create_proc(scope, proc_id(proc), proc);
	if (scope_add_recurse(scope, proc))
		return scope_add_proc(scope->parent, proc);

	return 0;
}

int scope_add_trait(struct scope *scope, struct ast *trait)
{
	assert(trait->k == AST_TRAIT_DEF);

	char *id = trait_id(trait);
	struct ast *exists = file_scope_find_type(scope, id);
	if (exists) {
		semantic_error(scope->fctx, trait, "type redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	create_type(scope, id, trait);
	if (scope_add_recurse(scope, trait))
		return scope_add_trait(scope->parent, trait);

	return 0;
}

int scope_add_expd_struct(struct scope *scope, struct ast *def,
                          struct type *types, struct ast *expd)
{
	assert(def->k == AST_STRUCT_DEF);
	assert(expd->k == AST_STRUCT_DEF);
	assert(file_scope_find_expd_struct(scope, def, types) == NULL);

	create_expanded(scope, def, types, expd);
	if (scope_add_recurse(scope, expd))
		return scope_add_expd_struct(scope->parent, def, types, expd);

	return 0;
}

int scope_add_expd_chain(struct scope *scope, struct ast *def,
                         struct type *types, struct ast *expd)
{
	assert(def->k == AST_STRUCT_CONT_DEF);
	assert(expd->k == AST_STRUCT_CONT_DEF);
	assert(file_scope_find_expd_struct(scope, def, types) == NULL);

	create_expanded(scope, def, types, expd);
	if (scope_add_recurse(scope, expd))
		return scope_add_expd_chain(scope->parent, def, types, expd);

	return 0;
}

struct ast *scope_find_type(struct scope *scope, char *id)
{
	struct ast **v = visible_find(&scope->types, id);
	if (!v)
		return NULL;

	return *v;
}

struct ast *file_scope_find_type(struct scope *scope, char *id)
{
	if (!scope)
		return NULL;

	struct ast *found = scope_find_type(scope, id);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_type(scope->parent, id);

	return NULL;
}

struct ast *scope_find_macro(struct scope *scope, char *id)
{
	struct ast **v = visible_find(&scope->macros, id);
	if (!v)
		return NULL;

	return *v;
}

struct ast *file_scope_find_macro(struct scope *scope, char *id)
{
	if (!scope)
		return NULL;

	struct ast *found = scope_find_macro(scope, id);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_macro(scope->parent, id);

	return NULL;
}

struct ast *scope_find_proc(struct scope *scope, char *id)
{
	struct ast **v = visible_find(&scope->symbols, id);
	if (!v)
		return NULL;

	struct ast *n = *v;
	assert(n);

	if (n->k != AST_PROC_DEF)
		return NULL;

	return n;
}

struct ast *file_scope_find_proc(struct scope *scope, char *id)
{
	struct ast *n = file_scope_find_symbol(scope, id);
	if (!n)
		return NULL;

	if (n->k != AST_PROC_DEF)
		return NULL;

	return n;
}

struct ast *scope_find_symbol(struct scope *scope, char *id)
{
	struct ast **v = visible_find(&scope->symbols, id);
	if (!v)
		return NULL;

	return *v;
}

struct ast *file_scope_find_symbol(struct scope *scope, char *id)
{
	if (!scope)
		return NULL;

	struct ast *found = scope_find_symbol(scope, id);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_symbol(scope->parent, id);

	return NULL;
}

struct ast *scope_find_var(struct scope *scope, char *id)
{
	struct ast **v = visible_find(&scope->symbols, id);
	if (!v)
		return NULL;

	struct ast *n = *v;
	assert(n);

	if (n->k != AST_VAR_DEF)
		return NULL;

	return n;
}

struct ast *file_scope_find_var(struct scope *scope, char *id)
{
	if (!scope)
		return NULL;

	struct ast *found = scope_find_var(scope, id);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_var(scope->parent, id);

	return NULL;
}

struct ast *scope_find_expd_struct(struct scope *scope, struct ast *def,
                                   struct type *types)
{
	assert(def->k == AST_STRUCT_DEF || def->k == AST_STRUCT_CONT_DEF);
	struct expanded_key key = {.def = def, .types = types};
	struct ast **expd = expanded_find(&scope->expanded, key);
	if (!expd)
		return NULL;

	struct ast *exists = *expd;
	assert(exists->k == AST_STRUCT_DEF || exists->k == AST_STRUCT_CONT_DEF);
	return exists;
}

struct ast *file_scope_find_expd_struct(struct scope *scope, struct ast *def,
                                        struct type *types)
{
	assert(def->k == AST_STRUCT_DEF || def->k == AST_STRUCT_CONT_DEF);
	struct ast *found = scope_find_expd_struct(scope, def, types);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_expd_struct(scope->parent, def, types);

	return NULL;
}

void scope_add_scope(struct scope *parent, struct scope *child)
{
	assert(parent);
	assert(child);

	if (!scope_flags(child, SCOPE_FILE)) {
		child->fctx = parent->fctx;
	}

	child->parent = parent;
	child->next = parent->children;
	parent->children = child;
}

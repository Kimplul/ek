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

struct scope *create_scope()
{
	/* if I ever try making the parser multithreaded, this should be atomic. */
	static size_t counter = 0;

	struct scope *scope = calloc(1, sizeof(struct scope));
	if (!scope) {
		internal_error("ran out of memory allocating scope");
		return NULL;
	}

	scope->number = counter++;
	return scope;
}

void destroy_visible(struct visible *visible)
{
	struct visible *prev = visible, *cur;
	if (prev)
		do {
			cur = prev->next;
			/* destroy AST nodes globally somewhere? */
			free(prev);
		} while ((prev = cur));
}

void destroy_scope(struct scope *scope)
{
	if (!scope)
		return;

	if (scope_flags(scope, SCOPE_FILE)) {
		free((void *)scope->fctx.fbuf);
		free((void *)scope->fctx.fname);
	}

	destroy_visible(scope->vars);
	destroy_visible(scope->procs);
	destroy_visible(scope->macros);
	destroy_visible(scope->types);

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
	return scope->flags & flags;
}

static struct visible *create_visible(char *id, struct ast *node)
{
	struct visible *visible = calloc(1, sizeof(struct visible));
	visible->id = id;
	visible->node = node;
	return visible;
}

struct visible *create_type(struct scope *scope, char *id, struct ast *type)
{
	struct visible *n = create_visible(id, type);
	if (!n)
		return NULL;

	n->next = scope->types;
	scope->types = n;

	return n;
}

struct visible *create_var(struct scope *scope, char *id, struct ast *var)
{
	struct visible *n = create_visible(id, var);
	if (!n)
		return NULL;

	n->next = scope->vars;
	scope->vars = n;

	return n;
}

struct visible *create_macro(struct scope *scope, char *id, struct ast *macro)
{
	struct visible *n = create_visible(id, macro);
	if (!n)
		return NULL;

	n->next = scope->macros;
	scope->macros = n;

	return n;
}

struct visible *create_proc(struct scope *scope, char *id, struct ast *proc)
{
	struct visible *n = create_visible(id, proc);
	if (!n)
		return NULL;

	n->next = scope->procs;
	scope->procs = n;

	return n;
}

int scope_add_var(struct scope *scope, struct ast *var)
{
	struct ast *exists = file_scope_find_var(scope, var_id(var));
	if (exists) {
		semantic_error(scope->fctx, var, "var redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	create_var(scope, var_id(var), var);
	if (scope->parent &&
	    scope_flags(scope, SCOPE_FILE) && ast_flags(var, AST_FLAG_PUBLIC))
		return scope_add_var(scope->parent, var);

	return 0;
}

int scope_add_type(struct scope *scope, char *id, struct ast *type)
{
	struct ast *exists = file_scope_find_type(scope, id);
	if (exists) {
		semantic_error(scope->fctx, type, "type redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	create_type(scope, id, type);
	if (scope->parent &&
	    scope_flags(scope, SCOPE_FILE) && ast_flags(type, AST_FLAG_PUBLIC))
		return scope_add_type(scope->parent, id, type);

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
	if (scope->parent &&
	    scope_flags(scope, SCOPE_FILE) && ast_flags(macro, AST_FLAG_PUBLIC))
		return scope_add_macro(scope->parent, macro);

	return 0;
}

int scope_add_proc(struct scope *scope, struct ast *proc)
{
	assert(proc->k == AST_PROC_DEF);
	struct ast *exists = file_scope_find_proc(scope, proc_id(proc));
	if (exists) {
		semantic_error(scope->fctx, proc, "proc redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	/* always add to scope, do resolve checking later */
	create_proc(scope, proc_id(proc), proc);
	if (scope->parent &&
	    scope_flags(scope, SCOPE_FILE) && ast_flags(proc, AST_FLAG_PUBLIC))
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
	if (scope->parent &&
	    scope_flags(scope, SCOPE_FILE) && ast_flags(trait, AST_FLAG_PUBLIC))
		return scope_add_trait(scope->parent, trait);

	return 0;
}

static struct ast *scope_find_visible(struct visible *v, char *id)
{
	if (!v)
		return NULL;

	foreach_visible(n, v) {
		struct ast *node = n->node;
		if (same_id(node->s, id))
			return node;
	}

	return NULL;
}

struct ast *scope_find_type(struct scope *scope, char *id)
{
	return scope_find_visible(scope->types, id);
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
	return scope_find_visible(scope->macros, id);
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
	return scope_find_visible(scope->procs, id);
}

struct ast *file_scope_find_proc(struct scope *scope, char *id)
{
	if (!scope)
		return NULL;

	struct ast *found = scope_find_proc(scope, id);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_proc(scope->parent, id);

	return NULL;
}

struct ast *scope_find_var(struct scope *scope, char *id)
{
	return scope_find_visible(scope->vars, id);
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

void scope_add_scope(struct scope *parent, struct scope *child)
{
	assert(parent);
	assert(child);

	if (!scope_flags(child, SCOPE_FILE)) {
		child->actuals = parent->actuals;
		child->fctx = parent->fctx;
	}

	child->parent = parent;
	child->next = parent->children;
	parent->children = child;
}

static int add_actual(struct actual *actuals, struct ast *node)
{
	if (!actuals->node) {
		/* fill empty first element */
		actuals->node = node;
		return 0;
	}

	/* TODO: check that there isn't already an actual like ours */
	struct actual *actual = calloc(1, sizeof(struct actual));
	if (!actual)
		return -1;

	actual->next = actuals->next;
	actual->node = node;
	actuals->next = actual;
	return 0;
}

int scope_add_actual(struct scope *scope, struct ast *node)
{
	return add_actual(scope->actuals, node);
}

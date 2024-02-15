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

void destroy_visible(struct scope *scope, struct visible *visible)
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

	destroy_visible(scope, scope->vars);
	destroy_visible(scope, scope->types);

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

int scope_flags(struct scope *scope, enum scope_flags flags)
{
	assert(scope);
	return scope->flags & flags;
}

static struct visible *create_visible(struct ast_node *id,
                                      struct ast_node *node)
{
	struct visible *visible = calloc(1, sizeof(struct visible));
	visible->id = id;
	visible->node = node;
	return visible;
}

struct visible *create_type(struct scope *scope, struct ast_node *id,
                            struct ast_node *type)
{
	struct visible *n = create_visible(id, type);
	if (!n)
		return NULL;

	n->next = scope->types;
	scope->types = n;

	return n;
}

struct visible *create_var(struct scope *scope, struct ast_node *id,
                           struct ast_node *var)
{
	struct visible *n = create_visible(id, var);
	if (!n)
		return NULL;

	n->next = scope->vars;
	scope->vars = n;

	return n;
}

struct visible *create_macro(struct scope *scope, struct ast_node *id,
                             struct ast_node *macro)
{
	struct visible *n = create_visible(id, macro);
	if (!n)
		return NULL;

	n->next = scope->macros;
	scope->macros = n;

	return n;
}

struct visible *create_proc(struct scope *scope, struct ast_node *id,
                            struct ast_node *proc)
{
	struct visible *n = create_visible(id, proc);
	if (!n)
		return NULL;

	n->next = scope->procs;
	scope->procs = n;

	return n;
}

int scope_add_var(struct scope *scope, struct ast_node *var)
{
	struct ast_node *exists = file_scope_find_var(scope, AST_VAR(var).id);
	if (exists) {
		semantic_error(scope->fctx, var, "var redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	create_var(scope, AST_VAR(var).id, var);
	if (scope->parent &&
	    scope_flags(scope, SCOPE_FILE) && ast_flags(var, AST_FLAG_PUBLIC))
		return scope_add_var(scope->parent, var);

	return 0;
}

int scope_add_type(struct scope *scope, struct ast_node *id,
                   struct ast_node *type)
{
	struct ast_node *exists = file_scope_find_type(scope, id);
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

int scope_add_macro(struct scope *scope, struct ast_node *macro)
{
	assert(macro->node_type == AST_MACRO_CONSTRUCT);
	struct ast_node *exists = file_scope_find_macro(scope, AST_MACRO_CONSTRUCT(
								macro).id);
	if (exists) {
		semantic_error(scope->fctx, macro, "macro redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	/* always add to scope, do resolve checking later */
	create_macro(scope, AST_MACRO_CONSTRUCT(macro).id, macro);
	if (scope->parent &&
	    scope_flags(scope, SCOPE_FILE) && ast_flags(macro, AST_FLAG_PUBLIC))
		return scope_add_macro(scope->parent, macro);

	return 0;
}

int scope_add_proc(struct scope *scope, struct ast_node *proc)
{
	assert(proc->node_type == AST_PROC);
	struct ast_node *exists =
		file_scope_find_proc(scope, AST_PROC(proc).id);
	if (exists) {
		semantic_error(scope->fctx, proc, "proc redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}
	/* always add to scope, do resolve checking later */
	create_proc(scope, AST_PROC(proc).id, proc);
	if (scope->parent &&
	    scope_flags(scope, SCOPE_FILE) && ast_flags(proc, AST_FLAG_PUBLIC))
		return scope_add_proc(scope->parent, proc);

	return 0;
}

int scope_add_trait(struct scope *scope, struct ast_node *trait)
{
	assert(trait->node_type == AST_TRAIT);

	struct ast_node *id = AST_TRAIT(trait).id;
	struct ast_node *exists = file_scope_find_type(scope, id);
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

static struct ast_node *scope_find_visible(struct visible *v,
                                           struct ast_node *id)
{
	if (!v)
		return NULL;

	while (v) {
		if (identical_ast_nodes(0, v->id, id))
			return v->node;

		v = v->next;
	}

	return NULL;
}

struct ast_node *scope_find_type(struct scope *scope, struct ast_node *type)
{
	return scope_find_visible(scope->types, type);
}

struct ast_node *file_scope_find_type(struct scope *scope,
                                      struct ast_node *type)
{
	assert(type->node_type == AST_ID);
	if (!scope)
		return NULL;

	struct ast_node *found = scope_find_type(scope, type);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_type(scope->parent, type);

	return NULL;
}

struct ast_node *scope_find_macro(struct scope *scope, struct ast_node *macro)
{
	return scope_find_visible(scope->macros, macro);
}

struct ast_node *file_scope_find_macro(struct scope *scope,
                                       struct ast_node *macro)
{
	assert(macro->node_type == AST_ID);
	if (!scope)
		return NULL;

	struct ast_node *found = scope_find_macro(scope, macro);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_macro(scope->parent, macro);

	return NULL;
}

struct ast_node *scope_find_proc(struct scope *scope, struct ast_node *proc)
{
	return scope_find_visible(scope->procs, proc);
}

struct ast_node *file_scope_find_proc(struct scope *scope,
                                      struct ast_node *proc)
{
	assert(proc->node_type == AST_ID);
	if (!scope)
		return NULL;

	struct ast_node *found = scope_find_proc(scope, proc);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_proc(scope->parent, proc);

	return NULL;
}

struct ast_node *scope_find_var(struct scope *scope, struct ast_node *var)
{
	return scope_find_visible(scope->vars, var);
}

struct ast_node *file_scope_find_var(struct scope *scope, struct ast_node *var)
{
	assert(var->node_type == AST_ID);
	if (!scope)
		return NULL;

	struct ast_node *found = scope_find_var(scope, var);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_find_var(scope->parent, var);

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

static int add_actual(struct actual *actuals, struct ast_node *node)
{
	if (!actuals->node) {
		/* fill empty first element */
		actuals->node = node;
		return 0;
	}

	/* TODO: check that there isn't already an actual like ours? */
	struct actual *actual = calloc(1, sizeof(struct actual));
	if (!actual)
		return -1;

	actual->next = actuals->next;
	actual->node = node;
	actuals->next = actual;
	return 0;
}

int scope_add_actual(struct scope *scope, struct ast_node *node)
{
	return add_actual(scope->actuals, node);
}

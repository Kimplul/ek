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

static int generics_trait_type(struct ast_node *generics)
{
	if (!generics)
		return 0;

	if (actual_type(generics)->_type.kind == AST_TYPE_TEMPLATE)
		return 1;

	return generics_trait_type(generics->_type.next);
}

static int generic_type(struct ast_node *type)
{
	if (!type)
		return 0;

	if (type->_type.kind == AST_TYPE_STRUCT)
		return generics_trait_type(type->_type.struc.impls);

	if (type->_type.kind == AST_TYPE_UNION) {
		return generics_trait_type(type->_type.unio.impls);
	}

	if (type->_type.kind == AST_TYPE_TEMPLATE)
		return type->_type.template.actual == NULL;

	return generic_type(type->_type.next);
}

static int referential_type(struct ast_node *type)
{
	if (!type)
		return 0;

	if (type->_type.kind == AST_TYPE_TYPEOF)
		return 1;

	if (type->_type.kind == AST_TYPE_MEMBER)
		return 1;

	return referential_type(type->_type.next);
}

int primitive_type(struct ast_node *type)
{
	if (!type)
		return 1;

	if (referential_type(type))
		return 0;

	if (generic_type(type))
		return 0;

	return 1;
}

int fully_qualified(struct ast_node *type)
{
	if (!type)
		return 1;

	assert(type->_type.kind != AST_TYPE_TEMPLATE);
	if (type->_type.kind == AST_TYPE_STRUCT) {
		if (!ast_flags(type, AST_FLAG_GENERIC))
			return 1;

		if (type->_type.struc.impls)
			return fully_qualified(type->_type.struc.impls);

		return 0;
	}

	if (type->_type.kind == AST_TYPE_UNION) {
		if (!ast_flags(type, AST_FLAG_GENERIC))
			return 1;

		if (type->_type.unio.impls)
			return fully_qualified(type->_type.unio.impls);

		return 0;
	}

	return fully_qualified(type->_type.next);
}

static struct param_node *find_primitive(struct proc_node *node,
                                         struct ast_node *type)
{
	struct param_node *param = node->primitives;
	while (param) {
		if (types_match(type, param->type))
			return param;

		param = param->next;
	}

	return NULL;
}

static int compare_primitives(struct ast_node *a, struct ast_node *b);

/* match also checks qualification status of the types, since we can
 * differentiate between fully qualified types and not fully qualified types
 * by placing qualified types towards the front of the primitive list.
 * This is analoguous to the fallback thing in traits, but we want to be able to
 * support multiple not fully qualified primitives, for example
 *
 * add(some_generic_struct)
 * add(some_other_generic_struct)
 *
 * since they are easily distinguishable from eachother, in contract to traits.
 *
 * Therefore, use this when checking if a primitive should be added to the list,
 * otherwise use find_primitive() to get which primitive matches.
 * (are these names inverted from their intention? I'm not sure)
 */
static struct param_node *match_primitive(struct proc_node *node,
                                          struct ast_node *type)
{
	struct param_node *param = node->primitives;
	while (param) {
		/* note very subtle change in that we pass param->type first
		 * here, but second in find_primitive. This could easily be
		 * confusing... */
		if (types_match(param->type, type))
			return param;

		param = param->next;
	}

	return NULL;
}

static int match_generic(struct scope *scope, struct ast_node *a,
                         struct ast_node *b)
{
	return implements(0, scope, a, b);
}

static int compare_impls(struct ast_node *a, struct ast_node *b)
{
	if (!a)
		return 1;

	if (!b)
		return 0;

	while (a && b) {
		if (compare_primitives(a, b) == 0)
			return 0;

		a = a->next;
		b = b->next;
	}

	return 1;
}

/* return 1 if a should come after b, 0 if a should come before b */
static int compare_primitives(struct ast_node *a, struct ast_node *b)
{
	assert(a);
	if (!b)
		return 0;

	/* fully qualified types go first */
	if (fully_qualified(a))
		return 0;

	if (fully_qualified(b))
		return 1;

	/* TODO: figure out what kind of unqualified type we're dealing with,
	 * i.e. some_generic(u32, some_other_generic) should come before
	 * some_generic */

	/* if we're dealing with different unqualified types, push stuff
	 * backwards, so we don't end up with something like
	 * 1. some_generic_type
	 * 2. some_generic_union
	 * 3. some_generic_type(u32)
	 */

	if (a->_type.kind != b->_type.kind)
		return 1;

	if (a->_type.kind == AST_TYPE_STRUCT)
		return compare_impls(a->_type.struc.impls,
		                     b->_type.struc.impls);

	if (a->_type.kind == AST_TYPE_UNION)
		return compare_impls(a->_type.unio.impls, b->_type.unio.impls);

	return 1;
}

static struct proc_node *insert_primitive(struct proc_node *node,
                                          struct ast_node *type)
{
	struct param_node *new = calloc(1, sizeof(struct param_node));
	if (!new) {
		return NULL;
	}
	new->type = type;

	struct proc_node *next = calloc(1, sizeof(struct proc_node));
	if (!next) {
		free(new);
		return NULL;
	}
	new->proc = next;

	if (!node->primitives) {
		node->primitives = new;
		return next;
	}

	struct param_node *iter = node->primitives, *prev = NULL;
	while (iter && compare_primitives(type, iter->type)) {
		prev = iter;
		iter = iter->next;
	}

	if (prev)
		prev->next = new;

	new->next = iter;

	if (iter == node->primitives)
		node->primitives = new;

	return next;
}

static int add_next_resolve(struct scope *scope, struct ast_node *proc,
                            struct proc_node *node, struct ast_node *params)
{
	assert(node);
	if (params && actualize_temp_type(scope, params))
		return -1;

	/* TODO: variadics? */
	/* we've run out of params, check if this is a suitable node */
	if (!params) {
		/* node is already occupied, error on ambiguous definition */
		if (node->proc) {
			semantic_error(scope->fctx, proc, "ambiguous callable");
			semantic_error(scope->fctx, node->proc, "matches here");
			return -1;
		}

		node->proc = proc;
		return 0;
	}

	assert(params->node_type == AST_VAR);
	if (primitive_type(params->type)) {
		struct param_node *match = match_primitive(node, params->type);
		if (match)
			return add_next_resolve(scope, proc, match->proc,
			                        params->next);

		struct proc_node *next = insert_primitive(node, params->type);
		if (!next)
			return -1;

		return add_next_resolve(scope, proc, next, params->next);
	}

	if (referential_type(params->type)) {
		/* TODO: I don't think there's a good way to check if the
		 * referential types are identical, but could be worth a shot */
		if (!node->referential) {
			node->referential =
				calloc(1, sizeof(struct param_node));
			node->referential->type = params->type;

			struct proc_node *next =
				calloc(1, sizeof(struct proc_node));
			node->referential->proc = next;

			return add_next_resolve(scope, proc, next,
			                        params->next);
		}

		if (!types_match(node->referential->type, params->type)) {
			semantic_error(scope->fctx, params->type,
			               "ambiguous referential");
			semantic_error(scope->fctx, node->referential->type,
			               "matches here");
			return -1;
		}

		/* common reference */
		destroy_ast_tree(params->type);
		params->_var.type = NULL;
		params->type = node->referential->type;
		return add_next_resolve(scope, proc, node->referential->proc,
		                        params->next);
	}

	/* otherwise try to use type as fallback */
	if (!node->fallback) {
		node->fallback = calloc(1, sizeof(struct param_node));
		node->fallback->type = params->type;

		struct proc_node *next = calloc(1, sizeof(struct proc_node));
		node->fallback->proc = next;
		return add_next_resolve(scope, proc, next, params->next);
	}

	if (!match_generic(scope, node->fallback->type, params->type)) {
		semantic_error(scope->fctx, params->type, "ambiguous generic");
		semantic_info(scope->fctx, node->fallback->type,
		              "matches here");
		return -1;
	}

	/* common reference */
	destroy_ast_tree(params->type);
	params->_var.type = NULL;
	params->type = node->fallback->type;
	return add_next_resolve(scope, proc, node->fallback->proc,
	                        params->next);
}

static int add_resolve(struct scope *scope, struct proc_node *root,
                       struct ast_node *proc)
{
	assert(root);

	struct ast_node *sign = proc->_proc.sign;
	struct ast_node *params = sign->_type.sign.params;

	struct scope *resolv_scope = create_scope();
	scope_add_scope(scope, resolv_scope);
	return add_next_resolve(resolv_scope, proc, root, params);
}

static struct ast_node *proc_resolve(struct scope *scope,
                                     struct proc_node *node,
                                     struct ast_node *args)
{
	assert(node);
	if (!args) {
		if (node->proc)
			return node->proc;

		return NULL;
	}

	/* first check if we match a primitive type */
	struct param_node *found = find_primitive(node, args->type);
	if (found)
		return proc_resolve(scope, found->proc, args->next);

	/* no primitives, check referentials */
	struct param_node *ref = node->referential;
	if (ref) {
		/* this works on the assumption that references actually are
		 * references to previous nodes, which we've hopefully
		 * initialized with real types by now.
		 * However, that doesn't happen, because the fallback isn't the
		 * one that the type is assigned to. Therefore, fuck. */
		if (types_match(args->type, ref->type))
			return proc_resolve(scope, ref->proc, args->next);
	}

	/* referential didn't match, check fallback */
	struct param_node *fallback = node->fallback;
	if (!fallback)
		return NULL;

	if (implements(0, scope, args->type, fallback->type)) {
		/* my idea is that we could lock each node individually and
		 * allow multithreading scopes, but I realize that recursively
		 * checking templates might cause a lock... */
		init_template_type(fallback->type, fallback->type, args->type);
		return proc_resolve(scope, fallback->proc, args->next);
	}

	return NULL;
}

/* if I ever try making the parser multithreaded, this should be atomic. */
static size_t counter = 0;
struct scope *create_scope()
{
	/* TODO: add in a scope counter, might make things easier to see in the
	 * AST dump */
	struct scope *scope = calloc(1, sizeof(struct scope));
	if (!scope) {
		internal_error("ran out of memory allocating scope");
		return NULL;
	}

	scope->number = counter++;
	return scope;
}

struct actual *create_actuals()
{
	struct actual *actuals = calloc(1, sizeof(struct actual));
	if (!actuals) {
		internal_error("ran out of memory allocating actuals");
		return NULL;
	}

	return actuals;
}

void destroy_visible(struct scope *scope, struct visible *visible)
{
	struct visible *prev = visible, *cur;
	if (prev)
		do {
			cur = prev->next;
			/* file scope actually owns all the AST nodes, so don't
			 * try to destroy them in lower level scopes */
			if (scope_flags(scope, SCOPE_FILE))
				if (prev->owner == scope)
					destroy_ast_node(prev->node);
			free(prev);
		} while ((prev = cur));
}

static void destroy_scratch(struct scratch *scratch)
{
	struct scratch *prev = scratch, *cur;
	if (prev)
		do {
			cur = prev->next;
			destroy_ast_node(prev->node);
			free(prev);
		} while ((prev = cur));
}

void destroy_actuals(struct actual *actuals)
{
	struct actual *prev = actuals, *cur;
	if (prev)
		do {
			cur = prev->next;
			destroy_ast_node(prev->node);
			free(prev);
		} while ((prev = cur));
}

void destroy_proc_node(struct proc_node *);

void destroy_param_nodes(struct param_node *param)
{
	if (!param)
		return;

	destroy_proc_node(param->proc);
	destroy_param_nodes(param->next);
	free(param);
}

void destroy_proc_node(struct proc_node *proc)
{
	destroy_param_nodes(proc->primitives);
	destroy_param_nodes(proc->referential);
	destroy_param_nodes(proc->fallback);
	free(proc);
}

void destroy_callable(struct callable *callable)
{
	struct callable *prev = callable, *cur;
	if (prev)
		do {
			cur = prev->next;
			destroy_proc_node(prev->root);
			destroy_ast_node(prev->id);
			free(prev);
		} while ((prev = cur));
}

void destroy_scope(struct scope *scope)
{
	if (!scope)
		return;

	if (scope_flags(scope, SCOPE_FILE)) {
		destroy_actuals(scope->actuals);
		free((void *)scope->fctx.fbuf);
		free((void *)scope->fctx.fname);
	}

	destroy_scratch(scope->scratch);
	destroy_callable(scope->callable);

	destroy_visible(scope, scope->vars);
	destroy_visible(scope, scope->procs);
	destroy_visible(scope, scope->builtins);

	destroy_visible(scope, scope->enums);
	destroy_visible(scope, scope->unions);
	destroy_visible(scope, scope->structs);
	destroy_visible(scope, scope->aliases);
	destroy_visible(scope, scope->templates);

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

static struct visible *create_visible(struct scope *owner,
                                      struct ast_node *node)
{
	struct visible *visible = calloc(1, sizeof(struct visible));
	visible->node = node;
	visible->owner = owner;
	return visible;
}

static struct scratch *create_scratch(struct ast_node *scratch)
{
	struct scratch *new = calloc(1, sizeof(struct scratch));
	new->node = scratch;
	return new;
}

/* set newest member as head of linked list */
#define CREATE_VISIBLE(name, type, ast_type)                                    \
	static struct visible *name(struct scope *owner, struct ast_node *node) \
	{                                                                       \
		assert(node->node_type == ast_type);                            \
		struct visible *visible = create_visible(owner, node);          \
		visible->next = owner->type;                                    \
		owner->type = visible;                                          \
		return visible;                                                 \
	}

CREATE_VISIBLE(create_var, vars, AST_VAR);
CREATE_VISIBLE(create_macro, macros, AST_MACRO);
CREATE_VISIBLE(create_proc, procs, AST_PROC);

CREATE_VISIBLE(create_enum, enums, AST_ENUM);
CREATE_VISIBLE(create_alias, aliases, AST_ALIAS);
CREATE_VISIBLE(create_struct, structs, AST_STRUCT);
CREATE_VISIBLE(create_union, unions, AST_UNION);
CREATE_VISIBLE(create_builtin, builtins, AST_TYPE);
CREATE_VISIBLE(create_template, templates, AST_TEMPLATE);

/* TODO: check for identical names in the scope? */
#define REFERENCE_VISIBLE(name, list, ast_type)                               \
	static int name(int public, struct scope *scope, struct visible *obj) \
	{                                                                     \
		if (!scope)                                                   \
		return 0;                                                     \
		assert(obj->node->node_type == ast_type);                     \
		struct visible *ref = create_visible(obj->owner, obj->node);  \
		ref->next = scope->list;                                      \
		scope->list = ref;                                            \
		if (scope_flags(scope, SCOPE_FILE) && public)                 \
		name(scope_flags(scope, SCOPE_PUBLIC), scope->parent, obj);   \
		return 0;                                                     \
	}

REFERENCE_VISIBLE(reference_var, vars, AST_VAR);
REFERENCE_VISIBLE(reference_macro, macros, AST_MACRO);
REFERENCE_VISIBLE(reference_proc, procs, AST_PROC);

REFERENCE_VISIBLE(reference_enum, enums, AST_ENUM);
REFERENCE_VISIBLE(reference_alias, aliases, AST_ALIAS);
REFERENCE_VISIBLE(reference_union, unions, AST_UNION);
REFERENCE_VISIBLE(reference_struct, structs, AST_STRUCT);
REFERENCE_VISIBLE(reference_builtin, builtins, AST_TYPE);
REFERENCE_VISIBLE(reference_template, templates, AST_TEMPLATE);

/* does NOT walk the scope tree upward if it doesn't find the var in the scope
 * */
#define FIND_VISIBLE(name, list, ast_type, ast_name)                             \
	struct ast_node *name(struct scope *scope, struct ast_node *id)          \
	{                                                                        \
		assert(id->node_type == AST_ID);                                 \
		struct visible *prev = scope->list, *cur;                        \
		if (prev) {                                                      \
			do {                                                     \
				cur = prev->next;                                \
				if (identical_ast_nodes(0,                       \
				                        prev->node->ast_name.id, \
				                        id)) {                   \
					return prev->node;                       \
				}                                                \
			} while ((prev = cur));                                  \
		}                                                                \
		return NULL;                                                     \
	}

FIND_VISIBLE(scope_find_enum, enums, AST_ENUM, _enum);
FIND_VISIBLE(scope_find_alias, aliases, AST_ALIAS, _alias);
FIND_VISIBLE(scope_find_builtin, builtins, AST_TYPE, _type);
FIND_VISIBLE(scope_find_struct, structs, AST_STRUCT, _struct);
FIND_VISIBLE(scope_find_union, unions, AST_UNION, _union);
FIND_VISIBLE(scope_find_template, templates, AST_TEMPLATE, _template);
/* note that these return the first match for the ID, and as such might not be
 * what should be called. */
FIND_VISIBLE(scope_find_var, vars, AST_VAR, _var);
FIND_VISIBLE(scope_find_macro, macros, AST_MACRO, _macro);
FIND_VISIBLE(scope_find_proc, procs, AST_PROC, _proc);

struct ast_node *scope_find(struct scope *scope, struct ast_node *id)
{
	assert(id->node_type == AST_ID);

	struct ast_node *found = scope_find_var(scope, id);
	if (found)
		return found;

	found = scope_find_proc(scope, id);
	if (found)
		return found;

	found = scope_find_macro(scope, id);
	if (found)
		return found;

	found = scope_find_alias(scope, id);
	if (found)
		return found;

	found = scope_find_template(scope, id);
	if (found)
		return found;

	return NULL;
}

/* procedure adding requires a bit of tweaking, as a different number of
 * arguments effectively means different functions, not just the name */
#define ADD_VISIBLE(name, obj_type, ast_type, ast_name)                          \
	int name(struct scope *scope, struct ast_node *node)                     \
	{                                                                        \
		assert(node->node_type == ast_type);                             \
		struct ast_node *shadow = file_scope_find(scope,                 \
		                                          node->ast_name.id);    \
		if (shadow) {                                                    \
			semantic_error(scope->fctx, node,                        \
			               "shadowing is not allowed");              \
			semantic_info(scope->fctx, shadow,                       \
			              "previous declaration was here");          \
			return -1;                                               \
		}                                                                \
		int public = scope_flags(scope, SCOPE_PUBLIC);                   \
		struct visible *visible = create_##obj_type(scope, node);        \
		if (scope_flags(scope,                                           \
		                SCOPE_FILE) && ast_flags(node, AST_FLAG_PUBLIC)) \
		return reference_##obj_type(public, scope->parent, visible);     \
		return 0;                                                        \
	}

struct visible *create_type(struct scope *scope, struct ast_node *type)
{
	switch (type->node_type) {
	case AST_TYPE: return create_builtin(scope, type);
	case AST_ALIAS: return create_alias(scope, type);
	case AST_TEMPLATE: return create_template(scope, type);
	case AST_ENUM: return create_enum(scope, type);
	case AST_STRUCT: return create_struct(scope, type);
	case AST_UNION: return create_union(scope, type);
	default:
		semantic_error(scope->fctx, type, "unknown type");
		return NULL;
	}
}

int reference_type(int public, struct scope *scope, struct visible *visible)
{
	switch (visible->node->node_type) {
	case AST_TYPE: return reference_builtin(public, scope, visible);
	case AST_ALIAS: return reference_alias(public, scope, visible);
	case AST_TEMPLATE: return reference_template(public, scope, visible);
	case AST_ENUM: return reference_enum(public, scope, visible);
	case AST_STRUCT: return reference_struct(public, scope, visible);
	case AST_UNION: return reference_union(public, scope, visible);
	default:
		semantic_error(scope->fctx, visible->node, "unknown type");
		return 1;
	}
}

int scope_add_type(struct scope *scope, struct ast_node *type)
{
	struct ast_node *exists = file_scope_resolve_type(scope, type);

	/* redefining a type to itself is allowed, and might be necessary for
	 * some generics operations. I'll have to double check this later,
	 * though */
	/* e.g. struct (vec{t}) or something, all instances of this 'type'
	 * detected anywhere should be allowed to be 'added' */
	if (exists)
		return 0;

	int public = scope_flags(scope, SCOPE_PUBLIC);
	/* during a redefine, if it's redefined to public should it be
	 * propagated upward? Probably not, but dunno for sure yet */
	struct visible *visible = create_type(scope, type);
	if (scope_flags(scope, SCOPE_FILE) && ast_flags(type, AST_FLAG_PUBLIC))
		return reference_type(public, scope->parent, visible);

	return 0;
}

struct ast_node *scope_find_type(struct scope *scope, struct ast_node *id)
{
	assert(id->node_type == AST_ID);

	struct ast_node *found = scope_find_builtin(scope, id);
	if (found)
		return found;

	found = scope_find_enum(scope, id);
	if (found)
		return found;

	found = scope_find_struct(scope, id);
	if (found)
		return found;

	found = scope_find_union(scope, id);
	if (found)
		return found;

	found = scope_find_alias(scope, id);
	if (found)
		return found;

	found = scope_find_template(scope, id);
	if (found)
		return found;

	return NULL;
}

ADD_VISIBLE(scope_add_var, var, AST_VAR, _var);
ADD_VISIBLE(scope_add_alias, alias, AST_ALIAS, _alias);
ADD_VISIBLE(scope_add_template, template, AST_TEMPLATE, _template);

static int add_implementation(struct ast_node *template, struct ast_node *type)
{
	assert(
		template->node_type == AST_TEMPLATE &&
		type->node_type == AST_TYPE);
	struct template_implemented *by = calloc(1, sizeof(*type));
	if (!by) {
		internal_error("failed allocating memory for implementation");
		return 1;
	}

	by->type = type;
	by->next = template->_template.impl_by;
	template->_template.impl_by = by;
	return 0;
}

static void remove_implementation(struct ast_node *template,
                                  struct ast_node *type)
{
	assert(template->node_type == AST_TEMPLATE);
	struct template_implemented *prev = template->_template.impl_by, *cur;
	if (prev)
		do {
			cur = prev->next;
			if (!cur)
				break;

			if (identical_ast_nodes(0, cur->type, type)) {
				struct template_implemented *next = cur->next;
				prev->next = next;
				free(cur);
				return;
			}
		} while ((prev = cur));
}

static int find_implementation(struct ast_node *template, struct ast_node *type)
{
	if (!type)
		return 0;

	assert(template->node_type == AST_TEMPLATE);
	if (type->_type.kind == AST_TYPE_TEMPLATE)
		return find_implementation(template,
		                           type->_type.template.actual);

	if (type->_type.kind == AST_TYPE_ALIAS)
		return find_implementation(template, type->_type.alias.actual);

	/* I'm not 100% sold on having to handle these special cases multiple
	 * times in different places, but I'm not sure what alternatives I have.
	 * For debugging purposes, maintaining as much info about the original
	 * code is useful, but I wonder if I can somehow maybe clone this stuff
	 * and keep a reference to the original or something without too much
	 * work? TODO */
	if (type->_type.kind == AST_TYPE_TYPEOF)
		return find_implementation(template, type->_type.typeo.actual);

	struct template_implemented *prev = template->_template.impl_by, *cur;
	if (prev)
		do {
			cur = prev->next;
			if (identical_ast_nodes(0, prev->type, type)) {
				return 1;
			}
		} while ((prev = cur));

	return 0;
}

static struct ast_node *match_macro(int global, struct scope *scope,
                                    struct ast_node *id, struct ast_node *args)
{
	const size_t arg_count = ast_list_len(args);
	struct visible *prev = scope->macros, *cur;
	if (prev)
		do {
			cur = prev->next;
			struct ast_node *macro = prev->node;
			/* must have identical IDs */
			if (!identical_ast_nodes(0, macro->_macro.id, id))
				continue;

			const size_t param_count = ast_list_len(
				macro->_macro.params);

			/* if macros have the same number of arguments, they
			 * match */
			if (param_count == arg_count)
				return macro;

			/* if we have a variadic macro, a longer list of args is
			 * a match */
			if (ast_flags(macro, AST_FLAG_VARIADIC)
			    && param_count < arg_count)
				return macro;

		} while ((prev = cur));

	if (global && !scope_flags(scope, SCOPE_FILE))
		return match_macro(global, scope->parent, id, args);

	return NULL;
}

static struct ast_node *match_proc(enum match_flags flags, struct scope *scope,
                                   struct ast_node *id, struct ast_node *args);

static int implements_proc(enum match_flags flags, struct scope *scope,
                           struct ast_node *arg_type,
                           struct ast_node *param_type, struct ast_node *proc)
{
	assert(proc->node_type == AST_PROC);
	/* temp */
	struct ast_node *id = proc->_proc.id;
	/* this removes type info, bit of an issue */
	struct ast_node *sign = clone_ast_node(proc->_proc.sign);
	struct ast_node *params = sign->_type.sign.params;
	struct ast_node *ret = sign->_type.sign.ret;

	init_template_types(params, param_type, arg_type);
	init_template_type(ret, param_type, arg_type);

	struct ast_node *impl = match_proc(1, scope, id, params);
	if (!impl)
		goto out;

	struct ast_node *impl_ret = impl->_proc.sign->_type.sign.ret;
	/* note important distinction between when to use ->type and when to not
	 * in short: ->type can be a template or alias, not using it is the type
	 * before being resolved.
	 */
	/* TODO: detect loops, such as when two template return params rely on
	 * eachother */
	if (!implements(flags, scope, impl_ret, ret)) {
		char *irt = type_str(impl_ret);
		char *prt = type_str(ret);
		semantic_error(scope->fctx, proc, "return type mismatch");
		semantic_info(scope->fctx, impl,
		              "found return type %s, expected %s",
		              irt, prt);
		free(irt);
		free(prt);
		impl = NULL;
	}

out:
	destroy_ast_node(sign);
	return impl != NULL;
}

static int implements_var(enum match_flags flags, struct scope *scope,
                          struct ast_node *arg_type,
                          struct ast_node *param_type, struct ast_node *var)
{
	(void)(flags);
	(void)(scope);
	(void)(arg_type);
	(void)(param_type);
	assert(var->node_type == AST_VAR);
	/* temp */
	return 0;
}

static int implements_template(enum match_flags flags, struct scope *scope,
                               struct ast_node *arg_type,
                               struct ast_node *param_type)
{
	assert(param_type->_type.kind == AST_TYPE_TEMPLATE);
	if (param_type->_type.template.actual)
		return implements(flags, scope, arg_type,
		                  param_type->_type.template.actual);

	struct ast_node *template = param_type->_type.template.template;
	/* if we already know we implement this template, nothing to do */
	if (find_implementation(template, arg_type))
		return 1;

	/* optimistically assume we implement type template */
	/* TODO: this optimism might be questionable, as some template might rely
	 * on another template being implemented by the same type.
	 * The other type will return an error message, and the compilation will
	 * fail, but the error messages generated might be misleading. Look into
	 * it at some point. */
	add_implementation(template, arg_type);

	struct ast_node *body = template->_template.body;

	/* if the body is empty, match */
	struct ast_node *elem = body;
	if (elem)
		do {
			if (elem->node_type == AST_VAR) {
				if (implements_var(flags, scope, arg_type,
				                   param_type,
				                   elem))
					continue;

				char *type = type_str(arg_type);
				struct ast_node *id = elem->_proc.id;
				semantic_error(scope->fctx, elem,
				               "%s does not have member %s",
				               type, id->_id.id);
				free(type);
				goto not_implemented;
			}

			else if (elem->node_type == AST_PROC) {
				if (implements_proc(flags, scope, arg_type,
				                    param_type,
				                    elem))
					continue;

				char *type = type_str(arg_type);
				struct ast_node *id = elem->_proc.id;
				semantic_error(scope->fctx, elem,
				               "%s does not implement %s",
				               type, id->_id.id);
				free(type);
				goto not_implemented;
			}

			else {
				semantic_error(scope->fctx, elem,
				               "illegal template element");
				goto not_implemented;
			}
		} while ((elem = elem->next));

	return 1;

not_implemented:
	remove_implementation(template, arg_type);
	return 0;
}

static int implements_alias(enum match_flags flags, struct scope *scope,
                            struct ast_node *arg_type,
                            struct ast_node *param_type)
{
	while (arg_type && arg_type->_type.kind == AST_TYPE_ALIAS)
		arg_type = arg_type->_type.alias.actual;

	while (param_type && param_type->_type.kind == AST_TYPE_ALIAS)
		param_type = param_type->_type.alias.actual;

	return implements(flags, scope, arg_type, param_type);
}

static int implements_typeof(enum match_flags flags, struct scope *scope,
                             struct ast_node *arg_type,
                             struct ast_node *param_type)
{
	while (arg_type && arg_type->_type.kind == AST_TYPE_TYPEOF)
		arg_type = arg_type->_type.typeo.actual;

	while (param_type && param_type->_type.kind == AST_TYPE_TYPEOF)
		param_type = param_type->_type.typeo.actual;

	return implements(flags, scope, arg_type, param_type);
}

int implements(enum match_flags flags, struct scope *scope,
               struct ast_node *arg_type, struct ast_node *param_type)
{
	/* if both types are null, they are uninitialized and we'll assume they
	 * don't implement eachother. This essentially means that during the
	 * analysis phase everything is added to the procs */
	if (!arg_type && !param_type)
		return 0;

	/* only the variadic argument in parameters has no type, so any actual
	 * type implements it */
	/* slight hack: macro arguments also don't have a type, so they will
	 * also 'implement' type */
	if (!param_type)
		return 1;

	/* at this point, we should always have some type for the argument */
	assert(arg_type);

	if (param_type->_type.kind == AST_TYPE_ALIAS ||
	    arg_type->_type.kind == AST_TYPE_ALIAS) {
		assert(param_type->_type.next == NULL);
		return implements_alias(flags, scope, arg_type, param_type);
	}


	if (param_type->_type.kind == AST_TYPE_TYPEOF ||
	    arg_type->_type.kind == AST_TYPE_TYPEOF) {
		/* if we're comparing procedure definitions, be more lenient */
		if (!(flags & MATCH_CALL) &&
		    param_type->_type.kind != arg_type->_type.kind)
			return 0;

		return implements_typeof(flags, scope, arg_type, param_type);
	}

	/* having the arg be a template is a bit of a special case */
	if (arg_type->_type.kind == AST_TYPE_TEMPLATE) {
		if (arg_type->_type.template.actual == NULL)
			return types_match(arg_type, param_type);

		return implements(flags, scope, arg_type->_type.template.actual,
		                  param_type);
	}

	/* TODO: do aliases and templates have to be converted to types? Are
	 * there any situations where a template will have to be followed by
	 * some other type? */
	/* if the parameter type is not a template, it's an actual type and therefore the
	 * argument type must be identical to it */
	if (param_type->_type.kind == AST_TYPE_TEMPLATE) {
		if (param_type->_type.template.actual == NULL)
			return implements_template(flags, scope, arg_type,
			                           param_type);

		return implements(flags, scope, arg_type,
		                  param_type->_type.template.actual);
	}

	if (param_type->_type.kind == AST_TYPE_POINTER) {
		if (arg_type->_type.kind != AST_TYPE_POINTER)
			return 0;

		return implements(flags, scope, arg_type->_type.next,
		                  param_type->_type.next);
	}

	if (!types_match(arg_type, param_type))
		return 0;

	/* if both types have next elements in them, analyze them as well */
	if (arg_type->_type.next && param_type->_type.next)
		return implements(flags, scope, arg_type->_type.next,
		                  param_type->_type.next);

	/* if this is the last type element in both types, they match */
	if (!arg_type->_type.next && !param_type->_type.next)
		return 1;

	/* otherwise, no match */
	return 0;
}

/* has to be executed in a temporary scope */
static int match_args(enum match_flags flags, struct scope *scope, int variadic,
                      const struct ast_node *args,
                      const struct ast_node *params)
{
	/* no arguments matches to no parameters */
	if (!params && !args)
		return 1;

	while (params && args) {
		if (!implements(flags, scope, args->type, params->type))
			return 0;

		init_template_type(params->type, params->type, args->type);

		params = params->next;
		args = args->next;
	}

	if (args) {
		/* if we have arguments left over and the proc is variadic, we
		 * match. The last argument is replaced with the trailing list
		 * of arguments beyond the parameter list. */
		if (variadic)
			return 1;

		return 0;
	}

	/* we have more parameters compared to arguments, so there's no way we
	 * match */
	if (params)
		return 0;

	/* we have the same number of arguments and they all implement the
	 * parameters, so we match */
	return 1;
}

static int match_params(enum match_flags flags, struct scope *scope,
                        int variadic,
                        struct ast_node *args, struct ast_node *params)
{
	struct scope *tmp_scope = create_temp_scope(scope);
	/* if the args aren't actualized, we're in the analysis phase? */
	/* TODO: this isn't necessary for actualized procedures */
	struct ast_node *params_clone = clone_ast_node(params);
	if (args->type && actualize_temp_type(tmp_scope, params_clone)) {
		destroy_ast_tree(params_clone);
		destroy_scope(tmp_scope);
		return 0;
	}

	int ret = match_args(flags, tmp_scope, variadic, args, params_clone);
	destroy_ast_tree(params_clone);
	destroy_scope(tmp_scope);
	return ret;
}

static struct ast_node *match_proc(enum match_flags flags, struct scope *scope,
                                   struct ast_node *id, struct ast_node *args)
{
	(void)(flags);
	struct callable *cb = scope->callable;
	while (cb) {
		if (identical_ast_nodes(0, cb->id, id))
			return proc_resolve(scope, cb->root, args);
	}
	return NULL;
}

int scope_add_macro(struct scope *scope, struct ast_node *macro)
{
	assert(macro->node_type == AST_MACRO);

	/* TODO: separate between arrays and macros? */
	struct ast_node *id = macro->_macro.id;
	struct ast_node *params = macro->_macro.params;

	int macro_exists = match_macro(0, scope, id, params) != NULL;
	// TODO: search for any proc with same number of parameters as macro */
	// int proc_exists = match_proc(0, scope, id, params) != NULL;
	int proc_exists = 0;

	if (macro_exists || proc_exists) {
		semantic_error(scope->fctx, macro, "macro redefined");
		return -1;
	}

	struct visible *new = create_macro(scope, macro);
	if (!new)
		return -1;

	int public = scope_flags(scope, SCOPE_PUBLIC);
	if (scope_flags(scope, SCOPE_FILE) && ast_flags(macro, AST_FLAG_PUBLIC))
		return reference_macro(public, scope->parent, new);

	return 0;
}

/* would be useful with scope_remove_proc which also removed all references? */
int scope_add_proc(struct scope *scope, struct ast_node *proc)
{
	assert(proc->node_type == AST_PROC);

	struct ast_node *id = proc->_proc.id;
	struct ast_node *sign = proc->_proc.sign;
	struct ast_node *params = sign->_type.sign.params;

	struct ast_node *macro_exists = match_macro(0, scope, id, params);

	if (macro_exists) {
		semantic_error(scope->fctx, proc, "proc redefined");
		semantic_info(scope->fctx, macro_exists, "previously as macro");
		return -1;
	}

	struct visible *new = create_proc(scope, proc);
	if (!new)
		return -1;

	int public = scope_flags(scope, SCOPE_PUBLIC);
	if (scope_flags(scope, SCOPE_FILE) && ast_flags(proc, AST_FLAG_PUBLIC))
		return reference_proc(public, scope->parent, new);

	return 0;
}

int scope_add_existing_var(struct scope *scope, struct visible *visible)
{
	struct ast_node *node = visible->node;
	assert(node->node_type == AST_VAR);
	struct ast_node *shadow = file_scope_find(scope, node->_var.id);
	if (shadow) {
		semantic_error(scope->fctx, node, "shadowing is not allowed\n");
		semantic_info(scope->fctx, shadow,
		              "previous declaration was here\n");
		return -1;
	}

	visible->next = scope->vars;
	scope->vars = visible;

	int public = scope_flags(scope, SCOPE_PUBLIC);
	if (scope_flags(scope, SCOPE_FILE) && ast_flags(node, AST_FLAG_PUBLIC))
		return reference_proc(public, scope->parent, visible);

	return 0;
}

int scope_add_existing_proc(struct scope *scope, struct visible *visible)
{
	struct ast_node *proc = visible->node;
	assert(proc->node_type == AST_PROC);

	struct ast_node *id = proc->_proc.id;
	struct ast_node *sign = proc->_proc.sign;
	struct ast_node *params = sign->_type.sign.params;

	struct ast_node *macro_exists = match_macro(0, scope, id, params);
	if (macro_exists) {
		semantic_error(scope->fctx, proc, "proc redefined");
		semantic_info(scope->fctx, macro_exists, "previously as macro");
		return -1;
	}

	if (!scope->callable) {
		scope->callable = calloc(1, sizeof(struct callable));
		scope->callable->root = calloc(1, sizeof(struct proc_node));
		scope->callable->id = clone_ast_node(id);
		return add_resolve(scope, scope->callable->root, proc);
	}

	struct callable *cb = scope->callable;
	while (cb) {
		if (identical_ast_nodes(0, cb->id, id))
			return add_resolve(scope, cb->root, proc);

		cb = cb->next;
	}

	cb = calloc(1, sizeof(struct callable));
	cb->root = calloc(1, sizeof(struct proc_node));
	cb->id = clone_ast_node(id);
	cb->next = scope->callable;
	scope->callable = cb;
	return add_resolve(scope, cb->root, proc);
}

#define FIND_FILE_VISIBLE(name, obj_type)                                     \
	struct ast_node *name(struct scope *scope, struct ast_node *id)       \
	{                                                                     \
		assert(id->node_type == AST_ID);                              \
		struct ast_node *found = scope_find_##obj_type(scope, id);    \
		if (found) {                                                  \
			return found;                                         \
		}                                                             \
		if (!scope_flags(scope, SCOPE_FILE)) {                        \
			return file_scope_find_##obj_type(scope->parent, id); \
		}                                                             \
		return NULL;                                                  \
	}

struct ast_node *file_scope_find_type(struct scope *scope,
                                      struct ast_node *type)
{
	assert(type->node_type == AST_ID);
	struct ast_node *found = scope_find_type(scope, type);
	if (found)
		return found;

	if (!found && !scope_flags(scope, SCOPE_FILE))
		return file_scope_find_type(scope->parent, type);

	return NULL;
}

FIND_FILE_VISIBLE(file_scope_find_var, var);
FIND_FILE_VISIBLE(file_scope_find_proc, proc);
FIND_FILE_VISIBLE(file_scope_find_macro, macro);

FIND_FILE_VISIBLE(file_scope_find_alias, alias);
FIND_FILE_VISIBLE(file_scope_find_template, template);

struct ast_node *file_scope_find(struct scope *scope, struct ast_node *id)
{
	/* TODO: should probably check for incoming search and filter out params
	 * etc */
	assert(id->node_type == AST_ID);

	struct ast_node *found = file_scope_find_var(scope, id);
	if (found)
		return found;

	found = file_scope_find_proc(scope, id);
	if (found)
		return found;

	found = file_scope_find_macro(scope, id);
	if (found)
		return found;

	found = file_scope_find_alias(scope, id);
	if (found)
		return found;

	found = file_scope_find_template(scope, id);
	if (found)
		return found;

	return NULL;
}

struct ast_node *scope_resolve_macro(struct scope *scope, struct ast_node *call)
{
	assert(call->node_type == AST_CALL);
	struct ast_node *id = call->_call.id;
	struct ast_node *args = call->_call.args;
	return match_macro(0, scope, id, args);
}

static int template_contains_proc(enum match_flags flags, struct scope *scope,
                                  struct ast_node *template,
                                  struct ast_node *id, struct ast_node *args)
{
	assert(template->_type.kind == AST_TYPE_TEMPLATE);
	template = template->_type.template.template;

	struct ast_node *elem = template->_template.body;
	if (elem)
		do {
			if (elem->node_type != AST_PROC)
				continue;

			if (!identical_ast_nodes(0, elem->_proc.id, id))
				continue;

			/* TODO: should I check for return type here as well? */
			int variadic = ast_flags(elem, AST_FLAG_VARIADIC);
			struct ast_node *sign = elem->_proc.sign;
			struct ast_node *params = sign->_type.sign.params;
			if (match_params(flags, scope, variadic, args, params))
				return 1;

		} while ((elem = elem->next));

	return 0;
}

struct ast_node *scope_resolve_proc(struct scope *scope, struct ast_node *call)
{
	/* TODO: we should prefer specialized procs over generic ones.
	 * i.e. do_stuff(a u32){} should be preferred over do_stuff(a some_type){},
	 * when u32 implements some_type. */
	assert(call->node_type == AST_CALL);
	struct ast_node *id = call->_call.id;
	struct ast_node *args = call->_call.args;

	/* TODO: this prints out an error for each scope we run through, figure
	 * out where we should check for this stuff so only a single error is
	 * printed */
	/* loop over arguments, if any of them are templated check that the
	 * found proc can be found in the template */
	struct ast_node *arg = args;
	while (arg) {
		struct ast_node *template = extract_template(arg->type);
		if (!template)
			goto next;

		if (!template_contains_proc(MATCH_CALL, scope, template, id,
		                            args)) {
			char *cstr = call_str(call);
			char *tstr = type_str(arg);
			semantic_error(scope->fctx, arg,
			               "%s not associated with %s",
			               cstr,
			               tstr);
			free(cstr);
			free(tstr);
			return NULL;
		}

next:
		arg = arg->next;
	}

	struct ast_node *proc = match_proc(MATCH_CALL, scope, id, args);
	if (!proc)
		return NULL;

	return proc;
}

struct ast_node *scope_resolve_actual(struct scope *scope,
                                      struct ast_node *call)
{
	assert(call->node_type == AST_CALL);
	struct actual *prev = scope->actuals, *cur;

	if (prev)
		do {
			cur = prev->next;
			struct ast_node *actual = prev->node;
			if (!actual)
				continue;

			if (!identical_ast_nodes(0, actual->_proc.id,
			                         call->_call.id))
				continue;

			assert(!ast_flags(actual, AST_FLAG_VARIADIC));
			/* could also check that arguments aren't templates */
			struct ast_node *args = call->_call.args;
			struct ast_node *sign = actual->_proc.sign;
			struct ast_node *params = sign->_type.sign.params;
			if (match_params(0, scope, 0, args, params))
				return actual;

		} while ((prev = cur));

	return NULL;
}

struct ast_node *scope_resolve_arr(struct scope *scope, struct ast_node *call)
{
	assert(call->node_type == AST_CALL);
	/* could implement arrays in multiple dimensions, though that might make
	 * other things complicated so disallow it for now */
	if (ast_list_len(call->_call.args) != 1)
		return NULL;

	struct ast_node *arg = call->_call.args;
	struct ast_node *var = scope_find_var(scope, call->_call.id);
	if (!var)
		return NULL;

	/* TODO: actualize has types_match, should it be generalized into ast.c
	 * or something? */
	if (!identical_ast_nodes(0, var->type, arg->type))
		return NULL;

	return var;
}

struct ast_node *scope_resolve_call(struct scope *scope, struct ast_node *call)
{
	assert(call->node_type == AST_CALL);
	/* TODO: should make sure we're getting an array at some point */
	struct ast_node *found = scope_resolve_arr(scope, call);
	if (found)
		return found;

	found = scope_resolve_macro(scope, call);
	if (found)
		return found;

	found = scope_resolve_actual(scope, call);
	if (found)
		return found;

	found = scope_resolve_proc(scope, call);
	if (found)
		return found;

	return NULL;
}

struct ast_node *file_scope_resolve_call(struct scope *scope,
                                         struct ast_node *call)
{
	struct ast_node *found = scope_resolve_call(scope, call);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_resolve_call(scope->parent, call);

	return NULL;
}

struct ast_node *scope_resolve_type(struct scope *scope, struct ast_node *type)
{
	struct ast_node *id = NULL;
	switch (type->node_type) {
	case AST_ID: id = type; break;
	case AST_TYPE:
		assert(type->_type.kind == AST_TYPE_ID);
		id = type->_type.id;
		break;

	case AST_ALIAS:
		id = type->_alias.id;
		break;

	case AST_TEMPLATE:
		id = type->_template.id;
		break;

	case AST_STRUCT:
		id = type->_struct.id;
		break;

	case AST_UNION:
		id = type->_union.id;
		break;

	case AST_ENUM:
		id = type->_enum.id;
		break;

	default:
		semantic_error(scope->fctx, type, "unknown type");
		return NULL;
	}

	return scope_find_type(scope, id);
}

struct ast_node *file_scope_resolve_type(struct scope *scope,
                                         struct ast_node *type)
{
	struct ast_node *found = scope_resolve_type(scope, type);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_resolve_type(scope->parent, type);

	return NULL;
}

/* this might be useful somewhere else as well */
static const char *default_types[] = {"u8", "u16", "u32", "u64",
	                              "i8" "i16", "i32", "i64",
	                              "usize", "isize", "f32", "f64", "void"};

/* TODO: add error checking */
int scope_add_defaults(struct scope *root)
{
	for (size_t i = 0; i < sizeof(default_types) / sizeof(default_types[0]);
	     ++i) {
		const char *type = default_types[i];
		struct ast_node *n = gen_id(strdup(type));
		if (!n)
			return -1;

		struct ast_node *a = gen_type(AST_TYPE_ID, n, NULL, NULL);
		if (!a)
			return -1;

		scope_add_type(root, a);
	}

	return 0;
}

void scope_destroy_defaults(struct scope *scope)
{
	/* just enough data to get through to the actual default aliases */
	struct ast_node type = {0};
	type.node_type = AST_ID;

	for (size_t i = 0; i < sizeof(default_types) / sizeof(default_types[0]);
	     ++i) {
		type._id.id = default_types[i];
		struct ast_node *n = scope_find_alias(scope, &type);
		/* something is afoot, but at least try to free the rest */
		if (!n)
			continue;

		destroy_ast_node(n);
	}
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
	/* TODO: check that there isn't already an actual like ours */
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

static struct ast_node *find_actual(struct actual *actuals,
                                    struct ast_node *node)
{
	assert(node->node_type == AST_ID);

	if (actuals)
		do {
			struct ast_node *actual = actuals->node;
			if (identical_ast_nodes(0, actual->_proc.id, node))
				return actual;

		} while ((actuals = actuals->next));

	return NULL;
}

struct ast_node *scope_find_actual(struct scope *scope, struct ast_node *node)
{
	return find_actual(scope->actuals, node);
}

int scope_add_scratch(struct scope *scope, struct ast_node *scratch)
{
	struct scratch *new = create_scratch(scratch);
	if (!new) {
		internal_error("failed allocating scratch node");
		return -1;
	}

	new->next = scope->scratch;
	scope->scratch = new;
	return 0;
}

struct scope *create_temp_scope(struct scope *parent)
{
	struct scope *scope = create_scope();
	if (!scope) {
		internal_error("failed allocating temp scope");
	}

	scope->parent = parent;
	scope->fctx = parent->fctx;
	return scope;
}

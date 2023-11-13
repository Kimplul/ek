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

static struct ast_node *match_proc(struct scope *scope,
                                   struct ast_node *id,
				   struct ast_node *args);

static struct ast_node *match_macro(struct scope *scope,
                                    struct ast_node *id, struct ast_node *args);

static struct param_node *find_matching_param(struct resolve_node *node,
                                         struct ast_node *type)
{
	struct param_node *param = node->params;
	while (param) {
		if (types_match(type, param->type))
			return param;

		param = param->next;
	}

	return NULL;
}

static int traits_resolve(struct ast_node *arg_type, struct ast_node *param_type)
{
	/** @todo are more checks required? */
	return AST_TYPE(arg_type).as == AST_TRAIT_TYPE(param_type).def;
}

static int typeofs_resolve(struct ast_node *arg_type, struct ast_node *param_type)
{
	internal_error("typeof resolve unimplemented");
	return 0;
}

static int types_resolve(struct ast_node *arg_type, struct ast_node *param_type)
{
	/* untyped resolves all */
	if (!param_type)
		return 1;

	if (AST_TYPE(param_type).kind == AST_TYPE_TRAIT)
		return traits_resolve(arg_type, param_type);

	if (AST_TYPE(param_type).kind == AST_TYPE_TYPEOF)
		return typeofs_resolve(arg_type, param_type);

	return types_match(arg_type, param_type);
}

static struct param_node *find_resolving_param(struct resolve_node *node,
		struct ast_node *type)
{
	struct param_node *param = node->params;
	while (param) {
		if (types_resolve(type, param->type))
			return param;

		param = param->next;
	}

	return NULL;
}

static struct resolve_node *insert_resolve(struct resolve_node *node,
                                          struct ast_node *type)
{
	struct param_node *new = calloc(1, sizeof(struct param_node));
	if (!new) {
		return NULL;
	}
	new->type = type;

	struct resolve_node *next = calloc(1, sizeof(struct resolve_node));
	if (!next) {
		free(new);
		return NULL;
	}
	new->resolved = next;

	if (!node->params) {
		node->params = new;
		return next;
	}

	new->next = node->params;
	node->params = new;

	return next;
}

static int add_next_resolve(struct scope *scope, struct ast_node *resolve,
                            struct resolve_node *node, struct ast_node *params)
{
	assert(node);
	if (params && actualize_temp_type(scope, params))
		return -1;

	/* TODO: variadics in macros? */
	/* we've run out of params, check if this is a suitable node */
	if (!params) {
		/* node is already occupied, error on ambiguous definition */
		if (node->resolved) {
			semantic_error(scope->fctx, resolve, "ambiguous resolution");
			semantic_error(scope->fctx, node->resolved, "matches here");
			return -1;
		}

		node->resolved = resolve;
		return 0;
	}

	assert(params->node_type == AST_VAR);
	struct param_node *match = find_matching_param(node, params->type);
	if (match)
		return add_next_resolve(scope, resolve,
				match->resolved,
					params->next);

	/** @todo referential stuff, should only one be allowed per slot or
	 * something? */
	struct resolve_node *next = insert_resolve(node, params->type);
	if (!next)
		return -1;

	return add_next_resolve(scope, resolve, next, params->next);
}

static int add_resolve(struct scope *scope, struct resolve *resolve,
                       struct ast_node *proc)
{
	struct ast_node *sign = AST_PROC(proc).sign;
	struct ast_node *params = AST_SIGN_TYPE(sign).params;
	return add_next_resolve(scope, proc, resolve->root, params);
}

static struct ast_node *resolve(struct scope *scope,
                                     struct resolve_node *node,
                                     struct ast_node *args)
{
	assert(node);
	/* check for no parameters case */
	if (!args) {
		if (node->resolved)
			return node->resolved;

		return NULL;
	}

	struct param_node *found = find_resolving_param(node, args->type);
	if (found)
		return resolve(scope, found->resolved, args->next);

	return NULL;
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
			/* destroy AST nodes globally somewhere? */
			free(prev);
		} while ((prev = cur));
}

void destroy_actuals(struct actual *actuals)
{
	struct actual *prev = actuals, *cur;
	if (prev)
		do {
			cur = prev->next;
			free(prev);
		} while ((prev = cur));
}

void destroy_resolve_node(struct resolve_node *);

void destroy_param_nodes(struct param_node *param)
{
	if (!param)
		return;

	destroy_resolve_node(param->resolved);
	destroy_param_nodes(param->next);
	free(param);
}

void destroy_resolve_node(struct resolve_node *resolve)
{
	if (!resolve)
		return;

	destroy_param_nodes(resolve->params);
	free(resolve);
}

void destroy_resolve(struct resolve *resolve)
{
	struct resolve *prev = resolve, *cur;
	if (prev)
		do {
			cur = prev->next;
			destroy_resolve_node(prev->root);
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

	destroy_resolve(scope->proc_resolve);
	destroy_resolve(scope->macro_resolve);
	destroy_resolve(scope->type_construct_resolve);

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

struct visible *create_type(struct scope *scope, struct ast_node *id, struct ast_node *type)
{
	struct visible *n = create_visible(id, type);
	if (!n)
		return NULL;

	n->next = scope->types;
	scope->types = n;
	return n;
}

struct visible *create_var(struct scope *scope, struct ast_node *id, struct ast_node *var)
{
	struct visible *n = create_visible(id, var);
	if (!n)
		return NULL;

	n->next = scope->vars;
	scope->vars = n;
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

	struct visible *visible = create_var(scope, AST_VAR(var).id, var);
	if (scope_flags(scope, SCOPE_FILE) && ast_flags(var, AST_FLAG_PUBLIC))
		return scope_add_var(scope->parent, var);

	return 0;
}

int scope_add_type(struct scope *scope, struct ast_node *id, struct ast_node *type)
{
	struct ast_node *exists = file_scope_find_type(scope, id);
	/* redefining a type to itself is allowed, and might be necessary for
	 * some generics operations. I'll have to double check this later,
	 * though */
	if (exists) {
		semantic_error(scope->fctx, type, "type redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	/* during a redefine, if it's redefined to public should it be
	 * propagated upward? Probably not, but dunno for sure yet */
	struct visible *visible = create_type(scope, id, type);
	if (scope_flags(scope, SCOPE_FILE) && ast_flags(type, AST_FLAG_PUBLIC))
		return scope_add_type(scope->parent, id, type);

	return 0;
}

static void remove_implementation(struct ast_node *trait,
                                  struct ast_node *type)
{
	assert(trait->node_type == AST_TRAIT);
	struct trait_implemented *prev = trait->_trait.impl_by, *cur;
	if (prev)
		do {
			cur = prev->next;
			if (!cur)
				break;

			if (identical_ast_nodes(0, cur->type, type)) {
				struct trait_implemented *next = cur->next;
				prev->next = next;
				free(cur);
				return;
			}
		} while ((prev = cur));
}

static int implements_proc(enum match_flags flags, struct scope *scope,
                           struct ast_node *arg_type,
                           struct ast_node *param_type, struct ast_node *proc)
{
	(void)(flags);
	(void)(scope);
	(void)(arg_type);
	(void)(param_type);
	assert(proc->node_type == AST_PROC);
	/** @todo implement */
	return 0;
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
	/** @todo implement */
	return 0;
}

static int implements_trait(enum match_flags flags, struct scope *scope,
                               struct ast_node *arg_type,
                               struct ast_node *param_type)
{
	assert(AST_TYPE(param_type).kind == AST_TYPE_TRAIT);
	struct ast_node *trait = AST_TRAIT_TYPE(param_type).def;
	struct ast_node *body = AST_TRAIT(trait).body;

	/* if the body is empty, match */
	struct ast_node *elem = body;
	if (!elem)
		return 1;

	/* this is somewhat ugly, hmmm */
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
				       "illegal trait element");
			goto not_implemented;
		}
	} while ((elem = elem->next));

	return 1;

not_implemented:
	remove_implementation(trait, arg_type);
	return 0;
}

static int implements_typeof(enum match_flags flags, struct scope *scope,
                             struct ast_node *arg_type,
                             struct ast_node *param_type)
{
	internal_error("typeof implementation unimplemented");
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

	/* slight hack: macro arguments also don't have a type, so they will
	 * also 'implement' type */
	if (!param_type)
		return 1;

	/* at this point, we should always have some type for the argument */
	assert(arg_type);

	if (AST_TYPE(param_type).kind == AST_TYPE_TYPEOF)
		return implements_typeof(flags, scope, arg_type, param_type);

	if (AST_TYPE(param_type).kind == AST_TYPE_TRAIT)
		return implements_trait(flags, scope, arg_type, param_type);

	return types_match(arg_type, param_type);
}

static int match_actual_params(enum match_flags flags, struct scope *scope,
                        struct ast_node *args, struct ast_node *params)
{
	/** @todo essentially just iterate over the parameters, right? */
	return 0;
}

static struct ast_node *match_resolve(struct scope *scope,
		struct resolve *s,
		struct ast_node *id,
		struct ast_node *args)
{
	while (s) {
		/** @todo linear search, a hashmap would be faster */
		if (identical_ast_nodes(0, s->id, id))
			return resolve(scope, s->root, args);

		s = s->next;
	}

	return NULL;
}

static struct ast_node *match_macro(struct scope *scope,
		struct ast_node *id,
		struct ast_node *args)
{
	return match_resolve(scope, scope->macro_resolve, id, args);
}

static struct ast_node *match_proc(struct scope *scope,
                                   struct ast_node *id,
				   struct ast_node *args)
{
	return match_resolve(scope, scope->proc_resolve, id, args);
}

static struct ast_node *match_type_construct(struct scope *scope,
		struct ast_node *id,
		struct ast_node *args)
{
	return match_resolve(scope, scope->type_construct_resolve, id, args);
}


static int add_proc_resolve(struct scope *scope, struct ast_node *proc)
{
	if (!scope->proc_resolve) {
		scope->proc_resolve = calloc(1, sizeof(struct resolve));
	}

	struct resolve *resolve = scope->proc_resolve;
	while (resolve) {
		if (identical_ast_nodes(0, resolve->id, proc->_proc.id))
			return add_resolve(scope, resolve, proc);

		resolve = resolve->next;
	}

	resolve = calloc(1, sizeof(struct resolve));
	resolve->root = calloc(1, sizeof(struct resolve_node));
	resolve->id = clone_ast_node(proc->_proc.id);
	resolve->next = scope->proc_resolve;
	scope->proc_resolve = resolve;

	return add_resolve(scope, resolve, proc);
}

static int add_macro_resolve(struct scope *scope, struct ast_node *macro)
{
	if (!scope->macro_resolve) {
		scope->macro_resolve = calloc(1, sizeof(struct resolve));
	}

	struct resolve *resolve = scope->macro_resolve;
	while (resolve) {
		if (identical_ast_nodes(0, resolve->id, AST_MACRO_CONSTRUCT(macro).id))
			return add_resolve(scope, resolve, macro);

		resolve = resolve->next;
	}

	resolve = calloc(1, sizeof(struct resolve));
	resolve->root = calloc(1, sizeof(struct resolve_node));
	resolve->id = clone_ast_node(AST_MACRO_CONSTRUCT(macro).id);
	resolve->next = scope->macro_resolve;
	scope->macro_resolve = resolve;

	return add_resolve(scope, resolve, macro);
}

int scope_add_macro(struct scope *scope, struct ast_node *macro)
{
	assert(macro->node_type == AST_MACRO_CONSTRUCT);
	struct ast_node *id = AST_MACRO_CONSTRUCT(macro).id;
	struct ast_node *params = AST_MACRO_CONSTRUCT(macro).params;

	struct ast_node *exists = match_macro(scope, id, params);;
	if (exists) {
		semantic_error(scope->fctx, macro, "macro redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	add_macro_resolve(scope, macro);

	if (scope_flags(scope, SCOPE_FILE) && ast_flags(macro, AST_FLAG_PUBLIC))
		return scope_add_macro(scope->parent, macro);

	return 0;
}

int add_type_construct_resolve(struct scope *scope, struct ast_node *type_construct)
{
	if (!scope->type_construct_resolve) {
		scope->type_construct_resolve = calloc(1, sizeof(struct resolve));
	}

	struct resolve *resolve = scope->type_construct_resolve;
	while (resolve) {
		if (identical_ast_nodes(0, resolve->id, AST_TYPE_CONSTRUCT(type_construct).id))
			return add_resolve(scope, resolve, type_construct);

		resolve = resolve->next;
	}

	resolve = calloc(1, sizeof(struct resolve));
	resolve->root = calloc(1, sizeof(struct resolve_node));
	resolve->id = clone_ast_node(AST_TYPE_CONSTRUCT(type_construct).id);
	resolve->next = scope->type_construct_resolve;
	scope->type_construct_resolve = resolve;

	return add_resolve(scope, resolve, type_construct);
}

int scope_add_proc(struct scope *scope, struct ast_node *proc)
{
	assert(proc->node_type == AST_PROC);

	struct ast_node *id = AST_PROC(proc).id;
	struct ast_node *sign = AST_PROC(proc).sign;
	struct ast_node *params = AST_SIGN_TYPE(sign).params;

	struct ast_node *exists = match_proc(scope, id, params);

	if (exists) {
		semantic_error(scope->fctx, proc, "proc redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	add_proc_resolve(scope, proc);

	if (scope_flags(scope, SCOPE_FILE) && ast_flags(proc, AST_FLAG_PUBLIC))
		return scope_add_proc(scope->parent, proc);

	return 0;
}

int scope_add_type_construct(struct scope *scope, struct ast_node *type_construct)
{
	assert(type_construct->node_type == AST_TYPE_CONSTRUCT);

	struct ast_node *id = AST_TYPE_CONSTRUCT(type_construct).id;
	struct ast_node *params = AST_TYPE_CONSTRUCT(type_construct).params;

	struct ast_node *exists = match_type_construct(scope, id, params);
	if (exists) {
		semantic_error(scope->fctx, type_construct, "type construct redefined");
		semantic_info(scope->fctx, exists, "previously here");
		return -1;
	}

	add_type_construct_resolve(scope, type_construct);

	if (scope_flags(scope, SCOPE_FILE) && ast_flags(type_construct, AST_FLAG_PUBLIC))
		return scope_add_type_construct(scope->parent, type_construct);

	return 0;
}

static struct ast_node *scope_find_visible(struct visible *v, struct ast_node *id)
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

struct ast_node *scope_resolve_macro(struct scope *scope, struct ast_node *macro)
{
	assert(macro->node_type == AST_MACRO_EXPAND);
	struct ast_node *id = macro->_macro_expand.id;
	struct ast_node *args = macro->_macro_expand.args;
	return match_macro(scope, id, args);
}

struct ast_node *scope_resolve_proc(struct scope *scope, struct ast_node *call)
{
	assert(call->node_type == AST_CALL);
	struct ast_node *id = call->_call.id;
	struct ast_node *args = call->_call.args;
	return match_proc(scope, id, args);
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
			/* could also check that arguments aren't traits */
			struct ast_node *args = AST_CALL(call).args;
			struct ast_node *sign = AST_PROC(actual).sign;
			struct ast_node *params = AST_SIGN_TYPE(sign).params;
			if (match_actual_params(0, scope, args, params))
				return actual;

		} while ((prev = cur));

	return NULL;
}

struct ast_node *scope_resolve_call(struct scope *scope, struct ast_node *call)
{
	assert(call->node_type == AST_CALL);
	/* unsure if actual should be here or somewhere else but eh */
	struct ast_node *found = scope_resolve_actual(scope, call);
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

struct ast_node *file_scope_resolve_macro(struct scope *scope, struct ast_node *macro)
{
	struct ast_node *found = scope_resolve_macro(scope, macro);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_resolve_macro(scope->parent, macro);

	return NULL;
}

/* this might be useful somewhere else as well */
static const char *default_types[] = {"void", "i9", "i27"};

/* TODO: add error checking */
int scope_add_defaults(struct scope *root)
{
	for (size_t i = 0;
	     i < sizeof(default_types) / sizeof(default_types[0]);
	     ++i) {
		const char *type = default_types[i];
		struct ast_node *n = gen_id(strdup(type), NULL_LOC());
		if (!n)
			return -1;

		struct ast_node *a = gen_type(AST_TYPE_PRIMITIVE, n, NULL, NULL);
		if (!a)
			return -1;

		scope_add_type(root, n, a);
	}

	return 0;
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

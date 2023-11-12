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

static int generics_trait_type(struct ast_node *generics)
{
	if (!generics)
		return 0;

	if (actual_type(generics)->_type.kind == AST_TYPE_TRAIT)
		return 1;

	return generics_trait_type(generics->_type.next);
}

static int generic_type(struct ast_node *type)
{
	if (!type)
		return 0;

	if (type->_type.kind == AST_TYPE_STRUCT)
		return generics_trait_type(type->_type.struc.impls);

	if (type->_type.kind == AST_TYPE_TRAIT)
		return type->_type.trait.actual == NULL;

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

	assert(type->_type.kind != AST_TYPE_TRAIT);
	if (type->_type.kind == AST_TYPE_STRUCT) {
		if (!ast_flags(type, AST_FLAG_GENERIC))
			return 1;

		if (type->_type.struc.impls)
			return fully_qualified(type->_type.struc.impls);

		return 0;
	}

	return fully_qualified(type->_type.next);
}

static struct param_node *find_matching_param(struct resolve_node *node,
                                         struct ast_node *type)
{
	struct param_node *param = node->params;
	while (param) {
		/* untyped matches everything, yay */
		if (!param->type)
			return param;

		if (types_match(type, param->type))
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
	struct ast_node *sign = proc->_proc.sign;
	struct ast_node *params = sign->_type.sign.params;

	struct scope *resolv_scope = create_scope();
	scope_add_scope(scope, resolv_scope);
	return add_next_resolve(resolv_scope, proc, resolve->root, params);
}

static struct ast_node *resolve(struct scope *scope,
                                     struct resolve_node *node,
                                     struct ast_node *args)
{
	assert(node);
	if (!args) {
		if (node->resolved)
			return node->resolved;

		return NULL;
	}

	/* first check if we match a primitive type */
	struct param_node *found = find_matching_param(node, args->type);
	if (found)
		return resolve(scope, found->resolved, args->next);

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
	destroy_resolve(scope->proc_resolve);
	destroy_resolve(scope->macro_resolve);
	destroy_resolve(scope->type_construct_resolve);

	destroy_visible(scope, scope->vars);
	destroy_visible(scope, scope->procs);
	destroy_visible(scope, scope->builtins);

	destroy_visible(scope, scope->enums);
	destroy_visible(scope, scope->structs);
	destroy_visible(scope, scope->aliases);
	destroy_visible(scope, scope->traits);

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
CREATE_VISIBLE(create_proc, procs, AST_PROC);
CREATE_VISIBLE(create_macro, macros, AST_MACRO_CONSTRUCT);
CREATE_VISIBLE(create_type_construct, type_constructs, AST_TYPE_CONSTRUCT);

CREATE_VISIBLE(create_enum, enums, AST_ENUM);
CREATE_VISIBLE(create_alias, aliases, AST_ALIAS);
CREATE_VISIBLE(create_struct, structs, AST_STRUCT);
CREATE_VISIBLE(create_builtin, builtins, AST_TYPE);
CREATE_VISIBLE(create_trait, traits, AST_TRAIT);

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
REFERENCE_VISIBLE(reference_proc, procs, AST_PROC);
REFERENCE_VISIBLE(reference_macro, macros, AST_MACRO_CONSTRUCT);

REFERENCE_VISIBLE(reference_enum, enums, AST_ENUM);
REFERENCE_VISIBLE(reference_trait, traits, AST_TRAIT);
REFERENCE_VISIBLE(reference_alias, aliases, AST_ALIAS);
REFERENCE_VISIBLE(reference_struct, structs, AST_STRUCT);
REFERENCE_VISIBLE(reference_builtin, builtins, AST_TYPE);
REFERENCE_VISIBLE(reference_type_construct, type_constructs, AST_TYPE_CONSTRUCT);

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
FIND_VISIBLE(scope_find_trait, traits, AST_TRAIT, _trait);
/* note that these return the first match for the ID, and as such might not be
 * what should be called. */
FIND_VISIBLE(scope_find_var, vars, AST_VAR, _var);
FIND_VISIBLE(scope_find_proc, procs, AST_PROC, _proc);
FIND_VISIBLE(scope_find_macro, macros, AST_MACRO_CONSTRUCT, _macro);
FIND_VISIBLE(scope_find_type_construct, type_constructs, AST_TYPE_CONSTRUCT, type_construct);

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

	found = scope_find_trait(scope, id);
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
		struct ast_node *shadow = file_scope_find_##obj_type(scope,                 \
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
	case AST_TRAIT: return create_trait(scope, type);
	case AST_ENUM: return create_enum(scope, type);
	case AST_STRUCT: return create_struct(scope, type);
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
	case AST_TRAIT: return reference_trait(public, scope, visible);
	case AST_ENUM: return reference_enum(public, scope, visible);
	case AST_STRUCT: return reference_struct(public, scope, visible);
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

	found = scope_find_alias(scope, id);
	if (found)
		return found;

	found = scope_find_trait(scope, id);
	if (found)
		return found;

	return NULL;
}

ADD_VISIBLE(scope_add_var, var, AST_VAR, _var);
ADD_VISIBLE(scope_add_alias, alias, AST_ALIAS, _alias);
ADD_VISIBLE(scope_add_trait, trait, AST_TRAIT, _trait);

static int add_implementation(struct ast_node *trait, struct ast_node *type)
{
	assert(
		trait->node_type == AST_TRAIT &&
		type->node_type == AST_TYPE);
	struct trait_implemented *by = calloc(1, sizeof(*type));
	if (!by) {
		internal_error("failed allocating memory for implementation");
		return 1;
	}

	by->type = type;
	by->next = trait->_trait.impl_by;
	trait->_trait.impl_by = by;
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

static int find_implementation(struct ast_node *trait, struct ast_node *type)
{
	if (!type)
		return 0;

	assert(trait->node_type == AST_TRAIT);
	if (type->_type.kind == AST_TYPE_TRAIT)
		return find_implementation(trait,
		                           type->_type.trait.actual);

	if (type->_type.kind == AST_TYPE_ALIAS)
		return find_implementation(trait, type->_type.alias.actual);

	/* I'm not 100% sold on having to handle these special cases multiple
	 * times in different places, but I'm not sure what alternatives I have.
	 * For debugging purposes, maintaining as much info about the original
	 * code is useful, but I wonder if I can somehow maybe clone this stuff
	 * and keep a reference to the original or something without too much
	 * work? TODO */
	if (type->_type.kind == AST_TYPE_TYPEOF)
		return find_implementation(trait, type->_type.typeo.actual);

	struct trait_implemented *prev = trait->_trait.impl_by, *cur;
	if (prev)
		do {
			cur = prev->next;
			if (identical_ast_nodes(0, prev->type, type)) {
				return 1;
			}
		} while ((prev = cur));

	return 0;
}

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

	init_trait_types(params, param_type, arg_type);
	init_trait_type(ret, param_type, arg_type);

	struct ast_node *impl = match_proc(scope, id, params);
	if (!impl)
		goto out;

	struct ast_node *impl_ret = impl->_proc.sign->_type.sign.ret;
	/* note important distinction between when to use ->type and when to not
	 * in short: ->type can be a trait or alias, not using it is the type
	 * before being resolved.
	 */
	/* TODO: detect loops, such as when two trait return params rely on
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

static int implements_trait(enum match_flags flags, struct scope *scope,
                               struct ast_node *arg_type,
                               struct ast_node *param_type)
{
	assert(param_type->_type.kind == AST_TYPE_TRAIT);
	if (param_type->_type.trait.actual)
		return implements(flags, scope, arg_type,
		                  param_type->_type.trait.actual);

	struct ast_node *trait = param_type->_type.trait.trait;
	/* if we already know we implement this trait, nothing to do */
	if (find_implementation(trait, arg_type))
		return 1;

	/* optimistically assume we implement type trait */
	/* TODO: this optimism might be questionable, as some trait might rely
	 * on another trait being implemented by the same type.
	 * The other type will return an error message, and the compilation will
	 * fail, but the error messages generated might be misleading. Look into
	 * it at some point. */
	add_implementation(trait, arg_type);

	struct ast_node *body = trait->_trait.body;

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
				               "illegal trait element");
				goto not_implemented;
			}
		} while ((elem = elem->next));

	return 1;

not_implemented:
	remove_implementation(trait, arg_type);
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

	/* having the arg be a trait is a bit of a special case */
	if (arg_type->_type.kind == AST_TYPE_TRAIT) {
		if (arg_type->_type.trait.actual == NULL)
			return types_match(arg_type, param_type);

		return implements(flags, scope, arg_type->_type.trait.actual,
		                  param_type);
	}

	/* TODO: do aliases and traits have to be converted to types? Are
	 * there any situations where a trait will have to be followed by
	 * some other type? */
	/* if the parameter type is not a trait, it's an actual type and therefore the
	 * argument type must be identical to it */
	if (param_type->_type.kind == AST_TYPE_TRAIT) {
		if (param_type->_type.trait.actual == NULL)
			return implements_trait(flags, scope, arg_type,
			                           param_type);

		return implements(flags, scope, arg_type,
		                  param_type->_type.trait.actual);
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

		init_trait_type(params->type, params->type, args->type);

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

int scope_add_macro(struct scope *scope, struct ast_node *macro)
{
	assert(macro->node_type == AST_MACRO_CONSTRUCT);

	/* TODO: separate between arrays and macros? */
	struct ast_node *id = macro->_macro.id;
	struct ast_node *params = macro->_macro.params;

	int macro_exists = (match_macro(scope, id, params) != NULL);
	if (macro_exists) {
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

int add_proc_resolve(struct scope *scope, struct ast_node *proc)
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

int add_macro_resolve(struct scope *scope, struct ast_node *macro)
{
	if (!scope->macro_resolve) {
		scope->macro_resolve = calloc(1, sizeof(struct resolve));
	}

	struct resolve *resolve = scope->macro_resolve;
	while (resolve) {
		if (identical_ast_nodes(0, resolve->id, macro->_macro.id))
			return add_resolve(scope, resolve, macro);

		resolve = resolve->next;
	}

	resolve = calloc(1, sizeof(struct resolve));
	resolve->root = calloc(1, sizeof(struct resolve_node));
	resolve->id = clone_ast_node(macro->_macro.id);
	resolve->next = scope->macro_resolve;
	scope->macro_resolve = resolve;

	return add_resolve(scope, resolve, macro);
}

int add_type_construct_resolve(struct scope *scope, struct ast_node *type_construct)
{
	if (!scope->type_construct_resolve) {
		scope->type_construct_resolve = calloc(1, sizeof(struct resolve));
	}

	struct resolve *resolve = scope->type_construct_resolve;
	while (resolve) {
		if (identical_ast_nodes(0, resolve->id, AST_GET(type_construct, id)))
			return add_resolve(scope, resolve, type_construct);

		resolve = resolve->next;
	}

	resolve = calloc(1, sizeof(struct resolve));
	resolve->root = calloc(1, sizeof(struct resolve_node));
	resolve->id = clone_ast_node(AST_GET(type_construct, id));
	resolve->next = scope->type_construct_resolve;
	scope->type_construct_resolve = resolve;

	return add_resolve(scope, resolve, type_construct);
}

/* would be useful with scope_remove_proc which also removed all references? */
int scope_add_proc(struct scope *scope, struct ast_node *proc)
{
	assert(proc->node_type == AST_PROC);

	struct ast_node *id = proc->_proc.id;
	struct ast_node *sign = proc->_proc.sign;
	struct ast_node *params = sign->_type.sign.params;

	struct ast_node *macro_exists = match_proc(scope, id, params);

	if (macro_exists) {
		semantic_error(scope->fctx, proc, "proc redefined");
		semantic_info(scope->fctx, macro_exists, "previously as macro");
		return -1;
	}

	struct visible *new = create_proc(scope, proc);
	if (!new)
		return -1;

	add_proc_resolve(scope, proc);

	int public = scope_flags(scope, SCOPE_PUBLIC);
	if (scope_flags(scope, SCOPE_FILE) && ast_flags(proc, AST_FLAG_PUBLIC))
		return reference_proc(public, scope->parent, new);

	return 0;
}

int scope_add_type_construct(struct scope *scope, struct ast_node *type_construct)
{
	assert(type_construct->node_type == AST_TYPE_CONSTRUCT);

	struct ast_node *id = AST_GET(type_construct, id);
	struct ast_node *params = AST_GET(type_construct, params);

	int type_construct_exists = (match_type_construct(scope, id, params) != NULL);
	if (type_construct_exists) {
		semantic_error(scope->fctx, type_construct, "type construct redefined");
		return -1;
	}

	struct visible *new = create_type_construct(scope, type_construct);
	if (!new)
		return -1;

	int public = scope_flags(scope, SCOPE_PUBLIC);
	if (scope_flags(scope, SCOPE_FILE) && ast_flags(type_construct, AST_FLAG_PUBLIC))
		return reference_type_construct(public, scope->parent, new);

	return 0;
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
FIND_FILE_VISIBLE(file_scope_find_trait, trait);

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

	found = file_scope_find_trait(scope, id);
	if (found)
		return found;

	return NULL;
}

struct ast_node *scope_resolve_macro(struct scope *scope, struct ast_node *macro)
{
	assert(macro->node_type == AST_MACRO_EXPAND);
	struct ast_node *id = macro->_macro_expand.id;
	struct ast_node *args = macro->_macro_expand.args;
	return match_macro(scope, id, args);
}

static int trait_contains_proc(enum match_flags flags, struct scope *scope,
                                  struct ast_node *trait,
                                  struct ast_node *id, struct ast_node *args)
{
	assert(trait->_type.kind == AST_TYPE_TRAIT);
	trait = trait->_type.trait.trait;

	struct ast_node *elem = trait->_trait.body;
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
			struct ast_node *args = call->_call.args;
			struct ast_node *sign = actual->_proc.sign;
			struct ast_node *params = sign->_type.sign.params;
			if (match_params(0, scope, 0, args, params))
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

	case AST_TRAIT:
		id = type->_trait.id;
		break;

	case AST_STRUCT:
		id = type->_struct.id;
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

struct ast_node *file_scope_resolve_macro(struct scope *scope, struct ast_node *macro)
{
	struct ast_node *found = scope_resolve_macro(scope, macro);
	if (found)
		return found;

	if (!scope_flags(scope, SCOPE_FILE))
		return file_scope_resolve_type(scope->parent, macro);

	return NULL;
}

/* this might be useful somewhere else as well */
static const char *default_types[] = {"u8", "u16", "u32", "u64",
	                              "i8" "i16", "i32", "i64",
	                              "usize", "isize",
	                              "f32", "f64",
	                              "bool", "void"};

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

	for (size_t i = 0;
	     i < sizeof(default_types) / sizeof(default_types[0]);
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

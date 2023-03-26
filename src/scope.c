/* SPDX-License-Identifier: GPL-3.0-or-later */

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

#include <cu/debug.h>
#include <cu/scope.h>
#include <cu/actualize.h>

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

	destroy_visible(scope, scope->vars);
	destroy_visible(scope, scope->procs);
	destroy_visible(scope, scope->macros);
	destroy_visible(scope, scope->builtins);
	destroy_visible(scope, scope->overrides);

	destroy_visible(scope, scope->enums);
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
CREATE_VISIBLE(create_proc, procs, AST_PROC);
CREATE_VISIBLE(create_macro, macros, AST_MACRO);

CREATE_VISIBLE(create_enum, enums, AST_ENUM);
CREATE_VISIBLE(create_alias, aliases, AST_ALIAS);
CREATE_VISIBLE(create_struct, structs, AST_STRUCT);
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
REFERENCE_VISIBLE(reference_proc, procs, AST_PROC);
REFERENCE_VISIBLE(reference_macro, macros, AST_MACRO);
REFERENCE_VISIBLE(reference_override, overrides, AST_PROC);

REFERENCE_VISIBLE(reference_enum, enums, AST_ENUM);
REFERENCE_VISIBLE(reference_alias, aliases, AST_ALIAS);
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
FIND_VISIBLE(scope_find_template, templates, AST_TEMPLATE, _template);
/* note that these return the first match for the ID, and as such might not be
 * what should be called. */
FIND_VISIBLE(scope_find_var, vars, AST_VAR, _var);
FIND_VISIBLE(scope_find_proc, procs, AST_PROC, _proc);
FIND_VISIBLE(scope_find_override, overrides, AST_PROC, _proc);
FIND_VISIBLE(scope_find_macro, macros, AST_MACRO, _macro);

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
	assert(template->node_type == AST_TEMPLATE);
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

static struct ast_node *match_proc(int global, struct scope *scope,
                                   struct ast_node *id, struct ast_node *args);

static int implements_proc(struct scope *scope, struct ast_node *arg_type,
                           struct ast_node *param_type, struct ast_node *proc)
{
	assert(proc->node_type == AST_PROC);
	/* temp */
	struct ast_node *id = proc->_proc.id;
	/* this removes type info, bit of an issue */
	struct ast_node *sign = clone_ast_node(proc->_proc.sign);
	struct ast_node *params = sign->_type.sign.params;
	struct ast_node *ret = sign->_type.sign.ret;

	replace_param_types(params, param_type, arg_type);
	replace_param_types(ret, param_type, arg_type);

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
	if (!implements(scope, impl_ret, ret)) {
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

static int implements_var(struct scope *scope, struct ast_node *arg_type,
                          struct ast_node *param_type, struct ast_node *var)
{
	assert(var->node_type == AST_VAR);
	/* temp */
	return 0;
}

static int implements_template(struct scope *scope, struct ast_node *arg_type,
                               struct ast_node *param_type)
{
	assert(param_type->_type.kind == AST_TYPE_TEMPLATE);
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
				if (implements_var(scope, arg_type, param_type,
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
				if (implements_proc(scope, arg_type, param_type,
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

int implements(struct scope *scope,
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

	if (param_type->_type.kind == AST_TYPE_ALIAS) {
		assert(param_type->_type.next == NULL);
		return implements(scope, arg_type,
		                  param_type->_type.alias.actual);
	}

	if (arg_type->_type.kind == AST_TYPE_ALIAS) {
		assert(arg_type->_type.next == NULL);
		return implements(scope, arg_type->_type.alias.actual,
		                  param_type);
	}

	/* TODO: do aliases and templates have to be converted to types? Are
	 * there any situations where a template will have to be followed by
	 * some other type? */
	/* if the parameter type is not a template, it's an actual type and therefore the
	 * argument type must be identical to it */
	if (param_type->_type.kind == AST_TYPE_TEMPLATE) {
		/* the argument type must at this point be templateable, i.e.
		 * 'i64 does not implement some_type, but would implement
		 * 'some_type
		   if (!is_templateable(arg_type))
		        return 0;
		 */

		return implements_template(scope, arg_type, param_type);
	}

	if (!types_match(arg_type, param_type))
		return 0;

	/* if both types have next elements in them, analyze them as well */
	if (arg_type->_type.next && param_type->_type.next)
		return implements(scope, arg_type->_type.next,
		                  param_type->_type.next);

	/* if this is the last type element in both types, they match */
	if (!arg_type->_type.next && !param_type->_type.next)
		return 1;

	/* otherwise, no match */
	return 0;
}

static int match_args(struct scope *scope, int variadic,
                      const struct ast_node *args,
                      const struct ast_node *params)
{
	/* no arguments matches to no parameters */
	if (!params && !args)
		return 1;

	while (params && args) {
		if (!implements(scope, args->type, params->type))
			return 0;

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

static struct ast_node *iter_procs(struct scope *scope, struct visible *first,
                                   struct ast_node *id, struct ast_node *args)
{
	struct visible *prev = first, *cur;
	if (prev)
		do {
			cur = prev->next;
			struct ast_node *proc = prev->node;
			/* must have identical IDs */
			if (!identical_ast_nodes(0, proc->_proc.id, id))
				continue;

			const int variadic = ast_flags(proc, AST_FLAG_VARIADIC);
			const struct ast_node *sign = proc->_proc.sign;
			const struct ast_node *params = sign->_type.sign.params;
			if (match_args(scope, variadic, args, params))
				return proc;

		} while ((prev = cur));

	return NULL;
}

static struct ast_node *match_proc(int global, struct scope *scope,
                                   struct ast_node *id, struct ast_node *args)
{
	struct ast_node *override =
		iter_procs(scope, scope->overrides, id, args);
	if (override)
		return override;

	struct ast_node *proc = iter_procs(scope, scope->procs, id, args);
	if (proc)
		return proc;

	if (global && !scope_flags(scope, SCOPE_FILE))
		return match_proc(global, scope->parent, id, args);

	return NULL;
}

int scope_add_macro(struct scope *scope, struct ast_node *macro)
{
	assert(macro->node_type == AST_MACRO);

	/* TODO: separate between arrays and macros? */
	struct ast_node *id = macro->_macro.id;
	struct ast_node *params = macro->_macro.params;

	int macro_exists = match_macro(0, scope, id, params) != NULL;
	int proc_exists = match_proc(0, scope, id, params) != NULL;

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

	int macro_exists = match_macro(0, scope, id, params) != NULL;
	int proc_exists = match_proc(0, scope, id, params) != NULL;

	if (macro_exists || proc_exists) {
		semantic_error(scope->fctx, proc, "proc redefined");
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

	int macro_exists = match_macro(0, scope, id, params) != NULL;
	int proc_exists = match_proc(0, scope, id, params) != NULL;

	if (macro_exists || proc_exists) {
		semantic_error(scope->fctx, proc, "proc redefined");
		return -1;
	}

	struct ast_node *template = NULL;
	while (params) {
		if ((template = extract_template(params->type)))
			break;

		params = params->next;
	}

	if (template) {
		visible->next = scope->procs;
		scope->procs = visible;
	}
	else {
		/* override is maybe a bit misleading, but essentially any
		 * procedure with no templates */
		visible->next = scope->overrides;
		scope->overrides = visible;
	}

	int public = scope_flags(scope, SCOPE_PUBLIC);
	if (scope_flags(scope,
	                SCOPE_FILE) && ast_flags(proc, AST_FLAG_PUBLIC)) {
		if (template)
			return reference_proc(public, scope->parent, visible);

		return reference_override(public, scope->parent, visible);
	}

	return 0;
}

#define FIND_FILE_VISIBLE(name, obj_type)                                  \
	struct ast_node *name(struct scope *scope, struct ast_node *id)    \
	{                                                                  \
		assert(id->node_type == AST_ID);                           \
		struct ast_node *found = scope_find_##obj_type(scope, id); \
		if (found)                                                 \
		return found;                                              \
		if (!scope_flags(scope, SCOPE_FILE))                       \
		return file_scope_find_##obj_type(scope->parent, id);      \
		return NULL;                                               \
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
FIND_FILE_VISIBLE(file_scope_find_override, override);
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

static int template_contains_proc(struct scope *scope,
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
			if (match_args(scope, variadic, args, params))
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

		if (!template_contains_proc(scope, template, id, args)) {
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

	struct ast_node *proc = match_proc(0, scope, id, args);
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
			const struct ast_node *args = call->_call.args;
			const struct ast_node *sign = actual->_proc.sign;
			const struct ast_node *params = sign->_type.sign.params;
			if (match_args(scope, 0, args, params))
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
	/* TODO */
	internal_error("finding actuals not yet implemented");
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

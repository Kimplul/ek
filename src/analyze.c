/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

/**
 * @file analyze.c
 *
 * Implementations for stuff actualization.
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <ek/analyze.h>
#include <ek/compiler.h>
#include <ek/debug.h>
#include <ek/vec.h>

#define UNUSED(x) do { (void)(x); } while (0)
#define MAYBE_UNUSED(x) UNUSED(x)

struct act_stack {
	struct ast *node;
	struct act_stack *next;
};

enum act_flags {
	ACT_IN_LOOP = (1 << 0),
	ACT_IN_SWITCH = (1 << 1),
	ACT_HAS_RETURN = (1 << 2),
};

struct act_state {
	enum act_flags flags;

	struct ast *cur_proc;
	struct act_stack *defer_stack;
	struct act_stack *loop_stack;
	struct act_stack *goto_stack;
	struct act_stack *label_stack;
};

static int rewrite_type(struct ast *node, struct ast *params, struct type *args);

static int compound_add_symbol(struct compound_type *to, struct ast *n, struct ast *params, struct type *args)
{
	if (n->k == AST_PROC_DEF) {
		struct compound_entry *exists = compound_map_find(&to->map, proc_id(n));
		if (!exists) {
			compound_map_insert(&to->map, proc_id(n), rewrite_type(n->t, params, args));
			return 0;
		}

		struct ast *def = exists->def;
		if (def->k != AST_PROC_DEF) {
			semantic_error(n, "redefined as different kind");
			return -1;
		}

		if (!types_match(def->t, n->t)) {
			semantic_error(n, "redefined as different type");
			return -1;
		}

		if (proc_body(def) && proc_body(n)) {
			semantic_error(n, "redefined implementation");
			return -1;
		}

		if (!proc_body(exists) && !proc_body(n)) {
			semantic_error(n, "redefined interface");
			return -1;
		}

		if (proc_body(exists) && !proc_body(n)) {
			/* silently ignore compatible prototype */
			return 0;
		}

		/* overwrite prototype with implementation */
		compound_map_insert(&to->map, proc_id(n), rewrite_type(n->t, params, args));
		return 0;
	}

	if (n->k == AST_VAR_DEF) {
		struct type *exists = compound_map_find(&to->map, var_id(n));
		if (exists) {
			semantic_erro(n, "redefined");
			return -1;
		}

		compound_map_insert(&to->map, var_id(n), rewrite_type(n->t, params, args));
		return 0;
	}

	if (n->k == AST_TYPE_EXPAND) {
		struct ast *d = analyzed_file_scope_find_trait(n->scope, type_expand_id(n));
		assert(d);

		struct type *expand = maybe_expand_type(state, n->scope, d, type_expand_args(n));
		if (!expand)
			return -1;

		return combine_compound(to, expand->d);
	}

	internal_error("unexpected node");
	return -1;
}

static int combine_compound(struct compound_type *to, struct compound_type *from)
{
	foreach(compound_map, n, from) {
		if (compound_add_symbol(to, n, NULL, NULL))
			return -1;
	}

	foreach(trait_set, n, from) {
		if (trait_set_insert(to, n))
			return -1;
	}
}

static int clear_scope(struct ast *nodes);

static int analyze(struct act_state *state, struct scope *scope,
                     struct ast *node);

static int analyze_list(struct act_state *state, struct scope *scope,
                          struct ast *l);

static int analyze_type(struct act_state *state, struct scope *scope,
                          struct type *node);

static int analyze_type_list(struct act_state *state, struct scope *scope,
                               struct type *node);

static struct ast *analyzed_scope_find_symbol(struct act_state *state,
                                                struct scope *scope, char *id)
{
	struct ast *exists = scope_find_symbol(scope, id);
	if (!exists)
		return NULL;

	if (!exists->t && analyze(state, exists->scope, exists))
		return NULL;

	return exists;
}

static struct ast *analyzed_file_scope_find_symbol(struct act_state *state,
                                                     struct scope *scope,
                                                     char *id)
{
	struct ast *exists = file_scope_find_symbol(scope, id);
	if (!exists)
		return NULL;

	if (!exists->t && analyze(state, exists->scope, exists))
		return NULL;

	return exists;
}

static struct ast *analyzed_file_scope_find_type(struct act_state *state,
                                                   struct scope *scope,
                                                   char *id)
{
	struct ast *exists = file_scope_find_type(scope, id);
	if (!exists)
		return NULL;

	if (!exists->t && analyze(state, exists->scope, exists))
		return NULL;

	return exists;
}

static int is_lvalue(struct ast *n)
{
	if (n->k == AST_ARR)
		return 1;

	if (n->k == AST_ID)
		return 1;

	if (n->k == AST_DEREF)
		return 1;

	/* at least generally speaking */
	if (n->k == AST_DOT)
		return 1;

	return 0;
}


static void act_set_flags(struct act_state *state, enum act_flags flags)
{
	state->flags |= flags;
}

static enum act_flags act_flags(struct act_state *state, enum act_flags flags)
{
	return state->flags & flags;
}

static bool is_void(struct type *t)
{
	/* missing return is void */
	if (!t)
		return 1;

	return t->k == TYPE_VOID;
}

static struct type *void_type()
{
	return tgen_primitive(TYPE_VOID, strdup("void"), NULL, NULL_LOC());
}

static struct type *i27_type(struct scope *scope)
{
	struct ast *def = file_scope_find_type(scope, "i27");
	if (!def) {
		error("missing definition of type 'i27'");
		return NULL;
	}

	return tgen_primitive(TYPE_I27, strdup("i27"), def, def->loc);
}

static struct type *i9_type(struct scope *scope)
{
	struct ast *def = file_scope_find_type(scope, "i9");
	if (!def) {
		error("missing definition of type 'i9'");
		return NULL;
	}

	return tgen_primitive(TYPE_I9, strdup("i9"), def, def->loc);
}

static struct type *str_type(struct scope *scope)
{
	struct ast *def = file_scope_find_type(scope, "str");
	if (!def) {
		error("missing definition of type 'str'");
		return NULL;
	}

	return tgen_primitive(TYPE_STR, strdup("str"), def, def->loc);
}

static struct type *bool_type(struct scope *scope)
{
	struct ast *def = file_scope_find_type(scope, "bool");
	if (!def) {
		error("missing definition of type 'bool'");
		return NULL;
	}

	return tgen_primitive(TYPE_BOOL, strdup("bool"), def, def->loc);
}

static int push_defer(struct act_state *state, struct ast *expr)
{
	struct act_stack *new = calloc(1, sizeof(struct act_stack));
	if (!new) {
		internal_error("failed allocating defer");
		return -1;
	}

	new->node = expr;
	new->next = state->defer_stack;
	state->defer_stack = new;
	return 0;
}

static int push_label(struct act_state *state, struct ast *label)
{
	struct act_stack *new = calloc(1, sizeof(struct act_stack));
	if (!new) {
		internal_error("failed allocating label");
		return -1;
	}

	new->node = label;
	new->next = state->label_stack;
	state->label_stack = new;
	return 0;
}

static struct ast *find_label(struct act_state *state, char *label)
{
	struct act_stack *prev = state->label_stack, *cur;
	if (prev)
		do {
			cur = prev->next;
			if (same_id(label_id(prev->node), label))
				return prev->node;
		} while ((prev = cur));

	return NULL;
}

static int push_goto(struct act_state *state, struct ast *got)
{
	struct act_stack *new = calloc(1, sizeof(struct act_stack));
	if (!new) {
		internal_error("failed allocating goto");
		return -1;
	}

	new->node = got;
	new->next = state->goto_stack;
	state->goto_stack = new;
	return 0;
}

static struct ast *clone_defers(struct act_state *state,
                                struct act_stack *to)
{
	struct act_stack *from = state->defer_stack;

	/* maintain reverse order */
	struct ast *defers = NULL, *prev = NULL;
	while (from != to) {
		struct ast *defer = clone_ast(from->node);
		if (prev)
			prev->n = defer;

		if (!defers)
			defers = defer;

		prev = defer;
		from = from->next;
	}

	return defers;
}

static void clear_stack(struct act_stack *from, struct act_stack *to)
{
	while (from != to) {
		struct act_stack *next = from->next;
		free(from);
		from = next;
	}
}

static void clear_defers(struct act_state *state, struct act_stack *to)
{
	struct act_stack *from = state->defer_stack;
	clear_stack(from, to);
	state->defer_stack = to;
}

static void clear_gotos(struct act_state *state, struct act_stack *to)
{
	struct act_stack *from = state->goto_stack;
	clear_stack(from, to);
	state->goto_stack = to;
}

static void clear_labels(struct act_state *state, struct act_stack *to)
{
	struct act_stack *from = state->label_stack;
	clear_stack(from, to);
	state->label_stack = to;
}

static void destroy_act_state(struct act_state *state)
{
	clear_defers(state, NULL);
	clear_labels(state, NULL);
	clear_gotos(state, NULL);
}

static void type_mismatch(struct scope *scope, char *s, struct ast *node,
                          struct type *a, struct type *b)
{
	char *left_type = type_str(a);
	char *right_type = type_str(b);
	semantic_error(node,
	               "%s: %s vs %s",
	               s, left_type, right_type);
	free(left_type);
	free(right_type);
}

static int eval_const_if(struct scope *scope, struct ast *node)
{
	assert(node
	       && node->k == AST_IF
	       && ast_flags(node, AST_FLAG_CONST));

	semantic_error(node,
	               "const if unimplemented");
	return -1;
}

static int analyze_proc_sign(struct scope *scope, struct ast *proc);

static int analyze_visibility(struct scope *scope, struct ast *node)
{
	if (!node)
		return 0;

	switch (node->k) {
	case AST_VAR_DEF: return scope_add_var(scope, node);
	case AST_PROC_DEF: {
		node->scope = create_scope();
		scope_add_scope(scope, node->scope);
		return scope_add_proc(scope, node);
	}
	case AST_MACRO_DEF: return scope_add_macro(scope, node);

	case AST_IMPORT: {
		const char *file = import_file(node);
		int ret = process_file(&scope,
		                       (int)ast_flags(node, AST_FLAG_PUBLIC),
		                       file);

		if (ret == 0)
			return 0;

		/** @todo should maybe make this some other type of error, kind
		 * of too busy atm */
		semantic_info(scope->fctx, node, "imported here");
		return ret;
	}

	case AST_IF: {
		assert(ast_flags(node, AST_FLAG_CONST));
		if (eval_const_if(scope, node))
			return -1;

		/* since a const if likely replaced the current node with
		 * something else, we have to analyze the replacement */
		return analyze_root(scope, node);
	}

	case AST_STRUCT_DEF: {
		node->scope = create_scope();
		scope_add_scope(scope, node->scope);
		return scope_add_type(scope, struct_id(node), node);
	}

	case AST_STRUCT_CONT_DEF: {
		node->scope = create_scope();
		scope_add_scope(scope, node->scope);
		return scope_add_chain(scope, struct_cont_id(node), node);
	}

	case AST_ENUM_DEF: {
		node->scope = create_scope();
		scope_add_scope(scope, node->scope);
		return scope_add_type(scope, enum_id(node), node);
	}

	case AST_ALIAS_DEF: {
		char *id = alias_id(node);
		return scope_add_type(scope, id, node);
	}

	case AST_TRAIT_DEF: {
		node->scope = create_scope();
		scope_add_scope(scope, node->scope);
		return scope_add_type(scope, trait_id(node), node);
	}

	case AST_EMPTY: {
		break;
	}

	default:
		semantic_error(node, "unknown top element");
		return -1;
	};

	return 0;
}

static int set_type(struct ast *node, struct type *type)
{
	node->t = clone_type_list(type);
	return node->t == NULL;
}

/* important to keep in mind that this does not maintain list state, must be
 * done elsewhere */
static void replace_type(struct type *t, struct type *r)
{
	/* free strings before they get overwritten */
	if (t->id)
		free(t->id);

	struct src_loc loc = t->loc;
	struct scope *scope = t->scope;

	*t = *r;

	/* clone so we don't accidentally free same string twice later */
	if (t->id)
		t->id = strdup(t->id);

	/* these things we generally don't want to replace */
	t->loc = loc;
	t->scope = scope;
}

static void replace_ast(struct ast *n, struct ast *t)
{
	if (n->s)
		free(n->s);

	struct src_loc loc = n->loc;
	struct scope *scope = n->scope;

	*n = *t;

	if (n->s)
		n->s = strdup(n->s);

	n->loc = loc;
	t->scope = scope;
}

static void replace_slice_ast(struct ast *n, struct ast *t)
{
	struct ast *next = n->n;
	replace_ast(n, t);
	n->n = next;
	/** @todo scope as well? */
}

static struct ast *analyze_type_expand(struct scope *scope,
                                       struct ast *n)
{
	assert(n->k == AST_TYPE_EXPAND);
	struct act_state state = {0};
	struct ast *trait = analyzed_file_scope_find_type(&state, scope,
	                                                    type_expand_id(n));
	if (!trait) {
		semantic_error(n, "no such type");
		return NULL;
	}

	if (trait->k != AST_TRAIT_DEF) {
		semantic_error(n, "not a trait");
		return NULL;
	}

	n->t = trait->t;

	struct ast *body = trait_body(trait);
	body = clone_ast(body);

	struct type *pa = type_expand_args(n);
	foreach_node(pt, trait_params(trait)) {
		replace_type_id(body, var_id(pt), pa);
		pa = pa->n;
	}

	return body;
}

static int has_trait(struct ast *body, char *id)
{
	foreach_node(n, body) {
		/* traits don't currently take generic parameters I guess? */
		if (n->k != AST_ID)
			continue;

		if (same_id(id_str(n), id))
			return -1;
	}

	return 0;
}

int analyze_root(struct scope *scope, struct ast *tree)
{
	foreach_node(node, tree) {
		/* make all defs visible */
		if (analyze_visibility(scope, node))
			return -1;
	}

	foreach_node(node, tree){
		struct act_state state = {0};
		if (analyze(&state, scope, node))
			return -1;

		printf("\n//analyzed:\n");
		ast_dump(0, node);
	}

	return 0;
}

static int structs_match(struct type *a, struct type *b)
{
	if (a->d != b->d)
		return 0;

	return type_lists_match(tstruct_params(a), tstruct_params(b));
}

static int traits_match(struct type *a, struct type *b)
{
	if (a->d != b->d)
		return 0;

	return type_lists_match(ttrait_params(a), ttrait_params(b));
}

int types_match(struct type *a, struct type *b)
{
	if (!a && !b)
		return 1;

	if (!a || !b)
		return 0;

	/* if the type kind doesn't match, we're done. */
	if (a->k != b->k)
		return 0;

	if (is_void(a) && is_void(b))
		return 1;

	if (a->k == TYPE_TRAIT)
		return traits_match(a, b);

	if (a->k == TYPE_STRUCT)
		return structs_match(a, b);

	if (a->k == TYPE_PTR && b->k == TYPE_PTR) {
		if (is_void(ptr_base(a)))
			return 1;
		else if (is_void(ptr_base(b)))
			return 1;
	}

	if (a->k == TYPE_PTR)
		return types_match(ptr_base(a), ptr_base(b));

	if (a->k == TYPE_CALLABLE)
		return types_match(callable_rtype(a), callable_rtype(b))
		       && types_match(callable_ptypes(a), callable_ptypes(b));

	if (is_primitive(a) && is_primitive(b))
		return 1;

	return 0;
}

int type_lists_match(struct type *a, struct type *b)
{
	while (a && b) {
		if (!types_match(a, b))
			return 0;

		a = a->n;
		b = b->n;
	}

	/* if we succesfully checked all types, lists match */
	return a == NULL && b == NULL;
}

static int implements(struct type *type, struct type *trait)
{
	assert(trait->k == TYPE_TRAIT);
	struct ast *def = trait->d->def;

	/* empty traits are implemented implicitly */
	if (!trait_body(def))
		return 1;

	char *name = trait_id(def);
	return trait_set_find(&type->d->set, name) != NULL;
}

static int implements_list(struct scope *scope, struct ast *params, struct type *args)
{
	size_t argno   = type_list_len(args);
	size_t paramno = ast_list_len(params);

	if (paramno != argno) {
		semantic_error(params, "expected %zu args, got %zu",
				paramno, argno);
		return 0;
	}

	for (size_t i = 0; i < paramno; ++i) {
		assert(params->k == AST_VAR_DEF);
		struct ast *param = params;

		struct type *trait = var_type(param);
		struct type *type = args;
		if (!implements(type, trait)) {
			char *t1 = type_str(type);
			char *t2 = type_str(trait);
			semantic_error(param,
			           "%s does not implement %s",
			           t1,
			           t2);
			free(t1);
			free(t2);
			return 0;
		}

		params = params->n;
		args = args->n;
	}

	return 0;
}

static int expansion_data(struct ast *def, char **name, struct ast **body, struct ast **params)
{
	switch (def->k) {
	case AST_STRUCT_DEF:
		if (name) *name = struct_id(def);
		if (body) *body = struct_body(def);
		if (params) *params = struct_params(def);
		return 0;

	case AST_STRUCT_CONT_DEF:
		if (name) *name = struct_cont_id(def);
		if (body) *body = struct_cont_body(def);
		if (params) *params = struct_cont_params(def);
		return 0;

	case AST_TRAIT_DEF:
		if (name) *name = trait_id(def);
		if (body) *body = trait_body(def);
		if (params) *params = trait_params(def);
		return 0;

	default:
		internal_error("unhandled expansion type");
		return -1;
	}
}

static int expand_compound(struct compound_type *expanded, struct scope *scope, struct ast *def, struct type *args)
{
	struct type *exists = file_scope_find_expd(scope, def, args);
	if (exists) {
		combine_compound(expanded, exists->d);
		return 0;
	}

	struct ast *body = NULL;
	struct ast *params = NULL;
	if (expansion_data(def, NULL, &body, &params))
		return -1;

	foreach_node(n, body) {
		if (compound_add_symbol(compound, n, params, args))
			return -1;
	}

	if (def->chain)
		return expand_compound(expanded, scope, def->chain, args);

	return 0;
}

static struct type *maybe_expand_type(struct act_state *state, struct scope *scope, struct ast *def, struct type *args)
{
	assert(ast_flags(def, AST_FLAG_ACTUAL));

	char *name = NULL;
	struct ast *params = NULL;
	if (expansion_data(def, &name, NULL, &params))
		return NULL;

	struct ast *exists = file_scope_find_expanded(scope, name, args);
	if (exists)
		return exists;

	if (implements_list(params, args))
		return -1;

	/** @todo arena allocator for compound types? */
	struct compound_type *compound = create_compound_type();
	compound->def = def;

	if (expand_compound(compound, scope, def, args))
		return NULL;

	/** @todo aliases? */
	struct type *expanded = tgen_type(def->k, NULL, NULL, compound, NULL, name, def->loc);
	scope_add_expanded(scope, name, args, expanded);
	return new;
}

static int analyze_macro_def(struct act_state *state,
                               struct scope *scope, struct ast *n)
{
	UNUSED(state);
	/* macro bodies, arguments, etc aren't expanded upon until the macro is
	 * called, so just try to add it to the local scope */
	assert(n && n->k == AST_MACRO_DEF);

	n->t = void_type();

	/* analysis should've added us to the file scope already */
	if (scope_flags(scope, SCOPE_FILE))
		return 0;

	/* otherwise, add us to whatever scope we're in */
	return scope_add_macro(scope, n);
}

static int analyze_macro_expand(struct act_state *state,
                                  struct scope *scope,
                                  struct ast *macro_expand)
{
	assert(macro_expand->k == AST_MACRO_EXPAND);
	char *id = macro_expand_id(macro_expand);
	struct ast *macro = file_scope_find_macro(scope, id);
	if (!macro) {
		semantic_error("no such macro");
		return -1;
	}

	assert(macro->k == AST_MACRO_DEF);
	if (ast_flags(macro, AST_FLAG_VARIADIC)) {
		semantic_error(macro,
		               "variadic macros not yet implemented");
		return -1;
	}

	struct ast *body = clone_ast(macro_def_body(macro));
	if (!body) {
		internal_error("failed allocating body for macro expansion");
		return -1;
	}

	/** @todo update all macro IDs to the correct scope */
	body->scope = macro_expand->scope;
	body->n = macro_expand->n;

	struct ast *param = macro_def_params(macro);
	struct ast *arg = macro_expand_args(macro_expand);

	while (param && arg) {
		/* feels slightly hacky, but essentially replace each individual
		 * component in the arg list by breaking it out of the list
		 * temporarily. After the replacement, insert it back into the
		 * list so the cleanup is easier. */
		struct ast *next_arg = arg->n;
		arg->n = NULL;

		if (replace_id(body, param, arg)) {
			semantic_error(macro_expand,
			               "failed replacing params with args");
			arg->n = next_arg;
			return -1;
		}

		param = param->n;
		arg = arg->n = next_arg;
	}

	replace_slice_ast(macro_expand, body);

	/* analyze the new content */
	if (analyze(state, scope, macro_expand)) {
		semantic_info(macro_expand, "while expanding %s",
		              id);
		return -1;
	}

	return 0;
}

static int simplify_refderef(struct act_state *state, struct scope *scope,
                             struct ast *n)
{
	if (!is_unop(n))
		return 0;

	struct ast *e = unop_expr(n);
	if (n->k == AST_REF && e->k == AST_DEREF) {
		replace_slice_ast(n, unop_expr(e));
		return simplify_refderef(state, scope, n);
	}

	if (n->k == AST_DEREF && e->k == AST_REF) {
		replace_slice_ast(n, unop_expr(e));
		return simplify_refderef(state, scope, n);
	}

	return 0;
}

/* not really ufcs at the moment */
static int maybe_ufcs(struct act_state *state, struct scope *scope,
                      struct ast *call)
{
	assert(call->k == AST_CALL);
	struct ast *dot = call_expr(call);
	if (dot->k != AST_DOT)
		return 0;

	struct type *ptypes = callable_ptypes(dot->t);
	struct ast *expr = dot_expr(dot);
	char *id = strdup(dot_id(dot));
	call_expr(call) = gen_fetch(id, clone_type(expr->t), dot->loc);
	(call_expr(call))->t = clone_type(dot->t);
	(call_expr(call))->scope = scope;

	struct ast *ref = NULL;

	if (!ptypes) {
		ref = NULL;
	}
	else if (ptypes->k == TYPE_PTR) {
		/* is ufcs expects reference to member, try to take address */
		ref = gen_unop(AST_REF, expr, dot->loc);
		ref->t = tgen_ptr(clone_type(expr->t), dot->loc);
		if (analyze_type(state, scope, ref->t))
			return -1;

		ref->scope = scope;
	}
	else {
		/* otherwise, try to pass expr as is */
		ref = expr;
	}

	if (ref && simplify_refderef(state, scope, ref))
		return -1;

	if (ref)
		call_args(call) = ast_prepend(call_args(call), ref);

	return 0;
}

static int analyze_call(struct act_state *state,
                          struct scope *scope, struct ast *call)
{
	assert(call && call->k == AST_CALL);

	if (analyze_list(state, scope, call_args(call)))
		return -1;

	if (analyze_list(state, scope, call_expr(call)))
		return -1;

	struct ast *expr = call_expr(call);
	if (expr->t->k != TYPE_CALLABLE) {
		char *tstr = type_str(expr->t);
		semantic_error("not a callable type: %s",
		               tstr);
		free(tstr);
		return -1;
	}

	if (maybe_ufcs(state, scope, call))
		return -1;

	struct type *callable = expr->t;
	struct type *ptypes = callable_ptypes(callable);
	struct ast *arg = call_args(call);
	foreach_type(p, ptypes) {
		if (!arg) {
			semantic_error("too many arguments");
			return -1;
		}

		if (!types_match(p, arg->t)) {
			type_mismatch(scope, "argument type mismatch", arg, p,
			              arg->t);
			return -1;
		}

		arg = arg->n;
	}

	if (arg) {
		semantic_error("too many arguments");
		return -1;
	}

	set_type(call, callable_rtype(callable));
	return 0;
}

static void warn_unused_labels(struct act_state *state, struct scope *scope)
{
	struct act_stack *labels = state->label_stack;
	if (!labels)
		return;

	do {
		struct ast *label = labels->node;
		if (!ast_flags(label, AST_FLAG_ACTUAL))
			semantic_warn(scope->fctx, label,
			              "unused label");

	} while ((labels = labels->next));
}

static int undefined_gotos(struct act_state *state, struct scope *scope)
{
	int ret = 0;
	struct act_stack *gotos = state->goto_stack;
	if (!gotos)
		return ret;

	do {
		struct ast *got = gotos->node;
		if (!ast_flags(got, AST_FLAG_ACTUAL)) {
			semantic_warn(scope->fctx, got,
			              "undefined label");
			ret = -1;
		}

	} while ((gotos = gotos->next));

	return ret;
}

static int analyze_proc_sign(struct scope *scope, struct ast *proc)
{
	assert(proc && proc->k == AST_PROC_DEF);

	struct act_state new_state = {0};
	proc->scope = create_scope();
	scope_add_scope(scope, proc->scope);

	if (analyze_list(&new_state, proc->scope, proc_params(proc))) {
		destroy_act_state(&new_state);
		return -1;
	}

	if (!proc_rtype(proc))
		proc_rtype(proc) = void_type();

	struct type *rtype = clone_type(proc_rtype(proc));
	if (analyze_type_list(&new_state, proc->scope, rtype)) {
		destroy_act_state(&new_state);
		return -1;
	}

	struct type *callable = tgen_callable(NULL, rtype, proc->loc);
	foreach_node(p, proc_params(proc)) {
		/* we must manually 'start' the chain */
		if (!callable_ptypes(callable)) {
			callable_ptypes(callable) = clone_type(p->t);
			continue;
		}

		type_append(&callable_ptypes(callable), p->t);
	}

	set_type(proc, callable);
	return 0;
}

static int analyze_proc(struct act_state *state,
                          struct scope *scope, struct ast *proc)
{
	UNUSED(state);
	if (analyze_proc_sign(scope, proc))
		return -1;

	/* external functions and so on */
	if (!proc_body(proc))
		return 0;

	/* analyze body */
	struct act_state new_state = {0};
	new_state.cur_proc = proc;
	if (analyze(&new_state, proc->scope, proc_body(proc))) {
		destroy_act_state(&new_state);
		return -1;
	}

	if (!act_flags(&new_state, ACT_HAS_RETURN)) {
		if (!is_void(proc_rtype(proc))) {
			semantic_error(proc,
			               "no return with non-void return type");
			destroy_act_state(&new_state);
			return -1;
		}

		/* add 'implicit' return as the last defer statement to be executed in a block*/
		struct ast *body = proc_body(proc);
		struct ast *r = gen_return(NULL, NULL, NULL_LOC());
		r->scope = body->scope;
		r->n = block_defers(body);
		block_defers(body) = r;
	}
	else if (ast_block_last(proc_body(proc))->k != AST_RETURN) {
		/* TODO: something more sophisticated than this */
		semantic_warn(scope->fctx, proc,
		              "unable to determine explicit return for all branches");
		destroy_act_state(&new_state);
		return -1;
	}

	warn_unused_labels(&new_state, scope);
	if (undefined_gotos(&new_state, scope)) {
		destroy_act_state(&new_state);
		return -1;
	}

	/* if we're main, don't mangle the entry point */
	char *id = proc_id(proc);
	if (strcmp("main", id) == 0)
		ast_set_flags(proc, AST_FLAG_NOMANGLE);

	/* we have successfully analyzed the procedure */
	destroy_act_state(&new_state);
	return 0;
}

static int analyze_binop(struct act_state *state,
                           struct scope *scope, struct ast *binop)
{
	assert(binop && is_binop(binop));

	struct ast *left = binop_left(binop);
	struct ast *right = binop_right(binop);

	if (analyze(state, scope, left))
		return -1;

	if (analyze(state, scope, right))
		return -1;

	if (!types_match(left->t, right->t)) {
		type_mismatch(scope, "op type mismatch", binop, left->t,
		              right->t);
		return -1;
	}

	/* types are the same, so the type of this expression is whichever */
	set_type(binop, left->t);
	return 0;
}


static int analyze_block(struct act_state *state,
                           struct scope *scope, struct ast *node)
{
	struct scope *block_scope = scope;
	if (!ast_flags(node, AST_FLAG_UNHYGIENIC)) {
		if (!(block_scope = create_scope())) {
			/* internal error */
			internal_error("failed to allocate block scope");
			return -1;
		}

		scope_add_scope(scope, block_scope);
	}

	struct act_stack *defers = state->defer_stack;
	foreach_node(pt, block_body(node)) {
		if (analyze(state, block_scope, pt))
			return -1;
	}

	if (block_body(node) == NULL) {
		node->t = void_type();
		/* still not a huge fan of directly mucking about with ast slots */
		block_body(node) = gen_empty(NULL_LOC());
		return 0;
	}

	/* the block type is the last statement in the block's type */
	set_type(node, ast_last(block_body(node))->t);
	if (!node->t) {
		semantic_error(node,
		               "unable to detect block type");
		return -1;
	}

	/* TODO: currently defers are sort of duplicated after a return, unsure
	 * if they should be handled here or somewhere else */
	if (state->defer_stack) {
		/* no new defers, no need to clone anything */
		if (state->defer_stack == defers)
			return 0;

		block_defers(node) = clone_defers(state, defers);
		if (!block_defers(node)) {
			internal_error("failed cloning defers");
			clear_defers(state, defers);
			return -1;
		}
	}

	clear_defers(state, defers);
	return 0;
}

static int analyze_id(struct act_state *state,
                        struct scope *scope, struct ast *id)
{
	UNUSED(state);
	assert(id && id->k == AST_ID);

	/** @todo vars and procs kind of override eachother, i.e.
	 *	do_something(){..}
	 *	^() do_something;
	 *
	 *	do_something_else(){
	 *		...
	 *		do_something(); // calls variable at the moment
	 *	}
	 *
	 *	Either add in some syntax to distinguish procedure calls and
	 *	pointer calls or make procs and vars share the same namespace.
	 *	*/
	struct ast *decl = analyzed_file_scope_find_symbol(state, scope,
	                                                     id_str(id));
	if (!decl) {
		semantic_error("no such symbol");
		return -1;
	}

	/* set scope of use to scope of definition, this makes sure that when
	 * lower() calls scope_find_*() it gets the one we just found and not a
	 * possible shadow. This is a pretty major hack, it might be more clean
	 * to add a ->def field into the AST or something but this works for
	 * now. */
	id->scope = decl->scope;
	set_type(id, decl->t);
	return 0;
}

static int analyze_var(struct act_state *state,
                         struct scope *scope, struct ast *var)
{
	assert(var && var->k == AST_VAR_DEF);
	struct ast *init = var_init(var);
	struct type *type = var_type(var);
	/* one of these must be defined, otherwise the parser fucked up */
	assert(type || init);

	if (init && analyze_list(state, scope, init))
		return -1;

	if (type) {
		type = clone_type(type);
		if (analyze_type_list(state, scope, type))
			return -1;
	}

	if (init && type) {
		/* make sure the asked type and the analyzed types match */
		if (!types_match(init->t, type)) {
			type_mismatch(scope, "var type mismatch", var, init->t,
			              type);
			return -1;
		}
	}

	var->scope = scope;

	if (init)
		/* infer */
		set_type(var, init->t);

	if (type)
		/* TODO: should there be some default zero value? */
		/* declare */
		set_type(var, type);

	/* an unnamed var is a var in a signature that should not produce a
	 * warning on not being used (if I ever get around to adding those kinds
	 * of warnings) */
	if (var_id(var) && !ast_flags(var, AST_FLAG_MEMBER))
		return scope_add_var(scope, var);

	return 0;
}

static int analyze_tid(struct act_state *state, struct scope *scope,
                         struct type *t)
{
	UNUSED(state);

	/* no id means void */
	if (!t->id) {
		replace_type(t, void_type());
		return 0;
	}

	struct ast *def = analyzed_file_scope_find_type(state, scope, t->id);
	if (!def) {
		type_error(scope->fctx, t, "no such type");
		return -1;
	}

	if (def->k == AST_STRUCT_DEF || def->k == AST_STRUCT_CONT_DEF) {
		struct ast *base = chain_base(def);
		if (struct_params(base)) {
			type_error(scope->fctx, t, "missing type params");
			return -1;
		}
	}

	assert(t->n == NULL);
	replace_type(t, clone_type_list(def->t));
	if (def->k == AST_ALIAS_DEF)
		t->a = def;

	return 0;
}

static int analyze_ptr(struct act_state *state, struct scope *scope,
                         struct type *t)
{
	assert(ptr_base(t));
	t->d = analyzed_file_scope_find_type(state, scope, "ptr");
	if (!t->d) {
		type_error(scope->fctx, t, "no pointer type");
		return -1;
	}

	if (analyze_type(state, scope, ptr_base(t)))
		return -1;

	return 0;
}

static int analyze_callable(struct act_state *state, struct scope *scope,
                              struct type *t)
{
	struct type *ptypes = callable_ptypes(t);
	struct type *rtype = callable_rtype(t);

	foreach_type(p, ptypes){
		if (analyze_type(state, scope, p))
			return -1;
	}

	if (!rtype)
		callable_rtype(t) = void_type();

	if (analyze_type(state, scope, rtype))
		return -1;

	return 0;
}

static int analyze_i27(struct act_state *state, struct scope *scope,
                         struct type *t)
{
	UNUSED(state);
	/* not much to do */
	if (t->d)
		return 0;

	struct ast *def = file_scope_find_type(scope, "i27");
	if (!def) {
		error("missing definition of type 'i27'");
		return -1;
	}

	t->d = def;
	return 0;
}

static int analyze_i9(struct act_state *state, struct scope *scope,
                        struct type *t)
{
	UNUSED(state);
	/* not much to do */
	if (t->d)
		return 0;

	struct ast *def = file_scope_find_type(scope, "i9");
	if (!def) {
		error("missing definition of type 'i9'");
		return -1;
	}

	t->d = def;
	return 0;
}

static int analyze_bool(struct act_state *state, struct scope *scope,
                          struct type *t)
{
	UNUSED(state);
	/* not much to do */
	if (t->d)
		return 0;

	struct ast *def = file_scope_find_type(scope, "bool");
	if (!def) {
		error("missing definition of type 'bool'");
		return -1;
	}

	t->d = def;
	return 0;
}

static int analyze_tstruct(struct act_state *state, struct scope *scope,
                             struct type *t)
{
	UNUSED(state);
	/* not much to do */
	if (t->d)
		return 0;

	struct ast *def = file_scope_find_type(scope, t->id);
	if (!def) {
		error("missing definition of type %s", t->id);
		return -1;
	}

	t->d = def;
	return 0;
}

static int analyze_ttrait(struct act_state *state, struct scope *scope,
                            struct type *t)
{
	UNUSED(state);
	/* not much to do */
	if (t->d)
		return 0;

	struct ast *def = file_scope_find_type(scope, t->id);
	if (!def) {
		error("missing definition of type %s", t->id);
		return -1;
	}

	t->d = def;
	return 0;
}

static int analyze_tconstruct(struct act_state *state,
                                struct scope *scope,
                                struct type *t)
{
	assert(t->k == TYPE_CONSTRUCT);
	struct type *d = analyzed_file_scope_find_type(state, scope,
	                                                construct_id(t));
	if (!d) {
		type_error(scope->fctx, t, "no such type");
		return -1;
	}

	if (analyze_type_list(state, scope, construct_atypes(t)))
		return -1;

	d = maybe_expand_type(state, scope, d, construct_atypes(t));
	if (!d)
		return -1;

	replace_type(t, d);
	return 0;
}

static int analyze_type(struct act_state *state,
                          struct scope *scope,
                          struct type *t)
{
	if (!t)
		return 0;

	t->scope = scope;

	if (analyze_type(state, scope, t->n))
		return -1;

	switch (t->k) {
	case TYPE_I27: return analyze_i27(state, scope, t);
	case TYPE_I9: return analyze_i9(state, scope, t);
	case TYPE_BOOL: return analyze_bool(state, scope, t);
	case TYPE_ID: return analyze_tid(state, scope, t);
	case TYPE_PTR: return analyze_ptr(state, scope, t);
	case TYPE_CALLABLE: return analyze_callable(state, scope, t);
	case TYPE_STRUCT: return analyze_tstruct(state, scope, t);
	case TYPE_TRAIT: return analyze_ttrait(state, scope, t);
	case TYPE_CONSTRUCT: return analyze_tconstruct(state, scope, t);
	case TYPE_VOID: return 0; /* void is by default analyzed */

	default:
		type_info(scope->fctx, t,
		          "unimplemented type");
		type_info(scope->fctx, t,
		          "continuing with compilation to see what breaks");
		return 0;
	}

	return 0;
}

static int analyze_type_list(struct act_state *state,
                               struct scope *scope,
                               struct type *l)
{
	foreach_type(t, l) {
		if (analyze_type(state, scope, t))
			return -1;
	}

	return 0;
}

static int analyze_empty(struct act_state *state,
                           struct scope *scope, struct ast *node)
{
	UNUSED(state);
	UNUSED(scope);
	node->t = void_type();
	return 0;
}

static int integral_type(struct type *type)
{
	switch (type->k) {
	case TYPE_I27:
	case TYPE_I9:
	case TYPE_BOOL:
		return true; /* maybe? */
	default:
		break;
	}

	return false;
}

static int pointer_type(struct type *type)
{
	return type->k == TYPE_PTR;
}

static int pointer_conversion(struct type *a, struct type *b)
{
	if (pointer_type(a)) {
		if (!is_primitive(b))
			return 0;

		/* for now */
		return b->k == TYPE_I27;
	}

	return 0;
}

static struct ast *lookup_enum_member(struct ast *enu,
                                      char *find)
{
	struct ast *m = enum_body(enu);
	while (m) {
		assert(m->k == AST_VAL);
		if (same_id(find, val_id(m)))
			break;
		m = m->n;
	}

	return m;
}

static int analyze_cast(struct act_state *state,
                          struct scope *scope, struct ast *cast)
{
	assert(cast->k == AST_CAST);
	struct ast *expr = cast_expr(cast);
	struct type *type = cast_type(cast);

	if (analyze_type(state, scope, type))
		return -1;

	if (analyze(state, scope, expr))
		return -1;

	if (types_match(expr->t, type)) {
		set_type(cast, type);
		return 0;
	}

	if (integral_type(expr->t) && integral_type(type)) {
		set_type(cast, type);
		return 0;
	}

	if (pointer_type(expr->t) && pointer_type(type)) {
		set_type(cast, type);
		return 0;
	}

	if (pointer_conversion(expr->t, type)
	    || pointer_conversion(type, expr->t)) {
		set_type(cast, type);
		return 0;
	}

	/* TODO: arrays? */

	char *left_type = type_str(expr->t);
	char *right_type = type_str(type);
	type_mismatch(scope, "illegal cast", cast, expr->t, type);
	free(left_type);
	free(right_type);
	return -1;
}

static int analyze_const(struct act_state *state, struct scope *scope,
                           struct ast *cons)
{
	UNUSED(state);
	if (cons->k == AST_CONST_INT)
		cons->t = i27_type(scope);

	else if (cons->k == AST_CONST_CHAR)
		cons->t = i9_type(scope);

	else if (cons->k == AST_CONST_BOOL)
		cons->t = bool_type(scope);

	else if (cons->k == AST_CONST_STR)
		cons->t = str_type(scope);

	if (cons->t)
		return 0;

	semantic_error("illegal constant");
	return -1;
}

static int analyze_alias(struct act_state *state, struct scope *scope,
                           struct ast *alias)
{
	/* I shall have to think about things, as currently very deeply nested
	 * aliases might be a bit cumbersome to work with. Still, this works
	 * well enough I suppose. */
	assert(alias->k == AST_ALIAS_DEF);
	if (analyze_type(state, scope, alias_type(alias))) {
		/* usually we don't want to output errors upon errors, but this
		 * is likely a useful message as it might show where a loop is
		 * occuring */
		semantic_error("failed actualizing alias");
		return -1;
	}

	alias->t = alias_type(alias);
	ast_set_flags(alias, AST_FLAG_ACTUAL);
	return 0;
}

static int analyze_defer(struct act_state *state,
                           struct scope *scope, struct ast *node)
{
	/** @todo this doesn't work for shadowed variables, as the scope might
	 * be set to the scope containing a shadowing variable, which means that
	 * when lower.c does a file_scope_find_*() it finds the shadowed
	 * variable first. */
	struct ast *expr = defer_expr(node);
	if (analyze(state, scope, expr))
		return -1;

	if (push_defer(state, expr))
		return -1;

	node->t = void_type();
	return 0;
}

static int analyze_return(struct act_state *state, struct scope *scope,
                            struct ast *node)
{
	act_set_flags(state, ACT_HAS_RETURN);
	struct ast *expr = return_expr(node);
	if (expr) {
		if (analyze(state, scope, expr))
			return -1;

		set_type(node, expr->t);
	}
	else {
		node->t = void_type();
	}

	assert(state->cur_proc);
	struct ast *cur_proc = state->cur_proc;
	struct type *rtype = callable_rtype(cur_proc->t);
	if (!types_match(node->t, rtype)) {
		type_mismatch(scope, "return type mismatch", node,
		              rtype, node->t);
		return -1;
	}

	if (state->defer_stack) {
		return_defers(node) = clone_defers(state, NULL);
		if (!return_defers(node)) {
			internal_error("failed cloning return defers");
			return -1;
		}
	}

	return 0;
}

/* Still slightly unsure if this works in all cases, but a good start
 * nonetheless. */
static void analyze_goto_defer(struct ast *got, struct ast *label)
{
	goto_label_ref(got) = label;

	struct ast *goto_defers = goto_defers(got);
	struct ast *label_defers = label_defers(label);
	/* since we're dealing with singly linked lists, keep a reference to one
	 * node before the current goto defer. */
	struct ast *prev_defer = NULL;

	/* this goto has a defined label */
	ast_set_flags(got, AST_FLAG_ACTUAL);
	ast_set_flags(label, AST_FLAG_ACTUAL);

	size_t goto_len = ast_list_len(goto_defers);
	size_t label_len = ast_list_len(label_defers);

	/* find first common defer statement */
	while (goto_len > label_len) {
		prev_defer = goto_defers;
		goto_defers = goto_defers->n;
		goto_len--;
	}

	while (label_len > goto_len) {
		label_defers = label_defers->n;
		label_len--;
	}

	/* TODO: possible optimisation could be maintaining references to the
	 * defer statements themselves, building up a sort of tree, allowing us
	 * to directly compare pointers, likely being a bit quicker. Still,
	 * unlikely that goto stuff would be a major bottleneck. */
	while (!equiv_nodes(goto_defers, label_defers)) {
		prev_defer = goto_defers;
		label_defers = label_defers->n;
		goto_defers = goto_defers->n;
	}

	/* only the defers below the common defer should be executed by the goto */
	if (goto_defers) {
		/* fuck, I actually need the one previous to this */
		assert(prev_defer->n == goto_defers);
		prev_defer->n = NULL;
	}

	/* nothing to do */
}


static int analyze_goto(struct act_state *state, struct scope *scope,
                          struct ast *node)
{
	UNUSED(scope);
	assert(node->k == AST_GOTO);
	push_goto(state, node);

	/* clone all defers as we don't know where the label might be */
	goto_defers(node) = clone_defers(state, NULL);
	node->t = void_type();

	struct ast *label = find_label(state, goto_label(node));
	/* this is a jump backwards, i.e. we can already do it */
	if (label)
		analyze_goto_defer(node, label);

	/* forward jump, handle stuff when we run into the corresponding label */
	return 0;
}

static void analyze_goto_defers(struct act_state *state,
                                  struct ast *label)
{
	struct act_stack *prev = state->goto_stack, *cur;
	if (prev)
		do {
			cur = prev->next;
			struct ast *got = prev->node;
			if (same_id(goto_label(got), label_id(label)))
				analyze_goto_defer(got, label);

		} while ((prev = cur));
}

static int analyze_label(struct act_state *state, struct scope *scope,
                           struct ast *node)
{
	UNUSED(scope);
	assert(node->k == AST_LABEL);
	struct ast *prev = find_label(state, label_id(node));
	if (prev) {
		semantic_error("label redefined");
		semantic_info(scope->fctx, prev, "previous definition");
		return -1;
	}

	push_label(state, node);
	/* clone all defers */
	label_defers(node) = clone_defers(state, NULL);
	node->t = void_type();

	analyze_goto_defers(state, node);
	return 0;
}

static int analyze_unop(struct act_state *state,
                          struct scope *scope, struct ast *node)
{
	assert(is_unop(node));
	struct ast *expr = unop_expr(node);
	if (analyze(state, scope, expr))
		return -1;

	/* generally speaking */
	set_type(node, expr->t);

	switch (node->k) {
	case AST_DEREF: {
		struct type *type = expr->t;
		if (type->k!= TYPE_PTR) {
			/** @todo or array? */
			char *tstr = type_str(type);
			semantic_error(expr,
			               "not a pointer: %s",
			               tstr);
			free(tstr);
			return -1;
		}

		set_type(node, ptr_base(type));
		assert(node->t);
		if (simplify_refderef(state, scope, node))
			return -1;

		break;
	}

	case AST_REF: {
		/** @todo array pointer decay? */
		node->t = tgen_ptr(clone_type(expr->t), node->loc);
		if (analyze_type(state, scope, node->t))
			return -1;

		if (simplify_refderef(state, scope, node))
			return -1;

		break;
	}

	case AST_LNOT: {
		if (is_primitive(expr->t)) {
			char *tstr = type_str(expr->t);
			semantic_error(node,
			               "'!' only implemented for primitive types: %s",
			               tstr);
			free(tstr);
			return -1;
		}

		if (expr->t->k == TYPE_VOID) {
			semantic_error(node,
			               "'!' not implemented for void");
			return -1;
		}

		node->t = bool_type(scope);
		break;
	}

	default: semantic_error(node,
		                "unimplemented unary operation");
		return -1;
	}

	if (!node->t)
		return -1;

	return 0;
}

static int analyze_as(struct act_state *state,
                        struct scope *scope, struct ast *as)
{
	assert(as->k == AST_AS);
	struct type *type = as->t;
	if (analyze_type(state, scope, type))
		return -1;

	set_type(as, type);
	return 0;
}

struct replace_data {
	char *id;
	struct type *replacement;
};

static int _replace_type_id(struct type *type, void *data)
{
	struct replace_data *pair = data;
	struct type *replacement = pair->replacement;
	char *id = pair->id;

	switch (type->k) {
	case TYPE_ID: {
		if (same_id(id, type->id))
			replace_type(type, clone_type(replacement));
		break;
	}

	case TYPE_TRAIT: {
		struct ast *def = type->d;
		assert(def);

		char *name = trait_id(def);
		if (same_id(id, name))
			replace_type(type, clone_type(replacement));
		break;
	}

	case TYPE_STRUCT: {
		struct ast *def = type->d;
		assert(def);

		char *name = struct_id(def);
		if (same_id(id, name))
			replace_type(type, clone_type(replacement));
		break;
	}

	default:
		break;
	}

	return 0;
}

static int _replace_slice_ast_type_id(struct ast *node, void *data)
{
	if (!node)
		return 0;

	/* handle t2 first since it's generally likely to be shorter */
	int ret = type_visit_list(_replace_type_id, NULL, node->t2, data);
	if (ret)
		return ret;

	/* now we can (potentially) do a tailcall */
	return type_visit_list(_replace_type_id, NULL, node->t, data);
}

static int replace_type_id(struct ast *nodes, char *id,
                           struct type *replacement)
{
	struct replace_data pair = {id, replacement};
	return ast_visit_list(_replace_slice_ast_type_id, NULL, nodes, &pair);
}

static int _clear_scope(struct ast *node, void *data)
{
	UNUSED(data);
	if (!node)
		return 0;

	node->scope = NULL;
	return 0;
}

static int clear_scope(struct ast *nodes)
{
	return ast_visit(_clear_scope, NULL, nodes, NULL);
}

static struct type *params_to_type_list(struct ast *params)
{
	assert(ast_flags(params, AST_FLAG_ACTUAL));
	if (!params)
		return NULL;

	struct type *root = type_clone(params->t);
	struct type *cur = root;
	foreach_node(n, params->n) {
		cur->n = type_clone(n->t);
		cur = n->t;
	}

	return root;
}

static int analyze_compound_chain(struct compound_type *compound,
		struct scope *scope,
		struct ast *node,
		struct ast *params,
		struct ast *body)
{
	foreach_node(n, body) {
		struct act_state state = {};
		if (analyze(&state, scope, n))
			return -1;

		if (compound_add_symbol(compound, n, NULL, NULL))
			return -1;
	}

	if (expansion_data(node, NULL, &body, &params))
		return -1;

	if (node->chain)
		return analyze_compound_chain(compound, scope, node->chain, params, body);

	return 0;
}

static int analyze_compound(struct act_state *state,
		struct scope *scope,
                struct ast *node,
		char *id,
		struct ast *params,
		struct ast *body)
{
	UNUSED(state);
	struct scope *new_scope = create_scope();
	if (!new_scope)
		return -1;

	scope_add_scope(node->scope, new_scope);
	node->scope = new_scope;

	struct act_state new_state = {};
	if (analyze_list(&new_state, new_scope, params))
		return -1;

	struct type *types = params_to_list(params);
	assert(types);

	struct type *type = NULL;
	switch (node->k) {
	case AST_STRUCT_DEF:
		type = tgen_struct(strdup(id), node, node->loc); break;

	case AST_STRUCT_CONT_DEF:
		type = tgen_struct(strdup(id), node, node->loc); break;

	case AST_TRAIT_DEF:
		type = tgen_trait(strdup(id), node, node->loc); break;

	default:
		internal_error("unhandled compound type");
		return -1;
	}

	struct compound_type compound = create_compound_type();
	compound->def = node;

	if (analyze_compound_chain(compound, node->scope, node, params, body))
		return -1;

	type->d = compound;
	node->t = type;
	scope_add_expanded(scope, node, types, node->t);
	return 0;
}

static struct ast *chain_lookup(struct act_state *state, struct ast *def,
                                char *id)
{
	if (!def)
		return NULL;

	struct ast *exists = analyzed_scope_find_symbol(state, def->scope,
	                                                  id);
	if (exists)
		return exists;

	if (def->chain)
		return chain_lookup(state, def->chain, id);

	return NULL;
}

static int analyze_trait(struct act_state *state,
		struct scope *scope, struct ast *node)
{
	assert(node->k == AST_TRAIT_DEF);
	return analyze_compound(state, scope, node,
			trait_id(node),
			trait_params(node),
			trait_body(node));
}

static int analyze_struct(struct act_state *state,
                            struct scope *scope, struct ast *node)
{
	assert(node->k == AST_STRUCT_DEF);
	return analyze_compound(state, scope, node,
	                          struct_id(node),
				  struct_params(node),
	                          struct_body(node));
}

static int analyze_struct_cont(struct act_state *state,
                                 struct scope *scope, struct ast *node)
{
	assert(node->k == AST_STRUCT_CONT_DEF);
	return analyze_compound(state, scope, node,
	                          struct_cont_id(node),
	                          struct_cont_params(node),
	                          struct_cont_body(node));
}

static int analyze_dot(struct act_state *state,
                         struct scope *scope, struct ast *node)
{
	assert(node->k == AST_DOT);
	struct ast *expr = dot_expr(node);
	if (analyze(state, scope, expr))
		return -1;

	char *id = dot_id(node);
	struct type *type = expr->t;

	struct ast *def = NULL;
	switch (type->k) {
	case TYPE_I9:
	case TYPE_I27:
	case TYPE_BOOL:
	case TYPE_PTR:
	case TYPE_TRAIT:
	case TYPE_STRUCT: def = type->d; break;
	default: {
		char *tstr = type_str(type);
		semantic_error(node,
		               "illegal type in dot expression: %s",
		               tstr);
		free(tstr);
		return -1;
	}
	}

	if (def->k == AST_ENUM_DEF)
		def = (enum_type(def))->d;

	if (!def) {
		semantic_error(node,
		               "no such type");
		return -1;
	}

	struct ast *exists = chain_lookup(state, def, id);

	if (exists) {
		assert(exists->t);
		set_type(node, exists->t);
		return 0;
	}

	char *tstr = type_str(type);
	semantic_error(node,
	               "%s does not have member",
	               tstr);
	free(tstr);
	return -1;
}

struct init_helper {
	char *id;
	struct ast *n;
};

static int init_sort(const struct init_helper *a, const struct init_helper *b)
{
	return strcmp(a->id, b->id);
}


static int analyze_init(struct act_state *state,
                          struct scope *scope, struct ast *node)
{
	assert(node->k == AST_INIT);
	struct ast *def = analyzed_file_scope_find_type(state, scope,
	                                                  init_id(node));
	if (!def) {
		semantic_error("no such type");
		return -1;
	}

	struct type *types = clone_type_list(init_args(node));
	if (analyze_type_list(state, scope, types))
		return -1;

	def = maybe_expand_type(state, scope, def, types);
	if (!def)
		return -1;

	struct vec init_args = vec_create(sizeof(struct init_helper));
	struct vec struct_members = vec_create(sizeof(struct init_helper));

	struct ast *base = chain_base(def);
	foreach_node(n, struct_body(base)) {
		if (n->k != AST_VAR_DEF)
			continue;

		struct init_helper h = {var_id(n), n};
		vect_append(struct init_helper, struct_members, &h);
	}

	foreach_node(n, init_body(node)) {
		/* don't initialize init members as regular vars */
		/* kind of hacky, could maybe add a AST_MEMBER enum or something */
		if (analyze(state, scope, var_init(n)))
			goto err;

		set_type(n, (var_init(n))->t);
		struct init_helper h = {var_id(n), n};
		vect_append(struct init_helper, init_args, &h);
	}

	vec_sort(&init_args, (vec_comp_t)init_sort);
	vec_sort(&struct_members, (vec_comp_t)init_sort);

	if (vec_len(&init_args) != vec_len(&struct_members)) {
		semantic_error(got %zu",
		               vec_len(&struct_members),
		               vec_len(&init_args));
		goto err;
	}

	/* not insanely fast but good enough I suppose */
	foreach_vec(ai, init_args) {
		struct init_helper arg = vect_at(struct init_helper, init_args,
		                                 ai);

		struct init_helper mem = vect_at(struct init_helper,
		                                 struct_members,
		                                 ai);

		/* not the best error message but works for now */
		if (!same_id(arg.id, mem.id)) {
			semantic_error("malformed init");
			goto err;
		}

		if (!types_match(arg.n->t, mem.n->t)) {
			type_mismatch(scope, "init type mismatch", arg.n,
			              arg.n->t, mem.n->t);
			goto err;
		}
	}

	vec_destroy(&init_args);
	vec_destroy(&struct_members);
	set_type(node, def->t);
	return 0;

err:
	vec_destroy(&init_args);
	vec_destroy(&struct_members);
	return -1;
}

static int analyze_assign(struct act_state *state, struct scope *scope,
                            struct ast *node)
{
	assert(node->k == AST_ASSIGN);
	struct ast *to = assign_to(node);
	if (analyze(state, scope, to))
		return -1;

	struct ast *from = assign_from(node);
	if (analyze_list(state, scope, from))
		return -1;

	if (!types_match(to->t, from->t)) {
		type_mismatch(scope, "assign type mismatch", node, to->t,
		              from->t);
		return -1;
	}

	/** @todo rvalue vs lvalue? */
	if (!is_lvalue(to)) {
		semantic_error(node,
		               "rvalue used where lvalue required");
		return -1;
	}

	set_type(node, to->t);
	return 0;
}

static int analyze_enum_fetch(struct act_state *state, struct scope *scope,
                                struct ast *fetch)
{
	UNUSED(state);
	char *id = fetch_id(fetch);
	struct type *type = fetch_type(fetch);
	struct ast *def = type->d;
	assert(def);

	struct ast *member = lookup_enum_member(def, id);
	if (!member) {
		char *estr = type_str(type);
		semantic_error("no such member in enum %s");
		free(estr);
		return -1;
	}

	/* this should be safe since we currently don't allow enums to be part
	 * of any generic structures. */
	replace_slice_ast(fetch, val_val(member));
	set_type(fetch, def->t);
	return 0;
}

static int analyze_fetch(struct act_state *state, struct scope *scope,
                           struct ast *fetch)
{
	assert(fetch->k == AST_FETCH);
	struct type *type = fetch_type(fetch);
	if (analyze_type(state, scope, type))
		return -1;

	assert(type->d);
	if (type->d->k == AST_ENUM_DEF)
		return analyze_enum_fetch(state, scope, fetch);

	if (type->k != TYPE_STRUCT && type->k != TYPE_TRAIT &&
	    !is_primitive(type)) {
		char *tstr = type_str(type);
		semantic_error(fetch,
		               "illegal fetch type %s", tstr);
		free(tstr);
		return -1;
	}

	struct ast *def = type->d->def;
	assert(def);

	struct ast *member = scope_find_proc(def->scope, fetch_id(fetch));
	if (!member) {
		semantic_error(fetch,
		               "no such proc");
		return -1;
	}

	set_type(fetch, member->t);
	return 0;
}

static int analyze_enum(struct act_state *state, struct scope *scope,
                          struct ast *node)
{
	assert(node->k == AST_ENUM_DEF);
	struct scope *enum_scope = node->scope;

	/* TODO: here we could save space by choosing the smallest type that
	 * fits */
	if (!enum_type(node))
		enum_type(node) = i27_type(scope);

	/* enum are at least currently limited to top scope, so we don't have to
	 * worry about them being part of some generic structure. Might be a
	 * future improvement, though. */
	struct type *type = enum_type(node);
	if (analyze_type(state, enum_scope, type))
		return -1;

	/** @todo build up a compound for enums? */
	node->t = type;

	long long counter = 0;
	struct ast *members = enum_body(node);
	while (members) {
		set_type(members, type);
		if (!val_val(members))
			val_val(members) = gen_const_int(counter, NULL_LOC());

		struct ast *val = val_val(members);
		if (analyze(state, enum_scope, val))
			return -1;

		if (val->k != AST_CONST_INT) {
			semantic_error(members,
			               "unable to process nonconstant expression");
			return -1;
		}

		counter = int_val(val) + 1;
		members = members->n;
	}

	/* TODO: check that we don't go outside the limits of the type */
	return 0;
}

static int analyze_if(struct act_state *state, struct scope *scope,
                        struct ast *node)
{
	assert(node->k == AST_IF);
	if (analyze(state, scope, if_cond(node)))
		return -1;

	if (analyze(state, scope, if_body(node)))
		return -1;

	if (analyze(state, scope, if_else(node)))
		return -1;

	if (ast_flags(node, AST_FLAG_DOEXPR)) {
		struct type *tt = ast_last(if_body(node))->t;
		struct type *ft = ast_last(if_else(node))->t;
		if (!types_match(tt, ft)) {
			semantic_error(node,
			               "mismatched if/else body values");
			return -1;
		}

		set_type(node, tt);
		return 0;
	}

	node->t = void_type();
	return 0;
}

static int analyze_for(struct act_state *state, struct scope *scope,
                         struct ast *node)
{
	assert(node->k == AST_FOR);
	struct act_stack *prev = state->loop_stack;
	enum act_flags flags = state->flags;
	node->t = void_type();

	if (analyze_list(state, scope, for_pre(node)))
		goto err;

	if (analyze_list(state, scope, for_post(node)))
		goto err;

	if (analyze_list(state, scope, for_cond(node)))
		goto err;

	state->flags |= ACT_IN_LOOP;
	if (analyze_list(state, scope, for_body(node)))
		goto err;

	state->loop_stack = prev;
	state->flags = flags;
	return 0;

err:
	state->loop_stack = prev;
	state->flags = flags;
	return -1;
}

static int analyze_continue(struct act_state *state, struct scope *scope,
                              struct ast *node)
{
	UNUSED(scope);
	node->t = void_type();
	if (!(state->flags & ACT_IN_LOOP)) {
		semantic_error(node,
		               "continue outside of loop");
		return -1;
	}

	continue_defers(node) = clone_defers(state, state->loop_stack);
	return 0;
}

static int analyze_break(struct act_state *state, struct scope *scope,
                           struct ast *node)
{
	UNUSED(scope);
	node->t = void_type();
	if (!(state->flags & ACT_IN_LOOP)) {
		semantic_error(node,
		               "break outside of loop");
		return -1;
	}

	break_defers(node) = clone_defers(state, state->loop_stack);
	return 0;
}

static int analyze_comparison(struct act_state *state, struct scope *scope,
                                struct ast *node)
{
	assert(is_comparison(node));
	struct ast *left = comparison_left(node);
	struct ast *right = comparison_right(node);

	if (analyze(state, scope, left))
		return -1;

	if (analyze(state, scope, right))
		return -1;

	if (!is_primitive(left->t)) {
		type_error(scope->fctx, left->t, "primitive type required");
		return -1;
	}

	if (!is_primitive(right->t)) {
		type_error(scope->fctx, right->t, "primitive type required");
		return -1;
	}

	if (!types_match(left->t, right->t)) {
		type_mismatch(scope, "comparison type mismatch", node, left->t,
		              right->t);
		return -1;
	}

	return set_type(node, bool_type(scope));
}

static int analyze(struct act_state *state, struct scope *scope,
                     struct ast *node)
{
	if (!node)
		return 0;

	if (ast_flags(node, AST_FLAG_ACTUAL)) {
		assert(node->t);
		return 0;
	}

	if (ast_flags(node, AST_FLAG_INIT)) {
		/* I don't think this should ever happen but just to be safe */
		semantic_error(node, "semantic loop detected");
		return -1;
	}

	ast_set_flags(node, AST_FLAG_INIT);

	if (!node->scope)
		node->scope = scope;

	int ret = 0;
	if (is_unop(node)) {
		ret = analyze_unop(state, scope, node);
		goto out;
	}

	if (is_binop(node)) {
		ret = analyze_binop(state, scope, node);
		goto out;
	}

	if (is_comparison(node)) {
		ret = analyze_comparison(state, scope, node);
		goto out;
	}

	if (is_const(node)) {
		ret = analyze_const(state, scope, node);
		goto out;
	}

	switch (node->k) {
	case AST_IMPORT: ret = 0; node->t = void_type(); break;
	case AST_PROC_DEF: ret = analyze_proc(state, scope, node); break;
	case AST_TRAIT_DEF: ret = analyze_trait(state, scope, node); break;
	case AST_ALIAS_DEF: ret = analyze_alias(state, scope, node); break;
	case AST_ENUM_DEF: ret = analyze_enum(state, scope, node); break;
	case AST_STRUCT_DEF: ret = analyze_struct(state, scope, node); break;
	case AST_STRUCT_CONT_DEF: ret = analyze_struct_cont(state, scope,
		                                              node); break;
	case AST_VAR_DEF: ret = analyze_var(state, scope, node); break;
	case AST_CALL: ret = analyze_call(state, scope, node); break;
	case AST_BLOCK: ret = analyze_block(state, scope, node); break;
	case AST_ID: ret = analyze_id(state, scope, node); break;
	case AST_EMPTY: ret = analyze_empty(state, scope, node); break;
	case AST_CAST: ret = analyze_cast(state, scope, node); break;
	case AST_DEFER: ret = analyze_defer(state, scope, node); break;
	case AST_RETURN: ret = analyze_return(state, scope, node); break;
	case AST_GOTO: ret = analyze_goto(state, scope, node); break;
	case AST_LABEL: ret = analyze_label(state, scope, node); break;
	case AST_AS: ret = analyze_as(state, scope, node); break;
	case AST_DOT: ret = analyze_dot(state, scope, node); break;
	case AST_INIT: ret = analyze_init(state, scope, node); break;
	case AST_ASSIGN: ret = analyze_assign(state, scope, node); break;
	case AST_FETCH: ret = analyze_fetch(state, scope, node); break;
	case AST_IF: ret = analyze_if(state, scope, node); break;
	case AST_FOR: ret = analyze_for(state, scope, node); break;
	case AST_CONTINUE: ret = analyze_continue(state, scope, node); break;
	case AST_BREAK: ret = analyze_break(state, scope, node); break;
	case AST_MACRO_EXPAND: ret = analyze_macro_expand(state, scope, node);
		break;
	case AST_MACRO_DEF: ret = analyze_macro_def(state, scope, node);
		break;
	default:
		/* more like internal_error, maybe? */
		semantic_error(node,
		               "unimplemented actualization");
		return -1;
	}

out:
	if (ret)
		return ret;

	assert(node->t);
	assert(node->scope);
	ast_set_flags(node, AST_FLAG_ACTUAL);
	return 0;
}

static int analyze_list(struct act_state *state, struct scope *scope,
                          struct ast *l)
{
	foreach_node(n, l) {
		if (analyze(state, scope, n))
			return -1;
	}

	return 0;
}

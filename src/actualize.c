/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

/**
 * @file actualize.c
 *
 * Implementations for stuff actualization.
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <ek/actualize.h>
#include <ek/compiler.h>
#include <ek/debug.h>

#define UNUSED(x) do { (void)(x); } while (0)

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
	struct act_stack *goto_stack;
	struct act_stack *label_stack;
};

static int replace_type_id(struct ast *nodes, char *id,
                           struct type *replacement);

static int actualize(struct act_state *state, struct scope *scope,
                     struct ast *node);

static int actualize_list(struct act_state *state, struct scope *scope,
                     struct ast *l);

static int actualize_type(struct act_state *state, struct scope *scope,
                     struct type *node);

static int actualize_type_list(struct act_state *state, struct scope *scope,
                     struct type *node);

static int is_lvalue(struct ast *n)
{
	if (n->k == AST_ARR)
		return 1;

	if (n->k == AST_ID)
		return 1;

	if (n->k == AST_DEREF)
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

static void type_mismatch(struct scope *scope, struct ast *node, struct type *a, struct type *b)
{
	char *left_type = type_str(a);
	char *right_type = type_str(b);
	semantic_error(scope->fctx, node,
		       "type mismatch: %s vs %s",
		       left_type, right_type);
	free(left_type);
	free(right_type);
}

static int analyze(struct scope *scope, struct ast *tree);

static int eval_const_if(struct scope *scope, struct ast *node)
{
	assert(node
	       && node->k == AST_IF
	       && ast_flags(node, AST_FLAG_CONST));

	semantic_error(scope->fctx, node,
		                "const if unimplemented");
	return -1;
}

static int analyze_visibility(struct scope *scope, struct ast *node)
{
	if (!node)
		return 0;

	node->scope = scope;

	switch (node->k) {
	case AST_PROC_DEF: return scope_add_proc(scope, node);
	case AST_MACRO_DEF: return scope_add_macro(scope, node);
	case AST_VAR_DEF: return scope_add_var(scope, node);

	case AST_IMPORT: {
		const char *file = import_file(node);
		return process_file(&scope,
		                    (int)ast_flags(node, AST_FLAG_PUBLIC),
				    file);
	}

	case AST_IF: {
		assert(ast_flags(node, AST_FLAG_CONST));
		if (eval_const_if(scope, node))
			return -1;

		/* since a const if likely replaced the current node with
		 * something else, we have to analyze the replacement */
		return analyze(scope, node);
	}

	case AST_STRUCT_DEF: {
		/* we shouldn't get any anonymous structs at this stage */
		char *id = struct_id(node);
		return scope_add_type(scope, id, node);
	}

	case AST_ENUM_DEF: {
		char *id = enum_id(node);
		return scope_add_type(scope, id, node);
	}

	case AST_ALIAS_DEF: {
		char *id = alias_id(node);
		return scope_add_type(scope, id, node);
	}

	case AST_TRAIT_DEF: {
		char *id = trait_id(node);
		return scope_add_type(scope, id, node);
	}

	case AST_EMPTY: {
		break;
	}

	default:
		semantic_error(scope->fctx, node, "unknown top element");
		return -1;
	};

	return 0;
}

static int analyze_var(struct scope *scope, struct ast *node)
{
	struct act_state state = {0};
	return actualize(&state, scope, node);
}

static void set_type(struct ast *node, struct type *type)
{
	node->t = clone_type_list(type);
}

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

static int analyze_proc(struct scope *scope, struct ast *node)
{
	struct scope *proc_scope = create_scope();
	scope_add_scope(scope, proc_scope);
	node->scope = proc_scope;

	struct ast *params = proc_params(node);
	struct act_state state = {0};
	if (actualize_list(&state, proc_scope, params))
		return -1;

	struct type *rtype = proc_rtype(node);

	if (actualize_type_list(&state, proc_scope, rtype))
		return -1;

	if (!rtype)
		proc_rtype(node) = void_type();

	struct type *callable = tgen_callable(NULL, proc_rtype(node), node->loc);
	foreach_node(p, params) {
		/* we must manually 'start' the chain **/
		if (!callable_ptypes(callable)) {
			callable_ptypes(callable) = clone_type(p->t);
			continue;
		}

		type_append(callable_ptypes(callable), p->t);
	}

	set_type(node, callable);
	return 0;
}

static struct ast *analyze_type_expand(struct scope *scope,
                                            struct ast *n)
{
	assert(n->k == AST_TYPE_EXPAND);
	struct ast *trait = file_scope_find_type(scope, type_expand_id(n));
	if (!trait) {
		semantic_error(scope->fctx, n, "no such type");
		return NULL;
	}

	if (trait->k != AST_TRAIT_DEF) {
		semantic_error(scope->fctx, n, "not a trait");
		return NULL;
	}

	semantic_info(scope->fctx, n,
	              "FIXME: skipping type param check for now");
	struct ast *body = trait_raw_body(trait);
	body = clone_ast(body);

	struct type *pa = type_expand_args(n);
	foreach_node(pt, trait_params(trait)) {
		replace_type_id(body, var_id(pt), pa);
		pa = pa->n;
	}
	return body;
}

static int implements_trait(struct ast *body, char *id)
{
	foreach_node(n, body) {
		/* traits don't currently take generic parameters I guess? */
		if (n->k != AST_ID)
			continue;

		if (same_id(id_str(n), id))
			return 1;
	}

	return 0;
}

static int analyze_struct(struct scope *scope, struct ast *node)
{
	assert(node->k == AST_STRUCT_DEF);
	struct ast *params = struct_params(node);
	struct scope *struct_scope = create_scope();
	if (!struct_scope)
		return -1;

	scope_add_scope(node->scope, struct_scope);
	node->scope = struct_scope;
	if (params)
		ast_set_flags(node, AST_FLAG_GENERIC);

	struct type *type = tgen_type(TYPE_STRUCT,
					NULL, NULL,
	                                 node, NULL,
					 strdup(struct_id(node)),
					 node->loc);

	foreach_node(n, struct_body(node)) {
		if (n->k != AST_TYPE_EXPAND)
			continue;

		if (implements_trait(struct_body(node), type_expand_id(n))) {
			n->k = AST_EMPTY;
			continue;
		}

		if (same_id(struct_id(node), type_expand_id(n))) {
			semantic_error(scope->fctx, n,
			               "recursive trait implementations not allowed");
			return -1;
		}

		struct ast *body = analyze_type_expand(scope, n);
		if (!body) {
			n->k = AST_EMPTY;
			continue;
		}

		replace_type_id(body, type_expand_id(n), type);
		ast_block_last(body)->n = n->n;
		n->n = body;
	}

	foreach_node(n, struct_body(node)) {
		switch (n->k) {
		case AST_EMPTY: continue;
		case AST_ID: continue;
		/* prototypes are checked later */
		case AST_PROC_DEF: if (!proc_body(n)) continue;
		default:
		}

		if (analyze_visibility(struct_scope, n))
			return -1;
	}

	foreach_node(n, struct_body(node)) {
		/* also checks prototypes */
		if (n->k != AST_PROC_DEF)
			continue;

		if (analyze_proc(struct_scope, n))
			return -1;
	}

	/* check that all prototypes are implemented */
	foreach_node(n, struct_body(node)) {
		if (n->k != AST_PROC_DEF)
			continue;

		if (proc_body(n))
			continue;

		struct ast *proc = scope_find_proc(struct_scope, proc_id(n));
		if (!proc) {
			semantic_error(scope->fctx, n,
			               "missing implementation");
			return -1;
		}

		if (!types_match(n->t, proc->t)) {
			semantic_error(scope->fctx, n, "mismatched signatures");
			semantic_info(scope->fctx, proc, "note: here");
			return -1;
		}
	}

	char *id = strdup(struct_id(node));
	if (same_id(id, "i27"))
		node->t = tgen_primitive(TYPE_I27, id, node, node->loc);
	else if (same_id(id, "i9"))
		node->t = tgen_primitive(TYPE_I9, id, node, node->loc);
	else if (same_id(id, "bool"))
		node->t = tgen_primitive(TYPE_BOOL, id, node, node->loc);
	else
		node->t = tgen_struct(id, node, node->loc);

	/** @todo there is the possibility that two different traits add the
	 * same prototype, which is reported in traits but not structs? */
	return 0;
}

/* quite a lot of overlap with analyze_struct, kind of ugly I guess */
static int analyze_trait(struct scope *scope, struct ast *node)
{
	assert(node->k == AST_TRAIT_DEF);
	struct ast *params = trait_params(node);
	struct scope *trait_scope = create_scope();
	if (!trait_scope)
		return -1;

	scope_add_scope(node->scope, trait_scope);
	node->scope = trait_scope;
	/** @todo should probably add in aliases for the traits in scope? */
	if (params)
		ast_set_flags(node, AST_FLAG_GENERIC);

	struct type *type = tgen_type(TYPE_TRAIT, NULL, NULL,
			node, NULL, strdup(trait_id(node)),
			node->loc);

	/* copy body */
	node->a2 = clone_ast(trait_raw_body(node));

	/* do type expansions */
	foreach_node(n, trait_body(node)) {
		if (n->k != AST_TYPE_EXPAND)
			continue;

		/* don't re-expand already implemented traits */
		if (implements_trait(trait_body(node), type_expand_id(n))) {
			/* not sure about this, but at least we don't have stray
			 * type expands everywhere */
			n->k = AST_EMPTY;
			continue;
		}

		if (same_id(trait_id(node), type_expand_id(n))) {
			semantic_error(scope->fctx, n,
			               "recursive trait implementations not allowed");
			return -1;
		}

		struct ast *body = analyze_type_expand(scope, n);
		if (!body) {
			n->k = AST_EMPTY;
			continue;
		}

		replace_type_id(body, type_expand_id(n), type);
		ast_last(body)->n = n->n;
		n->n = body;
	}

	/* add all procedure definitions to scope */
	foreach_node(n, trait_body(node)) {
		/* kind of a hack but these shouldn't be shown to
		 * analyze_visibility  */
		switch (n->k) {
		case AST_EMPTY: continue;
		case AST_ID: continue;
		/* prototypes are added later */
		case AST_PROC_DEF: if (!proc_body(n)) continue;
		default:
		}

		if (analyze_visibility(trait_scope, n))
			return -1;
	}

	/** @todo I should really check that there's just one prototype and one
	 * implementation of that prototype, not sure what the best approach
	 * would be. Add a prototypes -list to scopes? */

	/* add all prototypes that don't have matching definition to scope */
	foreach_node(n, trait_body(node)) {
		if (n->k != AST_PROC_DEF)
			continue;

		if (proc_body(n))
			continue;

		/* prototypes are checked only if there's no implementation */
		if (scope_find_proc(trait_scope, proc_id(n)))
			continue;

		if (analyze_visibility(trait_scope, n))
			return -1;
	}

	foreach_node(n, trait_body(node)) {
		if (n->k != AST_PROC_DEF)
			continue;

		if (analyze_proc(trait_scope, n))
			return -1;
	}

	node->t = tgen_trait(strdup(struct_id(node)), node, node->loc);

	return 0;
}

static int analyze_signs(struct scope *scope, struct ast *node)
{
	/** @todo aliases? */
	switch (node->k) {
	case AST_VAR_DEF: return analyze_var(scope, node); break;
	case AST_PROC_DEF: return analyze_proc(scope, node); break;
	case AST_STRUCT_DEF: return analyze_struct(scope, node); break;
	case AST_TRAIT_DEF: return analyze_trait(scope, node); break;
	default:
	}

	return 0;
}

static int analyze(struct scope *scope, struct ast *tree)
{
	foreach_node(node, tree) {
		if (analyze_visibility(scope, node))
			return -1;
	}

	foreach_node(node, tree) {
		if (analyze_signs(scope, node))
			return -1;
	}

	foreach_node(node, tree){
		struct act_state state = {0};
		if (actualize(&state, scope, node))
			return -1;

		printf("//actualized:\n");
		ast_dump(0, node);
	}

	return 0;
}

int analyze_root(struct scope *scope, struct ast *tree)
{
	if (analyze(scope, tree))
		return -1;

	return 0;
}

static int structs_match(struct type *a, struct type *b)
{
	/* dunno, let's go with this for now */
	return a->d == b->d;
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

	if (a->k == TYPE_STRUCT)
		return structs_match(a, b);

	if (a->k == TYPE_PTR)
		return types_match(ptr_base(a), ptr_base(b));

	return 1;
}

static int _replace_id(struct ast *node, void *data)
{
	if (!node)
		return 0;

	if (node->k != AST_ID)
		return 0;

	struct ast **pair = data;
	struct ast *id = pair[0];
	struct ast *expr = pair[1];

	/* no match, continue */
	if (!same_id(id_str(node), id_str(id)))
		return 0;

	struct ast *clone = clone_ast(expr);
	if (!clone) {
		internal_error("failed cloning replacement expr");
		return -1;
	}

	clone->n = node->n;
	clone->scope = node->scope;
	replace_ast(node, clone);

	/* a succesful replacement needs no futher replacements, I think */
	return 0;
}
static int replace_id(struct ast *body, struct ast *id,
                      struct ast *expr)
{
	struct ast *pair[2] = {id, expr};
	return ast_visit(_replace_id, NULL, body, pair);
}

static int actualize_macro_def(struct act_state *state,
                                     struct scope *scope, struct ast *n)
{
	UNUSED(state);
	/* macro bodies, arguments, etc aren't expanded upon until the macro is
	 * called, so just try to add it to the local scope */
	assert(n && n->k == AST_MACRO_DEF);
	return scope_add_macro(scope, n);
}

static int actualize_macro_expand(struct act_state *state,
                                  struct scope *scope,
                                  struct ast *macro_expand)
{
	assert(macro_expand->k == AST_MACRO_EXPAND);
	char *id = macro_expand_id(macro_expand);
	struct ast *macro = file_scope_find_macro(scope, id);
	if (!macro) {
		semantic_error(scope->fctx, macro_expand, "no such macro");
		return -1;
	}

	assert(macro->k == AST_MACRO_DEF);
	if (ast_flags(macro, AST_FLAG_VARIADIC)) {
		semantic_error(scope->fctx, macro,
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
			semantic_error(scope->fctx, macro_expand,
			               "failed replacing params with args");
			arg->n = next_arg;
			return -1;
		}

		param = param->n;
		arg = arg->n = next_arg;
	}

	free(macro_expand_id(macro_expand));
	*macro_expand = *body;
	/* actualize the new content */
	return actualize(state, scope, macro_expand);
}

static int actualize_call(struct act_state *state,
                          struct scope *scope, struct ast *call)
{
	assert(call && call->k == AST_CALL);

	if (actualize_list(state, scope, call_args(call)))
		return -1;

	if (actualize_list(state, scope, call_expr(call)))
		return -1;

	struct ast *expr = call_expr(call);
	if (expr->t->k != TYPE_CALLABLE) {
		char *tstr = type_str(expr->t);
		semantic_error(scope->fctx, call, "not a callable type: %s",
		              tstr);
		free(tstr);
		return -1;
	}

	struct type *callable = expr->t;
	struct type *ptypes = callable_ptypes(callable);
	struct ast *arg = call_args(call);
	foreach_type(p, ptypes) {
		if (!arg) {
			semantic_error(scope->fctx, call, "too many arguments");
			return -1;
		}

		if (!types_match(p, arg->t)) {
			type_mismatch(scope, arg, p, arg->t);
			return -1;
		}

		arg = arg->n;
	}

	if (arg) {
		semantic_error(scope->fctx, arg, "too many arguments");
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

static int actualize_proc(struct act_state *state,
                          struct scope *scope, struct ast *proc)
{
	UNUSED(state);
	/* actualize_proc is called on trait procs as well, but I believe
	 * that's fine? */
	assert(proc && proc->k == AST_PROC_DEF);

	struct act_state new_state = {0};
	/* params should already have been actualized, should maybe check */

	/* actualize body */
	new_state.cur_proc = proc;
	if (actualize(&new_state, proc->scope, proc_body(proc)))
		return -1;

	if (!act_flags(&new_state, ACT_HAS_RETURN)) {
		if (!is_void(proc_rtype(proc))) {
			semantic_error(scope->fctx, proc,
			               "no return with non-void return type");
			return -1;
		}

		/* add 'implicit' return */
		struct ast *body = proc_body(proc);
		struct ast *r = gen_return(NULL, NULL, NULL_LOC());
		r->scope = body->scope;
		ast_append(block_body(body), r);
	}
	else if (ast_block_last(proc_body(proc))->k != AST_RETURN) {
		/* TODO: something more sophisticated than this */
		semantic_warn(scope->fctx, proc,
		              "unable to determine explicit return for all branches");
		return -1;
	}

	warn_unused_labels(&new_state, scope);
	if (undefined_gotos(&new_state, scope))
		return -1;

	/* if we're main, don't mangle the entry point */
	char *id = proc_id(proc);
	if (strcmp("main", id) == 0)
		ast_set_flags(proc, AST_FLAG_NOMANGLE);

	/* we have successfully actualized the procedure */
	return 0;
}

static int actualize_binop(struct act_state *state,
                           struct scope *scope, struct ast *binop)
{
	assert(binop && is_binop(binop));

	struct ast *left = binop_left(binop);
	struct ast *right = binop_right(binop);

	if (actualize(state, scope, left))
		return -1;

	if (actualize(state, scope, right))
		return -1;

	if (!types_match(left->t, right->t)) {
		type_mismatch(scope, binop, left->t, right->t);
		return -1;
	}

	/* types are the same, so the type of this expression is whichever */
	set_type(binop, left->t);
	return 0;
}


static int actualize_block(struct act_state *state,
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
		if (actualize(state, block_scope, pt))
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
		semantic_error(scope->fctx, node,
		               "unable to detect block type");
		return -1;
	}

	/* TODO: currently defers are sort of duplicated after a return, unsure
	 * if they should be handled here or somewhere else */
	if (state->defer_stack) {
		block_defers(node) = clone_defers(state, defers);
		if (!block_defers(node)) {
			internal_error("failed cloning defers");
			return -1;
		}

		clear_defers(state, defers);
	}

	return 0;
}

static int actualize_id(struct act_state *state,
                        struct scope *scope, struct ast *id)
{
	UNUSED(state);
	assert(id && id->k == AST_ID);
	id->scope = scope;

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
	struct ast *decl = file_scope_find_var(scope, id_str(id));
	if (decl) {
		set_type(id, decl->t);
		decl->uses++;
		return 0;
	}

	decl = file_scope_find_proc(scope, id_str(id));
	if (decl) {
		set_type(id, decl->t);
		decl->uses++;
		return 0;
	}

	semantic_error(scope->fctx, id, "no such object");
	return -1;
}

static int actualize_var(struct act_state *state,
                         struct scope *scope, struct ast *var)
{
	assert(var && var->k == AST_VAR_DEF);
	struct ast *init = var_init(var);
	struct type *type = var_type(var);
	/* one of these must be defined, otherwise the parser fucked up */
	assert(type || init);

	if (init && actualize_list(state, scope, init))
		return -1;

	if (type && actualize_type_list(state, scope, type))
		return -1;

	if (init && init->k == AST_INIT) {
		assert(!init->t);
		set_type(init, type);
		/* TODO: some kind of check_init() */
	}

	if (init && type) {
		/* make sure the asked type and the actualized types match */
		if (!types_match(init->t, type)) {
			type_mismatch(scope, var, init->t, type);
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

static int actualize_tid(struct act_state *state, struct scope *scope, struct type *t)
{
	UNUSED(state);

	/* no id means void */
	if (!t->id) {
		replace_type(t, void_type());
		return 0;
	}

	struct src_loc l = t->loc;

	struct ast *def = file_scope_find_type(scope, t->id);
	if (!def) {
		type_error(scope->fctx, t, "no such type");
		return -1;
	}

	assert(t->n == NULL);
	assert(def->k != AST_TRAIT_DEF);

	if (def->k == AST_ALIAS_DEF) {
		replace_type(t, clone_type_list(def->t));
		t->a = def;
		return 0;
	}
	else if (def->k == AST_STRUCT_DEF) {
		replace_type(t, clone_type_list(def->t));
		return 0;
	}
	else if (def->k == AST_ENUM_DEF) {
		replace_type(t, clone_type_list(def->t));
		return 0;
	}

	return -1;
}

static int actualize_ptr(struct act_state *state, struct scope *scope, struct type *t)
{
	assert(ptr_base(t));
	if (actualize_type(state, scope, ptr_base(t)))
		return -1;

	return 0;
}

static int actualize_callable(struct act_state *state, struct scope *scope, struct type *t)
{
	struct type *ptypes = callable_ptypes(t);
	struct type *rtype = callable_rtype(t);

	foreach_type(p, ptypes){
		if (actualize_type(state, scope, p))
			return -1;
	}

	if (!rtype)
		callable_rtype(t) = void_type();

	if (actualize_type(state, scope, rtype))
		return -1;

	return 0;
}

static int actualize_i27(struct act_state *state, struct scope *scope, struct type *t)
{
	/* not much to do */
	if (t->d)
		return 0;

	struct ast *def = file_scope_find_type(scope, "i27");
	if (!def) {
		error("missing definition of type 'i27'");
		return NULL;
	}

	t->d = def;
	return 0;
}

static int actualize_i9(struct act_state *state, struct scope *scope, struct type *t)
{
	/* not much to do */
	if (t->d)
		return 0;

	struct ast *def = file_scope_find_type(scope, "i9");
	if (!def) {
		error("missing definition of type 'i9'");
		return NULL;
	}

	t->d = def;
	return 0;
}

static int actualize_bool(struct act_state *state, struct scope *scope, struct type *t)
{
	/* not much to do */
	if (t->d)
		return 0;

	struct ast *def = file_scope_find_type(scope, "bool");
	if (!def) {
		error("missing definition of type 'bool'");
		return NULL;
	}

	t->d = def;
	return 0;
}

static int actualize_type(struct act_state *state,
                          struct scope *scope,
			  struct type *t)
{
	if (!t)
		return 0;

	t->scope = scope;

	if (actualize_type(state, scope, t->n))
		return -1;

	switch (t->k) {
	case TYPE_I27: return actualize_i27(state, scope, t);
	case TYPE_I9: return actualize_i9(state, scope, t);
	case TYPE_BOOL: return actualize_bool(state, scope, t);
	case TYPE_ID: return actualize_tid(state, scope, t);
	case TYPE_PTR: return actualize_ptr(state, scope, t);
	case TYPE_CALLABLE: return actualize_callable(state, scope, t);
	case TYPE_VOID: return 0; /* void is by default actualized */

	default:
		type_info(scope->fctx, t,
		              "unimplemented type");
		type_info(scope->fctx, t,
			"continuing with compilation to see what breaks");
		return 0;
	}

	return 0;
}

static int actualize_type_list(struct act_state *state,
                          struct scope *scope,
			  struct type *l)
{
	foreach_type(t, l) {
		if (actualize_type(state, scope, t))
			return -1;
	}

	return 0;
}

static int actualize_empty(struct act_state *state,
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

static size_t member_count(struct ast *exists)
{
	assert(exists->k == AST_STRUCT_DEF);
	struct ast *body = struct_body(exists);

	size_t count = 0;
	foreach_node(n, body) {
		if (n->k == AST_VAR_DEF)
			count++;
	}

	return count;
}

static struct ast *lookup_member_idx(struct ast *body,
                                          char *find,
                                          size_t *idx)
{
	/* micro-optimisation, likely way premature but speeds up selection
	 * between lookup_struct_member_idx and *_name by a tiny amount */
	(void)(find);
	assert(idx);
	size_t i = *idx;
	struct ast *m = body;
	while (i != 0 && m) {
		m = m->n;
		i--;
	}

	return m;
}

static struct ast *lookup_member_name(struct ast *body,
                                           char *find,
                                           size_t *idx)
{
	size_t i = 0;
	struct ast *m = body;
	while (m) {
		assert(m->k == AST_VAR_DEF);
		if (same_id(find, var_id(m)))
			break;
		m = m->n;
		i++;
	}

	if (idx)
		*idx = i;

	return m;
}

static struct ast *lookup_struct_member(struct ast *struc,
                                             char *find, size_t *idx)
{
	if (find)
		return lookup_member_name(struct_body(struc), find, idx);

	return lookup_member_idx(struct_body(struc), find, idx);
}

static struct ast *lookup_enum_member(struct ast *enu,
                                           char *find)
{
	size_t i = 0;
	struct ast *m = enum_body(enu);
	while (m) {
		assert(m->k == AST_VAL);
		if (same_id(find, val_id(m)))
			break;
		m = m->n;
		i++;
	}

	return m;
}

static int init_struct(struct act_state *state, struct scope *scope,
                       struct ast *exists, struct ast *init)
{
	size_t i = 0;
	size_t mcount = member_count(exists);

	int ret = 0;
	char *initd = calloc(sizeof(char), mcount);
	if (!initd) {
		internal_error("failed allocating initd array");
		return -1;
	}

	struct ast *args = init_body(init);
	while (args) {
		if (i >= mcount) {
			semantic_error(scope->fctx, args,
			               "excessive elements in initializer");
			ret = -1;
			break;
		}

		if (initd[i]) {
			semantic_error(scope->fctx, args,
			               "overwriting already initialized elements");
			ret = -1;
			break;
		}

		if ((ret = actualize(state, scope, args)))
			break;

		char *find = NULL;
		if (ast_flags(args, AST_FLAG_MEMBER))
			find = var_id(args);

		struct ast *member =
			lookup_struct_member(exists, find, &i);

		if (!member) {
			char *sstr = type_str(exists->t);
			semantic_error(scope->fctx, args,
			               "no such member in %s",
			               sstr);
			free(sstr);
			ret = -1;
			break;
		}

		if (!types_match(args->t, member->t)) {
			char *astr = type_str(args->t);
			char *mstr = type_str(member->t);
			semantic_error(scope->fctx, args,
			               "%s does not match %s", astr, mstr);
			free(astr);
			free(mstr);
			ret = -1;
			break;
		}

		initd[i] = 1;
		args = args->n;
		i++;
	}

	free(initd);
	return ret;
}

static int actualize_struct_init_cast(struct act_state *state,
                                      struct scope *scope,
                                      struct ast *init,
                                      struct type *type)
{
	struct ast *def = type->d;
	return init_struct(state, scope, def, init);
}

static int actualize_init_cast(struct act_state *state,
                               struct scope *scope, struct ast *init,
                               struct type *type)
{
	if (type->k == TYPE_STRUCT)
		return actualize_struct_init_cast(state, scope, init, type);

	type_error(scope->fctx, type,
	               "type is not a struct");
	return -1;

}

static int actualize_cast(struct act_state *state,
                          struct scope *scope, struct ast *cast)
{
	assert(cast->k == AST_CAST);
	struct ast *expr = cast_expr(cast);
	struct type *type = cast_type(cast);

	if (actualize_type(state, scope, type))
		return -1;

	if (actualize(state, scope, expr))
		return -1;

	if (expr->k == AST_INIT) {
		set_type(cast, type);
		return actualize_init_cast(state, scope, expr, type);
	}

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
	semantic_error(scope->fctx, cast, "illegal cast: %s vs %s",
	               left_type, right_type);
	free(left_type);
	free(right_type);
	return -1;
}

static int actualize_const(struct act_state *state, struct scope *scope,
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

	semantic_error(scope->fctx, cons, "unimplemented constant");
	return 1;
}

static int actualize_alias(struct act_state *state, struct scope *scope,
                           struct ast *alias)
{
	/* I shall have to think about things, as currently very deeply nested
	 * aliases might be a bit cumbersome to work with. Still, this works
	 * well enough I suppose. */
	assert(alias->k == AST_ALIAS_DEF);
	if (actualize_type(state, scope, alias_type(alias))) {
		/* usually we don't want to output errors upon errors, but this
		 * is likely a useful message as it might show where a loop is
		 * occuring */
		semantic_error(scope->fctx, alias, "failed actualizing alias");
		return -1;
	}

	ast_set_flags(alias, AST_FLAG_ACTUAL);
	return 0;
}

static int actualize_defer(struct act_state *state,
                           struct scope *scope, struct ast *node)
{
	struct ast *expr = defer_expr(node);
	/* TODO: should the actualization only happen when the defers are
	 * called? */
	if (actualize(state, scope, expr))
		return -1;

	if (push_defer(state, expr))
		return -1;

	node->t = void_type();
	return 0;
}

static int actualize_return(struct act_state *state, struct scope *scope,
                            struct ast *node)
{
	act_set_flags(state, ACT_HAS_RETURN);
	struct ast *expr = return_expr(node);
	if (expr) {
		if (actualize(state, scope, expr))
			return -1;

		set_type(node, expr->t);
	}
	else {
		node->t = void_type();
	}

	assert(state->cur_proc);
	struct ast *cur_proc = state->cur_proc;
	struct type *rtype = proc_rtype(cur_proc);
	if (!types_match(node->t, rtype)) {
		/* hmm, should this be "return type mismatch? */
		type_mismatch(scope, node, rtype, node->t);
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
static void actualize_goto_defer(struct ast *got, struct ast *label)
{
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


static int actualize_goto(struct act_state *state, struct scope *scope,
                          struct ast *node)
{
	assert(node->k == AST_GOTO);
	push_goto(state, node);

	/* clone all defers as we don't know where the label might be */
	goto_defers(node) = clone_defers(state, NULL);
	node->t = void_type();

	struct ast *label = find_label(state, goto_label(node));
	/* this is a jump backwards, i.e. we can already do it */
	if (label)
		actualize_goto_defer(node, label);

	/* forward jump, handle stuff when we run into the corresponding label */
	return 0;
}

static void actualize_goto_defers(struct act_state *state,
                                  struct ast *label)
{
	struct act_stack *prev = state->goto_stack, *cur;
	if (prev)
		do {
			cur = prev->next;
			struct ast *got = prev->node;
			if (same_id(goto_label(got), label_id(label)))
				actualize_goto_defer(got, label);

		} while ((prev = cur));
}

static int actualize_label(struct act_state *state, struct scope *scope,
                           struct ast *node)
{
	assert(node->k == AST_LABEL);
	struct ast *prev = find_label(state, label_id(node));
	if (prev) {
		semantic_error(scope->fctx, node, "label redefined");
		semantic_info(scope->fctx, prev, "previous definition");
		return -1;
	}

	push_label(state, node);
	/* clone all defers */
	label_defers(node) = clone_defers(state, NULL);
	node->t = void_type();

	actualize_goto_defers(state, node);
	return 0;
}

static int actualize_unop(struct act_state *state,
                          struct scope *scope, struct ast *node)
{
	assert(is_unop(node));
	struct ast *expr = unop_expr(node);
	if (actualize(state, scope, expr))
		return -1;

	/* generally speaking */
	set_type(node, expr->t);

	switch (node->k) {
	case AST_DEREF: {
		struct type *type = expr->t;
		if (type->k!= TYPE_PTR) {
			/** @todo or array? */
			char *tstr = type_str(type);
			semantic_error(scope->fctx, expr,
			               "not a pointer: %s",
				       tstr);
			free(tstr);
			return -1;
		}

		set_type(node, ptr_base(type));
		assert(node->t);
		break;
	}

	case AST_REF: {
		/** @todo array pointer decay? */
		node->t = tgen_ptr(clone_type(expr->t), node->loc);
		break;
	}

	case AST_LNOT: {
		if (is_primitive(expr->t)) {
			char *tstr = type_str(expr->t);
			semantic_error(scope->fctx, node,
			               "'!' only implemented for primitive types: %s",
				       tstr);
			free(tstr);
			return -1;
		}

		if (expr->t->k == TYPE_VOID) {
			semantic_error(scope->fctx, node,
			               "'!' not implemented for void");
			return -1;
		}

		node->t = bool_type(scope);
		break;
	}

	default: semantic_error(scope->fctx, node,
		                "unimplemented unary operation");
		return -1;
	}

	return 0;
}

static int actualize_as(struct act_state *state,
                        struct scope *scope, struct ast *as)
{
	assert(as->k == AST_AS);
	struct type *type = as->t;
	if (actualize_type(state, scope, type))
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
	}

	return 0;
}

static int _replace_ast_type_id(struct ast *node, void *data)
{
	if (!node)
		return 0;

	return type_visit_list(_replace_type_id, NULL, node->t, data);
}

static int replace_type_id(struct ast *nodes, char *id,
                           struct type *replacement)
{
	struct replace_data pair = {id, replacement};
	return ast_visit(_replace_ast_type_id, NULL, nodes, &pair);
}


/* lots of overlap with actualize_struct, kind of ugly... */
static int actualize_trait(struct act_state *state, struct scope *scope,
                           struct ast *node)
{
	assert(node->k == AST_TRAIT_DEF);
	foreach_node(n, trait_body(node)) {
		/* there's really only prodcedure body actualization left I
		 * guess, as type stuff was taken care of in the analysis phase
		 * */
		if (n->k != AST_PROC_DEF)
			continue;

		/* don't actualize prototypes, duh */
		if (!proc_body(n))
			continue;

		if (actualize(state, node->scope, n))
			return -1;
	}

	return 0;
}

static int actualize_struct(struct act_state *state,
                            struct scope *scope, struct ast *node)
{
	assert(node->k == AST_STRUCT_DEF);
	foreach_node(n, struct_body(node)) {
		/* there's really only prodcedure body actualization left I
		 * guess, as type stuff was taken care of in the analysis phase
		 * */
		if (n->k != AST_PROC_DEF)
			continue;

		/* don't actualize prototypes, duh */
		if (!proc_body(n))
			continue;

		if (actualize(state, node->scope, n))
			return -1;
	}

	return 0;
}

/* could maybe be renamed, but essentially dot in copper works as either
 * -> or . in C, so allow structures or traits and single level pointers to
 *  structures or traits. */
static int has_members(struct type *type)
{
	/* most likely */
	if (type->k == TYPE_STRUCT)
		return 1;

	if (type->k == TYPE_TRAIT)
		return 1;

	if (type->k == TYPE_CONSTRUCT)
		return 1;

	return 0;
}

static int actualize_dot(struct act_state *state,
                         struct scope *scope, struct ast *node)
{
	/* TODO: handle enums as well, idea is something like
	 * enum whatever {A_FLAG}
	 * ...
	 * whatever.A_FLAG
	 *
	 * possibly also if the expr is of type whatever then .A_FLAG just gets
	 * the corresponding constant?
	 **/
	assert(node->k == AST_DOT);
	struct ast *expr = dot_expr(node);
	if (actualize(state, scope, expr))
		return -1;

	char *id = dot_id(node);
	struct type *type = expr->t;

	struct ast *def = NULL;
	switch (type->k) {
	case TYPE_TRAIT:
	case TYPE_STRUCT: def = type->d; break;
	default: {
		char *tstr = type_str(type);
		semantic_error(scope->fctx, node,
		               "illegal type in dot expression: %s",
		               tstr);
		free(tstr);
		return -1;
	}
	}

	struct ast *exists = scope_find_var(def->scope, id);
	if (exists) {
		assert(exists->t);
		set_type(node, exists->t);
		return 0;
	}

	exists = scope_find_proc(def->scope, id);
	if (exists) {
		assert(exists->t);
		set_type(node, exists->t);
		return 0;
	}

	semantic_error(scope->fctx, node,
	               "does not have member");
	return -1;
}

static int actualize_init(struct act_state *state,
                          struct scope *scope, struct ast *node)
{
	assert(node->k == AST_INIT);
	/* for now just do the types, the named stuff will be checked later */
	/* TODO: how to make sure all members are initialized? */
	return actualize_list(state, scope, init_body(node));
}

static int actualize_assign(struct act_state *state, struct scope *scope,
                            struct ast *node)
{
	assert(node->k == AST_ASSIGN);
	struct ast *to = assign_to(node);
	if (actualize(state, scope, to))
		return -1;

	struct ast *from = assign_from(node);
	if (actualize_list(state, scope, from))
		return -1;

	if (from->k == AST_INIT) {
		set_type(node,  to->t);
		return actualize_init_cast(state, scope, from, to->t);
	}

	if (!types_match(to->t, from->t)) {
		type_mismatch(scope, node, to->t, from->t);
		return -1;
	}

	/** @todo rvalue vs lvalue? */
	if (!is_lvalue(to)) {
		semantic_error(scope->fctx, node,
		               "rvalue used where lvalue required");
		return -1;
	}

	set_type(node, to->t);
	return 0;
}

static int actualize_fetch(struct act_state *state, struct scope *scope,
                           struct ast *fetch)
{
	assert(fetch->k == AST_FETCH);
	struct type *type = fetch_type(fetch);
	if (actualize_type(state, scope, type))
		return -1;

	if (type->k != TYPE_ENUM) {
		type_error(scope->fctx, type, "type is not an enum");
		return -1;
	}

	char *id = fetch_id(fetch);
	struct ast *def = type->d;
	assert(def);

	struct ast *member = lookup_enum_member(def, id);
	if (!member) {
		char *estr = type_str(type);
		semantic_error(scope->fctx, fetch, "no such member in enum %s");
		free(estr);
		return -1;
	}

	set_type(fetch, def->t);
	return 0;
}

static int actualize_enum(struct act_state *state, struct scope *scope,
                          struct ast *node)
{
	assert(node->k == AST_ENUM_DEF);
	struct type *type = enum_type(node);
	struct scope *enum_scope = node->scope;

	/* TODO: here we could save space by choosing the smallest type that
	 * fits */
	if (!type) {
		type = i27_type(scope);
		node->t = type;
	} else if (actualize_type(state, enum_scope, type))
		return -1;

	long long counter = 0;
	node->t = type;
	struct ast *members = enum_body(node);
	while (members) {
		set_type(members, type);
		if (val_val(members)) {
			struct ast *val = val_val(members);
			if (actualize(state, enum_scope, val))
				return -1;

			if (val->k != AST_CONST_INT) {
				semantic_error(scope->fctx, members,
				               "unable to process nonconstant expression");
				return -1;
			}

			counter = int_val(val);
		}
		else {
			val_val(members) = gen_const_int(counter, NULL_LOC());
		}

		members = members->n;
		counter++;
	}

	/* TODO: check that we don't go outside the limits of the type */
	return 0;
}

static int actualize_if(struct act_state *state, struct scope *scope,
                        struct ast *node)
{
	assert(node->k == AST_IF);
	if (actualize(state, scope, if_cond(node)))
		return -1;

	if (actualize(state, scope, if_body(node)))
		return -1;

	if (actualize(state, scope, if_else(node)))
		return -1;

	if (ast_flags(node, AST_FLAG_DOEXPR)) {
		struct type *tt = ast_last(if_body(node))->t;
		struct type *ft = ast_last(if_else(node))->t;
		if (!types_match(tt, ft)) {
			semantic_error(scope->fctx, node,
			               "mismatched if/else body values");
			return -1;
		}

		set_type(node, tt);
		return 0;
	}

	node->t = void_type();
	return 0;
}

static int actualize_for(struct act_state *state, struct scope *scope,
                         struct ast *node)
{
	assert(node->k == AST_FOR);
	if (actualize_list(state, scope, for_pre(node)))
		return -1;

	if (actualize_list(state, scope, for_post(node)))
		return -1;

	if (actualize_list(state, scope, for_cond(node)))
		return -1;

	if (actualize_list(state, scope, for_body(node)))
		return -1;

	node->t = void_type();
	return 0;
}

static int actualize_comparison(struct act_state *state, struct scope *scope, struct ast *node)
{
	assert(is_comparison(node));
	struct ast *left = comparison_left(node);
	struct ast *right = comparison_right(node);

	if (actualize(state, scope, left))
		return -1;

	if (actualize(state, scope, right))
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
		type_mismatch(scope, node, left->t, right->t);
		return -1;
	}

	set_type(node, bool_type(scope));
	return 0;
}

static int actualize(struct act_state *state, struct scope *scope,
                     struct ast *node)
{
	if (!node)
		return 0;

	if (!node->scope)
		node->scope = scope;

	if (is_unop(node))
		return actualize_unop(state, scope, node);

	if (is_binop(node))
		return actualize_binop(state, scope, node);

	if (is_comparison(node))
		return actualize_comparison(state, scope, node);

	if (is_const(node))
		return actualize_const(state, scope, node);

	switch (node->k) {
	case AST_PROC_DEF: return actualize_proc(state, scope, node);
	case AST_TRAIT_DEF: return actualize_trait(state, scope, node);
	case AST_ALIAS_DEF: return actualize_alias(state, scope, node);
	case AST_ENUM_DEF: return actualize_enum(state, scope, node);
	case AST_MACRO_DEF: return actualize_macro_def(state, scope, node);
	case AST_STRUCT_DEF: return actualize_struct(state, scope, node);
	case AST_VAR_DEF: return actualize_var(state, scope, node);
	case AST_CALL: return actualize_call(state, scope, node);
	case AST_BLOCK: return actualize_block(state, scope, node);
	case AST_ID: return actualize_id(state, scope, node);
	case AST_EMPTY: return actualize_empty(state, scope, node);
	case AST_CAST: return actualize_cast(state, scope, node);
	case AST_DEFER: return actualize_defer(state, scope, node);
	case AST_RETURN: return actualize_return(state, scope, node);
	case AST_GOTO: return actualize_goto(state, scope, node);
	case AST_LABEL: return actualize_label(state, scope, node);
	case AST_AS: return actualize_as(state, scope, node);
	case AST_DOT: return actualize_dot(state, scope, node);
	case AST_INIT: return actualize_init(state, scope, node);
	case AST_ASSIGN: return actualize_assign(state, scope, node);
	case AST_FETCH: return actualize_fetch(state, scope, node);
	case AST_IF: return actualize_if(state, scope, node);
	case AST_FOR: return actualize_for(state, scope, node);
	case AST_MACRO_EXPAND: return actualize_macro_expand(state, scope, node);
	default:
		/* more like internal_error, maybe? */
		semantic_error(scope->fctx, node,
		               "unimplemented actualization");
		return -1;
	}

	return 0;
}

static int actualize_list(struct act_state *state, struct scope *scope,
		struct ast *l)
{
	foreach_node(n, l) {
		if (actualize(state, scope, n))
			return -1;
	}

	return 0;
}

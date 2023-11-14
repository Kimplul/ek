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
	struct ast_node *node;
	struct act_stack *next;
};

enum act_flags {
	ACT_IN_LOOP = (1 << 0),
	ACT_IN_SWITCH = (1 << 1),
	ACT_ONLY_TYPES = (1 << 2),
	ACT_HAS_RETURN = (1 << 3),
	ACT_REQUIRE_FULLY_QUALIFIED = (1 << 4),
};

struct act_state {
	enum act_flags flags;

	struct ast_node *last_var;
	struct ast_node *cur_trait;
	struct ast_node *cur_proc;
	struct act_stack *defer_stack;
	struct act_stack *goto_stack;
	struct act_stack *label_stack;
};

static void act_set_flags(struct act_state *state, enum act_flags flags)
{
	state->flags |= flags;
}

static enum act_flags act_flags(struct act_state *state, enum act_flags flags)
{
	return state->flags & flags;
}

/* TODO: this could be improved if we get a global void thing */
static int is_void(struct ast_node *type)
{
	assert(type->node_type == AST_TYPE);
	if (AST_TYPE(type).kind != AST_TYPE_PRIMITIVE)
		return 0;

	return AST_PRIMITIVE_TYPE(type).type == AST_VOID;
}

static struct ast_node *void_type()
{
	struct ast_node *v = gen_primitive(AST_VOID, NULL_LOC());
	ast_set_flags(v, AST_FLAG_ACTUAL);
	v->type = v;
	return v;
}

static struct ast_node *i27_type()
{
	struct ast_node *a = gen_primitive(AST_I27, NULL_LOC());
	ast_set_flags(a, AST_FLAG_ACTUAL);
	a->type = a;
	return a;
}

static int push_defer(struct act_state *state, struct ast_node *expr)
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

static int push_label(struct act_state *state, struct ast_node *label)
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

static struct ast_node *find_label(struct act_state *state,
                                   struct ast_node *label)
{
	assert(label->node_type == AST_LABEL);
	struct act_stack *prev = state->label_stack, *cur;
	if (prev)
		do {
			cur = prev->next;
			if (identical_ast_nodes(0, prev->node, label))
				return prev->node;
		} while ((prev = cur));

	return NULL;
}

static int push_goto(struct act_state *state, struct ast_node *got)
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

static struct ast_node *clone_defers(struct act_state *state,
                                     struct act_stack *to)
{
	struct act_stack *from = state->defer_stack;

	/* maintain reverse order */
	struct ast_node *defers = NULL, *prev = NULL;
	while (from != to) {
		struct ast_node *defer = clone_ast_node(from->node);
		if (prev)
			prev->next = defer;

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
	/* clears all defers */
	clear_defers(state, NULL);
	clear_labels(state, NULL);
	clear_gotos(state, NULL);
}

static int actualize(struct act_state *state, struct scope *scope,
                     struct ast_node *node);
static int analyze(struct scope *scope, struct ast_node *tree);

static int eval_const_if(struct scope *scope, struct ast_node *node)
{
	assert(node
	       && node->node_type == AST_IF
	       && ast_flags(node, AST_FLAG_CONST));

	int eval = 0;
	struct ast_node *cond = node->_if.cond;
	struct ast_node *next = node->next;

	switch (cond->node_type) {
	/* for now just check if the variable exists, might change in
	 * the future */
	case AST_ID: eval = file_scope_find_var(scope, cond) != NULL;
		break;
	default: semantic_error(scope->fctx, node,
		                "const if conditional at file scope unimplemented");
		return -1;
	}

	if (eval) {
		/* condition evaluated true, so keep the if block */
		struct ast_node *body = node->_if.body;
		ast_last_node(body)->next = node->next;

		/* an if must have a body, otherwise the parser messed up */
		assert(body);

		*node = *body;
		free(body);
		return 0;
	}

	struct ast_node *els = node->_if.els;
	if (els) {
		*node = *els;
		ast_last_node(els)->next = next;
		free(els);
		return 0;
	}

	if (next) {
		/* copy the next node into our place */
		*node = *next;
		free(next);
		return 0;
	}

	free(node);
	return 0;
}

static int analyze_file_visibility(struct scope *scope, struct ast_node *node)
{
	assert(scope_flags(scope, SCOPE_FILE));

	if (!node)
		return 0;

	int ret = 0;
	node->scope = scope;

	/* TODO: add error checking */
	switch (node->node_type) {
	case AST_PROC: {
		ret |= scope_add_proc(scope, node);
		break;
	}

	case AST_VAR: {
		ret |= scope_add_var(scope, node);
		break;
	}

	case AST_IMPORT: {
		const char *file = AST_IMPORT(node).file;
		ret |= process_file(&scope,
				ast_flags(node, AST_FLAG_PUBLIC), file);
		break;
	}

	case AST_IF: {
		assert(ast_flags(node, AST_FLAG_CONST));
		ret |= eval_const_if(scope, node);
		if (ret)
			return -1;

		/* since a const if likely replaced the current node with
		 * something else, we have to analyze the replacement */
		ret = analyze(scope, node);
		break;
	}

	case AST_STRUCT: {
		/* we shouldn't get any anonymous structs at this stage */
		struct ast_node *id = AST_STRUCT(node).id;
		ret |= scope_add_type(scope, id, node);
		break;
	}

	case AST_ENUM: {
		struct ast_node *id = AST_ENUM(node).id;
		ret |= scope_add_type(scope, id, node);
		break;
	}

	case AST_ALIAS: {
		struct ast_node *id = AST_ALIAS(node).id;
		ret |= scope_add_type(scope, id, node);
		break;
	}

	case AST_TRAIT: {
		struct ast_node *id = AST_TRAIT(node).id;
		ret |= scope_add_type(scope, id, node);
		break;
	}

	case AST_TYPE_CONSTRUCT: {
		ret |= scope_add_type_construct(scope, node);
		break;
	}

	case AST_MACRO_CONSTRUCT: {
		ret |= scope_add_macro(scope, node);
		break;
	}

	case AST_EMPTY: {
		break;
	}

	case AST_BLOCK: {
		/* a block might be inserted by something, in which case jump
		 * down into it */
		assert(ast_flags(node, AST_FLAG_UNHYGIENIC));
		ret = analyze(scope, AST_BLOCK(node).body);
		break;
	}

	default:
		ret = -1;
		semantic_error(scope->fctx, node, "unknown top element\n");
		break;
	};

	return ret;
}

static int analyze(struct scope *scope, struct ast_node *tree)
{
	struct ast_node *node = tree, *next;
	while (node) {
		next = node->next;
		node->next = NULL;
		if (analyze_file_visibility(scope, node))
			return -1;

		node = next;
	}

	return 0;
}

int analyze_root(struct scope *scope, struct ast_node *tree)
{
	scope_add_defaults(scope);
	if (analyze(scope, tree))
		return -1;

	return 0;
}

static int structs_match(struct ast_node *a, struct ast_node *b)
{
	/** @todo: iterate over elements in structure */
	/** @todo: check tag as well? */
	return 0;
}

static int primitives_match(struct ast_node *a, struct ast_node *b)
{
	enum ast_primitive at = AST_PRIMITIVE_TYPE(a).type;
	enum ast_primitive bt = AST_PRIMITIVE_TYPE(b).type;

	return at == bt;
}

int types_match(struct ast_node *a, struct ast_node *b)
{
	if (!a && !b)
		return 1;

	if (!a || !b)
		return 0;

	assert(a->node_type == AST_TYPE);
	assert(b->node_type == AST_TYPE);

	/* typeofs match 'everything' */
	if (AST_TYPE(a).kind == AST_TYPE_TYPEOF || AST_TYPE(b).kind == AST_TYPE_TYPEOF)
		return 1;

	/* if the type kind doesn't match, we're done. */
	if (AST_TYPE(a).kind != AST_TYPE(b).kind)
		return 0;

	if (AST_TYPE(a).kind == AST_TYPE_STRUCT)
		return structs_match(a, b);

	if (AST_TYPE(a).kind == AST_TYPE_POINTER)
		return types_match(AST_PTR_TYPE(a).base,
				AST_PTR_TYPE(b).base);

	if (AST_TYPE(a).kind == AST_TYPE_PRIMITIVE)
		return primitives_match(a, b);

	return 0;
}

static int _replace_id(struct ast_node *node, void *data)
{
	if (!node)
		return 0;

	if (node->node_type != AST_ID)
		return ast_call_on(_replace_id, node, data);

	struct ast_node **pair = data;
	struct ast_node *id = pair[0];
	struct ast_node *expr = pair[1];

	if (!identical_ast_nodes(0, node, id))
		return ast_call_on(_replace_id, node, data);

	struct ast_node *clone = clone_ast_node(expr);
	if (!clone) {
		internal_error("failed cloning replacement expr");
		return -1;
	}

	clone->next = node->next;
	clone->scope = node->scope;
	/* we know this is an ID node, so we know exactly what to free */
	free((void *)node->_id.id);

	*node = *clone;
	free(clone);

	/* a succesful replacement needs no futher replacements, I think */
	return 0;
}
static int replace_id(struct ast_node *body, struct ast_node *id,
                      struct ast_node *expr)
{
	struct ast_node *pair[2] = {id, expr};
	return ast_call_on(_replace_id, body, pair);
}

static int actualize_macro_construct(struct act_state *state,
                           struct scope *scope, struct ast_node *n)
{
	UNUSED(state);
	/* macro bodies, arguments, etc aren't expanded upon until the macro is
	 * called, so just try to add it to the local scope */
	assert(n && n->node_type == AST_MACRO_CONSTRUCT);
	return scope_add_macro(scope, n);
}

struct ast_node *extract_typeof(struct ast_node *type)
{
	if (!type)
		return 0;

	assert(type->node_type == AST_TYPE);
	if (type->_type.kind == AST_TYPE_TYPEOF)
		return type;

	return extract_typeof(type->_type.next);
}

struct ast_node *extract_trait(struct ast_node *type)
{
	if (!type)
		return 0;

	assert(type->node_type == AST_TYPE);
	if (type->_type.kind == AST_TYPE_TRAIT)
		return type;

	return extract_trait(type->_type.next);
}

static void actualize_trait_types(struct ast_node *params,
                                     struct ast_node *args)
{
	/** @todo replace trait types with arg types, should probably be merged
	 * */
	/* TODO: this might not hold in variadic functions... */
	assert(!args && !params);
}

static int actualize_proc_call(struct act_state *state,
                               struct scope *scope, struct ast_node *call,
                               struct ast_node *proc)
{
	/* proc has already been actualized, so we don't have to do anything  */
	if (ast_flags(proc, AST_FLAG_ACTUAL)) {
		/* call node type is the return type */
		struct ast_node *sign = proc->type;
		assert(sign->node_type == AST_TYPE);

		call->type = AST_SIGN_TYPE(sign).ret;
		return 0;
	}

	if (act_flags(state, ACT_ONLY_TYPES)) {
		/* TODO: better cleanup */
		/* at this point we're really only interested in the return
		 * type, but if it's a typeof expression we need to actualize
		 * the arguments as well, unfortunately */
		struct ast_node *sign = clone_ast_node(proc->_proc.sign);
		if (!sign) {
			internal_error("failed cloning proc signature");
			return -1;
		}

		struct scope *tmp = create_scope();
		if (!tmp) {
			internal_error(
				"failed creating temporary signature scope");
			return -1;
		}

		/* if the function is in some completely different file for
		 * example, we want to use that file's scope */
		scope_add_scope(proc->scope, tmp);

		struct ast_node *params = AST_SIGN_TYPE(sign).params;
		struct ast_node *args = call->_call.args;
		/* fuck, analyze_proc gobbles up the return type typeof */
		actualize_trait_types(params, args);

		if (actualize(state, tmp, sign))
			return -1;

		call->type = AST_SIGN_TYPE(sign).ret;
		return 0;
	}

	/* clone procedure definition to
	 * replace trait types with actual types and actualize it */
	struct ast_node *def = clone_ast_node(proc);
	if (!def) {
		/* internal error */
		internal_error("failed allocating actualization");
		return -1;
	}

	struct ast_node *sign = def->_proc.sign;
	struct ast_node *params = AST_SIGN_TYPE(sign).params;
	struct ast_node *args = call->_call.args;
	actualize_trait_types(params, args);

	if (actualize(state, def->scope, def))
		return -1;

	call->type = AST_SIGN_TYPE(sign).ret;
	return 0;
}

static int actualize_macro_call(struct act_state *state,
                                struct scope *scope, struct ast_node *call,
                                struct ast_node *macro)
{
	assert(call->node_type == AST_CALL && macro->node_type == AST_MACRO_CONSTRUCT);
	if (ast_flags(macro, AST_FLAG_VARIADIC)) {
		semantic_error(scope->fctx, macro,
		               "variadic macros not yet implemented");
		return -1;
	}

	struct ast_node *body = clone_ast_node(AST_MACRO_CONSTRUCT(macro).body);
	if (!body) {
		internal_error("failed allocating body for macro expansion");
		return -1;
	}

	body->scope = call->scope;
	body->next = call->next;

	struct ast_node *param = AST_MACRO_CONSTRUCT(macro).params;
	struct ast_node *arg = AST_CALL(call).args;

	/* TODO: actual replacements */
	while (param && arg) {
		/* feels slightly hacky, but essentially replace each individual
		 * component in the arg list by breaking it out of the list
		 * temporarily. After the replacement, insert it back into the
		 * list so the cleanup is easier. */
		struct ast_node *next_arg = arg->next;
		arg->next = NULL;

		if (replace_id(body, param, arg)) {
			semantic_error(scope->fctx, call,
			               "failed replacing params with args");
			arg->next = next_arg;
			return -1;
		}

		param = param->next;
		arg = arg->next = next_arg;
	}

	/* variadic macros could just replace this bit with with replacing the
	 * rest of the list with the parameter? */
	if (param || arg) {
		/* TODO: internal error more like */
		semantic_error(scope->fctx, call, "uneven number of arguments");
		return -1;
	}

	*call = *body;
	free(body);
	/* actualize the new content */
	return actualize(state, scope, call);
}

static int actualize_call(struct act_state *state,
                          struct scope *scope, struct ast_node *call)
{
	assert(call && call->node_type == AST_CALL);

	/* check that arguments exist, make sure they have types etc. */
	/* TODO: procedure callbacks? */
	int ret = actualize(state, scope, call->_call.args);
	if (ret)
		return ret;

	/* this label implements a kind of on demand signature actualization,
	 * might work? */
	/* if it does, I might flesh this out into its own procedure that
	 * reinserts the found proc after actualization, see if maybe that way
	 * we get rid of duplicates? */
get_callable:
	struct ast_node *callable = file_scope_resolve_call(scope, call);
	if (!callable) {
		char *str = call_str(call);
		semantic_error(scope->fctx, call, "no such callable: %s", str);
		free(str);
		return -1;
	}

	if (act_flags(state, ACT_ONLY_TYPES)) {
		if (callable->node_type == AST_PROC
		    && !ast_flags(callable->_proc.sign, AST_FLAG_ACTUAL)) {
			/* since we're in types only mode, this should be fine */
			if (actualize(state, callable->scope, callable))
				return -1;

			goto get_callable;
		}
	}

	if (callable->node_type == AST_PROC)
		return actualize_proc_call(state, scope, call, callable);

	if (callable->node_type == AST_MACRO_EXPAND)
		return actualize_macro_call(state, scope, call, callable);

	/* TODO: add lambdas and arrays */
	semantic_error(scope->fctx, call,
	               "currently only procedures and macros are callable");
	return -1;
}

static void warn_unused_labels(struct act_state *state, struct scope *scope)
{
	struct act_stack *labels = state->label_stack;
	if (labels)
		do {
			struct ast_node *label = labels->node;
			if (!ast_flags(label, AST_FLAG_ACTUAL))
				semantic_warn(scope->fctx, label,
				              "unused label");

		} while ((labels = labels->next));
}

static int undefined_gotos(struct act_state *state, struct scope *scope)
{
	int ret = 0;
	struct act_stack *gotos = state->goto_stack;
	if (gotos)
		do {
			struct ast_node *got = gotos->node;
			if (!ast_flags(got, AST_FLAG_ACTUAL)) {
				semantic_warn(scope->fctx, got,
				              "undefined label");
				ret = -1;
			}

		} while ((gotos = gotos->next));

	return ret;
}

/* TODO: add in some kind of subsystem for keeping track of which procedure
 * we're in, what the last defined var is, possibly more? */
static int actualize_proc(struct act_state *state,
                          struct scope *scope, struct ast_node *proc)
{
	/* actualize_proc is called on trait procs as well, but I believe
	 * that's fine? */
	assert(proc && proc->node_type == AST_PROC);
	int ret = 0;
	/* mark the function as initialized, assume previously allocated for us */
	struct ast_node *actual = proc;
	ast_set_flags(actual, AST_FLAG_INIT);
	if (!act_flags(state, ACT_ONLY_TYPES)) {
		ret = scope_add_actual(scope, actual);
		if (ret) {
			return ret;
		}
	}

	struct ast_node *sign = actual->_proc.sign;
	struct scope *param_scope = create_scope();
	scope_add_scope(scope, param_scope);

	/* procedure type is the signature */
	sign->scope = param_scope;
	actual->type = sign;

	/* TODO: if we're actualizing the types here, how can we avoid
	 * duplicates in the scope proc list? Or can we at all? */

	/* actualize types in signature */
	if (actualize(state, param_scope, sign))
		return -1;

	if (act_flags(state, ACT_ONLY_TYPES))
		return 0;

	/* we don't have to maintain the same flags as the parent state, I don't
	 * think */
	struct act_state new_state = {0};
	new_state.cur_proc = actual;
	act_set_flags(&new_state, ACT_REQUIRE_FULLY_QUALIFIED);
	/* actualize body */
	ret |= actualize(&new_state, sign->scope, actual->_proc.body);
	if (!act_flags(&new_state, ACT_HAS_RETURN)) {
		if (!is_void(AST_SIGN_TYPE(sign).ret)) {
			semantic_error(scope->fctx, actual,
			               "no return with non-void return type");
			ret = -1;
		}
	}
	else if (ast_block_last(actual->_proc.body)->node_type != AST_RETURN) {
		/* TODO: something more sophisticated than this */
		semantic_warn(scope->fctx, actual,
		              "unable to determine explicit return for all branches");
	}

	warn_unused_labels(&new_state, scope);
	if (undefined_gotos(&new_state, scope))
		ret = -1;

	/* TODO: should ret be checked between each stage? */
	if (ret)
		return ret;

	printf("Actualized func:\n");
	dump_ast(0, actual);

	ast_set_flags(actual, AST_FLAG_ACTUAL);
	/* we have successfully actualized the procedure */
	return 0;
}

static int actualize_binop(struct act_state *state,
                           struct scope *scope, struct ast_node *binop)
{
	assert(binop && binop->node_type == AST_BINOP);

	struct ast_node *left = binop->binop.left;
	struct ast_node *right = binop->binop.right;

	int ret = 0;
	ret |= actualize(state, scope, left);
	ret |= actualize(state, scope, right);
	if (ret)
		return ret;

	if (!left->type) {
		semantic_error(scope->fctx, binop,
		               "unable to detect lefthand type");
		return -1;
	}

	if (!right->type) {
		semantic_error(scope->fctx, binop,
		               "unable to detect righthand type");
		return -1;
	}

	if (!types_match(left->type, right->type)) {
		char *left_type = type_str(left);
		char *right_type = type_str(right);
		semantic_error(scope->fctx, binop,
		               "type mismatch (%s vs %s)", left_type,
		               right_type);
		free(left_type);
		free(right_type);
		return -1;
	}

	/* TODO: also check trait types, just because two traits collapse
	 * to the same actual type doesn't mean that the two trait types
	 * should be allowed to operate on eachother */

	/* types are the same, so the type of this expression is whichever */
	binop->type = left->type;

	return 0;
}


static int actualize_block(struct act_state *state,
                           struct scope *scope, struct ast_node *node)
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
	if (actualize(state, block_scope, node->_block.body))
		return -1;

	/* the block type is the last statement in the block's type */
	node->type = ast_last_node(node->_block.body)->type;
	if (!node->type) {
		semantic_error(scope->fctx, node,
		               "unable to detect block type");
		return -1;
	}

	/* TODO: currently defers are sort of duplicated after a return, unsure
	 * if they should be handled here or somewhere else */
	if (state->defer_stack) {
		node->_block.defers = clone_defers(state, defers);
		if (!node->_block.defers) {
			internal_error("failed cloning defers");
			return -1;
		}

		clear_defers(state, defers);
	}

	return 0;
}

static int actualize_id(struct act_state *state,
                        struct scope *scope, struct ast_node *id)
{
	UNUSED(state);
	assert(id && id->node_type == AST_ID);
	/** @todo at the moment we always assume an ID is a variable, but stuff
	 * like function callbacks should be added in the future */
	struct ast_node *decl = file_scope_find_var(scope, id);
	if (!decl) {
		semantic_error(scope->fctx, id, "no such object");
		return -1;
	}

	if (!decl->type) {
		semantic_error(scope->fctx, id,
		               "no type associated with object");
		return -1;
	}

	id->type = decl->type;
	return 0;
}

static int actualize_var(struct act_state *state,
                         struct scope *scope, struct ast_node *var)
{
	assert(var && var->node_type == AST_VAR);
	struct ast_node *init = var->_var.init;
	struct ast_node *type = var->_var.type;
	/* one of these must be defined, otherwise the parser fucked up */
	assert(type || init);

	if (init && actualize(state, scope, init))
		return -1;

	if (type && actualize(state, scope, type))
		return -1;

	if (init && init->node_type == AST_INIT) {
		assert(!init->type);
		init->type = type;
		/* TODO: some kind of check_init() */
	}

	if (init && type) {
		/* make sure the asked type and the actualized types match */
		if (!types_match(init->type, type)) {
			char *init_type = type_str(init->type);
			char *req_type = type_str(type);
			semantic_error(scope->fctx, var,
			               "type mismatch (%s vs %s)",
			               req_type, init_type);
			free(init_type);
			free(req_type);
			return -1;
		}
	}

	if (init)
		/* infer */
		var->type = init->type;

	if (type)
		/* TODO: should there be some default value? */
		/* declare */
		var->type = type;

	/* an unnamed var is a var in a signature that should not produce a
	 * warning on not being used (if I ever get around to adding those kinds
	 * of warnings) */
	if (var->_var.id && !ast_flags(var, AST_FLAG_MEMBER))
		return scope_add_var(scope, var);

	/* TODO: we should make sure the type is fully qualified in bodies */
	return 0;
}

#define ENTER_ACT()                              \
	enum act_flags old_flags = state->flags; \
	struct ast_node *old_trait = state->cur_trait;

#define EXIT_ACT(r)                                 \
	do {                                        \
		state->cur_trait = old_trait; \
		state->flags = old_flags;           \
		return r;                           \
	} while (0);

static int actualize_type(struct act_state *state,
                          struct scope *scope, struct ast_node *type)
{
	/* TODO: there's gotta be a better way to handle flags. Maybe macros
	 * like ENTER_ACTUALIZE and EXIT_ACTUALIZE? */
	/* TODO: get rid of aliases, expand implements, fill out structures,
	 * etc. */
	assert(type->node_type == AST_TYPE);
	ENTER_ACT();
	act_set_flags(state, ACT_ONLY_TYPES);

	if (ast_flags(type,
	              AST_FLAG_INIT) && !ast_flags(type, AST_FLAG_ACTUAL)) {
		semantic_error(scope->fctx, type, "detected type loop");
		EXIT_ACT(-1);
	}

	/* mark type initialize. We can detect type loops if this is set but
	 * AST_FLAG_ACTUAL isn't. */
	ast_set_flags(type, AST_FLAG_INIT);
	if (actualize(state, scope, type->_type.next)) {
		EXIT_ACT(-1);
	}

	switch (AST_TYPE(type).kind) {
	case AST_TYPE_ID: {
		/* type IDs can really only be aliases to something else, or if
		 * they're missing, void */
		if (!AST_ID_TYPE(type).id) {
			/* no ID means void */
			AST_ID_TYPE(type).id = gen_id(strdup("void"), NULL_LOC());
		}

		struct ast_node *exists = file_scope_find_type(scope, AST_ID_TYPE(type).id);
		if (!exists) {
			semantic_error(scope->fctx, type, "no such type");
			EXIT_ACT(-1);
		}

		if (exists->node_type == AST_TYPE) {
			assert(AST_TYPE(exists).kind == AST_TYPE_PRIMITIVE);
			AST_TYPE(type) = AST_TYPE(exists);
			break;
		}

		/* actualize whatever type we have on demand, either alias or
		 * trait */
		if (!ast_flags(exists, AST_FLAG_ACTUAL))
			if (actualize(state, exists->scope, exists))
				EXIT_ACT(-1);

		assert(AST_TYPE(type).next == NULL);
		if (exists->node_type == AST_ALIAS) {
			AST_TYPE(type).aliased = exists;
			AST_TYPE(type) = AST_TYPE(exists);
		}
		else if (exists->node_type == AST_TRAIT) {
			/* this is kind of weird, have to think about it */
			AST_TYPE(type) = AST_TYPE(exists);
		}
		else if (exists->node_type == AST_STRUCT) {
			AST_TYPE(type) = AST_TYPE(exists);
		}
		else if (exists->node_type == AST_ENUM) {
			AST_TYPE(type) = AST_TYPE(exists);
		}

		break;
	}

	case AST_TYPE_ARR:
		/* TODO: expression should be expandable to integer constant */
		break;

	case AST_TYPE_TYPEOF: {
		struct ast_node *expr = AST_TYPEOF_TYPE(type).expr;
		/* TODO: expressions in top-level type declarations should
		 * probably be checked for, as we might not want to accidentally
		 * actualize procedure calls? */
		if (actualize(state, scope, expr))
			EXIT_ACT(-1);

		/* TODO: for now just trust that the expression is not looped or
		 * anything dumb like that, but I would feel better if I figure
		 * out some check */
		assert(type->_type.next == NULL);
		/** @todo add in some 'from' field for this situation? */
		type->type = expr->type;
		break;
	}

	case AST_TYPE_POINTER:
		assert(type->_type.next);
		type->loc = type->_type.next->loc;
		break;

	case AST_TYPE_SIGN: {
		struct ast_node *params = AST_SIGN_TYPE(type).params;
		struct ast_node *ret = AST_SIGN_TYPE(type).ret;

		if (actualize(state, scope, params))
			EXIT_ACT(-1);

		if (!ret)
			ret = AST_SIGN_TYPE(type).ret = void_type();

		if (actualize(state, scope, ret))
			EXIT_ACT(-1);

		break;
	}

	case AST_TYPE_STRUCT: {
		assert(ast_flags(type, AST_FLAG_ACTUAL));
		break;
	}

	case AST_TYPE_PRIMITIVE: {
		assert(ast_flags(type, AST_FLAG_ACTUAL));
		break;
	}

	default:
		semantic_error(scope->fctx, type, "unimplemented type");
		EXIT_ACT(-1);
	}

	ast_set_flags(type, AST_FLAG_ACTUAL);
	/* generally speaking */
	EXIT_ACT(0);
}

static int actualize_empty(struct act_state *state,
                           struct scope *scope, struct ast_node *node)
{
	UNUSED(state);
	/* TODO: converting to void is common enough that it might be worth
	 * creating a function for */
	struct ast_node *void_id = gen_id(strdup("void"), NULL_LOC());
	if (!void_id) {
		internal_error("couldn't allocate type id for empty statement\n");
		return -1;
	}

	node->type = gen_type(AST_TYPE_ID, void_id, NULL, NULL);
	if (!node->type) {
		internal_error("couldn't allocate type for empty statement\n");
		return -1;
	}

	return 0;
}

static int integral_type(struct ast_node *type)
{
	assert(type->node_type == AST_TYPE);
	if (AST_TYPE(type).kind != AST_TYPE_PRIMITIVE)
		return 0;

	/* here would be awesome with an enum of our base types */
	enum ast_primitive p = AST_PRIMITIVE_TYPE(type).type;
	switch (p) {
	case AST_I9: return 1;
	case AST_I27: return 1;
	default: return 0;
	}

	return 0;
}

static int pointer_type(struct ast_node *type)
{
	assert(type->node_type == AST_TYPE);
	return type->_type.kind == AST_TYPE_POINTER;
}

static int pointer_conversion(struct ast_node *a, struct ast_node *b)
{
	assert(a->node_type == AST_TYPE);
	assert(b->node_type == AST_TYPE);
	if (pointer_type(a)) {
		if (b->_type.kind != AST_TYPE_ID)
			return 0;

		struct ast_node *id = AST_ID_TYPE(b).id;
		/* there's gotta be a better way */
		if (strcmp(id->_id.id, "usize") == 0)
			return 1;
	}

	return 0;
}

static size_t member_count(struct ast_node *exists)
{
	assert(exists->node_type == AST_STRUCT);
	struct ast_node *body = exists->_struct.body;
	return ast_list_len(body);
}

static struct ast_node *lookup_member_idx(struct ast_node *body,
                                          struct ast_node *find,
                                          size_t *idx)
{
	/* micro-optimisation, likely way premature but speeds up selection
	 * between lookup_struct_member_idx and *_name by a tiny amount */
	(void)(find);
	assert(idx);
	size_t i = *idx;
	struct ast_node *m = body;
	while (i != 0 && m) {
		m = m->next;
		i--;
	}

	return m;
}

static struct ast_node *lookup_member_name(struct ast_node *body,
                                           struct ast_node *find,
                                           size_t *idx)
{
	assert(find->node_type == AST_ID);
	size_t i = 0;
	struct ast_node *m = body;
	while (m) {
		assert(m->node_type == AST_VAR);
		if (identical_ast_nodes(0, find, m->_var.id))
			break;
		m = m->next;
		i++;
	}

	if (idx)
		*idx = i;

	return m;
}

static struct ast_node *lookup_struct_member(struct ast_node *struc,
                                             struct ast_node *find, size_t *idx)
{
	if (find)
		return lookup_member_name(struc->_struct.body, find, idx);

	return lookup_member_idx(struc->_struct.body, find, idx);
}

static struct ast_node *lookup_enum_member(struct ast_node *enu,
                                           struct ast_node *find)
{
	size_t i = 0;
	struct ast_node *m = enu->_enum.body;
	while (m) {
		assert(m->node_type == AST_VAL);
		if (identical_ast_nodes(0, find, m->_val.id))
			break;
		m = m->next;
		i++;
	}

	return m;
}

static int init_struct(struct act_state *state, struct scope *scope,
                       struct ast_node *exists, struct ast_node *init)
{
	size_t i = 0;
	size_t mcount = member_count(exists);

	int ret = 0;
	char *initd = calloc(sizeof(char), mcount);
	if (!initd) {
		internal_error("failed allocating initd array");
		return -1;
	}

	struct ast_node *args = init->_init.body;
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

		struct ast_node *find = NULL;
		if (ast_flags(args, AST_FLAG_MEMBER))
			find = args->_var.id;

		struct ast_node *member =
			lookup_struct_member(exists, find, &i);

		if (!member) {
			char *sstr = type_str(exists->type);
			semantic_error(scope->fctx, args,
			               "no such member in %s",
			               sstr);
			free(sstr);
			ret = -1;
			break;
		}

		if (!implements(0, scope, args->type, member->type)) {
			char *astr = type_str(args->type);
			char *mstr = type_str(member->type);
			semantic_error(scope->fctx, args,
			               "%s does not implement %s", astr, mstr);
			free(astr);
			free(mstr);
			ret = -1;
			break;
		}

		initd[i] = 1;
		args = args->next;
		i++;
	}

	free(initd);
	return ret;
}

static int actualize_struct_init_cast(struct act_state *state,
                                      struct scope *scope,
                                      struct ast_node *init,
                                      struct ast_node *actual)
{
	struct ast_node *def = AST_STRUCT_TYPE(actual).def;
	return init_struct(state, scope, def, init);
}

static int actualize_init_cast(struct act_state *state,
                               struct scope *scope, struct ast_node *init,
                               struct ast_node *type)
{
	if (AST_TYPE(type).kind == AST_TYPE_STRUCT)
		return actualize_struct_init_cast(state, scope, init, type);

	semantic_error(scope->fctx, type,
	               "type is not a struct");
	return -1;

}

static int proc_pointer(struct ast_node *type)
{
	if (type->_type.kind != AST_TYPE_POINTER)
		return 0;

	struct ast_node *next = type->_type.next;
	if (next->_type.kind != AST_TYPE_SIGN)
		return 0;

	return 1;
}

static int proc_choice(struct ast_node *expr, struct ast_node *type)
{
	if (expr->node_type != AST_ID)
		return 0;

	if (!proc_pointer(type))
		return 0;

	return 1;
}

/* still slightly unsure about this, but hey ho */
static int match_proc(struct act_state *state, struct scope *scope,
                      struct ast_node *cast)
{
	(void)(state);
	semantic_error(scope->fctx, cast,
	               "procedure signature casts not yet implemented");
	return -1;
}

static int actualize_cast(struct act_state *state,
                          struct scope *scope, struct ast_node *cast)
{
	assert(cast->node_type == AST_CAST);
	struct ast_node *expr = cast->_cast.expr;
	struct ast_node *type = cast->_cast.type;

	if (actualize(state, scope, type))
		return -1;

	if (proc_choice(expr, type)) {
		cast->type = type;
		return match_proc(state, scope, cast);
	}

	if (actualize(state, scope, expr))
		return -1;

	if (expr->node_type == AST_INIT) {
		cast->type = type;
		return actualize_init_cast(state, scope, expr, type);
	}

	if (types_match(expr->type, type)) {
		cast->type = type;
		return 0;
	}

	if (integral_type(expr->type) && integral_type(type)) {
		cast->type = type;
		return 0;
	}

	if (pointer_type(expr->type) && pointer_type(type)) {
		cast->type = type;
		return 0;
	}

	if (pointer_conversion(expr->type, type)
	    || pointer_conversion(type, expr->type)) {
		cast->type = type;
		return 0;
	}

	/* TODO: arrays? lambdas? */

	char *left_type = type_str(expr);
	char *right_type = type_str(type);
	semantic_error(scope->fctx, cast, "illegal cast (%s vs %s)",
	               left_type, right_type);
	free(left_type);
	free(right_type);
	return -1;
}

static int actualize_const(struct act_state *state, struct scope *scope,
                           struct ast_node *cons)
{
	UNUSED(state);
	assert(cons->node_type == AST_CONST);
	if (cons->_const.kind == AST_CONST_INTEGER) {
		/* error checking would be doog */
		cons->type = i27_type();
		return 0;
	}

	semantic_error(scope->fctx, cons, "unimplemented constant");
	return 0;
}

static int actualize_alias(struct act_state *state, struct scope *scope,
                           struct ast_node *alias)
{
	/* I shall have to think about things, as currently very deeply nested
	 * aliases might be a bit cumbersome to work with. Still, this works
	 * well enough I suppose. */
	assert(alias->node_type == AST_ALIAS);
	if (ast_flags(alias, AST_FLAG_INIT)) {
		semantic_error(scope->fctx, alias, "alias loop");
		return -1;
	}

	ast_set_flags(alias, AST_FLAG_INIT);
	if (actualize(state, scope, AST_ALIAS(alias).type)) {
		/* usually we don't want to output errors upon errors, but this
		 * is likely a useful message as it might show where a loop is
		 * occuring */
		semantic_error(scope->fctx, alias, "failed actualizing alias");
		return -1;
	}

	ast_set_flags(alias, AST_FLAG_ACTUAL);
	return 0;
}

static int actualize_trait(struct act_state *state, struct scope *scope,
                              struct ast_node *trait)
{
	assert(trait->node_type == AST_TRAIT);
	ast_set_flags(trait, AST_FLAG_ACTUAL);
	ENTER_ACT();
	state->cur_trait = trait;

	/* will still have to figure out how I want to inform the actualizer
	 * that a some_type in a some_type just means whichever type we're
	 * testing for */
	act_set_flags(state, ACT_ONLY_TYPES);
	if (actualize(state, trait->scope, trait->_trait.body)) {
		semantic_error(scope->fctx, trait,
		               "failed actualizing trait");
		EXIT_ACT(-1);
	}

	/* TODO: check that all procs in the trait have something to do with
	 * the type, either as an argument or as a return type or something */

	/* TODO: implement supertraits, i.e. adding some previous trait to
	 * this trait */

	/* TODO: make sure that the trait itself doesn't have duplicates */

	trait->type = trait;
	EXIT_ACT(0);
}

static int actualize_defer(struct act_state *state,
                           struct scope *scope, struct ast_node *node)
{
	struct ast_node *expr = node->_defer.expr;
	/* TODO: should the actualization only happen when the defers are
	 * called? */
	if (actualize(state, scope, expr))
		return -1;

	if (push_defer(state, expr))
		return -1;

	node->type = void_type();
	return 0;
}

static int actualize_return(struct act_state *state, struct scope *scope,
                            struct ast_node *node)
{
	act_set_flags(state, ACT_HAS_RETURN);
	struct ast_node *expr = node->_return.expr;
	if (expr) {
		if (actualize(state, scope, expr))
			return -1;

		node->type = expr->type;
	}
	else {
		node->type = void_type();
	}

	assert(state->cur_proc);
	struct ast_node *cur_proc = state->cur_proc;
	struct ast_node *sign = AST_PROC(cur_proc).sign;
	struct ast_node *ret = AST_SIGN_TYPE(sign).ret;
	if (!types_match(node->type, ret)) {
		char *rt = type_str(ret);
		char *et = type_str(node);
		semantic_error(scope->fctx, node,
		               "return type mismatch: %s vs %s",
		               rt, et);
		free(rt);
		free(et);
		return -1;
	}

	if (state->defer_stack) {
		node->_return.defers = clone_defers(state, NULL);
		if (!node->_return.defers) {
			internal_error("failed cloning return defers");
			return -1;
		}
	}
	return 0;
}

/* Still slightly unsure if this works in all cases, but a good start
 * nonetheless. */
static void actualize_goto_defer(struct ast_node *got, struct ast_node *label)
{
	struct ast_node *goto_defers = got->_goto.defers;
	struct ast_node *label_defers = label->_label.defers;
	/* since we're dealing with singly linked lists, keep a reference to one
	 * node before the current goto defer. */
	struct ast_node *prev_defer = NULL;

	/* this goto has a defined label */
	ast_set_flags(got, AST_FLAG_ACTUAL);
	ast_set_flags(label, AST_FLAG_ACTUAL);

	size_t goto_len = ast_list_len(goto_defers);
	size_t label_len = ast_list_len(label_defers);

	/* find first common defer statement */
	while (goto_len > label_len) {
		prev_defer = goto_defers;
		goto_defers = goto_defers->next;
		goto_len--;
	}

	while (label_len > goto_len) {
		label_defers = label_defers->next;
		label_len--;
	}

	/* TODO: possible optimisation could be maintaining references to the
	 * defer statements themselves, building up a sort of tree, allowing us
	 * to directly compare pointers, likely being a bit quicker. Still,
	 * unlikely that goto stuff would be a major bottleneck. */
	while (!identical_ast_nodes(1, goto_defers, label_defers)) {
		prev_defer = goto_defers;
		label_defers = label_defers->next;
		goto_defers = goto_defers->next;
	}

	/* only the defers below the common defer should be executed by the goto */
	if (goto_defers) {
		/* fuck, I actually need the one previous to this */
		assert(prev_defer->next == goto_defers);
		prev_defer->next = NULL;
	}

	/* nothing to do */
}


static int actualize_goto(struct act_state *state, struct scope *scope,
                          struct ast_node *node)
{
	assert(node->node_type == AST_GOTO);
	push_goto(state, node);

	/* clone all defers as we don't know where the label might be */
	node->_goto.defers = clone_defers(state, NULL);
	node->type = void_type();

	struct ast_node *label = find_label(state, node->_goto.label);
	/* this is a jump backwards, i.e. we can already do it */
	if (label)
		actualize_goto_defer(node, label);

	/* forward jump, handle stuff when we run into the corresponding label */
	return 0;
}

static void actualize_goto_defers(struct act_state *state,
                                  struct ast_node *label)
{
	struct act_stack *prev = state->goto_stack, *cur;
	if (prev)
		do {
			cur = prev->next;
			struct ast_node *got = prev->node;
			if (identical_ast_nodes(0, got->_goto.label, label))
				actualize_goto_defer(got, label);

		} while ((prev = cur));
}

static int actualize_label(struct act_state *state, struct scope *scope,
                           struct ast_node *node)
{
	assert(node->node_type == AST_LABEL);
	struct ast_node *prev = find_label(state, node);
	if (prev) {
		semantic_error(scope->fctx, node, "label redefined");
		semantic_info(scope->fctx, prev, "previous definition");
		return -1;
	}

	push_label(state, node);
	/* clone all defers */
	node->_label.defers = clone_defers(state, NULL);
	node->type = void_type();

	actualize_goto_defers(state, node);
	return 0;
}

static int actualize_unop(struct act_state *state,
                          struct scope *scope, struct ast_node *node)
{
	assert(node->node_type == AST_UNOP);
	struct ast_node *expr = node->_unop.expr;
	if (actualize(state, scope, expr))
		return -1;

	/* generally speaking */
	node->type = expr->type;

	switch (node->_unop.op) {
	case AST_DEREF: {
		struct ast_node *type = expr->type;
		if (type->_type.kind != AST_TYPE_POINTER) {
			/* TODO: or array */
			semantic_error(scope->fctx, expr,
			               "trying to dereference something that's not a pointer");
			return -1;
		}

		node->type = type->_type.next;
		assert(node->type);
		break;
	}

	case AST_REF: {
		node->type = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		node->type->_type.next = expr->type;
		break;
	}

	default: semantic_error(scope->fctx, node,
		                "unimplemented unary operation");
		return -1;
	}

	return 0;
}

static int actualize_as(struct act_state *state,
                        struct scope *scope, struct ast_node *as)
{
	assert(as->node_type == AST_AS);
	if (!act_flags(state, ACT_ONLY_TYPES)) {
		semantic_error(scope->fctx, as,
		               "as used outside of type context");
		return -1;
	}

	struct ast_node *type = as->_as.type;
	if (actualize(state, scope, type))
		return -1;

	as->type = type;
	return 0;
}

static int actualize_struct(struct act_state *state,
                            struct scope *scope, struct ast_node *node)
{
	assert(node->node_type == AST_STRUCT);
	ast_set_flags(node, AST_FLAG_INIT);
	struct ast_node *generics = node->_struct.generics;
	struct scope *struct_scope = create_scope();
	if (!struct_scope)
		return -1;

	scope_add_scope(node->scope, struct_scope);
	if (generics)
		ast_set_flags(node, AST_FLAG_GENERIC);

	/* TODO: some IDs should be handles as just placeholders, I think? */
	if (actualize(state, struct_scope, generics))
		return -1;

	struct ast_node *body = node->_struct.body;
	if (actualize(state, struct_scope, body))
		return -1;

	/* cloning slightly odd, but I guess it's fine? */
	struct ast_node *clone_id = clone_ast_node(node->_struct.id);
	node->type = gen_type(AST_TYPE_STRUCT, clone_id, NULL, NULL);

	ast_set_flags(node, AST_FLAG_ACTUAL);
	return 0;
}

/* could maybe be renamed, but essentially dot in copper works as either
 * -> or . in C, so allow structures or traits and single level pointers to
 *  structures or traits. */
static int has_members(struct ast_node *type)
{
	if (AST_TYPE(type).kind == AST_TYPE_POINTER)
		type = AST_TYPE(type).next;

	/* most likely */
	if (AST_TYPE(type).kind == AST_TYPE_STRUCT)
		return 1;

	if (AST_TYPE(type).kind == AST_TYPE_TRAIT)
		return 1;

	return 0;
}

static int actualize_dot(struct act_state *state,
                         struct scope *scope, struct ast_node *node)
{
	/* TODO: handle enums as well, idea is something like
	 * enum whatever {A_FLAG}
	 * ...
	 * whatever.A_FLAG
	 *
	 * possibly also if the expr is of type whatever then .A_FLAG just gets
	 * the corresponding constant?
	 **/
	assert(node->node_type == AST_DOT);
	struct ast_node *expr = node->_dot.expr;
	if (actualize(state, scope, expr))
		return -1;

	struct ast_node *id = node->_dot.id;
	if (!has_members(expr->type)) {
		char *tstr = type_str(expr->type);
		semantic_error(scope->fctx, node, "%s does not have member %s",
		               tstr, id->_id.id);
		free(tstr);
		return -1;
	}

	/* TODO: actually look through stuff */
	/* TODO: figure out how to match traitd structures to actual */
	return 0;
}

static int actualize_init(struct act_state *state,
                          struct scope *scope, struct ast_node *node)
{
	assert(node->node_type == AST_INIT);
	/* for now just do the types, the named stuff will be checked later */
	/* TODO: how to make sure all members are initialized? */
	int ret = 0;
	enum act_flags old_flags = state->flags;
	act_set_flags(state, ACT_ONLY_TYPES);
	ret = actualize(state, scope, node->_init.body);
	state->flags = old_flags;
	return ret;
}

static int actualize_assign(struct act_state *state, struct scope *scope,
                            struct ast_node *node)
{
	assert(node->node_type == AST_ASSIGN);
	struct ast_node *to = node->_assign.to;
	if (actualize(state, scope, to))
		return -1;

	struct ast_node *from = node->_assign.from;
	if (actualize(state, scope, from))
		return -1;

	if (from->node_type == AST_INIT) {
		node->type = to->type;
		return actualize_init_cast(state, scope, from, to->type);
	}

	if (!types_match(to->type, from->type)) {
		char *tostr = type_str(to->type);
		char *fromstr = type_str(from->type);
		semantic_error(scope->fctx, node, "type mismatch (%s vs %s)",
		               tostr, fromstr);
		free(tostr);
		free(fromstr);
		return -1;
	}

	node->type = to->type;
	return 0;
}

static int actualize_fetch(struct act_state *state, struct scope *scope,
                           struct ast_node *fetch)
{
	assert(fetch->node_type == AST_FETCH);
	struct ast_node *type = fetch->_fetch.type;
	if (actualize(state, scope, type))
		return -1;

	if (type->_type.kind != AST_TYPE_ENUM) {
		semantic_error(scope->fctx, type, "type is not an enum");
		return -1;
	}

	struct ast_node *id = fetch->_fetch.id;
	struct ast_node *def = file_scope_find_type(scope, AST_ID_TYPE(type).id);
	assert(def);

	struct ast_node *member = lookup_enum_member(def, id);
	if (!member) {
		char *estr = type_str(type);
		semantic_error(scope->fctx, id, "no such member in enum %s");
		free(estr);
		return -1;
	}

	fetch->type = def->type;
	return 0;
}

static int actualize_enum(struct act_state *state, struct scope *scope,
                          struct ast_node *node)
{
	assert(node->node_type == AST_ENUM);
	struct ast_node *type = node->_enum.type;
	struct scope *enum_scope = node->scope;

	/* TODO: here we could save space by choosing the smallest type that
	 * fits */
	if (!type) {
		type = i27_type();
		node->_enum.type = type;
	} else if (actualize(state, enum_scope, type))
		return -1;

	long long counter = 0;
	node->type = type;
	struct ast_node *members = node->_enum.body;
	while (members) {
		members->type = type;
		if (members->_val.val) {
			struct ast_node *val = members->_val.val;
			if (actualize(state, enum_scope, val))
				return -1;

			if (val->node_type != AST_CONST) {
				semantic_error(scope->fctx, members,
				               "unable to process nonconstant expression");
				return -1;
			}

			if (val->_const.kind != AST_CONST_INTEGER) {
				semantic_error(scope->fctx, members,
				               "not expandable to an integer constant");
				return -1;
			}

			counter = val->_const.integer;
		}
		else {
			members->_val.val = gen_int(counter);
		}

		members = members->next;
		counter++;
	}

	/* TODO: check that we don't go outside the limits of the type */
	return 0;
}

static int actualize(struct act_state *state, struct scope *scope,
                     struct ast_node *node)
{
	int ret = 0;
	if (!node)
		return ret;

	if (!node->scope)
		node->scope = scope;

	switch (node->node_type) {
	case AST_PROC:
		/* procedure definitions only allowed at file scope */
		assert(scope_flags(scope, SCOPE_FILE));
		ret |= actualize_proc(state, scope, node);
		break;

	case AST_TRAIT: ret |= actualize_trait(state, scope, node); break;
	case AST_ALIAS: ret |= actualize_alias(state, scope, node); break;
	case AST_MACRO_CONSTRUCT: ret |= actualize_macro_construct(state, scope, node); break;
	case AST_CALL: ret |= actualize_call(state, scope, node); break;
	case AST_BINOP: ret |= actualize_binop(state, scope, node); break;
	case AST_BLOCK: ret |= actualize_block(state, scope, node); break;
	case AST_ID: ret |= actualize_id(state, scope, node); break;
	case AST_VAR: ret |= actualize_var(state, scope, node); break;
	case AST_TYPE: ret |= actualize_type(state, scope, node); break;
	case AST_EMPTY: ret |= actualize_empty(state, scope, node); break;
	case AST_CAST: ret |= actualize_cast(state, scope, node); break;
	case AST_CONST: ret |= actualize_const(state, scope, node); break;
	case AST_DEFER: ret |= actualize_defer(state, scope, node); break;
	case AST_RETURN: ret |= actualize_return(state, scope, node); break;
	case AST_GOTO: ret |= actualize_goto(state, scope, node); break;
	case AST_LABEL: ret |= actualize_label(state, scope, node); break;
	case AST_UNOP: ret |= actualize_unop(state, scope, node); break;
	case AST_AS: ret |= actualize_as(state, scope, node); break;
	case AST_STRUCT: ret |= actualize_struct(state, scope, node); break;
	case AST_DOT: ret |= actualize_dot(state, scope, node); break;
	case AST_INIT: ret |= actualize_init(state, scope, node); break;
	case AST_ASSIGN: ret |= actualize_assign(state, scope, node); break;
	case AST_FETCH: ret |= actualize_fetch(state, scope, node); break;
	case AST_ENUM: ret |= actualize_enum(state, scope, node); break;

	default:
		/* more like internal_error, maybe? */
		semantic_error(scope->fctx, node,
		               "unimplemented actualization");
		break;
	}

	/* should it automatically handle next nodes or should it be saved to
	 * actualize_block or something? */
	ret |= actualize(state, scope, node->next);
	return ret;
}

int actualize_main(struct scope *root)
{
	struct ast_node *main_id = gen_id(strdup("main"), NULL_LOC());
	struct ast_node *main_call = gen_call(main_id, NULL);

	struct act_state state = {0};

	/* skip checking signature for now */
	struct ast_node *main = file_scope_resolve_call(root, main_call);
	if (!main) {
		/* libraries are not really compilable... */
		error("no main");
		return -1;
	}
	int ret = actualize(&state, root, clone_ast_node(main));
	destroy_act_state(&state);
	return ret;
}

void replace_type(struct ast_node *type, struct ast_node *from,
                  struct ast_node *to)
{
	if (!type)
		return;

	assert(type->node_type == AST_TYPE);
	assert(from->node_type == AST_TYPE);
	assert(to->node_type == AST_TYPE);

	/* TODO: cleanup? */
	if (types_match(type, from)) {
		assert(type->_type.next == NULL);
		struct ast_node *clone = clone_ast_node(to);
		*type = *clone;
		free(clone);
		return;
	}

	replace_type(type->_type.next, from, to);
}

void replace_param_types(struct ast_node *param, struct ast_node *param_type,
                         struct ast_node *arg_type)
{
	if (arg_type->_type.kind == AST_TYPE_TRAIT) {
		replace_param_types(param, param_type, arg_type);
		return;
	}

	while (param) {
		replace_type(param->type, param_type, arg_type);
		param = param->next;
	}
}

int actualize_temp_type(struct scope *scope, struct ast_node *type)
{
	struct act_state state;
	act_set_flags(&state, ACT_ONLY_TYPES);
	struct ast_node *next = type->next;

	type->next = NULL;
	int ret = actualize(&state, scope, type);
	type->next = next;

	return ret;
}

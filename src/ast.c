/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

/**
 * @file ast.c
 *
 * Abstract syntax tree handling implementations.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <ek/ast.h>
#include <ek/scope.h>

#define ALLOC_NODE(n, type)                                      \
	struct ast_node *n = calloc(1, sizeof(struct ast_node)); \
	if (!n) {                                                \
		fprintf(stderr, "failed allocating" type "\n");  \
		return NULL;                                     \
	}

#define DESTROY_LIST(x)                          \
	{                                        \
		struct ast_node *prev = x, *cur; \
		if (prev)                        \
		do {                             \
			cur = prev->next;        \
			destroy_ast_node(prev);  \
		} while ((prev = cur));          \
	}

static struct src_loc loc_span(struct ast_node *left, struct ast_node *right)
{
	struct src_loc loc = {0};
	if (!left && !right)
		return loc;

	if (!left && right)
		return right->loc;

	if (left && !right)
		return left->loc;

	/* this might eventually be a good thing to do,
	 * but right now I'm still having issues with initializing all nodes
	 * with some kind of even slightly accurate location
	   assert(left->loc.first_line);
	   assert(left->loc.first_col);
	   assert(right->loc.last_line);
	   assert(right->loc.last_col);
	 */

	loc.first_line = left->loc.first_line;
	loc.first_col = left->loc.first_col;
	loc.last_line = right->loc.last_line;
	loc.last_col = right->loc.last_col;
	return loc;
}

struct ast_node *gen_macro_expansion(struct ast_node *id, struct ast_node *args)
{
	ALLOC_NODE(n, "macro_expansion");
	n->node_type = AST_MACRO_EXPANSION;
	n->_macro_expansion.id = id;
	n->_macro_expansion.args = args;
	n->loc = id->loc;
	return n;
}

void destroy_macro_expansion(struct ast_node *macro_expansion)
{
	assert(macro_expansion->node_type == AST_MACRO_EXPANSION);
	destroy_ast_node(macro_expansion->_macro_expansion.id);
	destroy_ast_node(macro_expansion->_macro_expansion.args);
	free(macro_expansion);
}

struct ast_node *gen_binop(enum ast_binops op,
                           struct ast_node *left, struct ast_node *right)
{
	ALLOC_NODE(n, "binop");
	n->node_type = AST_BINOP;
	n->_binop.op = op;
	n->_binop.left = left;
	n->_binop.right = right;
	n->loc = loc_span(left, right);
	return n;
}

void destroy_binop(struct ast_node *binop)
{
	assert(binop->node_type == AST_BINOP);
	destroy_ast_node(binop->_binop.left);
	destroy_ast_node(binop->_binop.right);
	free(binop);
}

struct ast_node *gen_unop(enum ast_unops op, struct ast_node *expr)
{
	ALLOC_NODE(n, "unop");
	n->node_type = AST_UNOP;
	n->_unop.op = op;
	n->_unop.expr = expr;
	n->loc = expr->loc;
	return n;
}

void destroy_unop(struct ast_node *unop)
{
	assert(unop->node_type == AST_UNOP);
	destroy_ast_node(unop->_unop.expr);
	free(unop);
}

struct ast_node *gen_call(struct ast_node *id, struct ast_node *args)
{
	ALLOC_NODE(n, "call");
	n->node_type = AST_CALL;
	n->_call.id = id;
	n->_call.args = args;
	n->loc = id->loc;
	return n;
}

void destroy_call(struct ast_node *call)
{
	assert(call->node_type == AST_CALL);
	destroy_ast_node(call->_call.id);
	DESTROY_LIST(call->_call.args);
	free(call);
}

struct ast_node *gen_id(const char *id)
{
	ALLOC_NODE(n, "id");
	n->node_type = AST_ID;
	n->_id.id = id;
	/* assume the parser populates location data */
	return n;
}

void destroy_id(struct ast_node *id)
{
	assert(id->node_type == AST_ID);
	free((void *)id->_id.id);
	free(id);
}

struct ast_node *gen_assign(struct ast_node *to, struct ast_node *from)
{
	ALLOC_NODE(n, "assign");
	n->node_type = AST_ASSIGN;
	n->_assign.to = to;
	n->_assign.from = from;
	n->loc = loc_span(to, from);
	return n;
}

static void destroy_assign(struct ast_node *assign)
{
	assert(assign->node_type == AST_ASSIGN);
	destroy_ast_node(assign->_assign.to);
	destroy_ast_node(assign->_assign.from);
	free(assign);
}

struct ast_node *gen_init(struct ast_node *body)
{
	ALLOC_NODE(n, "struct init");
	n->node_type = AST_INIT;
	n->_init.body = body;
	n->loc = body->loc;
	return n;
}

static void destroy_init(struct ast_node *init)
{
	assert(init->node_type == AST_INIT);
	DESTROY_LIST(init->_init.body);
	free(init);
}

struct ast_node *gen_int(long long integer)
{
	ALLOC_NODE(n, "int");
	n->node_type = AST_CONST;
	n->_const.kind = AST_CONST_INTEGER;
	n->_const.integer = integer;
	return n;
}

struct ast_node *gen_string(const char *str)
{
	ALLOC_NODE(n, "string");
	n->node_type = AST_CONST;
	n->_const.kind = AST_CONST_STRING;
	n->_const.str = str;
	return n;
}

struct ast_node *gen_float(double dbl)
{
	ALLOC_NODE(n, "float");
	n->node_type = AST_CONST;
	n->_const.kind = AST_CONST_FLOAT;
	n->_const.dbl = dbl;
	return n;
}

void destroy_const(struct ast_node *cons)
{
	assert(cons->node_type == AST_CONST);
	if (cons->_const.kind == AST_CONST_STRING)
		free((void *)cons->_const.str);

	free(cons);
}

struct ast_node *gen_while(struct ast_node *cond, struct ast_node *body)
{
	ALLOC_NODE(n, "while");
	n->node_type = AST_WHILE;
	n->_while.cond = cond;
	n->_while.body = body;
	return n;
}

void destroy_while(struct ast_node *whil)
{
	assert(whil->node_type == AST_WHILE);
	destroy_ast_node(whil->_while.cond);
	DESTROY_LIST(whil->_while.body);
	free(whil);
}

struct ast_node *gen_for(struct ast_node *pre, struct ast_node *cond,
                         struct ast_node *post, struct ast_node *body)
{
	ALLOC_NODE(n, "for");
	n->node_type = AST_FOR;
	n->_for.pre = pre;
	n->_for.cond = cond;
	n->_for.post = post;
	n->_for.body = body;
	return n;
}

void destroy_for(struct ast_node *fo)
{
	assert(fo->node_type == AST_FOR);
	destroy_ast_node(fo->_for.pre);
	destroy_ast_node(fo->_for.cond);
	destroy_ast_node(fo->_for.post);
	DESTROY_LIST(fo->_for.body);
	free(fo);
}

struct ast_node *gen_return(struct ast_node *expr)
{
	ALLOC_NODE(n, "return");
	n->node_type = AST_RETURN;
	n->_return.expr = expr;
	if (expr)
		n->loc = expr->loc;
	return n;
}

void destroy_return(struct ast_node *retur)
{
	assert(retur->node_type == AST_RETURN);
	destroy_ast_node(retur->_return.expr);
	DESTROY_LIST(retur->_return.defers);
	free(retur);
}

struct ast_node *gen_goto(struct ast_node *label)
{
	ALLOC_NODE(n, "goto");
	n->node_type = AST_GOTO;
	n->_goto.label = label;
	n->loc = label->loc;
	return n;
}

void destroy_goto(struct ast_node *got)
{
	assert(got->node_type == AST_GOTO);
	destroy_ast_node(got->_goto.label);
	free(got);
}

struct ast_node *gen_dot(struct ast_node *expr, struct ast_node *id)
{
	ALLOC_NODE(n, "dot");
	n->node_type = AST_DOT;
	n->_dot.expr = expr;
	n->_dot.id = id;
	return n;
}

void destroy_dot(struct ast_node *dot)
{
	assert(dot->node_type == AST_DOT);
	destroy_ast_node(dot->_dot.expr);
	destroy_ast_node(dot->_dot.id);
	free(dot);
}

struct ast_node *gen_label(struct ast_node *id)
{
	ALLOC_NODE(n, "label");
	n->node_type = AST_LABEL;
	n->_label.id = id;
	n->loc = id->loc;
	return n;
}

void destroy_label(struct ast_node *label)
{
	assert(label->node_type == AST_LABEL);
	destroy_ast_node(label->_label.id);
	free(label);
}

struct ast_node *gen_ctrl(enum ast_ctrl_kind kind, struct src_loc loc)
{
	ALLOC_NODE(n, "ctrl");
	n->node_type = AST_CTRL;
	n->loc = loc;
	n->_ctrl.kind = kind;
	return n;
}

void destroy_ctrl(struct ast_node *ctrl)
{
	free(ctrl);
}

struct ast_node *gen_fetch(struct ast_node *id, struct ast_node *type)
{
	ALLOC_NODE(n, "fetch");
	n->node_type = AST_FETCH;
	n->_fetch.id = id;
	n->_fetch.type = type;
	n->loc = id->loc;
	return n;
}

static void destroy_fetch(struct ast_node *fetch)
{
	assert(fetch->node_type == AST_FETCH);
	destroy_ast_node(fetch->_fetch.id);
	destroy_ast_node(fetch->_fetch.type);
	free(fetch);
}

struct ast_node *gen_macro(struct ast_node *id, struct ast_node *params,
                           struct ast_node *body)
{
	ALLOC_NODE(n, "body");
	n->node_type = AST_MACRO;
	n->_macro.id = id;
	n->_macro.params = params;
	n->_macro.body = body;
	n->loc = id->loc;
	return n;
}

void destroy_macro(struct ast_node *macro)
{
	assert(macro->node_type == AST_MACRO);
	destroy_ast_node(macro->_macro.id);
	DESTROY_LIST(macro->_macro.params);
	DESTROY_LIST(macro->_macro.body);
	free(macro);
}

struct ast_node *gen_if(struct ast_node *cond, struct ast_node *body,
                        struct ast_node *els)
{
	ALLOC_NODE(n, "if");
	n->node_type = AST_IF;
	n->_if.cond = cond;
	n->_if.body = body;
	n->_if.els = els;
	n->loc = loc_span(cond, els);
	return n;
}

void destroy_if(struct ast_node *i)
{
	assert(i->node_type == AST_IF);
	destroy_ast_node(i->_if.cond);
	DESTROY_LIST(i->_if.body);
	destroy_ast_node(i->_if.els);
	free(i);
}

struct ast_node *gen_switch(struct ast_node *cond, struct ast_node *cases)
{
	ALLOC_NODE(n, "switch");
	n->node_type = AST_SWITCH;
	n->_switch.cond = cond;
	n->_switch.cases = cases;
	n->loc = cond->loc;
	return n;
}

void destroy_switch(struct ast_node *switc)
{
	assert(switc->node_type == AST_SWITCH);
	destroy_ast_node(switc->_switch.cond);
	DESTROY_LIST(switc->_switch.cases);
	free(switc);
}

struct ast_node *gen_case(struct ast_node *cond, struct ast_node *body)
{
	ALLOC_NODE(n, "case");
	/* TODO: a macro to map proc name to node type would make sure I don't
	 * make any dumb mixups... */
	n->node_type = AST_CASE;
	n->_case.cond = cond;
	n->_case.body = body;
	/* TODO: where should I check the fallthrough flag? In the
	 * actualization stage, I guess */
	n->loc = body->loc;
	return n;
}

void destroy_case(struct ast_node *cas)
{
	assert(cas->node_type == AST_CASE);
	destroy_ast_node(cas->_case.cond);
	DESTROY_LIST(cas->_case.body);
	free(cas);
}

struct ast_node *gen_type(enum ast_type_kind kind, struct ast_node *id,
                          struct ast_node *expr, struct ast_node *ret)
{
	ALLOC_NODE(n, "type");
	n->node_type = AST_TYPE;
	n->_type.kind = kind;
	switch (kind) {
	case AST_TYPE_GENERIC:
		n->_type.generic.id = id;
		n->_type.generic.args = expr;
		n->loc = id->loc;
		break;

	case AST_TYPE_MEMBER:
		n->_type.member.id = id;
		n->_type.member.expr = expr;
		n->loc = id->loc;
		break;

	case AST_TYPE_ALIAS:
		n->_type.alias.alias = expr;
		n->_type.alias.actual = ret;
		n->loc = expr->loc;
		break;

	case AST_TYPE_TRAIT:
		n->_type.trait.trait = expr;
		n->_type.trait.actual = ret;
		n->loc = expr->loc;
		break;

	case AST_TYPE_ID:
		n->_type.id = id;
		n->loc = id->loc;
		break;

	case AST_TYPE_ARR:
		n->_type.arr.size = expr;
		if (expr)
			n->loc = expr->loc;
		break;

	case AST_TYPE_TYPEOF:
		n->_type.typeo.expr = expr;
		n->loc = expr->loc;
		break;

	case AST_TYPE_POINTER:
		break;

	case AST_TYPE_PROC:
		n->_type.proc.params = expr;
		n->_type.proc.ret = ret;
		n->loc = loc_span(expr, ret);
		break;

	case AST_TYPE_UNION:
		n->_type.unio.id = id;
		n->_type.unio.impls = expr;
		n->loc = id->loc;

		break;

	case AST_TYPE_STRUCT:
		n->_type.struc.id = id;
		n->_type.struc.impls = expr;
		n->loc = id->loc;
		break;

	case AST_TYPE_ENUM:
		n->_type.enu.id = id;
		n->_type.struc.impls = expr;
		n->loc = id->loc;
		break;

	case AST_TYPE_SIGN:
		n->_type.sign.params = expr;
		n->_type.sign.ret = ret;
		n->loc = loc_span(expr, ret);
		break;
	}

	return n;
}

void destroy_type(struct ast_node *type)
{
	assert(type->node_type == AST_TYPE);
	switch (type->_type.kind) {
	case AST_TYPE_GENERIC:
		destroy_ast_node(type->_type.generic.id);
		DESTROY_LIST(type->_type.generic.args);
		break;

	case AST_TYPE_MEMBER:
		destroy_ast_node(type->_type.member.id);
		destroy_ast_node(type->_type.member.expr);
		break;

	case AST_TYPE_ALIAS:
		break;

	case AST_TYPE_TRAIT:
		break;

	case AST_TYPE_ID:
		destroy_ast_node(type->_type.id);
		break;

	case AST_TYPE_ARR:
		destroy_ast_node(type->_type.arr.size);
		break;

	case AST_TYPE_TYPEOF:
		destroy_ast_node(type->_type.typeo.expr);
		break;

	case AST_TYPE_POINTER:
		break;

	case AST_TYPE_PROC:
		DESTROY_LIST(type->_type.proc.params);
		destroy_ast_node(type->_type.proc.ret);
		break;

	case AST_TYPE_STRUCT:
		destroy_ast_node(type->_type.struc.id);
		DESTROY_LIST(type->_type.struc.impls);
		break;

	case AST_TYPE_UNION:
		destroy_ast_node(type->_type.unio.id);
		DESTROY_LIST(type->_type.unio.impls);
		break;

	case AST_TYPE_ENUM:
		destroy_ast_node(type->_type.enu.id);
		destroy_ast_node(type->_type.enu.type);
		break;

	case AST_TYPE_SIGN:
		DESTROY_LIST(type->_type.sign.params);
		destroy_ast_node(type->_type.sign.ret);
		break;
	}

	destroy_ast_node(type->_type.next);
	free(type);
}

struct ast_node *gen_block(struct ast_node *body)
{
	ALLOC_NODE(n, "block");
	n->node_type = AST_BLOCK;
	n->_block.body = body;

	struct ast_node *first = body;
	struct ast_node *last = ast_last_node(body);
	n->loc = loc_span(first, last);
	return n;
}

void destroy_block(struct ast_node *block)
{
	assert(block->node_type == AST_BLOCK);
	DESTROY_LIST(block->_block.body);
	DESTROY_LIST(block->_block.defers);
	free(block);
}

struct ast_node *gen_sizeof(struct ast_node *expr)
{
	ALLOC_NODE(n, "sizeof");
	n->node_type = AST_SIZEOF;
	n->_sizeof.expr = expr;
	n->loc = expr->loc;
	return n;
}

void destroy_sizeof(struct ast_node *sizeo)
{
	assert(sizeo->node_type == AST_SIZEOF);
	destroy_ast_node(sizeo->_sizeof.expr);
	free(sizeo);
}
struct ast_node *gen_as(struct ast_node *type)
{
	ALLOC_NODE(n, "as");
	n->node_type = AST_AS;
	n->_as.type = type;
	n->loc = type->loc;
	return n;
}

void destroy_as(struct ast_node *as)
{
	assert(as->node_type == AST_AS);
	destroy_ast_node(as->_as.type);
	free(as);
}

struct ast_node *gen_defer(struct ast_node *expr)
{
	ALLOC_NODE(n, "defer");
	n->node_type = AST_DEFER;
	n->_defer.expr = expr;
	n->loc = expr->loc;
	return n;
}

void destroy_defer(struct ast_node *defer)
{
	assert(defer->node_type == AST_DEFER);
	destroy_ast_node(defer->_defer.expr);
	free(defer);
}

struct ast_node *gen_var(struct ast_node *id, struct ast_node *type,
                         struct ast_node *init)
{
	ALLOC_NODE(n, "var");
	n->node_type = AST_VAR;
	n->_var.id = id;
	n->_var.type = type;
	n->_var.init = init;
	if (id)
		n->loc = id->loc;
	else
		n->loc = type->loc;
	return n;
}

void destroy_var(struct ast_node *var)
{
	assert(var->node_type == AST_VAR);
	destroy_ast_node(var->_var.id);
	destroy_ast_node(var->_var.type);
	destroy_ast_node(var->_var.init);
	free(var);
}

struct ast_node *gen_proc(struct ast_node *id, struct ast_node *sign,
                          struct ast_node *body)
{
	ALLOC_NODE(n, "proc");
	n->node_type = AST_PROC;
	n->_proc.id = id;
	n->_proc.sign = sign;
	n->_proc.body = body;
	n->loc = id->loc;
	return n;
}

void destroy_proc(struct ast_node *proc)
{
	assert(proc->node_type == AST_PROC);
	destroy_ast_node(proc->_proc.id);
	DESTROY_LIST(proc->_proc.sign);
	DESTROY_LIST(proc->_proc.body);
	free(proc);
}

struct ast_node *gen_struct(struct ast_node *id,
                            struct ast_node *generics, struct ast_node *body)
{
	ALLOC_NODE(n, "struct");
	n->node_type = AST_STRUCT;
	n->_struct.id = id;
	n->_struct.generics = generics;
	n->_struct.body = body;
	if (id)
		n->loc = id->loc;
	else
		n->loc = body->loc;
	return n;
}

void destroy_struct(struct ast_node *struc)
{
	assert(struc->node_type == AST_STRUCT);
	destroy_ast_node(struc->_struct.id);
	DESTROY_LIST(struc->_struct.generics);
	DESTROY_LIST(struc->_struct.body);
	free(struc);
}

struct ast_node *gen_union(struct ast_node *id,
                           struct ast_node *generics, struct ast_node *body)
{
	ALLOC_NODE(n, "union");
	n->node_type = AST_UNION;
	n->_union.id = id;
	n->_union.generics = generics;
	n->_union.body = body;
	if (id)
		n->loc = id->loc;
	else
		n->loc = body->loc;
	return n;
}

void destroy_union(struct ast_node *unio)
{
	assert(unio->node_type == AST_UNION);
	destroy_ast_node(unio->_union.id);
	DESTROY_LIST(unio->_union.generics);
	DESTROY_LIST(unio->_union.body);
	free(unio);
}

struct ast_node *gen_enum(struct ast_node *id, struct ast_node *type,
                          struct ast_node *body)
{
	ALLOC_NODE(n, "enum");
	n->node_type = AST_ENUM;
	n->_enum.id = id;
	n->_enum.type = type;
	n->_enum.body = body;
	if (id)
		n->loc = id->loc;
	return n;
}

void destroy_enum(struct ast_node *enu)
{
	assert(enu->node_type == AST_ENUM);
	destroy_ast_node(enu->_enum.id);
	destroy_ast_node(enu->_enum.type);
	DESTROY_LIST(enu->_enum.body);
	free(enu);
}

struct ast_node *gen_cast(struct ast_node *expr, struct ast_node *type)
{
	ALLOC_NODE(n, "cast");
	n->node_type = AST_CAST;
	n->_cast.expr = expr;
	n->_cast.type = type;
	n->loc = loc_span(expr, type);
	return n;
}

void destroy_cast(struct ast_node *cast)
{
	assert(cast->node_type == AST_CAST);
	destroy_ast_node(cast->_cast.expr);
	destroy_ast_node(cast->_cast.type);
	free(cast);
}

struct ast_node *gen_val(struct ast_node *id, struct ast_node *val)
{
	ALLOC_NODE(n, "val");
	n->node_type = AST_VAL;
	n->_val.id = id;
	n->_val.val = val;
	n->loc = id->loc;
	return n;
}

void destroy_val(struct ast_node *val)
{
	assert(val->node_type == AST_VAL);
	destroy_ast_node(val->_val.id);
	destroy_ast_node(val->_val.val);
	free(val);
}

struct ast_node *gen_alias(struct ast_node *id, struct ast_node *type)
{
	ALLOC_NODE(n, "alias");
	n->node_type = AST_ALIAS;
	n->_alias.id = id;
	n->_alias.type = type;
	n->loc = id->loc;
	return n;
}

void destroy_alias(struct ast_node *alias)
{
	assert(alias->node_type == AST_ALIAS);
	destroy_ast_node(alias->_alias.id);
	destroy_ast_node(alias->_alias.type);
	free(alias);
}

struct ast_node *gen_trait(struct ast_node *id, struct ast_node *body)
{
	ALLOC_NODE(n, "trait");
	n->node_type = AST_TRAIT;
	n->_trait.id = id;
	n->_trait.body = body;
	n->loc = id->loc;
	return n;
}

void destroy_trait(struct ast_node *trait)
{
	assert(trait->node_type == AST_TRAIT);
	destroy_ast_node(trait->_trait.id);
	DESTROY_LIST(trait->_trait.body);

	struct trait_implemented *prev = trait->_trait.impl_by, *cur;
	if (prev)
		do {
			cur = prev->next;
			free(prev);
		} while ((prev = cur));
	free(trait);
}

struct ast_node *gen_import(const char *file)
{
	ALLOC_NODE(n, "import");
	n->node_type = AST_IMPORT;
	n->_import.file = file;
	/* TODO: where to get location */
	return n;
}

void destroy_import(struct ast_node *import)
{
	assert(import->node_type == AST_IMPORT);
	free((void *)import->_import.file);
	free(import);
}

struct ast_node *gen_embed(const char *file)
{
	ALLOC_NODE(n, "embed");
	n->node_type = AST_EMBED;
	n->_embed.file = file;
	/* TODO: location */
	return n;
}

void destroy_embed(struct ast_node *embed)
{
	assert(embed->node_type == AST_EMBED);
	free((void *)embed->_embed.file);
	free(embed);
}

struct ast_node *gen_empty()
{
	ALLOC_NODE(n, "empty");
	n->node_type = AST_EMPTY;
	/* TODO: location */
	return n;
}

void destroy_empty(struct ast_node *empty)
{
	assert(empty->node_type == AST_EMPTY);
	free(empty);
}

struct ast_node *gen_last()
{
	ALLOC_NODE(n, "last");
	n->node_type = AST_LAST;
	/* TODO: location */
	return n;
}

void destroy_last(struct ast_node *last)
{
	assert(last->node_type == AST_LAST);
	free(last);
}

void destroy_ast_node(struct ast_node *node)
{
	if (!node)
		return;

	assert(node->node_type);

	switch (node->node_type) {
	case AST_FETCH: destroy_fetch(node); break;
	case AST_UNION: destroy_union(node); break;
	case AST_ASSIGN: destroy_assign(node); break;
	case AST_INIT: destroy_init(node); break;
	case AST_SIZEOF: destroy_sizeof(node); break;
	case AST_DOT: destroy_dot(node); break;
	case AST_BINOP: destroy_binop(node); break;
	case AST_UNOP: destroy_unop(node); break;
	case AST_CALL: destroy_call(node); break;
	case AST_CAST: destroy_cast(node); break;
	case AST_MACRO: destroy_macro(node); break;
	case AST_MACRO_EXPANSION: destroy_macro_expansion(node); break;
	case AST_PROC: destroy_proc(node); break;
	case AST_GOTO: destroy_goto(node); break;
	case AST_LABEL: destroy_label(node); break;
	case AST_VAR: destroy_var(node); break;
	case AST_IF: destroy_if(node); break;
	case AST_FOR: destroy_for(node); break;
	case AST_WHILE: destroy_while(node); break;
	case AST_CTRL: destroy_ctrl(node); break;
	case AST_RETURN: destroy_return(node); break;
	case AST_TYPE: destroy_type(node); break;
	case AST_BLOCK: destroy_block(node); break;
	case AST_IMPORT: destroy_import(node); break;
	case AST_DEFER: destroy_defer(node); break;
	case AST_EMBED: destroy_embed(node); break;
	case AST_ENUM: destroy_enum(node); break;
	case AST_STRUCT: destroy_struct(node); break;
	case AST_VAL: destroy_val(node); break;
	case AST_SWITCH: destroy_switch(node); break;
	case AST_CASE: destroy_case(node); break;
	case AST_CONST: destroy_const(node); break;
	case AST_ALIAS: destroy_alias(node); break;
	case AST_TRAIT: destroy_trait(node); break;
	case AST_ID: destroy_id(node); break;
	case AST_AS: destroy_as(node); break;
	case AST_EMPTY: destroy_empty(node); break;
	case AST_LAST: destroy_last(node); break;
	}
}

void destroy_ast_tree(struct ast_node *root)
{
	DESTROY_LIST(root);
}

void ast_set_flags(struct ast_node *node, enum ast_flag flags)
{
	node->flags |= flags;
}

void ast_clear_flags(struct ast_node *node, enum ast_flag flags)
{
	node->flags &= ~(flags);
}

void ast_append(struct ast_node *list, struct ast_node *elem)
{
	struct ast_node *cur = list;
	while (cur->next)
		cur = cur->next;

	cur->next = elem;
}


static const char *binop_symbol(int op)
{
	switch (op) {
	case AST_ADD: return "+";
	case AST_SUB: return "-";
	case AST_MUL: return "*";
	case AST_DIV: return "/";
	case AST_REM: return "%";
	case AST_XOR: return "^";
	case AST_POW: return "^^";
	case AST_AND: return "&";
	case AST_OR: return "|";
	case AST_LOR: return "||";
	case AST_LAND: return "&&";
	case AST_LSHIFT: return "<<";
	case AST_RSHIFT: return ">>";
	case AST_ASSIGN_ADD: return "+=";
	case AST_ASSIGN_SUB: return "-=";
	case AST_ASSIGN_MUL: return "*=";
	case AST_ASSIGN_DIV: return "/=";
	case AST_ASSIGN_REM: return "%=";
	case AST_ASSIGN_AND: return "&=";
	case AST_ASSIGN_OR: return "|=";
	case AST_ASSIGN_XOR: return "^=";
	case AST_ASSIGN_LSHIFT: return "<<=";
	case AST_ASSIGN_RSHIFT: return ">>=";
	case AST_LT: return "<";
	case AST_GT: return ">";
	case AST_LE: return "<=";
	case AST_GE: return ">=";
	case AST_NE: return "!=";
	case AST_EQ: return "==";
	}

	return "UNKNOWN";
}

static const char *unop_symbol(int op)
{
	switch (op) {
	case AST_NEG: return "-";
	case AST_LNOT: return "!";
	case AST_REF: return "&";
	case AST_DEREF: return "'";
	case AST_NOT: return "~";
	}

	return "UNKNOWN";
}

static void dump(int depth, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	for (int i = 0; i < depth; ++i)
		putchar('\t');

	vprintf(fmt, args);

	va_end(args);
}

static void dump_flags(struct ast_node *node)
{
	if (node->scope)
		printf(" %zu:", node->scope->number);

	enum ast_flag flags = node->flags;
	if (flags & AST_FLAG_MUTABLE)
		printf(" MUT");

	if (flags & AST_FLAG_CONST)
		printf(" CONST");

	if (flags & AST_FLAG_EXTERN)
		printf(" EXTERN");

	if (flags & AST_FLAG_VARIADIC)
		printf(" VARIADIC");

	if (flags & AST_FLAG_DELAYED)
		printf(" DELAYED");

	if (flags & AST_FLAG_PUBLIC)
		printf(" PUB");

	if (flags & AST_FLAG_UNTYPED)
		printf(" UNTYPED");

	if (flags & AST_FLAG_FALLTHROUGH)
		printf(" FALLTHROUGH");
}

static void __dump_ast(int depth, struct ast_node *node)
{
	switch (node->node_type) {
	case AST_FETCH:
		dump(depth, "{FETCH:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_fetch.id);
		dump_ast(depth + 1, node->_fetch.type);

		dump(depth, "}\n");
		break;

	case AST_UNION:
		dump(depth, "{UNION:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_union.id);
		dump_ast(depth + 1, node->_union.generics);
		dump_ast(depth + 1, node->_union.body);

		dump(depth, "}\n");
		break;

	case AST_ASSIGN:
		dump(depth, "{ASSIGN:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_assign.to);
		dump_ast(depth + 1, node->_assign.from);

		dump(depth, "}\n");
		break;

	case AST_INIT:
		dump(depth, "{INIT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_init.body);

		dump(depth, "}\n");
		break;

	case AST_SIZEOF:
		dump(depth, "{SIZEOF:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_sizeof.expr);

		dump(depth, "}\n");
		break;

	case AST_DOT:
		dump(depth, "{DOT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_dot.expr);
		dump_ast(depth + 1, node->_dot.id);

		dump(depth, "}\n");
		break;

	case AST_GOTO:
		dump(depth, "{GOTO:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_goto.defers);
		dump_ast(depth + 1, node->_goto.label);

		dump(depth, "}\n");
		break;

	case AST_LABEL:
		dump(depth, "{LABEL:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_label.id);

		dump(depth, "}\n");
		break;

	case AST_BINOP:
		dump(depth, "{BINOP:");
		dump_flags(node);
		printf(" %s\n", binop_symbol(node->_binop.op));

		dump_ast(depth + 1, node->_binop.left);
		dump_ast(depth + 1, node->_binop.right);

		dump(depth, "}\n");
		break;

	case AST_UNOP:
		dump(depth, "{UNOP:");
		dump_flags(node);
		printf(" %s\n", unop_symbol(node->_unop.op));

		dump_ast(depth + 1, node->_unop.expr);

		dump(depth, "}\n");
		break;

	case AST_CALL:
		dump(depth, "{CALL:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_call.id);
		dump_ast(depth + 1, node->_call.args);

		dump(depth, "}\n");
		break;

	case AST_DEFER:
		dump(depth, "{DEFER:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_defer.expr);

		dump(depth, "}\n");
		break;

	case AST_CAST:
		dump(depth, "{CAST:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_cast.expr);
		dump_ast(depth + 1, node->_cast.type);

		dump(depth, "}\n");
		break;

	case AST_MACRO:
		dump(depth, "{MACRO:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_macro.id);
		dump_ast(depth + 1, node->_macro.params);
		dump_ast(depth + 1, node->_macro.body);

		dump(depth, "}\n");
		break;

	case AST_MACRO_EXPANSION:
		dump(depth, "{MACRO_EXPANSION:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_macro_expansion.id);
		dump_ast(depth + 1, node->_macro_expansion.args);

		dump(depth, "}\n");
		break;

	case AST_PROC:
		dump(depth, "{PROC:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_proc.id);
		dump_ast(depth + 1, node->_proc.sign);
		dump_ast(depth + 1, node->_proc.body);

		dump(depth, "}\n");
		break;

	case AST_VAR:
		dump(depth, "{VAR:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_var.id);
		dump_ast(depth + 1, node->_var.type);
		dump_ast(depth + 1, node->_var.init);

		dump(depth, "}\n");
		break;

	case AST_ID:
		dump(depth, "{ID:");
		dump_flags(node);
		printf(" %s}\n", node->_id.id);
		break;

	case AST_AS:
		dump(depth, "{AS:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_as.type);
		dump(depth, "}\n");
		break;

	case AST_BLOCK:
		dump(depth, "{BLOCK:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_block.body);
		dump_ast(depth + 1, node->_block.defers);

		dump(depth, "}\n");
		break;

	case AST_RETURN:
		dump(depth, "{RETURN:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_return.defers);
		dump_ast(depth + 1, node->_return.expr);

		dump(depth, "}\n");
		break;

	case AST_TYPE:
		dump(depth, "{TYPE:");
		dump_flags(node);

		switch (node->_type.kind) {
		case AST_TYPE_GENERIC:
			printf(" GENERIC\n");
			dump_ast(depth + 1, node->_type.generic.id);
			dump_ast(depth + 1, node->_type.generic.args);
			break;

		case AST_TYPE_MEMBER:
			printf(" MEMBER\n");
			dump_ast(depth + 1, node->_type.member.id);
			dump_ast(depth + 1, node->_type.member.expr);
			break;

		case AST_TYPE_ALIAS:
			printf(" ALIAS\n");
			dump_ast(depth + 1, node->_type.alias.alias->_alias.id);
			dump_ast(depth + 1, node->_type.alias.actual);
			break;

		case AST_TYPE_TRAIT:
			printf(" TRAIT\n");
			dump_ast(depth + 1,
			         node->_type.trait.trait->_trait.id);
			dump_ast(depth + 1, node->_type.trait.actual);
			break;

		case AST_TYPE_ID:
			printf(" ID\n");
			dump_ast(depth + 1, node->_type.id);
			break;

		case AST_TYPE_ARR:
			printf(" ARR\n");
			dump_ast(depth + 1, node->_type.arr.size);
			break;

		case AST_TYPE_POINTER:
			printf(" PTR\n");
			break;

		case AST_TYPE_TYPEOF:
			printf(" TYPEOF\n");
			dump_ast(depth + 1, node->_type.typeo.expr);
			dump_ast(depth + 1, node->_type.typeo.actual);
			break;

		case AST_TYPE_PROC:
			printf(" PROC\n");
			dump_ast(depth + 1, node->_type.proc.params);
			dump_ast(depth + 1, node->_type.proc.ret);
			break;

		case AST_TYPE_STRUCT:
			printf(" STRUCT\n");
			/* oh yeah, struc is at least right now just an ID that
			 * we can use to fetch the actual struct with. */
			dump_ast(depth + 1, node->_type.struc.id);
			dump_ast(depth + 1, node->_type.struc.impls);
			break;

		case AST_TYPE_ENUM:
			printf(" ENUM\n");
			dump_ast(depth + 1, node->_type.enu.id);
			dump_ast(depth + 1, node->_type.enu.type);
			break;

		case AST_TYPE_UNION:
			printf(" UNION\n");
			dump_ast(depth + 1, node->_type.unio.id);
			dump_ast(depth + 1, node->_type.unio.impls);
			break;

		case AST_TYPE_SIGN: printf(" SIGN\n");
			dump_ast(depth + 1, node->_type.sign.params);
			dump_ast(depth + 1, node->_type.sign.ret);
			break;
		}

		dump_ast(depth + 1, node->_type.next);

		dump(depth, "}\n");
		break;

	case AST_LAST:
		dump(depth, "{LAST:");
		dump_flags(node);
		printf("}\n");
		break;

	case AST_EMPTY:
		dump(depth, "{EMPTY:");
		dump_flags(node);
		printf("}\n");
		break;

	case AST_FOR:
		dump(depth, "{FOR:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_for.pre);
		dump_ast(depth + 1, node->_for.cond);
		dump_ast(depth + 1, node->_for.post);
		dump_ast(depth + 1, node->_for.body);

		dump(depth, "}\n");
		break;

	case AST_WHILE:
		dump(depth, "{WHILE:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_while.cond);
		dump_ast(depth + 1, node->_while.body);

		dump(depth, "}\n");
		break;

	case AST_CTRL:
		dump(depth, "{CTRL:");
		dump_flags(node);
		switch(node->_ctrl.kind) {
		case AST_CTRL_BREAK: printf(" BREAK"); break;
		case AST_CTRL_CONTINUE: printf(" CONTINUE"); break;
		}
		printf("}\n");
		break;

	case AST_IF:
		dump(depth, "{IF:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_if.cond);
		dump_ast(depth + 1, node->_if.body);
		dump_ast(depth + 1, node->_if.els);

		dump(depth, "}\n");
		break;

	case AST_IMPORT:
		dump(depth, "{IMPORT:");
		dump_flags(node);
		printf(" %s}\n", node->_import.file);
		break;

	case AST_EMBED:
		dump(depth, "{EMBED:");
		dump_flags(node);
		printf(" %s}\n", node->_import.file);
		break;

	case AST_ENUM:
		dump(depth, "{ENUM:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_enum.id);
		dump_ast(depth + 1, node->_enum.type);
		dump_ast(depth + 1, node->_enum.body);

		dump(depth, "}\n");
		break;

	case AST_STRUCT:
		dump(depth, "{STRUCT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_struct.id);
		dump_ast(depth + 1, node->_struct.generics);
		dump_ast(depth + 1, node->_struct.body);

		dump(depth, "}\n");
		break;

	case AST_VAL:
		dump(depth, "{VAL:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_val.id);
		dump_ast(depth + 1, node->_val.val);

		dump(depth, "}\n");
		break;

	case AST_SWITCH:
		dump(depth, "{SWITCH:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_switch.cond);
		dump_ast(depth + 1, node->_switch.cases);

		dump(depth, "}\n");
		break;

	case AST_CASE:
		dump(depth, "{CASE:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_case.cond);
		dump_ast(depth + 1, node->_case.body);

		dump(depth, "}\n");
		break;

	case AST_CONST:
		dump(depth, "{CONST:");
		dump_flags(node);
		switch (node->_const.kind) {
		case AST_CONST_INTEGER: printf("%lli", node->_const.integer);
			break;
		case AST_CONST_STRING: printf("\"%s\"", node->_const.str);
			break;
		case AST_CONST_FLOAT: printf("%lf", node->_const.dbl); break;
		}
		printf("}\n");
		break;

	case AST_ALIAS:
		dump(depth, "{ALIAS:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_alias.id);
		dump_ast(depth + 1, node->_alias.type);

		dump(depth, "}\n");
		break;

	case AST_TRAIT:
		dump(depth, "{TRAIT:");
		dump_flags(node);
		putchar('\n');

		dump_ast(depth + 1, node->_trait.id);
		dump_ast(depth + 1, node->_trait.body);

		dump(depth, "}\n");
		break;
	}
}

void dump_ast(int depth, struct ast_node *root)
{
	if (!root) {
		dump(depth, "{NULL}\n");
		return;
	}

	struct ast_node *n = root;
	do {
		__dump_ast(depth, n);
	} while ((n = n->next));
}

struct ast_node *clone_ast_node(struct ast_node *node)
{
	if (!node)
		return NULL;

	assert(node->node_type);
	struct ast_node *new = NULL;
	switch (node->node_type) {
	case AST_FETCH:
		new = gen_fetch(clone_ast_node(node->_fetch.id),
		                clone_ast_node(node->_fetch.type));
		break;

	case AST_UNION:
		new = gen_union(clone_ast_node(node->_union.id),
		                clone_ast_node(node->_union.generics),
		                clone_ast_node(node->_union.body));
		break;

	case AST_ASSIGN:
		new = gen_assign(clone_ast_node(node->_assign.to),
		                 clone_ast_node(node->_assign.from));
		break;

	case AST_INIT: new = gen_init(clone_ast_node(node->_init.body));
		break;

	case AST_SIZEOF: new = gen_sizeof(clone_ast_node(node->_sizeof.expr));
		break;

	case AST_DOT: new = gen_dot(clone_ast_node(node->_dot.expr),
		                    clone_ast_node(node->_dot.id));
		break;

	case AST_AS: new = gen_as(clone_ast_node(node->_as.type));
		break;

	case AST_GOTO: new = gen_goto(clone_ast_node(node->_goto.label));
		break;

	case AST_LABEL: new = gen_label(clone_ast_node(node->_label.id));
		break;

	case AST_BINOP: new = gen_binop(node->_binop.op,
		                        clone_ast_node(node->_binop.left),
		                        clone_ast_node(node->_binop.right));
		break;

	case AST_UNOP: new = gen_unop(node->_unop.op,
		                      clone_ast_node(node->_unop.expr));
		break;

	case AST_CALL: new = gen_call(clone_ast_node(node->_call.id),
		                      clone_ast_node(node->_call.args));
		break;

	case AST_DEFER: new = gen_defer(clone_ast_node(node->_defer.expr));
		break;

	case AST_MACRO: new = gen_macro(clone_ast_node(node->_macro.id),
		                        clone_ast_node(node->_macro.params),
		                        clone_ast_node(node->_macro.body));
		break;

	case AST_MACRO_EXPANSION: new = gen_macro_expansion(clone_ast_node(node->_macro_expansion.id),
						  clone_ast_node(node->_macro_expansion.args));
				  break;

	case AST_CAST: new = gen_cast(clone_ast_node(node->_cast.expr),
		                      clone_ast_node(node->_cast.type));
		break;

	case AST_PROC: new = gen_proc(clone_ast_node(node->_proc.id),
		                      clone_ast_node(node->_proc.sign),
		                      clone_ast_node(node->_proc.body));
		break;

	case AST_VAR: {
		/* I don't like how messy this is, should maybe try and come up
		 * with something better */
		struct ast_node *type = NULL;
		if (node->type)
			type = clone_ast_node(node->type);
		else
			type = clone_ast_node(node->_var.type);

		new = gen_var(clone_ast_node(node->_var.id),
		              type,
		              clone_ast_node(node->_var.init));
		/* vars always reference the type associated with them? */
		if (node->type)
			new->type = type;
		break;
	}

	case AST_FOR: new = gen_for(clone_ast_node(node->_for.pre),
		                    clone_ast_node(node->_for.cond),
		                    clone_ast_node(node->_for.post),
		                    clone_ast_node(node->_for.body));
		break;

	case AST_WHILE: new = gen_while(clone_ast_node(node->_while.cond),
		                        clone_ast_node(node->_while.body));
		break;

	case AST_CTRL: new = gen_ctrl(node->_ctrl.kind, node->loc);
		break;

	case AST_RETURN: new = gen_return(clone_ast_node(node->_return.expr));
		break;

	case AST_TYPE:
		/* oh, if a node has a ->type it probably isn't cloned
		 * correctly... */
		switch (node->_type.kind) {
		case AST_TYPE_GENERIC:
			new = gen_type(AST_TYPE_GENERIC,
			               clone_ast_node(node->_type.generic.id),
			               clone_ast_node(node->_type.generic.args),
			               NULL);
			break;

		case AST_TYPE_MEMBER:
			new = gen_type(AST_TYPE_MEMBER,
			               clone_ast_node(node->_type.member.id),
			               clone_ast_node(node->_type.member.expr),
			               NULL);
			break;

		case AST_TYPE_ALIAS:
			new = gen_type(AST_TYPE_ALIAS, NULL,
			               /* should make it more obvious what is a
			                * reference and what isn't */
			               node->_type.alias.alias,
			               node->_type.alias.actual);
			break;

		case AST_TYPE_TRAIT:
			new = gen_type(AST_TYPE_TRAIT, NULL,
			               node->_type.trait.trait,
			               /* ditto, should actual be cloned? */
			               node->_type.trait.actual);
			break;
		case AST_TYPE_ID:
			new = gen_type(AST_TYPE_ID,
			               clone_ast_node(node->_type.id),
			               NULL, NULL);
			break;

		case AST_TYPE_ARR:
			new = gen_type(AST_TYPE_ARR, NULL,
			               clone_ast_node(node->_type.arr.size),
			               NULL);
			break;

		case AST_TYPE_TYPEOF:
			new = gen_type(AST_TYPE_TYPEOF, NULL,
			               clone_ast_node(node->_type.typeo.expr),
			               NULL);
			break;

		case AST_TYPE_POINTER:
			new = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
			break;

		case AST_TYPE_STRUCT:
			new = gen_type(AST_TYPE_STRUCT,
			               clone_ast_node(node->_type.struc.id),
			               clone_ast_node(node->_type.struc.impls),
			               NULL);
			break;

		case AST_TYPE_ENUM:
			new = gen_type(AST_TYPE_ENUM,
			               clone_ast_node(node->_type.enu.id),
			               clone_ast_node(node->_type.enu.type),
			               NULL);
			break;

		case AST_TYPE_UNION:
			new = gen_type(AST_TYPE_UNION,
			               clone_ast_node(node->_type.unio.id),
			               clone_ast_node(node->_type.unio.impls),
			               NULL);
			break;

		case AST_TYPE_PROC:
			new = gen_type(AST_TYPE_PROC, NULL,
			               clone_ast_node(node->_type.proc.params),
			               clone_ast_node(node->_type.proc.ret));
			break;

		case AST_TYPE_SIGN:
			new = gen_type(AST_TYPE_SIGN, NULL,
			               clone_ast_node(node->_type.sign.params),
			               clone_ast_node(node->_type.sign.ret));
			break;

		}

		assert(new);
		new->_type.next = clone_ast_node(node->_type.next);
		break;

	case AST_BLOCK:
		/* TODO: should defers also be cloned? Probably? */
		new = gen_block(clone_ast_node(node->_block.body));
		break;

	case AST_IMPORT:
		new = gen_import(strdup(node->_import.file));
		break;

	case AST_EMBED:
		new = gen_embed(strdup(node->_import.file));
		break;

	case AST_ENUM:
		new = gen_enum(clone_ast_node(node->_enum.id),
		               clone_ast_node(node->_enum.type),
		               clone_ast_node(node->_enum.body));
		break;

	case AST_STRUCT:
		new = gen_struct(clone_ast_node(node->_struct.id),
		                 clone_ast_node(node->_struct.generics),
		                 clone_ast_node(node->_struct.body));
		break;

	case AST_VAL:
		new = gen_val(clone_ast_node(node->_val.id),
		              clone_ast_node(node->_val.val));
		break;

	case AST_SWITCH:
		new = gen_switch(clone_ast_node(node->_switch.cond),
		                 clone_ast_node(node->_switch.cases));
		break;

	case AST_CASE:
		new = gen_case(clone_ast_node(node->_case.cond),
		               clone_ast_node(node->_case.body));
		break;

	case AST_CONST:
		switch (node->_const.kind) {
		case AST_CONST_INTEGER:
			new = gen_int(node->_const.integer);
			break;

		case AST_CONST_STRING:
			new = gen_string(strdup(node->_const.str));
			break;

		case AST_CONST_FLOAT:
			new = gen_float(node->_const.dbl);
			break;
		}
		break;

	case AST_ID:
		new = gen_id(strdup(node->_id.id));
		break;

	case AST_EMPTY:
		new = gen_empty();
		break;

	case AST_LAST:
		new = gen_last();
		break;

	case AST_ALIAS:
		new = gen_alias(clone_ast_node(node->_alias.id),
		                clone_ast_node(node->_alias.type));
		break;

	case AST_TRAIT:
		new = gen_trait(clone_ast_node(node->_trait.id),
		                   clone_ast_node(node->_trait.body));
		break;

	case AST_IF:
		new = gen_if(clone_ast_node(node->_if.cond),
		             clone_ast_node(node->_if.body),
		             clone_ast_node(node->_if.els));
		break;
	}

	/* if we run out of memory, this assert is likely a bit dumb... */
	assert(new);
	new->scope = node->scope;
	new->flags = node->flags;
	new->loc = node->loc;
	new->next = clone_ast_node(node->next);

	/* some special case handled type references for us */
	if (!new->type)
		new->type = node->type;

	return new;
}

/* here we could do a memcmp... */
static int identical_loc(struct src_loc left, struct src_loc right)
{
	return left.first_line == right.first_line
	       && left.last_line == right.last_line
	       && left.first_col == right.first_col
	       && left.last_col == right.last_col;
}

static int identical_flags(enum ast_flag left, enum ast_flag right)
{
	return left == right;
}

/* TODO: remember to update this if I decide to not mess aroung with this void*
 * nonsense */
static int identical_scope(void *left, void *right)
{
	return left == right;
}

static int identical_union(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_union.id, b->_union.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_union.generics, b->_union.generics))
		return 0;

	if (!identical_ast_nodes(exact, a->_union.body, b->_union.body))
		return 0;

	return 1;
}

static int identical_assign(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_assign.to, a->_assign.to))
		return 0;

	if (!identical_ast_nodes(exact, b->_assign.from, b->_assign.from))
		return 0;

	return 1;
}

static int identical_init(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_init.body, b->_init.body);
}

static int identical_sizeof(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_sizeof.expr, b->_sizeof.expr);
}

static int identical_dot(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_dot.expr, b->_dot.expr))
		return 0;

	if (!identical_ast_nodes(exact, a->_dot.id, b->_dot.id))
		return 0;

	return 1;
}

static int identical_as(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_as.type, b->_as.type);
}

static int identical_goto(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_goto.label, b->_goto.label);
}

static int identical_label(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_label.id, b->_label.id);
}

static int identical_binop(int exact, struct ast_node *a, struct ast_node *b)
{
	if (a->_binop.op != b->_binop.op)
		return 0;

	if (!identical_ast_nodes(exact, a->_binop.left, b->_binop.left))
		return 0;

	if (!identical_ast_nodes(exact, a->_binop.right, b->_binop.right))
		return 0;

	return 1;
}

static int identical_unop(int exact, struct ast_node *a, struct ast_node *b)
{
	if (a->_unop.op != b->_unop.op)
		return 0;

	if (!identical_ast_nodes(exact, a->_unop.expr, b->_unop.expr))
		return 0;

	return 1;
}

static int identical_call(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_call.id, b->_call.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_call.args, b->_call.args))
		return 0;

	return 1;
}

static int identical_cast(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_cast.expr, b->_cast.expr))
		return 0;

	if (!identical_ast_nodes(exact, a->_cast.type, b->_cast.type))
		return 0;

	return 1;
}

static int identical_defer(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_defer.expr, b->_defer.expr);
}

static int identical_macro(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_macro.id, b->_macro.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_macro.params, b->_macro.params))
		return 0;

	if (!identical_ast_nodes(exact, a->_macro.body, b->_macro.body))
		return 0;

	return 1;
}

static int identical_proc(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_proc.id, b->_proc.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_proc.sign, b->_proc.sign))
		return 0;

	if (!identical_ast_nodes(exact, a->_proc.body, b->_proc.body))
		return 0;

	return 1;
}

static int identical_var(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_var.id, b->_var.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_var.type, b->_var.type))
		return 0;

	if (!identical_ast_nodes(exact, a->_var.init, b->_var.init))
		return 0;

	return 1;
}

static int identical_for(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_for.pre, b->_for.pre))
		return 0;

	if (!identical_ast_nodes(exact, a->_for.cond, b->_for.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_for.post, b->_for.post))
		return 0;

	if (!identical_ast_nodes(exact, a->_for.body, b->_for.body))
		return 0;

	return 1;
}

static int identical_while(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_while.cond, b->_while.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_while.body, b->_while.body))
		return 0;

	return 1;
}

static int identical_ctrl(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	return a->_ctrl.kind == b->_ctrl.kind;
}

static int identical_return(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_return.expr, b->_return.expr);
}

static int identical_type_alias(int exact, struct ast_node *a,
                                struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_type.alias.alias,
	                         b->_type.alias.alias))
		return 0;

	if (!identical_ast_nodes(exact, a->_type.alias.actual,
	                         b->_type.alias.actual))
		return 0;
	return 1;
}

static int identical_type_trait(int exact, struct ast_node *a,
                                   struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_type.trait.trait,
	                         b->_type.trait.trait))
		return 0;

	if (!identical_ast_nodes(exact, a->_type.trait.actual,
	                         b->_type.trait.actual))
		return 0;

	return 1;
}

static int identical_type_id(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_type.id, b->_type.id);
}

static int identical_type_arr(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_type.arr.size, b->_type.arr.size);
}

static int identical_type_typeof(int exact, struct ast_node *a,
                                 struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_type.typeo.expr,
	                           b->_type.typeo.expr);
}

static int identical_type_proc(int exact, struct ast_node *a,
                               struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_type.proc.params,
	                         b->_type.proc.params))
		return 0;

	if (!identical_ast_nodes(exact, a->_type.proc.ret, b->_type.proc.ret))
		return 0;

	return 1;
}

static int identical_type_sign(int exact, struct ast_node *a,
                               struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_type.sign.params,
	                         b->_type.sign.params))
		return 0;

	if (!identical_ast_nodes(exact, a->_type.sign.ret, b->_type.sign.ret))
		return 0;

	return 1;
}

static int identical_type_struct(int exact, struct ast_node *a,
                                 struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_type.struc.id, b->_type.struc.id))
		return 0;

	if (!identical_ast_nodes(1, a->_type.struc.impls,
	                         b->_type.struc.impls))
		return 0;

	return 1;
}

static int identical_type_union(int exact, struct ast_node *a,
                                struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_type.unio.id, b->_type.unio.id))
		return 0;

	if (!identical_ast_nodes(1, a->_type.unio.impls,
	                         b->_type.unio.impls))
		return 0;

	return 1;
}

static int identical_type_enum(int exact, struct ast_node *a,
                               struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_type.enu.id, b->_type.enu.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_type.enu.type, b->_type.enu.type))
		return 0;

	return 1;
}

static int identical_type_member(int exact, struct ast_node *a,
                                 struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_type.member.id, b->_type.member.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_type.member.expr,
	                         b->_type.member.expr))
		return 0;

	return 1;
}

static int identical_type_generic(int exact, struct ast_node *a,
                                  struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_type.generic.id,
	                         b->_type.generic.id))
		return 0;

	/* array should always be checked, so do an exact match */
	if (!identical_ast_nodes(1, a->_type.generic.args,
	                         b->_type.generic.args))
		return 0;

	return 1;
}

static int identical_type(int exact, struct ast_node *a, struct ast_node *b)
{
	if (a->_type.kind != b->_type.kind)
		return 0;

	int ret = 0;
	switch (a->_type.kind) {
	case AST_TYPE_GENERIC: ret = identical_type_generic(exact, a, b); break;
	case AST_TYPE_MEMBER: ret = identical_type_member(exact, a, b); break;
	case AST_TYPE_ENUM: ret = identical_type_enum(exact, a, b); break;
	case AST_TYPE_ALIAS: ret = identical_type_alias(exact, a, b); break;
	case AST_TYPE_TRAIT: ret = identical_type_trait(exact, a, b);
		break;
	case AST_TYPE_ID: ret = identical_type_id(exact, a, b); break;
	case AST_TYPE_ARR: ret = identical_type_arr(exact, a, b); break;
	case AST_TYPE_TYPEOF: ret = identical_type_typeof(exact, a, b); break;
	case AST_TYPE_PROC: ret = identical_type_proc(exact, a, b); break;
	case AST_TYPE_SIGN: ret = identical_type_sign(exact, a, b); break;
	case AST_TYPE_STRUCT: ret = identical_type_struct(exact, a, b); break;
	case AST_TYPE_UNION: ret = identical_type_union(exact, a, b); break;
	case AST_TYPE_POINTER: break;
	}

	return ret;
}

static int identical_block(int exact, struct ast_node *a, struct ast_node *b)
{
	return identical_ast_nodes(exact, a->_block.body, b->_block.body);
}

static int identical_import(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	return strcmp(a->_import.file, b->_import.file) == 0;
}

static int identical_embed(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	return strcmp(a->_embed.file, b->_embed.file) == 0;
}

static int identical_enum(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_enum.id, b->_enum.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_enum.type, b->_enum.type))
		return 0;

	if (!identical_ast_nodes(exact, a->_enum.body, b->_enum.body))
		return 0;

	return 1;
}

static int identical_struct(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_struct.id, b->_struct.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_struct.generics,
	                         b->_struct.generics))
		return 0;

	if (!identical_ast_nodes(exact, a->_struct.body, b->_struct.body))
		return 0;

	return 1;
}

static int identical_val(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_val.id, b->_val.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_val.val, b->_val.val))
		return 0;

	return 1;
}

static int identical_switch(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_switch.cond, b->_switch.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_switch.cases, b->_switch.cases))
		return 0;

	return 1;
}

static int identical_case(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_case.cond, b->_switch.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_case.body, b->_case.body))
		return 0;

	return 1;
}

static int identical_const(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	if (a->_const.kind != b->_const.kind)
		return 0;

	/* these could potentially also be broken out to their own
	 * procedures, but I don't think it's that important */
	switch (a->_const.kind) {
	case AST_CONST_INTEGER:
		if (a->_const.integer != b->_const.integer)
			return 0;

		break;

	case AST_CONST_FLOAT:
		/* NaNs aren't comparable */
		if (isnan(a->_const.dbl) && isnan(b->_const.dbl))
			break;

		if (a->_const.dbl != b->_const.dbl)
			return 0;

		break;

	case AST_CONST_STRING:
		if (strcmp(a->_const.str, b->_const.str) != 0)
			return 0;

		break;
	}

	return 1;
}

static int identical_id(int exact, struct ast_node *a, struct ast_node *b)
{
	(void)(exact);
	return strcmp(a->_id.id, b->_id.id) == 0;
}

static int identical_alias(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_alias.id, b->_alias.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_alias.type, b->_alias.type))
		return 0;

	return 1;
}

static int identical_trait(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_trait.id, b->_trait.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_trait.body, b->_trait.body))
		return 0;

	return 1;
}

static int identical_if(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_if.cond, b->_if.cond))
		return 0;

	if (!identical_ast_nodes(exact, a->_if.body, b->_if.body))
		return 0;

	if (!identical_ast_nodes(exact, a->_if.els, b->_if.els))
		return 0;

	return 1;
}

static int identical_fetch(int exact, struct ast_node *a, struct ast_node *b)
{
	if (!identical_ast_nodes(exact, a->_fetch.id, b->_fetch.id))
		return 0;

	if (!identical_ast_nodes(exact, a->_fetch.type, b->_fetch.type))
		return 0;

	return 1;
}

/* sort of unfortnate that we can't just do a direct memcmp... */
int identical_ast_nodes(int exact, struct ast_node *a, struct ast_node *b)
{
	/* both being NULL counts as identical */
	if (!a && !b)
		return 1;

	/* the same node must be the same */
	if (a == b)
		return 1;

	/* either one being null means not identical */
	if (!a)
		return 0;

	if (!b)
		return 0;

	if (a->node_type != b->node_type)
		return 0;

	if (exact && !identical_flags(a->flags, b->flags))
		return 0;

	if (exact && !identical_loc(a->loc, b->loc))
		return 0;

	if (exact && !identical_scope(a->scope, b->scope))
		return 0;

	int ret = 0;
	switch (a->node_type) {
	case AST_FETCH: ret = identical_fetch(exact, a, b); break;
	case AST_UNION: ret = identical_union(exact, a, b); break;
	case AST_ASSIGN: ret = identical_assign(exact, a, b); break;
	case AST_INIT: ret = identical_init(exact, a, b); break;
	case AST_SIZEOF: ret = identical_sizeof(exact, a, b); break;
	case AST_DOT: ret = identical_dot(exact, a, b); break;
	case AST_AS: ret = identical_as(exact, a, b); break;
	case AST_GOTO: ret = identical_goto(exact, a, b); break;
	case AST_LABEL: ret = identical_label(exact, a, b); break;
	case AST_BINOP: ret = identical_binop(exact, a, b); break;
	case AST_UNOP: ret = identical_unop(exact, a, b); break;
	case AST_CALL: ret = identical_call(exact, a, b); break;
	case AST_CAST: ret = identical_cast(exact, a, b); break;
	case AST_DEFER: ret = identical_defer(exact, a, b); break;
	case AST_MACRO: ret = identical_macro(exact, a, b); break;
	case AST_MACRO_EXPANSION: ret = identical_macro(exact, a, b); break;
	case AST_PROC: ret = identical_proc(exact, a, b); break;
	case AST_VAR: ret = identical_var(exact, a, b); break;
	case AST_FOR: ret = identical_for(exact, a, b); break;
	case AST_WHILE: ret = identical_while(exact, a, b); break;
	case AST_CTRL: ret = identical_ctrl(exact, a, b); break;
	case AST_RETURN: ret = identical_return(exact, a, b); break;
	case AST_TYPE: ret = identical_type(exact, a, b); break;
	case AST_BLOCK: ret = identical_block(exact, a, b); break;
	case AST_IMPORT: ret = identical_import(exact, a, b); break;
	case AST_EMBED: ret = identical_embed(exact, a, b); break;
	case AST_ENUM: ret = identical_enum(exact, a, b); break;
	case AST_STRUCT: ret = identical_struct(exact, a, b); break;
	case AST_VAL: ret = identical_val(exact, a, b); break;
	case AST_SWITCH: ret = identical_switch(exact, a, b); break;
	case AST_CASE: ret = identical_case(exact, a, b); break;
	case AST_CONST: ret = identical_const(exact, a, b); break;
	case AST_ID: ret = identical_id(exact, a, b); break;
	case AST_ALIAS: ret = identical_alias(exact, a, b); break;
	case AST_TRAIT: ret = identical_trait(exact, a, b); break;
	case AST_IF: ret = identical_if(exact, a, b); break;
	case AST_EMPTY: break;
	case AST_LAST: break;
	}

	if (ret == 0)
		return 0;

	/* Unsure if exact should be more of a flag or what,
	 * but at least right now the issue is that the analyzer in some cases
	 * has nodes that follow each other, i.e. next is populated, but we're
	 * only interested in the current node. Calls, mainly. */
	if (exact)
		return identical_ast_nodes(exact, a->next, b->next);

	return 1;
}

int ast_flags(struct ast_node *node, enum ast_flag flags)
{
	return node->flags & flags;
}

static int call_on_union(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_union.id, data);
	ret |= call(node->_union.generics, data);
	ret |= call(node->_union.body, data);
	return ret;
}

static int call_on_assign(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_assign.to, data);
	ret |= call(node->_assign.from, data);
	return ret;
}

static int call_on_init(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	return call(node->_init.body, data);
}

static int call_on_sizeof(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	return call(node->_sizeof.expr, data);
}

static int call_on_dot(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_dot.expr, data);
	ret |= call(node->_dot.id, data);
	return ret;
}

static int call_on_as(int (*call)(struct ast_node *,
                                  void *), struct ast_node *node, void *data)
{
	return call(node->_as.type, data);
}

static int call_on_cast(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_cast.expr, data);
	ret |= call(node->_cast.type, data);
	return ret;
}

static int call_on_defer(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	return call(node->_defer.expr, data);
}

static int call_on_var(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_var.id, data);
	ret |= call(node->_var.type, data);
	ret |= call(node->_var.init, data);
	return ret;
}

static int call_on_for(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_for.pre, data);
	ret |= call(node->_for.cond, data);
	ret |= call(node->_for.post, data);
	ret |= call(node->_for.body, data);
	return ret;
}

static int call_on_while(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_while.cond, data);
	ret |= call(node->_while.body, data);
	return ret;
}

static int call_on_return(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	return call(node->_return.expr, data);
}

static int call_on_alias(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_alias.id, data);
	ret |= call(node->_alias.type, data);
	return ret;
}

static int call_on_trait(int (*call)(struct ast_node *,
                                        void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_trait.id, data);
	ret |= call(node->_trait.body, data);
	return ret;
}

static int call_on_if(int (*call)(struct ast_node *,
                                  void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_if.cond, data);
	ret |= call(node->_if.body, data);
	ret |= call(node->_if.els, data);
	return ret;
}

static int call_on_enum(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_enum.id, data);
	ret |= call(node->_enum.type, data);
	ret |= call(node->_enum.body, data);
	return ret;
}

static int call_on_struct(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_struct.id, data);
	ret |= call(node->_struct.generics, data);
	ret |= call(node->_struct.body, data);
	return ret;
}

static int call_on_val(int (*call)(struct ast_node *,
                                   void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_val.id, data);
	ret |= call(node->_val.val, data);
	return ret;
}

static int call_on_switch(int (*call)(struct ast_node *,
                                      void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_switch.cond, data);
	ret |= call(node->_switch.cases, data);
	return ret;
}

static int call_on_case(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_case.cond, data);
	ret |= call(node->_case.body, data);
	return ret;
}

static int call_on_type_alias(int (*call)(struct ast_node *,
                                          void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_type.alias.alias, data);
	ret |= call(node->_type.alias.actual, data);
	return ret;
}

static int call_on_type_trait(int (*call)(struct ast_node *,
                                             void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_type.trait.trait, data);
	ret |= call(node->_type.trait.actual, data);
	return ret;
}

static int call_on_type_id(int (*call)(struct ast_node *,
                                       void *), struct ast_node *node, void *data)
{
	return call(node->_type.id, data);
}

static int call_on_type_arr(int (*call)(struct ast_node *,
                                        void *), struct ast_node *node, void *data)
{
	return call(node->_type.arr.size, data);
}

static int call_on_type_typeof(int (*call)(struct ast_node *,
                                           void *), struct ast_node *node, void *data)
{
	return call(node->_type.typeo.expr, data);
}

static int call_on_type_union(int (*call)(struct ast_node *,
                                          void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_type.unio.id, data);
	ret |= call(node->_type.unio.impls, data);
	return ret;
}

static int call_on_type_struct(int (*call)(struct ast_node *,
                                           void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_type.struc.id, data);
	ret |= call(node->_type.struc.impls, data);
	return ret;
}

static int call_on_type_proc(int (*call)(struct ast_node *,
                                         void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_type.proc.id, data);
	ret |= call(node->_type.proc.params, data);
	ret |= call(node->_type.proc.ret, data);
	return ret;
}

static int call_on_type_sign(int (*call)(struct ast_node *,
                                         void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_type.sign.params, data);
	ret |= call(node->_type.sign.ret, data);
	return ret;
}

static int call_on_type_enum(int (*call)(struct ast_node *,
                                         void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_type.enu.id, data);
	ret |= call(node->_type.enu.type, data);
	return ret;
}

static int call_on_type_member(int (*call)(struct ast_node *,
                                           void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_type.member.id, data);
	ret |= call(node->_type.member.expr, data);
	return ret;
}

static int call_on_type_generic(int (*call)(struct ast_node *,
                                            void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_type.generic.id, data);
	ret |= call(node->_type.generic.args, data);
	return ret;
}

static int call_on_type(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	switch (node->_type.kind) {
	case AST_TYPE_GENERIC: ret = call_on_type_generic(call, node, data);
		break;
	case AST_TYPE_MEMBER: ret = call_on_type_member(call, node, data);
		break;
	case AST_TYPE_ENUM: ret = call_on_type_enum(call, node, data); break;
	case AST_TYPE_ALIAS: ret = call_on_type_alias(call, node, data); break;
	case AST_TYPE_TRAIT: ret = call_on_type_trait(call, node, data);
		break;
	case AST_TYPE_ID: ret = call_on_type_id(call, node, data); break;
	case AST_TYPE_ARR: ret = call_on_type_arr(call, node, data); break;
	case AST_TYPE_TYPEOF: ret = call_on_type_typeof(call, node, data);
		break;
	case AST_TYPE_UNION: ret = call_on_type_union(call, node, data); break;
	case AST_TYPE_STRUCT: ret = call_on_type_struct(call, node, data);
		break;
	case AST_TYPE_PROC: ret = call_on_type_proc(call, node, data); break;
		break;
	case AST_TYPE_SIGN: ret = call_on_type_sign(call, node, data); break;
	case AST_TYPE_POINTER: break;
	}

	return ret;
}

static int call_on_goto(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	return call(node->_goto.label, data);
}

static int call_on_label(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	return call(node->_label.id, data);
}

static int call_on_binop(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_binop.left, data);
	ret |= call(node->_binop.right, data);
	return ret;
}

static int call_on_unop(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	return call(node->_unop.expr, data);
}

static int call_on_call(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_call.id, data);
	ret |= call(node->_call.args, data);
	return ret;
}

static int call_on_macro(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_macro.id, data);
	ret |= call(node->_macro.params, data);
	ret |= call(node->_macro.body, data);
	return ret;
}

static int call_on_proc(int (*call)(struct ast_node *,
                                    void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_proc.id, data);
	ret |= call(node->_proc.sign, data);
	ret |= call(node->_proc.body, data);
	return ret;
}

static int call_on_block(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	return call(node->_block.body, data);
}

static int call_on_fetch(int (*call)(struct ast_node *,
                                     void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_fetch.id, data);
	ret |= call(node->_fetch.type, data);
	return ret;
}

static int call_on_macro_expansion(int (*call)(struct ast_node *, void *), struct ast_node *node, void *data)
{
	int ret = 0;
	ret |= call(node->_macro_expansion.id, data);
	ret |= call(node->_macro_expansion.args, data);
	return ret;
}

/* I guess this works, but it's not exactly optimal as the caller sort of has to
 * know when to continue to call on, and when it would cause an infinite loop.
 * I.e. a call on an ID that is forwarded results in an infinite loop.
 *
 * Maybe add in something like ast_continue_call_on() that can check for the
 * user if there's any point in continuing?
 */
int ast_call_on(int (*call)(struct ast_node *,
                            void *), struct ast_node *node, void *data)
{
	int ret = 0;
	if (!node)
		return ret;

	switch (node->node_type) {
	case AST_FETCH: ret = call_on_fetch(call, node, data); break;
	case AST_UNION: ret = call_on_union(call, node, data); break;
	case AST_ASSIGN: ret = call_on_assign(call, node, data); break;
	case AST_INIT: ret = call_on_init(call, node, data); break;
	case AST_SIZEOF: ret = call_on_sizeof(call, node, data); break;
	case AST_DOT: ret = call_on_dot(call, node, data); break;
	case AST_AS: ret = call_on_as(call, node, data); break;
	case AST_CAST: ret = call_on_cast(call, node, data); break;
	case AST_DEFER: ret = call_on_defer(call, node, data); break;
	case AST_VAR: ret = call_on_var(call, node, data); break;
	case AST_FOR: ret = call_on_for(call, node, data); break;
	case AST_WHILE: ret = call_on_while(call, node, data); break;
	case AST_RETURN: ret = call_on_return(call, node, data); break;
	case AST_ALIAS: ret = call_on_alias(call, node, data); break;
	case AST_TRAIT: ret = call_on_trait(call, node, data); break;
	case AST_IF: ret = call_on_if(call, node, data); break;
	case AST_ENUM: ret = call_on_enum(call, node, data); break;
	case AST_STRUCT: ret = call_on_struct(call, node, data); break;
	case AST_VAL: ret = call_on_val(call, node, data); break;
	case AST_SWITCH: ret = call_on_switch(call, node, data); break;
	case AST_CASE: ret = call_on_case(call, node, data); break;
	case AST_TYPE: ret = call_on_type(call, node, data); break;
	case AST_GOTO: ret = call_on_goto(call, node, data); break;
	case AST_LABEL: ret = call_on_label(call, node, data); break;
	case AST_BINOP: ret = call_on_binop(call, node, data); break;
	case AST_UNOP: ret = call_on_unop(call, node, data); break;
	case AST_CALL: ret = call_on_call(call, node, data); break;
	case AST_MACRO: ret = call_on_macro(call, node, data); break;
	case AST_MACRO_EXPANSION: ret = call_on_macro_expansion(call, node, data); break;
	case AST_PROC: ret = call_on_proc(call, node, data); break;
	case AST_BLOCK: ret = call_on_block(call, node, data); break;
	case AST_LAST: break;
	case AST_EMBED: break;
	case AST_CTRL: break;
	case AST_IMPORT: break;
	case AST_CONST: break;
	case AST_ID: break;
	case AST_EMPTY: break;
	}

	ret |= call(node->next, data);
	return ret;
}

size_t ast_list_len(struct ast_node *node)
{
	size_t count = 0;
	while (node) {
		count++;
		node = node->next;
	}

	return count;
}

struct ast_node *ast_last_node(struct ast_node *list)
{
	if (!list)
		return NULL;

	while (list->next)
		list = list->next;

	return list;
}

struct ast_node *ast_block_last(struct ast_node *block)
{
	struct ast_node *b = ast_last_node(block);
	if (b && b->node_type == AST_BLOCK)
		return ast_block_last(b->_block.body);

	return b;
}

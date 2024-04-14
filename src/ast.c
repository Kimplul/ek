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
#include <ek/vec.h>
#include <ek/scope.h>

static struct vec nodes = {0};
static struct vec types = {0};

static void destroy_ast_node(struct ast *n)
{
	if (!n)
		return;

	if (n->s)
		free(n->s);

	free(n);
}

static void destroy_type(struct type *n)
{
	if (!n)
		return;

	if (n->id)
		free(n->id);

	free(n);
}

void destroy_ast_nodes()
{
	foreach_vec(ni, nodes) {
		struct ast *n = vect_at(struct ast *, nodes, ni);
		destroy_ast_node(n);
	}

	vec_destroy(&nodes);
}

void destroy_types()
{
	foreach_vec(ti, types) {
		struct type *t = vect_at(struct type *, types, ti);
		destroy_type(t);
	}

	vec_destroy(&types);
}

void destroy_allocs()
{
	destroy_ast_nodes();
	destroy_types();
}

static struct ast *create_empty_ast()
{
	if (vec_uninit(nodes)) {
		nodes = vec_create(sizeof(struct ast *));
	}

	struct ast *n = calloc(1, sizeof(struct ast));
	/* just to be safe */
	n->k = AST_EMPTY;
	vect_append(struct ast *, nodes, &n);
	return n;
}

static struct type *create_empty_type()
{
	if (vec_uninit(types)) {
		types = vec_create(sizeof(struct type *));
	}

	struct type *n = calloc(1, sizeof(struct type));
	/* just to be safe */
	n->k = TYPE_VOID;
	n->size = -1;
	vect_append(struct ast *, types, &n);
	return n;
}

struct ast *gen_ast(enum ast_kind kind,
                    struct ast *a0,
                    struct ast *a1,
                    struct ast *a2,
                    struct ast *a3,
                    struct type *t2,
                    char *s,
                    long long v,
                    struct src_loc loc)
{
	struct ast *n = create_empty_ast();
	n->k = kind;
	n->a0 = a0;
	n->a1 = a1;
	n->a2 = a2;
	n->a3 = a3;
	n->t2 = t2;
	n->s = s;
	n->v = v;
	n->loc = loc;
	return n;
}

struct type *tgen_type(enum type_kind kind,
                       struct type *t0,
                       struct type *t1,
                       struct ast *d,
                       struct ast *a,
                       char *id,
                       struct src_loc loc)
{
	struct type *n = create_empty_type();
	n->k = kind;
	n->t0 = t0;
	n->t1 = t1;
	n->d = d;
	n->a = a;
	n->id = id;
	n->loc = loc;
	return n;
}

void ast_set_flags(struct ast *node, enum ast_flags flags)
{
	node->f |= flags;
}

void ast_clear_flags(struct ast *node, enum ast_flags flags)
{
	node->f &= ~(flags);
}

unsigned ast_flags(struct ast *node, enum ast_flags flags)
{
	return node->f & flags;
}

void ast_append(struct ast *list, struct ast *elem)
{
	struct ast *cur = list;
	while (cur->n)
		cur = cur->n;

	cur->n = elem;
}

struct ast *ast_prepend(struct ast *list, struct ast *elem)
{
	elem->n = list;
	return elem;
}

void type_append(struct type *list, struct type *elem)
{
	struct type *cur = list;
	while (cur->n)
		cur = cur->n;

	cur->n = elem;
}

struct type *type_prepend(struct type *list, struct type *elem)
{
	elem->n = list;
	return elem;
}

static void dump(int depth, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf("//");
	for (int i = 0; i < depth; ++i)
		printf("  ");

	vprintf(fmt, args);

	va_end(args);
}

const char *primitive_str(struct type *type)
{
	switch (type->k) {
	case TYPE_VOID: return "void";
	case TYPE_I9: return "i9";
	case TYPE_I27: return "i27";
	case TYPE_BOOL: return "bool";
	default: return "unimp";
	}

	return "unimp";
}

void ast_dump(int depth, struct ast *n)
{
	if (!n) {
		dump(depth, "{NULL}\n");
		return;
	}

#define DUMP(x) case x: dump(depth, #x); break;
	switch (n->k) {
	DUMP(AST_FETCH);
	DUMP(AST_INIT);
	DUMP(AST_ASSIGN);
	DUMP(AST_CALL);
	DUMP(AST_ARR);
	DUMP(AST_SIZEOF);
	DUMP(AST_CAST);
	DUMP(AST_DEFER);
	DUMP(AST_MACRO_DEF);
	DUMP(AST_MACRO_EXPAND);
	DUMP(AST_TYPE_EXPAND);
	DUMP(AST_PROC_DEF);
	DUMP(AST_GOTO);
	DUMP(AST_LABEL);
	DUMP(AST_VAR_DEF);
	DUMP(AST_FOR);
	DUMP(AST_EMBED);
	DUMP(AST_DOT);
	DUMP(AST_WHILE);
	DUMP(AST_DO_WHILE);
	DUMP(AST_BREAK);
	DUMP(AST_CONTINUE);
	DUMP(AST_RETURN);
	DUMP(AST_ALIAS_DEF);
	DUMP(AST_TRAIT_DEF);
	DUMP(AST_STRUCT_DEF);
	DUMP(AST_IF);
	DUMP(AST_BLOCK);
	DUMP(AST_IMPORT);
	DUMP(AST_ENUM_DEF);
	DUMP(AST_VAL);
	DUMP(AST_SWITCH);
	DUMP(AST_CASE);
	DUMP(AST_ID);
	DUMP(AST_AS);
	DUMP(AST_EMPTY);
	DUMP(AST_ADD);
	DUMP(AST_SUB);
	DUMP(AST_MUL);
	DUMP(AST_DIV);
	DUMP(AST_REM);
	DUMP(AST_LAND);
	DUMP(AST_LOR);
	DUMP(AST_LSHIFT);
	DUMP(AST_RSHIFT);
	DUMP(AST_ASSIGN_ADD);
	DUMP(AST_ASSIGN_SUB);
	DUMP(AST_ASSIGN_MUL);
	DUMP(AST_ASSIGN_DIV);
	DUMP(AST_ASSIGN_REM);
	DUMP(AST_ASSIGN_LSHIFT);
	DUMP(AST_ASSIGN_RSHIFT);
	DUMP(AST_LT);
	DUMP(AST_GT);
	DUMP(AST_LE);
	DUMP(AST_GE);
	DUMP(AST_NE);
	DUMP(AST_EQ);
	DUMP(AST_NEG);
	DUMP(AST_LNOT);
	DUMP(AST_NOT);
	DUMP(AST_REF);
	DUMP(AST_DEREF);
	DUMP(AST_CONST_INT);
	DUMP(AST_CONST_CHAR);
	DUMP(AST_CONST_BOOL);
	DUMP(AST_CONST_STR);
	}
#undef DUMP

	depth++;

	if (n->t) {
		printf(" ("); type_dump_list(n->t); printf(")");
	}

	if (n->t2)
		type_dump_list(n->t2);

	printf("\n");

	if (n->s)
		dump(depth, "%s\n", n->s);

	if (is_const(n))
		dump(depth, "%lli\n", n->v);

	if (n->a0)
		ast_dump_list(depth, n->a0);

	if (n->a1)
		ast_dump_list(depth, n->a1);

	if (n->a2)
		ast_dump_list(depth, n->a2);

	if (n->a3)
		ast_dump_list(depth, n->a3);
}

void ast_dump_list(int depth, struct ast *root)
{
	if (!root) {
		dump(depth, "{NULL}\n");
		return;
	}

	foreach_node(n, root) {
		ast_dump(depth, n);
	}
}

void type_dump(struct type *n)
{
	if (!n) {
		printf(" {NULL}");
		return;
	}

	printf(" ");

#define DUMP(x) case x: printf(#x); break;
	switch (n->k) {
	DUMP(TYPE_VOID);
	DUMP(TYPE_BOOL);
	DUMP(TYPE_I9);
	DUMP(TYPE_I27);
	DUMP(TYPE_STR);
	DUMP(TYPE_PTR);
	DUMP(TYPE_ID);
	DUMP(TYPE_CONSTRUCT);
	DUMP(TYPE_STRUCT);
	DUMP(TYPE_ENUM);
	DUMP(TYPE_CALLABLE);
	DUMP(TYPE_TRAIT);
	}
}

void type_dump_list(struct type *root)
{
	if (!root)
		return;

	foreach_type(t, root) {
		type_dump(t);
	}
}

struct ast *clone_ast(struct ast *n)
{
	if (!n)
		return NULL;

	assert(n->k);
	struct ast *new = create_empty_ast();
	new->scope = n->scope;
	new->uses = n->uses;
	new->loc = n->loc;
	new->k = n->k;
	new->v = n->v;
	new->f = n->f;

	/* unsure if this should be a separate step maybe? Generally this is
	 * unwanted, but I might run into exceptions and then it's more
	 * difficult to rebuild the init/actual state... */
	ast_clear_flags(new, AST_FLAG_INIT | AST_FLAG_ACTUAL);

	if (n->t)
		new->t = clone_type_list(n->t);

	if (n->s)
		new->s = strdup(n->s);

	if (n->a0)
		new->a0 = clone_ast_list(n->a0);

	if (n->a1)
		new->a1 = clone_ast_list(n->a1);

	if (n->a2)
		new->a2 = clone_ast_list(n->a2);

	if (n->a3)
		new->a3 = clone_ast_list(n->a3);

	if (n->t2)
		new->t2 = clone_type_list(n->t2);

	return new;
}

struct type *clone_type(struct type *n)
{
	if (!n)
		return NULL;

	assert(n->k);
	struct type *new = create_empty_type();
	new->scope = n->scope;
	new->loc = n->loc;
	new->k = n->k;
	new->a = n->a;
	new->d = n->d;

	if (n->id)
		new->id = strdup(n->id);

	if (n->t0)
		new->t0 = clone_type_list(n->t0);

	if (n->t1)
		new->t1 = clone_type_list(n->t1);

	return new;
}

struct ast *clone_ast_list(struct ast *root)
{
	struct ast *n = root, *new_root = NULL, *prev = NULL;
	while (n) {
		struct ast *new = clone_ast(n);

		if (prev) prev->n = new;
		else new_root = new;

		prev = new;
		n = n->n;
	}

	return new_root;
}

struct type *clone_type_list(struct type *root)
{
	struct type *n = root, *new_root = NULL, *prev = NULL;
	while (n) {
		struct type *new = clone_type(n);

		if (prev) prev->n = new;
		else new_root = new;

		prev = new;
		n = n->n;
	}

	return new_root;
}

int type_visit(type_callback_t before, type_callback_t after, struct type *n,
               void *d)
{
	int ret = 0;
	if (!n)
		return ret;

	if (before && (ret = before(n, d)))
		return ret;

	if (n->t0 && (ret = type_visit_list(before, after, n->t0, d)))
		return ret;

	if (n->t1 && (ret = type_visit_list(before, after, n->t1, d)))
		return ret;

	if (after && (ret = after(n, d)))
		return ret;

	return ret;
}

int ast_visit(ast_callback_t before, ast_callback_t after, struct ast *n,
              void *d)
{
	int ret = 0;
	if (!n)
		return ret;

	if (before && (ret = before(n, d)))
		return ret;

	if (n->a0 && (ret = ast_visit_list(before, after, n->a0, d)))
		return ret;

	if (n->a1 && (ret = ast_visit_list(before, after, n->a1, d)))
		return ret;

	if (n->a2 && (ret = ast_visit_list(before, after, n->a2, d)))
		return ret;

	if (n->a3 && (ret = ast_visit_list(before, after, n->a3, d)))
		return ret;

	if (after && (ret = after(n, d)))
		return ret;

	return ret;
}

int ast_visit_list(ast_callback_t before, ast_callback_t after, struct ast *l,
                   void *d)
{
	int ret = 0;
	foreach_node(n, l) {
		if ((ret = ast_visit(before, after, n, d)))
			return ret;
	}

	return ret;
}

int type_visit_list(type_callback_t before, type_callback_t after,
                    struct type *l, void *d)
{
	int ret = 0;
	foreach_type(n, l) {
		if ((ret = type_visit(before, after, n, d)))
			return ret;
	}

	return ret;
}

size_t ast_list_len(struct ast *node)
{
	size_t count = 0;
	while (node) {
		count++;
		node = node->n;
	}

	return count;
}

struct ast *ast_last(struct ast *list)
{
	if (!list)
		return NULL;

	while (list->n)
		list = list->n;

	return list;
}

struct ast *ast_block_last(struct ast *block)
{
	struct ast *b = ast_last(block);
	if (b && b->k == AST_BLOCK)
		return ast_block_last(block_body(b));

	return b;
}

int same_id(char *id1, char *id2)
{
	return strcmp(id1, id2) == 0;
}

int equiv_types(struct type *n1, struct type *n2)
{
	if (n1 == n2)
		return 1;

	if (n1 && !n2)
		return 0;

	if (!n1 && n2)
		return 0;

	if (n1->k != n2->k)
		return 0;

	if (n1->id && strcmp(n1->id, n2->id) != 0)
		return 0;

	if (n1->t0 && !equiv_type_lists(n1->t0, n2->t0))
		return 0;

	if (n1->t1 && !equiv_type_lists(n1->t1, n2->t1))
		return 0;

	return 1;
}

int equiv_nodes(struct ast *n1, struct ast *n2)
{
	if (n1 && !n2)
		return 0;

	if (!n1 && n2)
		return 0;

	if (!n1 && !n2)
		return 1;

	if (n1->k != n2->k)
		return 0;

	if (n1->s && strcmp(n1->s, n2->s) != 0)
		return 0;

	if (n1->a0 && !equiv_node_lists(n1->a0, n2->a0))
		return 0;

	if (n1->a1 && !equiv_node_lists(n1->a1, n2->a1))
		return 0;

	if (n1->a2 && !equiv_node_lists(n1->a2, n2->a2))
		return 0;

	if (n1->a3 && !equiv_node_lists(n1->a3, n2->a3))
		return 0;

	if (n1->t2 && !equiv_type_lists(n1->t2, n2->t2))
		return 0;

	return 1;
}

int equiv_node_lists(struct ast *c1, struct ast *c2)
{
	do {
		if (!equiv_nodes(c1, c2))
			return 0;

		c1 = c1->n;
		c2 = c2->n;

	} while (c1 && c2);

	return 1;
}

int equiv_type_lists(struct type *t1, struct type *t2)
{
	do {
		if (!equiv_types(t1, t2))
			return 0;

		t1 = t1->n;
		t2 = t2->n;

	} while (t1 && t2);

	return 1;
}

size_t align3k(size_t o)
{
	size_t rem = o % 3;
	if (rem)
		o += rem;

	return o;
}

static size_t struct_size(struct type *t)
{
	if (t->size != -1)
		return (size_t)t->size;

	size_t size = 0;
	foreach_node(n, struct_body(t->d)) {
		if (n->k != AST_VAR_DEF)
			continue;

		size_t sz = type_size(n->t);
		if (sz > 2)
			size = align3k(size);

		size += sz;
	}

	size = align3k(size);
	t->size = (ssize_t)size;
	return size;
}

size_t type_size(struct type *t)
{
	switch (t->k) {
	case TYPE_I9: return 1;
	case TYPE_I27: return 3;
	case TYPE_PTR: return 3;
	case TYPE_STRUCT: return struct_size(t);
	default:
	}

	assert(0 && "unhandled type to get size of");
	abort();
}

size_t type_offsetof(struct type *t, char *m)
{
	assert(t->k == TYPE_STRUCT);

	size_t offset = 0;
	foreach_node(n, struct_body(t->d)) {
		if (n->k != AST_VAR_DEF)
			continue;

		if (same_id(var_id(n), m))
			break;

		size_t size = type_size(n->t);
		if (size > 2)
			offset = align3k(offset);

		offset += size;
	}

	return offset;
}

/* SPDX-License-Identifier: copyleft-next-0.3.1 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include <ek/lower.h>
#include <ek/scope.h>
#include <ek/vec.h>

#define UNUSED(x) (void)x

enum retval_kind {
	REG_I27,
	REG_I9,
	CONST_I9,
	CONST_I27,
};

struct retval {
	enum retval_kind kind;
	char *s;
};

struct lower_state {
	struct vec top;
	struct vec bottom;
	struct vec out;
	int64_t uniq;

	struct vec dealloc;
	size_t deallocs;
};

static struct lower_state create_state()
{
	struct lower_state state;
	state.top = vec_create(sizeof(char *));
	state.bottom = vec_create(sizeof(char *));
	state.out = vec_create(sizeof(char *));
	state.dealloc = vec_create(sizeof(char *));
	state.deallocs = 0;
	state.uniq = 0;
	return state;
}

static void destroy_state(struct lower_state *state)
{
	assert(vec_len(&state->top) == 0);
	assert(vec_len(&state->bottom) == 0);
	assert(vec_len(&state->out) == 0);
	assert(vec_len(&state->dealloc) == 0);

	vec_destroy(&state->top);
	vec_destroy(&state->bottom);
	vec_destroy(&state->out);
	vec_destroy(&state->dealloc);
}

static void add_dealloc(struct lower_state *s, char *dealloc)
{
	vect_append(char *, s->dealloc, &dealloc);
}

static void push_loop(struct lower_state *s, char *top, char *bottom, char *out)
{
	vect_append(char *, s->top, &top);
	vect_append(char *, s->bottom, &bottom);
	vect_append(char *, s->out, &out);
}

static void pop_loop(struct lower_state *s)
{
	char *top = vect_pop(char *, s->top);
	char *bottom = vect_pop(char *, s->bottom);
	char *out = vect_pop(char *, s->out);

	free(top);
	free(bottom);
	free(out);
}

#define label_peek(v) \
	vect_back(char *, v)

static int64_t retval_width(struct retval r)
{
	switch (r.kind) {
	case REG_I27: return 3;
	case REG_I9: return 1;
	case CONST_I9: return 1;
	case CONST_I27: return 3;
	default: abort();
	}

	return 0;
}

static const char *retval_kind_str(enum retval_kind kind)
{
	switch (kind) {
	case REG_I27: return "i27";
	case REG_I9: return "i9";
	case CONST_I9: return "i9";
	case CONST_I27: return "i27";
	default: abort();
	}

	return 0;
}

static const char *retval_type_str(struct retval r)
{
	/* I guess it saves a bit on typing? */
	return retval_kind_str(r.kind);
}

static bool retval_is_const(struct retval r)
{
	return r.kind == CONST_I9 || r.kind == CONST_I27;
}

static bool is_small_type(struct type *type)
{
	switch (type->k) {
	case TYPE_I9:
	case TYPE_BOOL:
		return true;

	default:
	}

	return false;
}

#define retval_create() \
	(struct retval){0, NULL}

static void retval_destroy(struct retval *retval)
{
	free(retval->s);
}

static struct retval build_retval(enum retval_kind kind, char *s)
{
	return (struct retval){.kind = kind, .s = s};
}

static void strvec_destroy(struct vec *v)
{
	foreach_vec(vi, *v) {
		char *s = vect_at(char *, *v, vi);
		free(s);
	}

	vec_destroy(v);
}

static __attribute__((format (printf, 1, 2)))
char *build_str(const char *fmt, ...) {
	va_list args1, args2;
	va_start(args1, fmt);
	va_copy(args2, args1);

	/* I don't expect this to fail, although I guess it could */
	size_t size = (size_t)vsnprintf(NULL, 0, fmt, args1);
	va_end(args1);

	char *buf = malloc(size + 1);
	vsnprintf(buf, size + 1, fmt, args2);

	va_end(args2);
	return buf;
}

static char *mangle_scope(struct ast *id, struct scope *s)
{
	return build_str("%s_s%zi", id->s, s->number);
}

static char *mangle(struct ast *id)
{
	char *name = id->s;
	struct ast *def = file_scope_find_symbol(id->scope, name);
	if (ast_flags(def, AST_FLAG_NOMANGLE))
		return strdup(name);

	return mangle_scope(id, def->scope);
}

typedef int (*visit_struct_t)(struct lower_state *s, struct ast *n, size_t o,
                              void *d);
static ssize_t visit_struct(struct lower_state *s, struct ast *def, size_t base,
                            visit_struct_t cb, void *data)
{
	size_t offset = (size_t)base;
	foreach_node(n, struct_body(def)) {
		if (n->k != AST_VAR_DEF)
			continue;

		struct type *t = n->t;
		if (t->k == TYPE_STRUCT) {
			ssize_t r = visit_struct(s, t->d, offset, cb, data);
			if (r < 0)
				return -1;

			offset += (size_t)r;
			continue;
		}

		if (cb(s, n, offset, data))
			return -1;

		size_t size = type_size(t);
		if (size > 2)
			offset = align3k(offset);

		offset += size;
	}

	assert((offset - base) == type_size(def->t));
	return (ssize_t)offset;
}

static int lower_expr(struct lower_state *s, struct ast *e,
                      struct retval *retval);
static int lower_statement(struct lower_state *s, struct ast *n);

static void output_ast_id(struct ast *id)
{
	assert(id->s);
	char *name = mangle(id);
	printf("%s", name);
	free(name);
}

static int lower_global_var(struct ast *n)
{
	/* trivial types are reasonably easy, but stuff like compound types need
	 * a lot of work */
	struct type *type = var_type(n);
	if (is_primitive(type)) {
		semantic_error(n->scope->fctx, n,
		               "only primitive globals currently implemented");
		return -1;
	}

	struct ast *init = var_init(n);
	if (init->k != AST_CONST_INT) {
		semantic_error(n->scope->fctx, n,
		               "only constant expressions currently implemented");
		return -1;
	}

	output_ast_id(n);
	printf(" = ");

	/* hmm, this might be useful elsewhere as well */
	char *t = is_small_type(type) ? "i9" : "i27";
	printf("%s %lli", t, int_val(init));
	printf(";\n");
	return 0;
}

static int lower_simple_param(struct lower_state *s, struct ast *p)
{
	UNUSED(s);
	char *t = is_small_type(p->t) ? "i9" : "i27";
	printf("%s ", t);

	if (var_id(p)) output_ast_id(p);
	else printf("tmp%zd", s->uniq++);

	printf(", ");
	return 0;
}

struct struct_param_helper {
	char *name;
	struct vec *fixups;
};

static int collect_struct_param(struct lower_state *s, struct ast *n,
                                size_t offset, struct struct_param_helper *h)
{
	UNUSED(s);
	size_t size = type_size(n->t);
	assert(size == 1 || size == 3);

	char *type = size == 1 ? "i9" : "i27";
	char *pname = build_str("%s_%zd", h->name, offset);

	printf("%s %s, ", type, pname);
	char *f = build_str("%s >> %s %s %zd;\n", pname, type, h->name, offset);
	vect_append(char *, *h->fixups, &f);

	free(pname);
	return 0;
}

static int lower_param(struct lower_state *s, struct ast *p, struct vec *fixups)
{
	UNUSED(s);
	assert(p->k == AST_VAR_DEF);
	assert(var_init(p) == NULL);

	if (is_primitive(p->t) || p->t->k == TYPE_PTR) {
		return lower_simple_param(s, p);
	}

	assert(p->t->k == TYPE_STRUCT);

	char *name = NULL;
	if (var_id(p)) name = mangle(p);
	else name = build_str("tmp%zd", s->uniq++);

	/* alloc param struct */
	size_t size = type_size(p->t);
	char *alloc = build_str("i27 %s = ^ %zd;\n", name, size);
	vect_append(char *, *fixups, &alloc);

	struct struct_param_helper h = {name, fixups};
	int ret = visit_struct(s, p->t->d, 0,
	                       (visit_struct_t)collect_struct_param, &h) < 0;
	free(name);
	return ret;
}

static int lower_params(struct lower_state *s, struct ast *params,
                        struct vec *fixups)
{
	/** @todo fix structs, struct arguments must be stored to some
	 * structures on the stack */
	foreach_node(p, params) {
		if (lower_param(s, p, fixups))
			return -1;
	}

	return 0;
}

static int lower_var(struct lower_state *s, struct ast *v,
                     struct retval *retval)
{
	assert(v->k == AST_VAR_DEF);
	assert(var_init(v));

	struct retval input = retval_create();
	if (lower_expr(s, var_init(v), &input)) {
		retval_destroy(&input);
		return -1;
	}

	char *name = mangle(v);
	/* if we're a struct, we can just reuse the newly built constant struct,
	 * yay, just rename it */
	printf("i27 %s = %s;\n", name, input.s);
	*retval = build_retval(REG_I27, name);
	retval_destroy(&input);
	return 0;
}

static void do_const_store(struct lower_state *s, struct retval *from,
                           struct retval t, struct retval o)
{
	UNUSED(s);
	/* I know, kind of silly to swap back and forth between string/int but
	 * good enough for now */
	int64_t addr = strtoll(t.s, 0, 0) + strtoll(o.s, 0, 0);
	printf("%s >> %s (%zi);\n", from->s, retval_type_str(*from), addr);
}

static void do_store(struct lower_state *s, struct retval *from,
                     struct retval *to, struct retval *off)
{
	struct retval t = *to;
	struct retval o = build_retval(CONST_I27, "0");
	if (off)
		o = *off;

	if (retval_is_const(t) && retval_is_const(o)) {
		do_const_store(s, from, t, o);
		return;
	}

	if (retval_is_const(t)) {
		/* o must be register, so swap around for the format to make
		 * sense */
		struct retval tmp = t; t = o; o = tmp;
	}

	assert(retval_is_const(o));

	int64_t addr = strtoll(o.s, 0, 0);
	/* doesn't really take into account possible padding etc, should
	 * probably fix at some point */
	printf("%s >> %s %s %zi;\n", from->s, retval_type_str(*from), t.s,
	       addr);
}

static int lower_cast(struct lower_state *s, struct ast *e,
                      struct retval *retval)
{
	assert(e->k == AST_CAST);
	/** @todo make sure actualize removes casts that aren't of these types
	 * */
	assert(is_primitive(e->t));

	if (lower_expr(s, cast_expr(e), retval))
		return -1;

	enum retval_kind kind = is_small_type(e->t) ? REG_I9 : REG_I27;
	/* build new temporary cast result and replace the previous
	 * retval */
	char *cast = build_str("%s%s", "cast", retval->s);

	printf("%s %s = %s;\n", retval_kind_str(kind), cast, retval->s);
	free(retval->s);

	retval->s = cast;
	retval->kind = kind;
	return 0;
}

static int lower_const(struct lower_state *s, struct ast *c,
                       struct retval *retval)
{
	UNUSED(s);
	assert(is_const(c));
	char *str = build_str("%lli", (long long)c->v);
	enum retval_kind kind = is_small_type(c->t) ? CONST_I9: CONST_I27;
	*retval = build_retval(kind, str);
	return 0;
}

static int lower_deref_assign(struct lower_state *s, struct ast *d,
                              struct retval *retval)
{
	struct ast *base = unop_expr(d);
	struct retval loc = retval_create();

	if (lower_expr(s, base, &loc)) {
		retval_destroy(&loc);
		return -1;
	}

	do_store(s, retval, &loc, NULL);
	return 0;
}

static int lower_dot_assign(struct lower_state *s, struct ast *d,
                            struct retval *retval)
{
	struct ast *base = dot_expr(d);
	struct retval loc = retval_create();

	if (lower_expr(s, base, &loc)) {
		retval_destroy(&loc);
		return -1;
	}

	size_t offset = type_offsetof(base->t, dot_id(d));
	if (d->t->k == TYPE_STRUCT) {
		size_t size = type_size(base->t);
		printf("i27 %s%s = %s + %zd;\n", retval->s, dot_id(d),
		       retval->s, offset);
		printf("%s%s <<* %zd %s;\n", retval->s, dot_id(d), size, loc.s);
	}
	else {
		struct retval r = build_retval(CONST_I27,
		                               build_str("%zd", offset));
		do_store(s, retval, &loc, &r);
		retval_destroy(&r);
	}

	retval_destroy(&loc);
	return 0;
}

static int lower_assign(struct lower_state *s, struct ast *a,
                        struct retval *retval)
{
	assert(a->k == AST_ASSIGN);
	if (lower_expr(s, assign_from(a), retval))
		return -1;

	struct retval loc = retval_create();

	struct ast *to = assign_to(a);
	if (to->k == AST_DEREF) {
		return lower_deref_assign(s, to, retval);
	}
	else if (to->k == AST_DOT) {
		return lower_dot_assign(s, to, retval);
	}

	if (lower_expr(s, to, &loc)) {
		retval_destroy(&loc);
		return -1;
	}

	printf("i27 %s = %s;\n", loc.s, retval->s);
	return 0;
}

static int lower_id(struct lower_state *s, struct ast *id,
                    struct retval *retval)
{
	UNUSED(s);
	assert(id->k == AST_ID);
	char *m = mangle(id);

	struct type *type = id->t;
	enum retval_kind kind = is_small_type(type) ? REG_I9 : REG_I27;

	/* this likely isn't enough and we need to add the & to most things we
	 * want to take the address of */
	if (type->k == TYPE_CALLABLE) {
		char *o = m;
		m = build_str("&%s", m);
		free(o);
	}

	*retval = build_retval(kind, m);
	return 0;
}

struct struct_return_helper {
	char *name;
	struct vec *locs;
};

static int lower_struct_return(struct lower_state *s, struct ast *n, size_t o,
                               struct struct_return_helper *h)
{
	UNUSED(s);
	size_t size = type_size(n->t);
	assert(size == 1 || size == 3);

	char *type = size == 1 ? "i9" : "i27";
	char *rname = build_str("%s_%zd", h->name, o);
	vect_append(char *, *h->locs, &rname);
	printf("%s %s << %s %zd;\n", type, rname, h->name, o);
	return 0;
}

static int lower_return(struct lower_state *s, struct ast *r,
                        struct retval *retval)
{
	assert(r->k == AST_RETURN);
	if (!return_expr(r)) {
		printf("=> ();\n");
		return 0;
	}

	/** @todo defers, should they be handled here or in ast? */
	if (lower_expr(s, return_expr(r), retval))
		return -1;

	char *name = retval->s;
	if (is_primitive(r->t) || r->t->k == TYPE_PTR) {
		printf("=> (%s);\n", name);
		return 0;
	}

	assert(r->t->k == TYPE_STRUCT);
	struct vec locs = vec_create(sizeof(char *));
	struct struct_return_helper h = {name, &locs};
	if (visit_struct(s, r->t->d, 0, (visit_struct_t)lower_struct_return,
	                 &h) < 0)
		return -1;

	printf("=> (");
	foreach_vec(li, locs) {
		char *l = vect_at(char *, locs, li);
		printf("%s, ", l);
		free(l);
	}
	vec_destroy(&locs);
	printf(");\n");
	return 0;
}

static int lower_if(struct lower_state *s, struct ast *i,
                    struct retval *retval)
{
	assert(i->k == AST_IF);
	if (lower_expr(s, if_cond(i), retval))
		return -1;

	/* helps readability a little bit */
	long long uniq = s->uniq++;
	printf("if%lli:\n", uniq);

	char *bottom = build_str("if_else%lli", uniq);
	char *out = build_str("if_out%lli", uniq);

	printf("! %s -> %s;\n", retval->s, bottom);

	/* a block counts as a statement in this case */
	if (lower_statement(s, if_body(i))) {
		free(bottom);
		return -1;
	}

	printf("-> %s;\n", out);
	printf("%s:\n", bottom);
	free(bottom);

	if (if_else(i) && lower_statement(s, if_else(i))) {
		free(out);
		return -1;
	}

	printf("%s:\n", out);
	free(out);
	return 0;
}

static int lower_for(struct lower_state *s, struct ast *f,
                     struct retval *retval)
{
	assert(f->k == AST_FOR);
	if (lower_statement(s, for_pre(f)))
		return -1;

	long long uniq = s->uniq++;

	char *top = build_str("for_top%lli", uniq);
	char *bottom = build_str("for_bottom%lli", uniq);
	char *out = build_str("for_out%lli", uniq);

	push_loop(s, top, bottom, out);

	printf("-> %s;\n", out);

	printf("%s:\n", top);
	if (lower_statement(s, for_body(f))) {
		pop_loop(s);
		return -1;
	}

	printf("%s:\n", bottom);
	if (lower_statement(s, for_post(f))) {
		pop_loop(s);
		return -1;
	}

	printf("%s:\n", out);
	if (lower_expr(s, for_cond(f), retval)) {
		pop_loop(s);
		return -1;
	}

	printf("%s -> %s;\n", retval->s, top);

	pop_loop(s);
	return 0;
}

static int lower_expr_if(struct lower_state *s, struct ast *i,
                         struct retval *retval)
{
	UNUSED(s);
	UNUSED(retval);
	semantic_error(i->scope->fctx, i,
	               "expr if unimplemented");
	return 0;
}

static int lower_binop(struct lower_state *s, struct ast *i,
                       struct retval *retval)
{
	struct retval l = retval_create();
	struct retval r = retval_create();

	if (lower_expr(s, binop_left(i), &l)) {
		retval_destroy(&l);
		retval_destroy(&r);
		return -1;
	}

	if (lower_expr(s, binop_right(i), &r)) {
		retval_destroy(&l);
		retval_destroy(&r);
		return -1;
	}


	char *name = build_str("binop%lli", (long long)s->uniq++);
	*retval = build_retval(REG_I27, name);

	char *op = "";
	switch (i->k) {
	case AST_ADD: op = "+"; break;
	case AST_SUB: op = "-"; break;
	case AST_MUL: op = "*"; break;
	case AST_DIV: op = "/"; break;
	case AST_REM: op = "%"; break;
	case AST_LSHIFT: op = "<<"; break;
	case AST_RSHIFT: op = ">>"; break;
	default: semantic_error(i->scope->fctx, i,
		                "unimplemented binary operation");
		retval_destroy(&l);
		retval_destroy(&r);
		return -1;
	}

	printf("i27 %s = %s %s %s;\n", name, l.s, op, r.s);

	retval_destroy(&l);
	retval_destroy(&r);
	return 0;
}

static int lower_comparison(struct lower_state *s, struct ast *i,
                            struct retval *retval)
{
	/* very similar to lower_binop, hmm */
	struct retval l = retval_create();
	struct retval r = retval_create();

	if (lower_expr(s, comparison_left(i), &l)) {
		retval_destroy(&l);
		retval_destroy(&r);
		return -1;
	}

	if (lower_expr(s, comparison_right(i), &r)) {
		retval_destroy(&l);
		retval_destroy(&r);
		return -1;
	}

	char *name = build_str("comp%lli", (long long)s->uniq++);
	*retval = build_retval(REG_I27, name);

	char *op = "";
	switch (i->k) {
	case AST_LT: op = "<"; break;
	case AST_GT: op = ">"; break;
	case AST_LE: op = "<="; break;
	case AST_GE: op = ">="; break;
	case AST_NE: op = "!="; break;
	case AST_EQ: op = "=="; break;
	default: semantic_error(i->scope->fctx, i,
		                "unimplemented comparison operation");
		retval_destroy(&l);
		retval_destroy(&r);
		return -1;
	}

	printf("i9 %s = %s %s %s;\n", name, l.s, op, r.s);

	retval_destroy(&l);
	retval_destroy(&r);
	return 0;
}

static int lower_simple_arg(struct lower_state *s, struct ast *c,
                            struct vec *retval)
{
	struct retval arg = retval_create();
	if (lower_expr(s, c, &arg)) {
		retval_destroy(&arg);
		return -1;
	}

	vec_append(retval, &arg);
	return 0;
}

struct struct_arg_helper {
	char *name;
	struct vec *args;
};

static int collect_struct_arg(struct lower_state *s, struct ast *n,
                              size_t offset, struct struct_arg_helper *h)
{
	size_t size = type_size(n->t);
	assert(size == 1 || size == 3);

	char *type = size == 1 ? "i9" : "i27";
	char *tmp = build_str("callstruct_%zd", s->uniq++);
	printf("%s %s << %s %zd;\n", type, tmp, h->name, offset);

	struct retval r = build_retval(size == 1 ? REG_I9 : REG_I27, tmp);
	vect_append(struct retval, *h->args, &r);
	return 0;
}

static int lower_struct_arg(struct lower_state *s, struct ast *c,
                            struct vec *args)
{
	struct retval arg = retval_create();
	if (lower_expr(s, c, &arg)) {
		retval_destroy(&arg);
		return -1;
	}

	struct ast *def = c->t->d;
	char *name = arg.s;
	struct struct_arg_helper h = {name, args};
	int ret = visit_struct(s, def, 0, (visit_struct_t)collect_struct_arg,
	                       &h) < 0;
	retval_destroy(&arg);
	return ret;
}

struct struct_retval_helper {
	char *rbuf;
	struct vec *stores;
};

static int collect_struct_retval(struct lower_state *s, struct ast *n,
                                 size_t offset, struct struct_retval_helper *h)
{
	size_t size = type_size(n->t);
	assert(size == 1 || size == 3);

	char *type = size == 1 ? "i9" : "i27";
	char *tmp = build_str("callret_%zd", s->uniq++);
	printf("%s, ", tmp);

	char *store = build_str("%s >> %s %s %zd;\n", tmp, type, h->rbuf,
	                        offset);
	vect_append(char *, *h->stores, &store);
	free(tmp);
	return 0;
}

static void lower_struct_retval(struct lower_state *s, struct type *rtype,
                                char *rbuf, struct retval *retval)
{
	struct ast *def = rtype->d;
	struct vec stores = vec_create(sizeof(char *));

	printf("(");
	struct struct_retval_helper h = {rbuf, &stores};
	if (visit_struct(s, def, 0, (visit_struct_t)collect_struct_retval,
	                 &h) < 0) {
		vec_destroy(&stores);
		return;
	}
	printf(");\n");

	foreach_vec(si, stores) {
		char *store = vect_at(char *, stores, si);
		printf("%s", store);
		free(store);
	}
	vec_destroy(&stores);

	*retval = build_retval(REG_I27, rbuf);
}

static void lower_simple_retval(struct lower_state *s, struct type *rtype,
                                struct retval *retval)
{
	char *name = build_str("rv_%zd", s->uniq++);
	printf("(%s);\n", name);
	*retval = build_retval(is_small_type(rtype) ? REG_I9 : REG_I27, name);
}

static int lower_call(struct lower_state *s, struct ast *c,
                      struct retval *retval)
{
	assert(c->k == AST_CALL);

	struct retval call = retval_create();
	if (lower_expr(s, call_expr(c), &call)) {
		retval_destroy(&call);
		return -1;
	}

	struct type *rtype = callable_rtype((call_expr(c))->t);
	char *rbuf = NULL;
	if (rtype->k == TYPE_STRUCT) {
		rbuf = build_str("rbuf_%zd", s->uniq++);
		printf("i27 %s = ^ %zd;\n", rbuf, type_size(rtype));
	}

	/* collect all args */
	struct vec args = vec_create(sizeof(struct retval));
	foreach_node(a, call_args(c)) {
		if (a->t->k == TYPE_STRUCT) {
			if (lower_struct_arg(s, a, &args)) {
				strvec_destroy(&args);
				return -1;
			}

			continue;
		}

		if (lower_simple_arg(s, a, &args)) {
			strvec_destroy(&args);
			return -1;
		}
	}

	printf("%s (", call.s);
	retval_destroy(&call);

	foreach_vec(ai, args) {
		struct retval r = vect_at(struct retval, args, ai);
		printf("%s, ", r.s);
		free(r.s);
	}
	vec_destroy(&args);

	printf(") => ");

	if (rtype->k == TYPE_STRUCT) {
		lower_struct_retval(s, rtype, rbuf, retval);
	}
	else if (rtype->k != TYPE_VOID) {
		lower_simple_retval(s, rtype, retval);
	}
	else {
		printf("();\n");
	}

	return 0;
}

static int lower_init(struct lower_state *s, struct ast *init,
                      struct retval *retval)
{
	assert(init->k == AST_INIT);
	char *name = build_str("init_%zi", s->uniq++);
	size_t size = type_size(init->t);
	assert(size % 3 == 0);

	/* alloc stack space for struct */
	printf("i27 %s = ^ %zi;\n", name, size);

	char *dealloc = build_str("^^ %zi;\n", size);
	add_dealloc(s, dealloc);

	foreach_node(n, init_body(init)) {
		struct retval val = retval_create();
		if (lower_expr(s, var_init(n), &val)) {
			retval_destroy(&val);
			return -1;
		}

		size_t size = type_size(n->t);
		size_t offset = type_offsetof(init->t, var_id(n));
		printf("i27 %soff = %s + %zi;\n", name, name, offset);

		char *type = is_small_type(n->t) ? "i9" : "i27";
		if (n->t->k == TYPE_STRUCT)
			printf("%soff <<* %zi %s;\n", name, size, val.s);
		else
			printf("%s >> %s %soff 0;\n", val.s, type, name);

		retval_destroy(&val);
	}

	*retval = build_retval(REG_I27, name);
	return 0;
}

static int lower_fetch(struct lower_state *s, struct ast *f,
                       struct retval *retval)
{
	UNUSED(s);
	/* at this point all fetches should exclusively be about fetching a
	 * specific function from a struct */
	assert(f->k == AST_FETCH);
	assert(f->t->k == TYPE_CALLABLE);

	struct ast *def = (fetch_type(f))->d;
	assert(def);

	struct ast *proc = scope_find_proc(def->scope, fetch_id(f));
	assert(proc);

	char *name = mangle(proc);
	char *fetch = build_str("&%s", name);
	*retval = build_retval(REG_I27, fetch);
	free(name);
	return 0;
}

static int lower_ref(struct lower_state *s, struct ast *r,
                     struct retval *retval)
{
	assert(r->k == AST_REF);
	struct retval input = retval_create();
	if (lower_expr(s, unop_expr(r), &input))
		return -1;

	/* structs are internally references anyway */
	if (unop_expr(r)->t->k == TYPE_STRUCT) {
		*retval = input;
		return 0;
	}

	char *ref = build_str("ref%lli", (long long)s->uniq++);
	printf("i27 %s = %s;\n", ref, input.s);

	*retval = build_retval(REG_I27, ref);
	retval_destroy(&input);
	return 0;
}

static int lower_deref(struct lower_state *s, struct ast *d,
                       struct retval *retval)
{
	assert(d->k == AST_DEREF);
	struct ast *expr = unop_expr(d);
	struct retval input = retval_create();
	if (lower_expr(s, expr, &input)) {
		retval_destroy(&input);
		return -1;
	}

	assert(expr->t->k == TYPE_PTR);

	/* structs are internally handled as pointers so don't do anything */
	if (d->t->k == TYPE_STRUCT) {
		*retval = input;
		return 0;
	}

	char *base = input.s;
	char *name = build_str("deref_%zd", s->uniq++);
	char *type = is_small_type(expr->t) ? "i9" : "i27";
	printf("%s %s = << %s 0;\n", type, name, base);

	retval_destroy(&input);

	*retval = build_retval(is_small_type(expr->t) ? REG_I9 : REG_I27, name);
	return 0;
}

static int lower_dot(struct lower_state *s, struct ast *d,
                     struct retval *retval)
{
	assert(d->k == AST_DOT);
	assert((dot_expr(d))->t->k == TYPE_STRUCT);

	struct retval input;
	if (lower_expr(s, dot_expr(d), &input))
		return -1;

	struct type *type = d->t;
	size_t off = type_offsetof((dot_expr(d))->t, dot_id(d));
	char *name = build_str("dot_%zd", s->uniq++);
	char *base = input.s;

	struct retval r;
	if (type->k == TYPE_STRUCT) {
		size_t size = type_size(type);
		printf("i27 %s = ^ %zd;\n", name, type_size(type));
		printf("i27 %soff = %s + %zd;\n", name, base, off);
		printf("%s <<* %zd %soff;\n", name, size, name);
		r = build_retval(REG_I27, name);
	}
	else {
		char *t = is_small_type(type) ? "i9" : "i27";
		printf("%s %s << %s %zd;\n", t, name, base, off);
		r = build_retval(is_small_type(type) ? REG_I9 : REG_I27, name);
	}

	retval_destroy(&input);
	*retval = r;
	return 0;
}

static int lower_expr(struct lower_state *s, struct ast *e,
                      struct retval *retval)
{
	if (!e)
		return 0;

	if (is_const(e))
		return lower_const(s, e, retval);

	if (is_binop(e))
		return lower_binop(s, e, retval);

	if (is_comparison(e))
		return lower_comparison(s, e, retval);

	switch (e->k) {
	case AST_VAR_DEF: return lower_var(s, e, retval);
	case AST_INIT: return lower_init(s, e, retval);
	case AST_ID: return lower_id(s, e, retval);
	/* var is considered an expression in this case */
	case AST_CAST: return lower_cast(s, e, retval);
	case AST_RETURN: return lower_return(s, e, retval);
	case AST_ASSIGN: return lower_assign(s, e, retval);
	case AST_CALL: return lower_call(s, e, retval);
	case AST_FETCH: return lower_fetch(s, e, retval);
	/* in the AST, it's useful to think of ref as just a
	 * unary operation, but here it's weird enough that it's
	 * not really worth it */
	case AST_REF: return lower_ref(s, e, retval);
	case AST_DEREF: return lower_deref(s, e, retval);
	case AST_DOT: return lower_dot(s, e, retval);
	case AST_IF: return lower_expr_if(s, e, retval);
	default:
		semantic_error(e->scope->fctx, e,
		               "unhandled expr in lowering");
		return -1;
	}

	return 0;
}

static int lower_block(struct lower_state *s, struct ast *block)
{
	assert(block->k == AST_BLOCK);
	assert(!ast_flags(block, AST_FLAG_DOEXPR));

	/* deallocs_top marks where the dealloc stack was when entering the
	 * block, and deallocs_bottom where the parent block's dealloc stack
	 * is. Stuff like continue and break will probably need this
	 * information, which is why it's attached to lower_state */
	size_t deallocs_top = vec_len(&s->dealloc);
	size_t deallocs_parent = s->deallocs;

	s->deallocs = deallocs_top;
	foreach_node(n, block_body(block)) {
		if (lower_statement(s, n))
			return -1;
	}

	assert(deallocs_top <= vec_len(&s->dealloc));
	s->deallocs = deallocs_parent;

	while (vec_len(&s->dealloc) > deallocs_top) {
		/* perform all deallocs that were queued within this block */
		char *dealloc = vect_pop(char *, s->dealloc);

		/* slight hack, top block doesn't need to care about freeing
		* anything as it must return, this sidesteps the case where qbt
		* requires that a return be the last thing in a procedure */
		if (s->deallocs)
			printf("%s", dealloc);

		free(dealloc);
	}

	return 0;
}

static int lower_statement(struct lower_state *s, struct ast *n)
{
	struct retval retval = retval_create();

	int ret = 0;
	switch (n->k) {
	case AST_RETURN: ret = lower_return(s, n, &retval); break;
	case AST_IF: ret = lower_if(s, n, &retval); break;
	case AST_FOR: ret = lower_for(s, n, &retval); break;
	case AST_BLOCK: ret = lower_block(s, n); break;
	case AST_EMPTY: break;
	default: ret = lower_expr(s, n, &retval); break;
	}

	retval_destroy(&retval);
	return ret;
}

static int lower_proc(struct ast *n)
{
	assert(n->k == AST_PROC_DEF);
	/* nobody uses the proc, so no need to do anything */
	if (n->uses == 0 && !ast_flags(n, AST_FLAG_NOMANGLE))
		return 0;

	/* we're just a prototype, no need to do anything */
	if (!proc_body(n))
		return 0;

	if (ast_flags(n, AST_FLAG_LOWERED))
		return 0;

	struct lower_state state = create_state();

	/* name */
	output_ast_id(n);

	/* args */
	printf("(");

	struct vec fixups = vec_create(sizeof(char *));
	if (lower_params(&state, proc_params(n), &fixups)) {
		destroy_state(&state);
		return -1;
	}

	/* no return type currently supported by qbt */
	printf(")\n");

	/* body */
	printf("{\n");

	foreach_vec(fi, fixups) {
		char *f = vect_at(char *, fixups, fi);
		printf("%s", f);
		free(f);
	}

	vec_destroy(&fixups);

	if (lower_block(&state, proc_body(n))) {
		destroy_state(&state);
		return -1;
	}

	printf("}\n");
	destroy_state(&state);
	ast_set_flags(n, AST_FLAG_LOWERED);
	return 0;
}

static int lower_struct(struct ast *s)
{
	if (ast_flags(s, AST_FLAG_LOWERED))
		return 0;

	foreach_node(n, struct_body(s)) {
		if (n->k == AST_PROC_DEF && lower_proc(n))
			return -1;
	}

	ast_set_flags(s, AST_FLAG_LOWERED);
	return 0;
}

int lower(struct scope *root)
{
	/* go through all child scopes but only do actual work on file-scope
	 * includes are allowed inside procs etc to make something only locally
	 * visible */
	for (struct scope *c = root->children; c; c = c->next) {
		if (lower(c))
			return -1;
	}

	if (!scope_flags(root, SCOPE_FILE))
		return 0;

	foreach_visible(p, root->symbols) {
		assert(p->node);
		struct ast *node = p->node;
		if (node->k == AST_PROC_DEF && lower_proc(p->node))
			return -1;
	}

	foreach_visible(p, root->types) {
		assert(p->node);
		struct ast *node = p->node;
		if (node->k == AST_STRUCT_DEF && lower_struct(p->node))
			return -1;
	}

	return 0;
}

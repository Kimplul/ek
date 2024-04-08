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
};

static struct lower_state create_state()
{
	struct lower_state state;
	state.top = vec_create(sizeof(char *));
	state.bottom = vec_create(sizeof(char *));
	state.out = vec_create(sizeof(char *));
	state.uniq = 0;
	return state;
}

static void destroy_state(struct lower_state *state)
{
	assert(vec_len(&state->top) == 0);
	assert(vec_len(&state->bottom) == 0);
	assert(vec_len(&state->out) == 0);

	vec_destroy(&state->top);
	vec_destroy(&state->bottom);
	vec_destroy(&state->out);
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
	vec_create(sizeof(struct retval))

#define foreach_retval(ri, retval) \
	foreach_vec(ri, retval)

#define retval_at(rv, ri) \
	vect_at(struct retval, rv, ri)

static void retval_destroy(struct vec *retval)
{
	foreach_retval(ri, *retval) {
		struct retval s = retval_at(*retval, ri);
		free(s.s);
	}

	vec_destroy(retval);
}

static struct retval build_retval(enum retval_kind kind, char *s)
{
	return (struct retval){.kind = kind, .s = s};
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

static size_t get_scope_number(struct ast *id)
{
	/** @todo this mirrors what's in actualize.c:actualize_id, same comments
	 * apply */
	struct ast *def = file_scope_find_var(id->scope, id->s);
	if (def)
		return def->scope->number;

	def = file_scope_find_proc(id->scope, id->s);
	if (def)
		return def->scope->number;

	return 0;
}

static char *mangle_idx(struct ast *id, size_t idx)
{
	assert(id->scope);
	assert(id->s);

	const char *name = id->s;
	/* oh wait, I need to do a variable lookup on the ID, not use the ID's
	 * scope number, duh */
	size_t number = get_scope_number(id);

	if (ast_flags(id, AST_FLAG_NOMANGLE))
		return strdup(name);

	return build_str("%s_s%zif%zi", name, number, idx);
}

static char *mangle(struct ast *id)
{
	return mangle_idx(id, 0);
}

static int lower_expr(struct lower_state *s, struct ast *e,
                      struct vec *retval);
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

static int lower_param(struct lower_state *s, struct ast *p)
{
	UNUSED(s);
	assert(p->k == AST_VAR_DEF);
	struct type *type = var_type(p);
	if (!is_primitive(type)) {
		semantic_error(p->scope->fctx, p,
		               "only primitive params currently implemented");
		return -1;
	}

	assert(var_init(p) == NULL);

	char *t = is_small_type(type) ? "i9" : "i27";
	printf("%s ", t);
	output_ast_id(p);
	printf(",");
	return 0;
}

static int lower_params(struct lower_state *s, struct ast *params)
{
	foreach_node(p, params) {
		if (lower_param(s, p))
			return -1;
	}

	return 0;
}

static int lower_var(struct lower_state *s, struct ast *v,
                     struct vec *retval)
{
	assert(v->k == AST_VAR_DEF);
	struct vec input = retval_create();
	if (lower_expr(s, var_init(v), &input))
		return -1;

	/* if we have a struct, we should add the member name to the base name
	 * */
	foreach_retval(ri, input) {
		struct retval r = retval_at(input, ri);
		char *name = mangle_idx(v, ri);
		/* I assume we're always dealing with i27 for now */
		/** @todo qbt could maybe skip the type stuff except for casts */
		printf("i27 %s = %s;\n", name, r.s);
		struct retval n = build_retval(REG_I27, name);
		vec_append(retval, &n);
	}

	retval_destroy(&input);
	return 0;
}

static void do_const_store(struct lower_state *s, struct vec *from,
                           struct retval t, struct retval o)
{
	UNUSED(s);
	/* I know, kind of silly to swap back and forth between string/int but
	 * good enough for now */
	int64_t addr = strtoll(t.s, 0, 0) + strtoll(o.s, 0, 0);
	foreach_retval(ri, *from) {
		struct retval r = retval_at(*from, ri);
		/* doesn't really take into account possible padding etc, should
		 * probably fix at some point */
		printf("%s >> %s (%zi);\n",
		       r.s, retval_type_str(r), addr);

		addr += retval_width(r);
	}
}

static void do_store(struct lower_state *s, struct vec *from, struct vec *to,
                     struct vec *off)
{
	assert(vec_len(to) == 1);
	struct retval t = retval_at(*to, 0);

	struct retval o = build_retval(CONST_I27, "0");
	if (off)
		o = retval_at(*off, 0);

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
	foreach_retval(ri, *from) {
		struct retval r = retval_at(*from, ri);
		/* doesn't really take into account possible padding etc, should
		 * probably fix at some point */
		printf("%s >> %s %s %zi;\n",
		       r.s, retval_type_str(r), t.s, addr);

		addr += retval_width(r);
	}
}

static int lower_cast(struct lower_state *s, struct ast *e,
                      struct vec *retval)
{
	assert(e->k == AST_CAST);
	/** @todo make sure actualize removes casts that aren't of these types
	 * */
	assert(is_primitive(e->t));

	if (lower_expr(s, cast_expr(e), retval))
		return -1;

	enum retval_kind kind = is_small_type(e->t) ? REG_I9 : REG_I27;

	foreach_retval(ri, *retval) {
		struct retval r = retval_at(*retval, ri);
		/* build new temporary cast result and replace the previous
		 * retval */
		char *s = build_str("%s%s", "cast", r.s);

		printf("%s %s = %s;\n", retval_kind_str(kind), s, r.s);
		free(r.s);

		r.s = s;
		r.kind = kind;
		retval_at(*retval, ri) = r;
	}

	return 0;
}

static int lower_const(struct lower_state *s, struct ast *c,
                       struct vec *retval)
{
	UNUSED(s);
	assert(is_const(c));
	char *str = build_str("%lli", (long long)c->v);
	enum retval_kind kind = is_small_type(c->t) ? CONST_I9: CONST_I27;
	struct retval r = build_retval(kind, str);
	vec_append(retval, &r);
	return 0;
}

static int lower_assign(struct lower_state *s, struct ast *a,
                        struct vec *retval)
{
	assert(a->k == AST_ASSIGN);
	if (lower_expr(s, assign_from(a), retval))
		return -1;

	struct vec loc = retval_create();
	struct vec off = retval_create();

	struct ast *to = assign_to(a);
	struct ast *base = to;
	if (to->k == AST_DEREF)
		base = unop_expr(to);
	else if (to->k == AST_ARR) {
		base = arr_base(to);
		if (lower_expr(s, arr_idx(to), &off)) {
			retval_destroy(&loc);
			retval_destroy(&off);
			return -1;
		}
	}

	if (lower_expr(s, base, &loc)) {
		retval_destroy(&loc);
		retval_destroy(&off);
		return -1;
	}

	if (to->k == AST_DEREF) {
		do_store(s, retval, &loc, NULL);
	}
	else if (to->k == AST_ARR) {
		do_store(s, retval, &loc, &off);
	} else {
		assert(vec_len(retval) == vec_len(&loc));
		foreach_retval(ri, *retval) {
			struct retval to = retval_at(loc, ri);
			struct retval from = retval_at(*retval, ri);
			printf("i27 %s = %s;\n", to.s, from.s);
		}
	}

	retval_destroy(&loc);
	retval_destroy(&off);
	return 0;
#undef IS_DEREF
#undef IS_ARR
}

static int lower_id(struct lower_state *s, struct ast *id,
                    struct vec *retval)
{
	UNUSED(s);
	assert(id->k == AST_ID);
	char *m = mangle(id);

	struct type *type = id->t;
	if (!is_primitive(type) && type->k != TYPE_CALLABLE) {
		semantic_error(id->scope->fctx, id,
		               "only primitive ids currently implemented");
		return -1;
	}

	enum retval_kind kind = is_small_type(type) ? REG_I9 : REG_I27;

	/* this likely isn't enough and we need to add the & to most things we
	 * want to take the address of */
	if (type->k == TYPE_CALLABLE) {
		char *o = m;
		m = build_str("&%s", m);
		free(o);
	}

	struct retval r = build_retval(kind, m);
	vec_append(retval, &r);
	return 0;
}

static int lower_return(struct lower_state *s, struct ast *r,
                        struct vec *retval)
{
	assert(r->k == AST_RETURN);
	/** @todo defers, should they be handled here or in ast? */
	if (lower_expr(s, return_expr(r), retval))
		return -1;

	printf("=> ( ");

	foreach_retval(ri, *retval) {
		struct retval r = retval_at(*retval, ri);
		printf("%s, ", r.s);
	}

	printf(" );\n");
	return 0;
}

static int lower_if(struct lower_state *s, struct ast *i,
                    struct vec *retval)
{
	assert(i->k == AST_IF);
	if (lower_expr(s, if_cond(i), retval))
		return -1;

	assert(vec_len(retval) == 1);
	/* helps readability a little bit */
	long long uniq = s->uniq++;
	printf("if%lli:\n", uniq);

	char *bottom = build_str("if_else%lli", uniq);
	char *out = build_str("if_out%lli", uniq);

	printf("! %s -> %s;\n", (retval_at(*retval, 0)).s, bottom);

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
                     struct vec *retval)
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

	assert(vec_len(retval) == 1);
	printf("%s -> %s;\n", (retval_at(*retval, 0)).s, top);

	pop_loop(s);
	return 0;
}

static int lower_expr_if(struct lower_state *s, struct ast *i,
                         struct vec *retval)
{
	semantic_error(i->scope->fctx, i,
	               "expr if unimplemented");
	return 0;
}

static int lower_binop(struct lower_state *s, struct ast *i,
                       struct vec *retval)
{
	struct vec l = retval_create();
	struct vec r = retval_create();

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

	assert(vec_len(&l) == 1);
	assert(vec_len(&r) == 1);

	char *name = build_str("binop%lli", (long long)s->uniq++);
	struct retval ret = build_retval(REG_I27, name);
	vec_append(retval, &ret);

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

	printf("i27 %s = %s %s %s;\n", name,
	       (retval_at(l, 0)).s,
	       op,
	       (retval_at(r, 0)).s);

	retval_destroy(&l);
	retval_destroy(&r);
	return 0;
}

static int lower_comparison(struct lower_state *s, struct ast *i, struct vec *retval)
{
	/* very similar to lower_binop, hmm */
	struct vec l = retval_create();
	struct vec r = retval_create();

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

	assert(vec_len(&l) == 1);
	assert(vec_len(&r) == 1);

	char *name = build_str("comp%lli", (long long)s->uniq++);
	struct retval ret = build_retval(REG_I27, name);
	vec_append(retval, &ret);

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

	printf("i9 %s = %s %s %s;\n", name,
	       (retval_at(l, 0)).s,
	       op,
	       (retval_at(r, 0)).s);

	retval_destroy(&l);
	retval_destroy(&r);
	return 0;
}

static int lower_call(struct lower_state *s, struct ast *c,
                      struct vec *retval)
{
	assert(c->k == AST_CALL);

	struct vec call = retval_create();
	if (lower_expr(s, call_expr(c), &call)) {
		retval_destroy(&call);
		return -1;
	}

	/* collect all args */
	struct vec args = retval_create();
	foreach_node(a, call_args(c)) {
		struct vec arg = retval_create();
		if (lower_expr(s, a, &arg)) {
			retval_destroy(&arg);
			retval_destroy(&args);
			return -1;
		}

		foreach_retval(ri, arg) {
			struct retval r = retval_at(arg, ri);
			/* very important! */
			r.s = strdup(r.s);
			vec_append(&args, &r);
		}

		retval_destroy(&arg);
	}

	assert(vec_len(&call) == 1);
	printf("%s (", (retval_at(call, 0)).s);
	retval_destroy(&call);

	foreach_retval(ri, args) {
		struct retval r = retval_at(args, ri);
		printf("%s, ", r.s);
	}

	if (!is_primitive(c->t) && c->t->k != TYPE_VOID) {
		semantic_error(c->scope->fctx, c,
		               "only primitive return types implemented");
		retval_destroy(&args);
		return -1;
	}

	printf(") => ( ");

	int i = 0;
	foreach_type(t, c->t) {
		char *s = build_str("r%i\n", i);
		enum retval_kind k = is_small_type(t) ? REG_I9 : REG_I27;
		struct retval r = build_retval(k, s);
		vec_append(retval, &r);
		i++;
	}

	printf(" );\n");
	retval_destroy(&args);
	return 0;
}

static int lower_expr(struct lower_state *s, struct ast *e,
                      struct vec *retval)
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
	case AST_ID: return lower_id(s, e, retval);
	/* var is considered an expression in this case */
	case AST_CAST: return lower_cast(s, e, retval);
	case AST_RETURN: return lower_return(s, e, retval);
	case AST_ASSIGN: return lower_assign(s, e, retval);
	case AST_CALL: return lower_call(s, e, retval);
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
	foreach_node(n, block_body(block)) {
		if (lower_statement(s, n))
			return -1;
	}

	return 0;
}

static int lower_statement(struct lower_state *s, struct ast *n)
{
	struct vec retval = retval_create();

	int ret = 0;
	switch (n->k) {
	case AST_RETURN: ret = lower_return(s, n, &retval); break;
	case AST_IF: ret = lower_if(s, n, &retval); break;
	case AST_FOR: ret = lower_for(s, n, &retval); break;
	case AST_BLOCK: ret = lower_block(s, n); break;
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

	struct lower_state state = create_state();

	/* name */
	output_ast_id(n);

	/* args */
	printf("(");

	if (lower_params(&state, proc_params(n))) {
		destroy_state(&state);
		return -1;
	}

	/* no return type currently supported by qbt */
	printf(")\n");

	/* body */
	printf("{\n");

	if (lower_block(&state, proc_body(n))) {
		destroy_state(&state);
		return -1;
	}

	printf("}\n");
	destroy_state(&state);
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

	for (struct visible *v = root->vars; v; v = v->next) {
		assert(v->node);
		if (lower_global_var(v->node))
			return -1;
	}

	for (struct visible *p = root->procs; p; p = p->next) {
		assert(p->node);
		if (lower_proc(p->node))
			return -1;
	}

	return 0;
}

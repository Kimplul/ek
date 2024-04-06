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

static bool is_i9(struct ast_node *n)
{
	if (AST_TYPE(n->type).kind != AST_TYPE_PRIMITIVE)
		return false;

	return AST_PRIMITIVE_TYPE(n->type).type == AST_I9;
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

static size_t get_scope_number(struct ast_node *id)
{
	/** @todo this mirrors what's in actualize.c:actualize_id, same comments
	 * apply */
	struct ast_node *def = file_scope_find_var(id->scope, id);
	if (def)
		return def->scope->number;

	def = file_scope_find_proc(id->scope, id);
	if (def)
		return def->scope->number;

	return 0;
}

static char *mangle_idx(struct ast_node *id, size_t idx)
{
	assert(id->node_type == AST_ID);
	assert(id->scope);
	const char *name = AST_ID(id).id;
	/* oh wait, I need to do a variable lookup on the ID, not use the ID's
	 * scope number, duh */
	size_t number = get_scope_number(id);

	if (ast_flags(id, AST_FLAG_NOMANGLE))
		return strdup(name);

	return build_str("%s_s%zif%zi", name, number, idx);
}

static char *mangle(struct ast_node *id)
{
	return mangle_idx(id, 0);
}

static int lower_expr(struct lower_state *s, struct ast_node *e,
                      struct vec *retval);
static int lower_statement(struct lower_state *s, struct ast_node *n);

static void output_id(struct ast_node *id)
{
	char *name = mangle(id);
	printf("%s", name);
	free(name);
}

static int lower_global_var(struct ast_node *n)
{
	/* trivial types are reasonably easy, but stuff like compound types need
	 * a lot of work */
	struct ast_node *type = AST_VAR(n).type;
	if (AST_TYPE(type).kind != AST_TYPE_PRIMITIVE) {
		semantic_error(n->scope->fctx, n,
		               "only primitive globals currently implemented");
		return -1;
	}

	struct ast_node *id = AST_VAR(n).id;
	struct ast_node *init = AST_VAR(n).init;
	if (init->node_type != AST_CONST) {
		semantic_error(n->scope->fctx, n,
		               "constant expressions currently not implemented");
		return -1;
	}

	output_id(id);
	printf(" = ");

	/* hmm, this might be useful elsewhere as well */
	switch (AST_PRIMITIVE_TYPE(type).type) {
	case AST_I27: printf("i27 %lli", AST_CONST(init).integer); break;
	case AST_I9: printf("i9 %lli", AST_CONST(init).integer); break;
	default:
		semantic_error(n->scope->fctx, n,
		               "unhandled primitive type");
		return -1;
	}

	printf(";\n");
	return 0;
}

static int lower_param(struct lower_state *s, struct ast_node *p)
{
	UNUSED(s);
	assert(p->node_type == AST_VAR);
	struct ast_node *type = AST_VAR(p).type;
	if (AST_TYPE(type).kind != AST_TYPE_PRIMITIVE) {
		semantic_error(p->scope->fctx, p,
		               "only primitive params currently implemented");
		return -1;
	}

	assert(AST_VAR(p).init == NULL);

	switch (AST_PRIMITIVE_TYPE(type).type) {
	case AST_I27: printf("i27 "); break;
	case AST_I9: printf("i9 "); break;
	default:
		semantic_error(p->scope->fctx, p,
		               "unhandled primitive type");
		return -1;
	}

	struct ast_node *id = AST_VAR(p).id;
	output_id(id);
	printf(",");
	return 0;
}

static int lower_params(struct lower_state *s, struct ast_node *params)
{
	for (struct ast_node *p = params; p; p = p->next) {
		if (lower_param(s, p))
			return -1;
	}

	return 0;
}

static int lower_var(struct lower_state *s, struct ast_node *v,
                     struct vec *retval)
{
	assert(v->node_type == AST_VAR);
	struct vec input = retval_create();
	if (lower_expr(s, AST_VAR(v).init, &input))
		return -1;

	struct ast_node *id = AST_VAR(v).id;
	/* if we have a struct, we should add the member name to the base name
	 * */
	foreach_retval(ri, input) {
		struct retval r = retval_at(input, ri);
		char *name = mangle_idx(id, ri);
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

static int lower_cast(struct lower_state *s, struct ast_node *e,
                      struct vec *retval)
{
	assert(e->node_type == AST_CAST);
	/** @todo make sure actualize removes casts that aren't of these types
	 * */
	assert(AST_TYPE(e->type).kind == AST_TYPE_PRIMITIVE
	       || AST_TYPE(e->type).kind == AST_TYPE_POINTER);

	if (lower_expr(s, AST_CAST(e).expr, retval))
		return -1;

	enum retval_kind kind = REG_I27;
	if (is_i9(e))
		kind = REG_I9;

	foreach_retval(ri, *retval) {
		struct retval r = retval_at(*retval, ri);
		/* build new temporary cast result and replace the previous
		 * retval */
		char *s = build_str("%s%s", "cast_", r.s);

		printf("%s %s = %s;\n", retval_kind_str(kind), s, r.s);
		free(r.s);

		r.s = s;
		r.kind = kind;
		retval_at(*retval, ri) = r;
	}

	return 0;
}

static int lower_const(struct lower_state *s, struct ast_node *c,
                       struct vec *retval)
{
	UNUSED(s);
	assert(c->node_type == AST_CONST);
	if (AST_CONST(c).kind == AST_CONST_STRING) {
		/* requires pushing strings as variables and replacing them with
		 * references */
		semantic_error(c->scope->fctx, c,
		               "string constant lowering not yet implemented");
		return -1;
	}

	enum retval_kind type = CONST_I27;
	if (AST_PRIMITIVE_TYPE(c->type).type == AST_I9)
		type = CONST_I9;

	char *str = build_str("%lli", (long long int)AST_CONST(c).integer);
	struct retval r = build_retval(type, str);
	vec_append(retval, &r);
	return 0;
}

static int lower_assign(struct lower_state *s, struct ast_node *a,
                        struct vec *retval)
{
#define IS_DEREF(t) (t->node_type == AST_UNOP && AST_UNOP(t).op == AST_DEREF)
#define IS_ARR(t) (t->node_type == AST_ARR_ACCESS)

	assert(a->node_type == AST_ASSIGN);
	if (lower_expr(s, AST_ASSIGN(a).from, retval))
		return -1;

	struct vec loc = retval_create();
	struct vec off = retval_create();

	struct ast_node *to = AST_ASSIGN(a).to;
	struct ast_node *base = to;
	if (IS_DEREF(to))
		base = AST_UNOP(to).expr;
	else if (IS_ARR(to)) {
		base = AST_ARR_ACCESS(to).base;
		if (lower_expr(s, AST_ARR_ACCESS(to).idx, &off)) {
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

	if (IS_DEREF(to)) {
		do_store(s, retval, &loc, NULL);
	}
	else if (IS_ARR(to)) {
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

static int lower_id(struct lower_state *s, struct ast_node *id,
                    struct vec *retval)
{
	UNUSED(s);
	assert(id->node_type == AST_ID);
	char *m = mangle(id);

	struct ast_node *type = id->type;
	if (AST_TYPE(type).kind != AST_TYPE_PRIMITIVE
	    && AST_TYPE(type).kind != AST_TYPE_POINTER
	    && AST_TYPE(type).kind != AST_TYPE_SIGN) {
		semantic_error(id->scope->fctx, id,
		               "only primitive ids currently implemented");
		return -1;
	}

	enum retval_kind kind = REG_I27;
	if (is_i9(id))
		kind = REG_I9;

	/* this likely isn't enough and we need to add the & to most things we
	 * want to take the address of */
	if (AST_TYPE(type).kind == AST_TYPE_SIGN) {
		char *o = m;
		m = build_str("&%s", m);
		free(o);
	}

	struct retval r = build_retval(kind, m);
	vec_append(retval, &r);
	return 0;
}

static int lower_return(struct lower_state *s, struct ast_node *r,
                        struct vec *retval)
{
	assert(r->node_type == AST_RETURN);
	if (lower_expr(s, AST_RETURN(r).expr, retval))
		return -1;

	printf("=> ( ");

	foreach_retval(ri, *retval) {
		struct retval r = retval_at(*retval, ri);
		printf("%s, ", r.s);
	}

	printf(" );\n");
	return 0;
}

static int lower_if(struct lower_state *s, struct ast_node *i,
                    struct vec *retval)
{
	assert(i->node_type == AST_IF);
	if (lower_expr(s, AST_IF(i).cond, retval))
		return -1;

	assert(vec_len(retval) == 1);
	/* helps readability a little bit */
	long long uniq = s->uniq++;
	printf("if%lli:\n", uniq);

	char *bottom = build_str("if_else%lli", uniq);
	char *out = build_str("if_out%lli", uniq);

	printf("! %s -> %s;\n", (retval_at(*retval, 0)).s, bottom);

	/* a block counts as a statement in this case */
	if (lower_statement(s, AST_IF(i).body)) {
		free(bottom);
		return -1;
	}

	printf("-> %s;\n", out);
	printf("%s:\n", bottom);
	free(bottom);

	if (AST_IF(i).els && lower_statement(s, AST_IF(i).els)) {
		free(out);
		return -1;
	}

	printf("%s:\n", out);
	free(out);
	return 0;
}

static int lower_for(struct lower_state *s, struct ast_node *f,
                     struct vec *retval)
{
	assert(f->node_type == AST_FOR);
	if (lower_statement(s, AST_FOR(f).pre))
		return -1;

	long long uniq = s->uniq++;

	char *top = build_str("for_top%lli", uniq);
	char *bottom = build_str("for_bottom%lli", uniq);
	char *out = build_str("for_out%lli", uniq);

	push_loop(s, top, bottom, out);

	printf("-> %s;\n", out);

	printf("%s:\n", top);
	if (lower_statement(s, AST_FOR(f).body)) {
		pop_loop(s);
		return -1;
	}

	printf("%s:\n", bottom);
	if (lower_statement(s, AST_FOR(f).post)) {
		pop_loop(s);
		return -1;
	}

	printf("%s:\n", out);
	if (lower_expr(s, AST_FOR(f).cond, retval)) {
		pop_loop(s);
		return -1;
	}

	assert(vec_len(retval) == 1);
	printf("%s -> %s;\n", (retval_at(*retval, 0)).s, top);

	pop_loop(s);
	return 0;
}

static int lower_expr_if(struct lower_state *s, struct ast_node *i,
                         struct vec *retval)
{
	semantic_error(i->scope->fctx, i,
	               "expr if unimplemented");
	return 0;
}

static int lower_binop(struct lower_state *s, struct ast_node *i,
                       struct vec *retval)
{
	struct vec l = retval_create();
	struct vec r = retval_create();

	if (lower_expr(s, AST_BINOP(i).left, &l)) {
		retval_destroy(&l);
		retval_destroy(&r);
		return -1;
	}

	if (lower_expr(s, AST_BINOP(i).right, &r)) {
		retval_destroy(&l);
		retval_destroy(&r);
		return -1;
	}

	assert(vec_len(&l) == 1);
	assert(vec_len(&r) == 1);

	char *name = build_str("tmp%lli", (long long)s->uniq++);
	struct retval ret = build_retval(REG_I27, name);
	vec_append(retval, &ret);

	char *op = "";
	switch (AST_BINOP(i).op) {
	case AST_ADD: op = "+"; break;
	case AST_SUB: op = "-"; break;
	case AST_MUL: op = "*"; break;
	case AST_DIV: op = "/"; break;
	case AST_REM: op = "%"; break;
	case AST_LSHIFT: op = "<<"; break;
	case AST_RSHIFT: op = ">>"; break;
	case AST_LT: op = "<"; break;
	case AST_GT: op = ">"; break;
	case AST_LE: op = "<="; break;
	case AST_GE: op = ">="; break;
	case AST_NE: op = "!="; break;
	case AST_EQ: op = "=="; break;
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

static int lower_call(struct lower_state *s, struct ast_node *c,
                      struct vec *retval)
{
	assert(c->node_type == AST_CALL);

	struct vec call = retval_create();
	if (lower_expr(s, AST_CALL(c).expr, &call)) {
		retval_destroy(&call);
		return -1;
	}

	/* collect all args */
	struct vec args = retval_create();
	foreach_node(a, AST_CALL(c).args) {
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

#define IS_VOID(t) \
	(t->node_type == AST_TYPE && AST_TYPE(t).kind == AST_TYPE_PRIMITIVE && \
	 AST_PRIMITIVE_TYPE(t).type == AST_VOID)

	if (!IS_VOID(c->type)) {
		semantic_error(c->scope->fctx, c,
		               "only void return type implemented");
		retval_destroy(&args);
		return -1;
	}

	printf(") => ();\n");
	retval_destroy(&args);
	return 0;
}

static int lower_expr(struct lower_state *s, struct ast_node *e,
                      struct vec *retval)
{
	if (!e)
		return 0;

	switch (e->node_type) {
	case AST_ID: return lower_id(s, e, retval);
	/* var is considered an expression in this case */
	case AST_VAR: return lower_var(s, e, retval);
	case AST_CAST: return lower_cast(s, e, retval);
	case AST_CONST: return lower_const(s, e, retval);
	case AST_RETURN: return lower_return(s, e, retval);
	case AST_ASSIGN: return lower_assign(s, e, retval);
	case AST_BINOP: return lower_binop(s, e, retval);
	case AST_CALL: return lower_call(s, e, retval);
	case AST_IF: return lower_expr_if(s, e, retval);
	default:
		semantic_error(e->scope->fctx, e,
		               "unhandled expr in lowering");
		return -1;
	}

	return 0;
}

static int lower_block(struct lower_state *s, struct ast_node *body)
{
	assert(body->node_type == AST_BLOCK);
	assert(!ast_flags(body, AST_FLAG_DOEXPR));
	struct ast_node *stmt = AST_BLOCK(body).body;
	for (; stmt; stmt = stmt->next) {
		if (lower_statement(s, stmt))
			return -1;
	}

	return 0;
}

static int lower_statement(struct lower_state *s, struct ast_node *n)
{
	struct vec retval = retval_create();

	int ret = 0;
	switch (n->node_type) {
	case AST_RETURN: ret = lower_return(s, n, &retval); break;
	case AST_IF: ret = lower_if(s, n, &retval); break;
	case AST_FOR: ret = lower_for(s, n, &retval); break;
	case AST_BLOCK: ret = lower_block(s, n); break;
	default: ret = lower_expr(s, n, &retval); break;
	}

	retval_destroy(&retval);
	return ret;
}

static int lower_proc(struct ast_node *n)
{
	assert(n->node_type == AST_PROC);
	/* nobody uses the proc, so no need to do anything */
	if (n->uses == 0 && !ast_flags(AST_PROC(n).id, AST_FLAG_NOMANGLE))
		return 0;

	struct lower_state state = create_state();

	/* name */
	struct ast_node *id = AST_PROC(n).id;
	output_id(id);

	/* args */
	printf("(");

	struct ast_node *sign = AST_PROC(n).sign;
	if (lower_params(&state, AST_SIGN_TYPE(sign).params)) {
		destroy_state(&state);
		return -1;
	}

	/* no return type currently supported by qbt */
	printf(")\n");

	/* body */
	printf("{\n");

	if (lower_block(&state, AST_PROC(n).body)) {
		destroy_state(&state);
		return -1;
	}

	printf("}\n");
	destroy_state(&state);
	return 0;
}

static int lower_actual(struct ast_node *n)
{
	assert(AST_TYPE(n).kind == AST_TYPE_CONSTRUCT);
	return 0;
}

static int _lower_actuals(struct scope *root)
{
	/* go through all child scopes but only do actual work on file-scope
	 * includes are allowed inside procs etc to make something only locally
	 * visible */
	for (struct scope *c = root->children; c; c = c->next) {
		if (_lower_actuals(c))
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

int lower_actuals(struct scope *root)
{
	int ret = _lower_actuals(root);
	/* actuals are currently global, would it make more sense for them to be
	 * scope-local? */
	for (struct actual *a = root->actuals; a; a = a->next) {
		assert(a->node);
		if (lower_actual(a->node))
			return -1;
	}

	return ret;
}

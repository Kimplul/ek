/* SPDX-License-Identifier: GPL-3.0-or-later */

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <cu/actualize.h>
#include <cu/compiler.h>
#include <cu/string.h>
#include <cu/parser.h>
#include <cu/debug.h>
#include <cu/scope.h>
#include <cu/path.h>
#include <cu/res.h>

static char *read_file(const char *file, FILE *f)
{
	fseek(f, 0, SEEK_END);
	/* TODO: check how well standardized this actually is */
	long s = ftell(f);
	if (s == LONG_MAX) {
		error("%s might be a directory", file);
		return NULL;
	}

	fseek(f, 0, SEEK_SET);

	char *buf = malloc(s + 1);
	if (!buf)
		return NULL;

	fread(buf, s + 1, 1, f);
	/* remember terminating null */
	buf[s] = 0;
	return buf;
}

static int process(struct scope **parent, int public, const char *file)
{
	FILE *f = fopen(file, "rb");
	if (!f) {
		error("failed opening %s: %s\n", file, strerror(errno));
		return -1;
	}

	const char *buf = read_file(file, f);
	fclose(f);

	if (!buf)
		return -1;

	struct parser *p = create_parser();
	if (!p)
		return -1;
	parse(p, file, buf);
	struct ast_node *tree = p->tree;
	bool failed = p->failed;
	destroy_parser(p);

	if (failed)
		return -1;

	dump_ast(0, tree);

	struct scope *scope = create_scope();
	if (!scope)
		return -1;

	if (public)
		scope_set_flags(scope, SCOPE_PUBLIC);

	scope->fctx.fbuf = buf;
	scope->fctx.fname = strdup(file);
	scope->actuals = create_actuals();
	scope_set_flags(scope, SCOPE_FILE);

	if (*parent)
		scope_add_scope(*parent, scope);
	else
		*parent = scope;

	if (analyze_root(scope, tree))
		return -1;

	return 0;
}

int process_file(struct scope **scope, int public, const char *file)
{
	int res = -1;
	/* TODO: report failure allocating stuff maybe? */
	struct res *r = res_create();
	if (!r)
		return -1;

	const char *base = cu_basename(file);
	res_add(r, (void *)base);
	if (!base)
		goto out;

	const char *dir = cu_dirname(file);
	res_add(r, (void *)dir);
	if (!dir)
		goto out;

	/* TODO: iterate through include paths */
	const char *cwd = cu_cwdname();
	res_add(r, (void *)cwd);
	if (!cwd)
		goto out;

	debug("(cwd:%s)(dir:%s)(base:%s)", cwd, dir, base);

	if (*dir != 0 && chdir(dir)) {
		error("couldn't change to directory %s: %s", dir, strerror(
			      errno));
		goto out;
	}

	if (process(scope, public, base))
		goto out;

	if (chdir(cwd)) {
		error("couldn't change back to directory %s: %s\n", cwd, strerror(
			      errno));
		goto out;
	}

	res = 0;
out:
	res_destroy(r);
	return res;
}

int compile(const char *file) {
	int ret = -1;
	struct scope *root = NULL;
	if (process_file(&root, 0, file)) {
		destroy_scope(root);
		error("compilation of %s stopped due to errors", file);
		return ret;
	}

	ret = actualize_main(root);
	/* TODO: backend */
	destroy_scope(root);
	return ret;
}

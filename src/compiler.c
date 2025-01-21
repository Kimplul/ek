/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

/**
 * @file compiler.c
 *
 * Top level compiler implementation.
 */

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <ek/actualize.h>
#include <ek/compiler.h>
#include <ek/string.h>
#include <ek/parser.h>
#include <ek/debug.h>
#include <ek/scope.h>
#include <ek/lower.h>
#include <ek/path.h>
#include <ek/res.h>

/**
 * Read whole file into a buffer and return pointer to buffer.
 * Possibly kind of silly to have both \p file and \p f.
 * Apparently there's no standardized way to get the file name of a
 * file pointer.
 *
 * @param file Name of file to read.
 * @param f File pointer.
 * @return Pointer to buffer with file contents.
 */
static char *read_file(const char *file, FILE *f)
{
	fseek(f, 0, SEEK_END);
	/** @todo check how well standardized this actually is */
	long s = ftell(f);
	if (s == LONG_MAX) {
		error("%s might be a directory", file);
		return NULL;
	}

	fseek(f, 0, SEEK_SET);

	char *buf = malloc((size_t)(s + 1));
	if (!buf)
		return NULL;

	fread(buf, (size_t)(s + 1), 1, f);
	/* remember terminating null */
	buf[s] = 0;
	return buf;
}

/**
 * Helper for process_file(), actually processes the file
 * after process_file() has done path lookups and working directory
 * changes and whatnot.
 *
 * @param parent Parent file context. \c NULL if root file.
 * @param public \c 1 if file is being imported publicly, \c 0 otherwise.
 * @param file File name to process.
 * @return \c 0 if processing was succesful, non-zero value otherwise.
 */
static int process(struct scope *scope, const char *file)
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
	if (!p) {
		free((void *)buf);
		return -1;
	}

	parse(p, file, buf);
	struct ast *tree = p->tree;
	bool failed = p->failed;
	destroy_parser(p);

	if (failed) {
		free((void*)buf);
		return -1;
	}

	ast_dump_list(0, tree);

	scope->fctx.fbuf = buf;
	scope->fctx.fname = strdup(file);
	scope_set_flags(scope, SCOPE_FILE);

	if (analyze_root(scope, tree))
		return -1;

	return 0;
}

#define MAP_KEY char *
#define MAP_TYPE struct scope *
#define MAP_CMP(a, b) strcmp((a), (b))
#define MAP_NAME scopes
#include "ek/map.h"

/* ugly global for now */
static struct scopes scopes;

static void destroy_scopes()
{
	if (scopes_len(&scopes))
		foreach(scopes, n, &scopes) {
			destroy_scope(n->data);
			free(n->key);
		}

	scopes_destroy(&scopes);
}

struct scope *process_file(const char *file)
{
	/** todo report failure allocating stuff maybe? */
	struct res *r = res_create();
	if (!r)
		return NULL;

	const char *base = ek_basename(file);
	res_add(r, (void *)base);
	if (!base)
		goto out;

	const char *dir = ek_dirname(file);
	res_add(r, (void *)dir);
	if (!dir)
		goto out;

	/* TODO: iterate through include paths? */
	const char *cwd = ek_cwdname();
	res_add(r, (void *)cwd);
	if (!cwd)
		goto out;

	if (*dir != 0 && chdir(dir)) {
		error("couldn't change to directory %s: %s", dir, strerror(
			      errno));
		goto out;
	}

	char *real = realpath(base, NULL);
	if (!real) {
		error("no such file: %s", file);
		goto out;
	}

	struct scope **exists = scopes_find(&scopes, real);
	if (exists) {
		res_destroy(r);
		free(real);
		return *exists;
	} else {
		struct scope *scope = create_scope();
		if (scopes_len(&scopes) == 0)
			scope_set_flags(scope, SCOPE_ROOT);

		scopes_insert(&scopes, real, scope);

		if (process(scope, base))
			goto out;

		res_destroy(r);
		return scope;
	}

	if (chdir(cwd)) {
		error("couldn't change back to directory %s: %s\n", cwd,
		      strerror(errno));
		goto out;
	}

out:
	res_destroy(r);
	return NULL;
}

int compile(const char *input) {
	scopes = scopes_create();

	int ret = -1;
	struct scope *root = process_file(input);
	if (!root) {
		destroy_allocs();
		destroy_scopes();
		error("compilation of %s stopped due to errors", input);
		return ret;
	}

	if ((ret = lower(root))) {
		destroy_allocs();
		destroy_scopes();
		error("compilation of %s stopped due to errors", input);
		return ret;
	}

	destroy_allocs();
	destroy_scopes();
	return 0;
}

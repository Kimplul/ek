/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

/**
 * @file debug.c
 *
 * Debugging and information printing helper implementations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <ek/debug.h>

/**
 * Get string representation of issue_level.
 *
 * @param level issue_level to get string representation for.
 * @return \p level as a string.
 */
const char *issue_level_str(enum issue_level level)
{
	switch (level) {
	case SRC_INFO: return "info";
	case SRC_WARN: return "warn";
	case SRC_ERROR: return "error";
	}

	return "unknown";
}

/**
 * Find position in file buffer where line number \p no
 * starts. Lines are assumed to be one-indexed, with
 * \p no = \c 0 and \p no = \c 1 both considered the first line.
 *
 * @param buf Buffer to look in.
 * @param no Line number whose start to look for.
 * @return Pointer to location in buffer where line number \p no
 * starts.
 */
static const char *find_lineno(const char *buf, size_t no)
{
	if (no == 0 || no == 1)
		return buf;

	char c;
	while ((c = *buf)) {
		buf++;

		if (c == '\n')
			no--;

		if (no == 1)
			break;
	}

	return buf;
}

/**
 * Helper for printing out an issue.
 *
 * @param issue Issue context.
 * @param fmt Format string. Follows standard printf() formatting.
 * @param args Arguments for \p fmt.
 */
static void _issue(struct src_issue issue, const char *fmt, va_list args)
{
	/* get start and end of current line in buffer */
	const char *line_start = find_lineno(issue.fctx.fbuf,
	                                     issue.loc.first_line);
	const char *line_end = strchr(line_start, '\n');
	if (!line_end)
		line_end = strchr(line_start, 0);

	const int line_len = line_end - line_start;

	fprintf(stderr, "%s:%i:%i: %s: ", issue.fctx.fname,
	        issue.loc.first_line,
	        issue.loc.first_col,
	        issue_level_str(issue.level));

	vfprintf(stderr, fmt, args);
	fputc('\n', stderr);

	int lineno_len = snprintf(NULL, 0, "%i", issue.loc.first_line);
	fputc(' ', stderr);
	fprintf(stderr, "%i | ", issue.loc.first_line);

	fprintf(stderr, "%.*s\n", line_len, line_start);

	for (int i = 0; i < lineno_len + 2; ++i)
		fputc(' ', stderr);

	fprintf(stderr, "| ");

	for (int i = 0; i < issue.loc.first_col - 1; ++i)
		fputc(line_start[i] == '\t' ? '\t' : ' ', stderr);

	for (int i = issue.loc.first_col; i < issue.loc.last_col; ++i) {
		if (i == issue.loc.first_col)
			fputc('^', stderr);
		else
			fputc('~', stderr);
	}

	fputc('\n', stderr);
}

void src_issue(struct src_issue issue, const char *err_msg, ...)
{
	va_list args;
	va_start(args, err_msg);
	_issue(issue, err_msg, args);
	va_end(args);
}

void semantic_error(struct file_ctx fctx, struct ast *node,
                    const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	struct src_issue issue;
	issue.level = SRC_ERROR;
	issue.loc = node->loc;
	issue.fctx = fctx;
	_issue(issue, fmt, args);
	va_end(args);
}

void type_error(struct file_ctx fctx, struct type *node,
                    const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	struct src_issue issue;
	issue.level = SRC_ERROR;
	issue.loc = node->loc;
	issue.fctx = fctx;
	_issue(issue, fmt, args);
	va_end(args);
}

void semantic_warn(struct file_ctx fctx, struct ast *node, const char *fmt,
                   ...)
{
	va_list args;
	va_start(args, fmt);
	struct src_issue issue;
	issue.level = SRC_WARN;
	issue.loc = node->loc;
	issue.fctx = fctx;
	_issue(issue, fmt, args);
	va_end(args);
}

void semantic_info(struct file_ctx fctx, struct ast *node, const char *fmt,
                   ...)
{
	va_list args;
	va_start(args, fmt);
	struct src_issue issue;
	issue.level = SRC_INFO;
	issue.loc = node->loc;
	issue.fctx = fctx;
	_issue(issue, fmt, args);
	va_end(args);
}

void type_info(struct file_ctx fctx, struct type *node, const char *fmt,
                   ...)
{
	va_list args;
	va_start(args, fmt);
	struct src_issue issue;
	issue.level = SRC_INFO;
	issue.loc = node->loc;
	issue.fctx = fctx;
	_issue(issue, fmt, args);
	va_end(args);
}

void internal_error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "internal error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
}

void internal_warn(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "internal warning: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
}

/**
 * Workhorse for type_str().
 *
 * @param fp File pointer to write string representation to.
 * @param type Type to generate string representation for.
 */
static void _type_str(FILE *fp, struct type *type)
{
	if (!type)
		return;

	switch (type->k) {
	case TYPE_PTR:
		fputc('*', fp);
		_type_str(fp, ptr_base(type));
		break;

	case TYPE_ID: {
		fprintf(fp, "%s", type->id);
		break;
	}

	case TYPE_TRAIT: {
		struct ast *def = type->d;
		if (trait_id(def)) {
			fprintf(fp, "%s ", trait_id(def));
		}
		fprintf(fp, "(trait)");
		break;
	}

	case TYPE_STRUCT: {
		struct ast *def = type->d;
		if (struct_id(def)) {
			fprintf(fp, "%s ", struct_id(def));
		}
		fprintf(fp, "(struct)");
		break;
	}

	default:
		if (is_primitive(type))
			fprintf(fp, "%s", primitive_str(type));
		else
			fprintf(fp, "UNKNOWN TYPE");
	}
}

char *type_str(struct type *t)
{
	/* maybe hacky? */
	if (!t)
		return strdup("void");

	char *buf = NULL; size_t size = 0;
	/* hehe */
	FILE *memstream = open_memstream(&buf, &size);

	_type_str(memstream, t);

	fclose(memstream);
	return buf;
}

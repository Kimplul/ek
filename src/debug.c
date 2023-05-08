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

const char *issue_level_str(enum issue_level level)
{
	switch (level) {
	case SRC_INFO: return "info";
	case SRC_WARN: return "warn";
	case SRC_ERROR: return "error";
	}

	return "unknown";
}

static const char *find_lineno(const char *buf, size_t no)
{
	if (no == 1)
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

/* TODO: should really implement these better, the bad error messages are
 * starting to play a role in debugging */
void semantic_error(struct file_ctx fctx, struct ast_node *node,
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

void semantic_warn(struct file_ctx fctx, struct ast_node *node, const char *fmt,
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

void semantic_info(struct file_ctx fctx, struct ast_node *node, const char *fmt,
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

static void _type_str(FILE *fp, struct ast_node *type)
{
	if (!type)
		return;

	assert(type->node_type == AST_TYPE);

	switch (type->_type.kind) {
	case AST_TYPE_POINTER:
		fputc('\'', fp);
		break;

	case AST_TYPE_ID: {
		struct ast_node *id = type->_type.id;
		fprintf(fp, "%s", id->_id.id);
		break;
	}

	case AST_TYPE_TEMPLATE: {
		struct ast_node *template = type->_type.template.template;
		assert(template);

		struct ast_node *template_id = template->_template.id;
		struct ast_node *template_act = type->_type.template.actual;
		if (template_act) {
			fprintf(fp, "%s as ", template_id->_id.id);
			_type_str(fp, template_act);
		}
		else {
			fprintf(fp, "%s", template_id->_id.id);
		}
		break;
	}

	case AST_TYPE_ALIAS: {
		struct ast_node *alias = type->_type.alias.alias;
		assert(alias);

		struct ast_node *alias_id = alias->_alias.id;
		struct ast_node *alias_act = type->_type.alias.actual;
		if (alias_act) {
			/* deeply nested aliases look pretty funny here */
			fprintf(fp, "%s aka ", alias_id->_id.id);
			_type_str(fp, alias_act);
		}
		else {
			fprintf(fp, "%s", alias_id->_id.id);
		}
		break;
	}

	case AST_TYPE_STRUCT: {
		struct ast_node *struc_id = type->_type.struc.id;
		fprintf(fp, "%s", struc_id->_id.id);

		struct ast_node *impls = type->_type.struc.impls;
		if (impls) {
			fprintf(fp, "(");
			while (impls) {
				_type_str(fp, impls);
				impls = impls->next;
				if (impls)
					fprintf(fp, ", ");
			}
			fprintf(fp, ")");
		}
		break;
	}

	case AST_TYPE_UNION: {
		struct ast_node *unio_id = type->_type.unio.id;
		fprintf(fp, "%s", unio_id->_id.id);

		struct ast_node *impls = type->_type.unio.impls;
		if (impls) {
			fprintf(fp, "(");
			while (impls) {
				_type_str(fp, impls);
				impls = impls->next;
				if (impls)
					fprintf(fp, ", ");
			}
			fprintf(fp, ")");
		}
		break;
	}

	case AST_TYPE_TYPEOF: {
		_type_str(fp, type->_type.typeo.actual);
		fprintf(fp, " (typeof)");
		break;
	}

	default:
		fprintf(fp, "NOT YET IMPLEMENTED");
	}

	_type_str(fp, type->_type.next);
}

char *type_str(struct ast_node *node)
{
	/* maybe hacky? */
	if (!node)
		return strdup("void");

	char *buf = NULL; size_t size = 0;
	FILE *memstream = open_memstream(&buf, &size);

	/* TODO: improve template detection */
	/* we were given a plain type, pass it directly along to _type_str */
	if (node->node_type == AST_TYPE)
		_type_str(memstream, node);
	else
		/* otherwise, try to fish out the type of the node */
		_type_str(memstream, node->type);

	fclose(memstream);
	return buf;
}

static void _call_str(FILE *f, struct ast_node *call)
{
	struct ast_node *id = call->_call.id;
	const char *id_str = id->_id.id;
	fprintf(f, "%s", id_str);

	struct ast_node *args = call->_call.args;
	fprintf(f, "(");

	while (args) {
		char *type = type_str(args);
		fprintf(f, "%s", type);
		free(type);

		args = args->next;
		if (args)
			fprintf(f, ", ");
		else
			break;
	}

	fprintf(f, ")");
}

char *call_str(struct ast_node *call)
{
	assert(call->node_type == AST_CALL);
	char *buf = NULL; size_t size = 0;
	FILE *memstream = open_memstream(&buf, &size);
	_call_str(memstream, call);
	fclose(memstream);
	return buf;
}

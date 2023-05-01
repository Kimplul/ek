/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#include <errno.h>
#include <stdlib.h>

#include <ek/debug.h>
#include <ek/string.h>

struct string *new_string(const char *s)
{
	struct string *n = malloc(sizeof(struct string));
	if (!n) {
		error("allocating new string: %s\n", strerror(errno));
		return NULL;
	}

	if (!s) {
		n->len = 1;
		n->buf = calloc(1, 1);
		return n;
	}

	n->len = strlen(s) + 1;
	n->buf = strdup(s);
	return n;
}

void destroy_string(struct string *s)
{
	free(s->buf);
	free(s);
}

int str_append(struct string *s, char c)
{
	s->len += 1;
	s->buf = realloc(s->buf, s->len);
	if (!s->buf) {
		error("appending to string: %s\n", strerror(errno));
		return -1;
	}

	s->buf[s->len - 2] = c;
	s->buf[s->len - 1] = 0;
	return 0;
}

int str_concat(struct string *s, const char *c)
{
	size_t c_len = strlen(c);
	size_t len = s->len + c_len;
	s->buf = realloc(s->buf, len);
	if (!s->buf) {
		error("concatenating strings: %s\n", strerror(errno));
		return -1;
	}

	strncat(s->buf + s->len - 1, c, c_len);
	s->len = len;
	return 0;
}

int str_add(struct string *s, struct string *c)
{
	size_t len = s->len + c->len - 1;
	s->buf = realloc(s->buf, len);
	if (!s->buf) {
		error("adding to string: %s\n", strerror(errno));
		return -1;
	}

	strncat(s->buf + s->len - 1, c->buf, c->len);
	s->len = len;
	return 0;
}

bool str_compare(struct string *s, const char *c)
{
	return strncmp(s->buf, c, s->len - 1) == 0;
}

void str_clear(struct string *s)
{
	s->len = 1;
	if (s->buf)
		s->buf[0] = 0;
}

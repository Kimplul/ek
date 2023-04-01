/* SPDX-License-Identifier: GPL-3.0-or-later */

#ifndef CT_STRING_H
#define CT_STRING_H

#include <stddef.h>
#include <string.h>
#include <stdbool.h>

struct string {
	size_t len;
	char *buf;
};

struct string *new_string(const char *s);
void destroy_string(struct string *s);

int str_append(struct string *s, char c);
int str_concat(struct string *s, const char *c);
int str_add(struct string *s, struct string *c);

char str_index(struct string *s, size_t i);
char str_rindex(struct string *s, size_t i);

bool str_compare(struct string *s, const char *c);
void str_clear(struct string *s);

#endif /* CT_STRING_H */

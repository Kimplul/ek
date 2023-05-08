/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_STRING_H
#define EK_STRING_H

/**
 * @file string.h
 *
 * String handling helper stuff.
 * At the moment mostly unused.
 */

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

#endif /* EK_STRING_H */

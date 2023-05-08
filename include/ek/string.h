/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_STRING_H
#define EK_STRING_H

/**
 * @file string.h
 *
 * String handling helper stuff.
 * At the moment mostly unused.
 * Doesn't implement short string optimizations or anything like that for now.
 */

#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/** Simple representation of a string. */
struct string {
	/** Lenght of string. */
	size_t len;
	/** String buffer. */
	char *buf;
};

/**
 * Create new string from null terminated character array.
 * Allocates a string object on the heap and copies \p s into it.
 *
 * @param s Null terminated character array.
 * @return \p s as a string.
 */
struct string *new_string(const char *s);

/**
 * Destroy previously created string.
 * Frees the string and anything associated with it.
 *
 * @param s String to destroy.
 */
void destroy_string(struct string *s);

/**
 * Append a character to a string.
 *
 * @param s String to append \c to.
 * @param c Character to append to \p s.
 * @return \c 0 if appending succeeded, non-zero otherwise.
 */
int str_append(struct string *s, char c);

/**
 * Concatenate a string and a null terminated character array.
 * Essentially adds \p c to the end of \p s.
 *
 * @param s String to concatenate \p c with.
 * @param c Null terminated character array to concatenate with \p s.
 * @return \c 0 if concatenation succeeded, non-zero otherwise.
 */
int str_concat(struct string *s, const char *c);

/**
 * Add \p c to the end of \p s.
 *
 * @param s String to add \p c to.
 * @param c String to att to \p s.
 * @return \c 0 if addition succeedes, non-zero otherwise.
 */
int str_add(struct string *s, struct string *c);

/**
 * Get character at index \p i in \p s.
 *
 * @todo implement, range checking?
 *
 * @param s String to index into.
 * @param i Index of character to get.
 * @return Character at \p i in \p s.
 */
char str_index(struct string *s, size_t i);

/**
 * Get character at index \p i from the end of \p s.
 *
 * @todo implement, range checking?
 *
 * @param s String to index into?
 * @param i Index of character from the end to get.
 * @return Character at \p i from the end of \p s.
 */
char str_rindex(struct string *s, size_t i);

/**
 * Compare string with null-terminated character array.
 * Essentially a wrapper around strncmp().
 *
 * @param s String to compare against \p c.
 * @param c Null-terminated array to compare against \p s.
 * @return \c true if identical, \c false otherwise.
 */
bool str_compare(struct string *s, const char *c);

/**
 * Clear content of string.
 *
 * @param s String to clear content of.
 */
void str_clear(struct string *s);

#endif /* EK_STRING_H */

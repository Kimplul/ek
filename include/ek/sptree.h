#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

#ifndef SPTREE_TYPE
#error "Need sptree type"
#endif

#ifndef SPTREE_CMP
#error "Need sptree cmp"
#endif

#ifndef SPTREE_NAME
#error "Need sptree name"
#endif

#include "conts.h"

#define SPTREE(a) CONTS_JOIN(SPTREE_NAME, a)

#define SPNODE SPTREE(node)
#define SPROOT SPTREE_NAME

#ifndef SPTREE_H
#define SPTREE_H

#define sp_left(n) ((n)->left)
#define sp_right(n) ((n)->right)
#define sp_paren(n) ((n)->parent)
#define sp_lparen(n) (sp_left(n)->parent)
#define sp_rparen(n) (sp_right(n)->parent)

#endif /* SPTREE_H */

struct SPNODE {
	int_fast16_t hint;
	struct SPNODE *left, *right, *parent;
	SPTREE_TYPE data;
};

struct SPROOT {
	size_t n;
	struct SPNODE *root;
};

static inline struct SPROOT SPTREE(create)()
{
	return (struct SPROOT){.n = 0, .root = NULL};
}

static inline size_t SPTREE(len)(struct SPROOT *s)
{
	return s->n;
}

static inline struct SPNODE *SPTREE(first)(struct SPNODE *n)
{
	while (sp_left(n))
		n = sp_left(n);

	return n;
}

static inline struct SPNODE *SPTREE(last)(struct SPNODE *n)
{
	while (sp_right(n))
		n = sp_right(n);

	return n;
}

static inline SPTREE_TYPE *SPTREE(begin)(struct SPROOT *s)
{
	if (SPTREE(len)(s) == 0)
		return NULL;

	return &SPTREE(first)(s->root)->data;
}

static inline SPTREE_TYPE *SPTREE(next)(SPTREE_TYPE *prev)
{
	struct SPNODE *n = CONTAINER_OF(prev, struct SPNODE, data);
	if (sp_right(n)) {
		n = sp_right(n);
		while (sp_left(n))
			n = sp_left(n);

		return &n->data;
	}

	while (n) {
		struct SPNODE *p = sp_paren(n);
		if (!p)
			return NULL;

		if (sp_left(p) == n)
			return &p->data;

		n = p;
	}

	return NULL;
}

static inline bool SPTREE(end)(struct SPROOT *s, SPTREE_TYPE *prev)
{
	(void)s;
	return prev == NULL;
}

static inline void SPTREE(turn_left)(struct SPNODE *n)
{
	struct SPNODE *l = sp_left(n);
	struct SPNODE *p = sp_paren(n);

	assert(l);

	sp_paren(l) = sp_paren(n);
	sp_left(n) = sp_right(l);
	sp_paren(n) = l;
	sp_right(l) = n;

	if (p && sp_left(p) == n)
		sp_left(p) = l;
	else if (p)
		sp_right(p) = l;

	if (sp_left(n))
		sp_lparen(n) = n;
}

static inline void SPTREE(turn_right)(struct SPNODE *n)
{
	struct SPNODE *r = sp_right(n);
	struct SPNODE *p = sp_paren(n);

	assert(r);

	sp_paren(r) = sp_paren(n);
	sp_right(n) = sp_left(r);
	sp_paren(n) = r;
	sp_left(r) = n;

	if (p && sp_left(p) == n)
		sp_left(p) = r;
	else if (p)
		sp_right(p) = r;

	if (sp_right(n))
		sp_rparen(n) = n;
}

static inline int_fast16_t SPTREE(leaning)(struct SPNODE *n)
{
	int_fast16_t l = 0;
	int_fast16_t r = 0;

	if (sp_left(n))
		l = sp_left(n)->hint + 1;

	if (sp_right(n))
		r = sp_right(n)->hint + 1;

	return l - r;
}

static inline int_fast16_t SPTREE(max_hint)(struct SPNODE *n)
{
	int_fast16_t l = 0;
	int_fast16_t r = 0;

	if (sp_left(n))
		l = sp_left(n)->hint + 1;

	if (sp_right(n))
		r = sp_right(n)->hint + 1;

	if (l > r)
		return l;
	else
		return r;
}

static inline void SPTREE(update)(struct SPROOT *r, struct SPNODE *n)
{
	while (n) {
		int b = SPTREE(leaning)(n);
		int prev_hint = n->hint;
		struct SPNODE *p = sp_paren(n);

		if (b < -1) {
			/* leaning to the right */
			if (n == r->root)
				r->root = sp_right(n);

			SPTREE(turn_right)(n);
		}

		else if (b > 1) {
			/* leaning to the left */
			if (n == r->root)
				r->root = sp_left(n);

			SPTREE(turn_left)(n);
		}

		n->hint = SPTREE(max_hint)(n);
		if (n->hint == 0 || n->hint != prev_hint)
			n = p;
		else
			return;
	}
}

static inline SPTREE_TYPE *SPTREE(insert)(struct SPROOT *s, SPTREE_TYPE data)
{
	if (!s->root) {
		assert(s->n == 0);
		struct SPNODE *new = malloc(sizeof(struct SPNODE));
		if (!new)
			return NULL;

		new->left = new->right = new->parent = NULL;
		new->data = data;
		new->hint = 0;

		s->root = new;
		s->n = 1;
		return &new->data;
	}

	bool insert_left = false;

	struct SPNODE *n = s->root;
	struct SPNODE *p = NULL;
	while (n) {
		p = n;
		int c = SPTREE_CMP(n->data, data);
		if (c < 0) {
			n = sp_left(n);
			insert_left = true;
			continue;
		}
		if (c > 0) {
			n = sp_right(n);
			insert_left = false;
			continue;
		}

		/* we already have a node like this */
		return &n->data;
	}

	struct SPNODE *new = malloc(sizeof(struct SPNODE));
	if (!new)
		return NULL;

	new->left = new->right = NULL;
	new->parent = p;
	new->data = data;
	new->hint = 0;

	if (insert_left)
		sp_left(p) = new;
	else
		sp_right(p) = new;

	SPTREE(update)(s, new);
	s->n++;
	return &new->data;
}

static inline void SPTREE(replace_right)(struct SPNODE *n, struct SPNODE *r)
{
	struct SPNODE *p = sp_paren(n);
	struct SPNODE *rp = sp_paren(r);

	if (sp_left(rp) == r) {
		sp_left(rp) = sp_right(r);
		if (sp_right(r))
			sp_rparen(r) = rp;
	}

	if (sp_paren(rp) == n)
		sp_paren(rp) = r;

	sp_paren(r) = p;
	sp_left(r) = sp_left(n);

	if (sp_right(n) != r) {
		sp_right(r) = sp_right(n);
		sp_rparen(n) = r;
	}

	if (p && sp_left(p) == n)
		sp_left(p) = r;
	else if (p)
		sp_right(p) = r;

	if (sp_left(n))
		sp_lparen(n) = r;
}

static inline void SPTREE(replace_left)(struct SPNODE *n, struct SPNODE *l)
{
	struct SPNODE *p = sp_paren(n);
	struct SPNODE *lp = sp_paren(l);

	if (sp_right(lp) == l) {
		sp_right(lp) = sp_left(l);
		if (sp_left(l))
			sp_lparen(l) = lp;
	}

	if (sp_paren(lp) == n)
		sp_paren(lp) = l;

	sp_paren(l) = p;
	sp_right(l) = sp_right(n);

	if (sp_left(n) != l) {
		sp_left(l) = sp_left(n);
		sp_lparen(n) = l;
	}

	if (p && sp_left(p) == n)
		sp_left(p) = l;
	else if (p)
		sp_right(p) = l;

	if (sp_right(n))
		sp_rparen(n) = l;
}

static inline SPTREE_TYPE *SPTREE(find)(struct SPROOT *s, SPTREE_TYPE data)
{
	struct SPNODE *n = s->root;
	while (n) {
		int c = SPTREE_CMP(n->data, data);
		if (c < 0) {
			n = n->left;
			continue;
		}

		if (c > 0) {
			n = n->right;
			continue;
		}

		return &n->data;
	}

	return NULL;
}

static inline void SPTREE(remove_found)(struct SPROOT *s, SPTREE_TYPE *found)
{
	s->n--;
	struct SPNODE *del = CONTAINER_OF(found, struct SPNODE, data);
	if (sp_right(del)) {
		struct SPNODE *least = SPTREE(first)(sp_right(del));

		if (del == s->root)
			s->root = least;

		SPTREE(replace_right)(del, least);
		SPTREE(update)(s, sp_right(least));
		return;
	}

	if (sp_left(del)) {
		struct SPNODE *most = SPTREE(last)(sp_left(del));

		if (del == s->root)
			s->root = most;

		SPTREE(replace_left)(del, most);
		SPTREE(update)(s, sp_left(most));
		return;
	}

	if (del == s->root) {
		s->root = NULL;
		return;
	}

	/* empty node */
	struct SPNODE *paren = sp_paren(del);

	if (sp_left(paren) == del)
		sp_left(paren) = NULL;
	else
		sp_right(paren) = NULL;

	SPTREE(update)(s, paren);
}

static inline void SPTREE(remove)(struct SPROOT *s, SPTREE_TYPE data)
{
	SPTREE_TYPE *found = SPTREE(find)(s, data);
	if (!found)
		return;

	SPTREE(remove_found)(s, found);
	struct SPNODE *del = CONTAINER_OF(found, struct SPNODE, data);
	free(del);
}

static inline void SPTREE(destroy)(struct SPROOT *s)
{
	while (s->root) {
		SPTREE_TYPE *top = &s->root->data;
		SPTREE(remove_found)(s, top);
		struct SPNODE *del = CONTAINER_OF(top, struct SPNODE, data);
		free(del);
	}
}

#undef SPTREE
#undef SPNODE
#undef SPROOT
#undef SPTREE_NAME
#undef SPTREE_TYPE
#undef SPTREE_CMP

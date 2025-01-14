#ifndef MAP_KEY
#error "Need map key"
#endif

#ifndef MAP_TYPE
#error "Need map type"
#endif

#ifndef MAP_CMP
#error "Need map cmp"
#endif

#ifndef MAP_NAME
#error "Need map name"
#endif

#include "conts.h"

#define MAP(a) CONTS_JOIN(MAP_NAME, a)

#define MAP_NODE MAP(node)
#define MAP_ROOT MAP_NAME

struct MAP_NODE {
	MAP_KEY key;
	MAP_TYPE data;
};

static inline int MAP(cmp)(struct MAP_NODE a, struct MAP_NODE b)
{
	return MAP_CMP(a.key, b.key);
}

#define BASE(a) CONTS_JOIN(MAP(map_base), a)

#define SPTREE_TYPE struct MAP_NODE
#define SPTREE_CMP MAP(cmp)
#define SPTREE_NAME MAP(map_base)
#include "sptree.h"

struct MAP_ROOT {
	struct MAP(map_base) root;
};

static inline struct MAP_ROOT MAP(create)()
{
	return (struct MAP_ROOT){.root = BASE(create)()};
}

static inline void MAP(destroy)(struct MAP_ROOT *root)
{
	BASE(destroy)(&root->root);
}

static inline MAP_TYPE *MAP(insert)(struct MAP_ROOT *root, MAP_KEY key, MAP_TYPE data)
{
	struct MAP_NODE node = {.key = key, .data = data};
	struct MAP_NODE *res = BASE(insert)(&root->root, node);
	if (!res)
		return NULL;

	return &res->data;
}

static inline MAP_TYPE *MAP(find)(struct MAP_ROOT *root, MAP_KEY key)
{
	struct MAP_NODE node = {.key = key};
	struct MAP_NODE *res = BASE(find)(&root->root, node);
	if (!res)
		return NULL;

	return &res->data;
}

static inline void MAP(remove)(struct MAP_ROOT *root, MAP_KEY key)
{
	struct MAP_NODE node = {.key = key};
	BASE(remove)(&root->root, node);
}

static inline struct MAP_NODE *MAP(begin)(struct MAP_ROOT *root)
{
	return BASE(begin)(&root->root);
}

static inline struct MAP_NODE *MAP(next)(struct MAP_NODE *n)
{
	return BASE(next)(n);
}

static inline bool MAP(end)(struct MAP_ROOT *root, struct MAP_NODE *n)
{
	return BASE(end)(&root->root, n);
}

static inline size_t MAP(len)(struct MAP_ROOT *root)
{
	return BASE(len)(&root->root);
}

#undef MAP_KEY
#undef MAP_TYPE
#undef MAP_CMP
#undef MAP_NAME

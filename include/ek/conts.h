#ifndef CONTS_H
#define CONTS_H

#define CONTS_JOIN2(a, b) a##_##b
#define CONTS_JOIN(a, b) CONTS_JOIN2(a, b)

#define CONTAINER_OF(ptr, type, member) \
	(type *)((char *)(ptr) - offsetof(type, member))

#define foreach(name, i, s)\
	for (auto i = CONTS_JOIN(name, begin)(s);\
			!CONTS_JOIN(name, end)(s, i);\
			i = CONTS_JOIN(name, next)(i))
#endif /* CONTS_H */

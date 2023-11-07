/* common.ek */
typedef any {}

/* vec.ek */
typedef vec {
	i27  size;
	i27  cap;
	*any buf;
}

insert(*vec v, i27 i, typeof(*v.buf) e)
{
	...
}

/* define local vector type */
define vec!(t)
{
	struct vec [vec] {*t buf;}
}

/* map.ek */
typedef hashable {
	/* pointers? */
	i27 hash(hashable);
}

typedef map {
	i27 size;
	i27 cap;
	*hashable keys;
	*any values;
}

// vs. append(*map h, typeof h.keys[0] k, typeof h.values[0] e)
// vs. append(*map h, ?h.keys[0] k, ?h.values[0] e)
// vs. append(*map h, #h.keys[0] k, #h.values[0] e)
// vs. append(*map h, :h.keys[0] k, :h.values[0] e)
// vs something else, hmm
append(*map h, `h.keys[0] k, `h.values[0] e)
{
	...
}

/* main.ek */
main()
{
	vec!(i27) v;
	// should automatically find the correct insert (unless the same
	// elements as the vec typedef are used somewhere else)
	insert(v, 0, 20);
	// otherwise, force search as vec?
	insert(v as vec, 0, 20);
}

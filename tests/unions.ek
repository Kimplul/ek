typedef any {}

union basic_union {
	a u32;
	b i64;
	c f32;
}

union complex_union(A any, B any, C any) {
	a A;
	b B;
	c C;
}

main()
{
	simple_named const = {.b = 1} as basic_union;
	simple_ordinal const = {1 as u32} as basic_union; 

	// TODO: unions should be fully actualized
	complex_named const = {.b = 1} as complex_union(u32, i64, f32);
	complex_ordinal const = {1 as u32} as complex_union(u32, i64, f32);
}

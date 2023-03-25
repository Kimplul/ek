typedef any {}

struct basic_struct {
	a i64;
	b i64;
	c i64;
}

struct complex_struct (A any, B any, C any) {
	a A;
	b B;
	c C;
}

main()
{
	/* infer types */
	simple_named const = {.a = 1, .b = 2, .c = 3} as basic_struct;
	simple_ordinal const = {1, 2, 3} as basic_struct;
	simple_mixed const = {1, .b = 2, 3} as basic_struct;

	complex_named const = {.a = 1, .b = 2, .c = 3} as complex_struct;
	/* should parentheses be required around typeof? */
	complex_ordinal const = {1, 2, 3} as typeof complex_named;
	complex_mixed const = {1, .b = 2, 3} as complex_struct;

	/* force types */
	force_named complex_struct(u32, u32, u32) = {.a = 1, .b = 2, .c = 3};
	force_ordinal typeof force_named = {1, 2, 3};
	force_mixed typeof force_ordinal = {1, .b = 2, 3};

	force_inferred_named mut = {.a = 1, .b = 2, .c = 3} as
		complex_struct(u32, u32, u32);

	force_inferred_ordinal mut = {1, 2, 3} as
		complex_struct(u32, u32, u32);

	force_inferred_mixed mut = {1, .b = 2, 3} as
		complex_struct(u32, u32, u32);

	/* shouldn't be compileable due to not enough type info */
	// error_named const = {.a = 1, .b = 2, .c = 3};

	/* types should be inferred */
	force_inferred_named = {.a = 2, .b = 3, .c = 4};
	force_inferred_ordinal = {2, 3, 4};
	force_inferred_mixed = {2, .b = 3, 4};
}

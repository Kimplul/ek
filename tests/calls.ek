typedef some_type {
	add(some_type, some_type => some_type);
}

add(a u32, b u32 => u32)
{
	return a + b;
}

/* ah fuck, analyze_proc gobbles up the typeof */
some_proc(a some_type, b typeof a => typeof a)
{
	return add(a, b);
}

main()
{
	some_proc(20 as u32, 40 as u32);
}

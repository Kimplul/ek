enum A {
	a = 200,
	b
}

enum B: u8 {
	b, c
}

main()
{
	a const = a::A;
	b const = b::B;
}

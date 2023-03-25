typedef any {}

struct some_struct {
	a i64;
}

struct some_template (A any) {
	a A;
}

main()
{
	a mut i64 = 20;
	a = 200;

	b mut some_struct = {20};
	b = {200};

	c mut = {20} as some_struct;
	c = {200};

	d mut some_template = {20};
	d = {200};

	e mut some_template (i64) = {20};
	e = {200};

	f mut = {20} as some_template;
	f = {200};

	g mut = {20} as some_template(i64);
	g = {200};
}

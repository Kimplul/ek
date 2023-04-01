typedef A {}

struct generic (T1 A, T2 A) {
	a T1;
	b T2;
}

struct other_generic(T1 A) {
	a T1;
	b T1;
}

/* wow this works pretty good */
//some_func(a A, b typeof a, c i64){1;}
//some_func(a A, b typeof a, c typeof b){2;}
//some_func(a A, b typeof a, c A){3;}
//some_func(a generic(u32, u32)) {5;}
//some_func(a other_generic){6;}
// TODO: partial templates shouldn't be allowed
//some_func(a generic(u32)){6;}
//some_func(a generic) {4;}
// illegal
// TODO: traits shouldn't be allowed in template instantiation
//some_func(a generic(A, A)){6;}
//some_func(generic(generic, generic)){1;}
some_func(generic(generic, i64)){2;}
some_func(generic(i64, generic)){3;}
//some_func(generic(i64, i64)){4;}
some_func(generic){5;}

main(){
	// TODO: not fully qualified types in bodies should cause an error
	a generic(i64, u32);
	some_func(a);
}

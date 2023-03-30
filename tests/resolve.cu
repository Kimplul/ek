typedef A {}

/* wow this works pretty good */
some_func(c A, d typeof c, e i64){c;}
some_func(c A, d typeof c, e typeof d){d;}
some_func(c A, d typeof c, e A){e;}

main(){
	some_func(20 as f32, 20 as f32, 20 as f64);
}

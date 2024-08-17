gen/gen_parser.c: src/parser.y gen/gen_lexer.inc
	bison -Wcounterexamples -o gen/gen_parser.c src/parser.y

gen/gen_lexer.inc: src/lexer.l
	flex -o gen/gen_lexer.inc src/lexer.l

build/gen/parser.o: gen/gen_parser.c
	mkdir -p build/gen
	$(COMPILE_EK) -fno-analyzer -c gen/gen_parser.c -o build/gen/parser.o

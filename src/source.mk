SRC_LOCAL != echo src/*.c
SOURCES += $(SRC_LOCAL)

gen/gen_parser.c: src/parser.y
	bison -Wcounterexamples -H -o $@ $<

gen/gen_lexer.c: src/lexer.l
	flex --header-file=src/gen_lexer.h -o $@ $<

include/cu/parser.h: gen/gen_lexer.c gen/gen_parser.c

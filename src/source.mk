SRC_LOCAL != echo src/*.c
SOURCES += $(SRC_LOCAL)

src/gen_parser.c: src/parser.y
	bison -Wcounterexamples -H -o $@ $<

src/gen_lexer.c: src/lexer.l
	flex --header-file=src/gen_lexer.h -o $@ $<

include/cu/parser.h: src/gen_lexer.c src/gen_parser.c

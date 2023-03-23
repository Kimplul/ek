DO	!= echo -n > deps.mk

DEBUGFLAGS	!= [ $(RELEASE) ] && echo "-flto -O2 -DNODEBUG" || echo "-O0 -g -DDEBUG"
CFLAGS		= -Wall -Wextra
DEPFLAGS	= -MT $@ -MMD -MP -MF $@.d
INCLUDEFLAGS	= -Iinclude
COMPILEFLAGS	=
LINKFLAGS	=

# should the compiler be renamed ctc? C with Traits Compiler?
all: cu

# default values
CROSS_COMPILE	?=

# common programs
CC		= gcc

SOURCES		:=

include src/source.mk

COMPILE		= $(CROSS_COMPILE)$(CC) $(DEBUGFLAGS)\
		  $(CFLAGS) $(DEPFLAGS) $(COMPILEFLAGS) $(INCLUDEFLAGS)

OBJS		!= ./scripts/gen-deps --sources "$(SOURCES)"

include deps.mk

.PHONY: format
format:
	@find . -iname '*.[ch]' |\
		xargs -n 10 -P 0 uncrustify -c uncrustify.conf --no-backup -F -

.PHONY: license
license:
	@find . -iname '*.[ch]' |\
		xargs -n 10 -P 0 ./scripts/license

.PHONY: docs
docs:
	@./scripts/warn-undocumented
	@doxygen docs/doxygen.conf

.PHONY: check
check: cu
	./tests/check.sh

cu: $(OBJS)
	$(COMPILE) $(OBJS) -o $@

.PHONY: clean
clean:
	@$(RM) -r build cu deps.mk

.PHONY: clean_docs
clean_docs:
	@$(RM) -r docs/output
check:
	$(MAKE) -f scripts/makefile check

.DEFAULT:
	$(MAKE) -f scripts/makefile $<

SOURCES	!= echo */source.mk
DO	!= echo -n > tests.mk && rm -rf reports

# hmm, initially I had each test call a gen-simple with command line arguments
# and all but thought that running a script for each test would be too slow, so
# I tried to simplify things by making the trivial cases just append a string to
# a make variable. Apparently it didn't end up having a significant effect since
# the bottleneck was actually my SSD write speed, since all output from the test
# programs gets collected.
#
# I guess the previous approach was slightly less hacky but I'll go with this
# for now, at least it (probably) scales slightly better :) More exotic tests
# can still generate their own test cases fairly easily

# basic tests that shouldn't cause the return code to be nonzero
SIMPLE :=
# simple tests where we expect the compiler to error out with some message,
# see tests/empty for an example of usage
SIMPLE_XFAIL :=

include $(SOURCES)

# pass through xargs to 'trick' it into expanding each SIMPLE_XFAIL into a
# separate argument for the script, as make would otherwise just split at each space
# this way we can pass spaces as arguments to the generator scripts, pretty neat
# huh?
DO	!= echo "$(SIMPLE)" | xargs ./scripts/gen-simple
DO	!= echo "$(SIMPLE_XFAIL)" | xargs ./scripts/gen-simple-xfail

RM	?= rm

.PHONY: clean
clean:
	$(RM) -rf reports

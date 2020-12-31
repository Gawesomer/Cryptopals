CURRPROGS := set1/challenge5/main
CURRTESTS := set1/challenge5/tests/test_repeat_xor

PROGRAMS += $(CURRPROGS)
TESTS	 += $(CURRTESTS)

PHONYS += set1/challenge5 set1/challenge5/tests

set1/challenge5: $(CURRPROGS) $(CURRTESTS)

set1/challenge5/tests: $(CURRTESTS)

set1/challenge5/main: set1/challenge5/main.o set1/challenge5/repeat_xor.o

set1/challenge5/tests/test_repeat_xor: set1/challenge5/tests/test_repeat_xor.o \
	cTest/lib/test.a

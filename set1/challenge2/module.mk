CURRPROGS := set1/challenge2/main
CURRTESTS := set1/challenge2/tests/test_xor

PROGRAMS += $(CURRPROGS)
TESTS	 += $(CURRTESTS)

PHONYS += set1/challenge2 set1/challenge2/tests

set1/challenge2: $(CURRPROGS) $(CURRTESTS)

set1/challenge2/tests: $(CURRTESTS)

set1/challenge2/main: set1/challenge2/main.o set1/challenge2/xor.o \
	set1/challenge1/hex.o $(UTILDIR)/div.o

set1/challenge2/tests/test_xor: set1/challenge2/tests/test_xor.o \
	set1/challenge1/hex.o $(UTILDIR)/div.o cTest/lib/test.a

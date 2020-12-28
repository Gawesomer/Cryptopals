CURRPROGS := set1/challenge3/main
CURRTESTS := set1/challenge3/tests/test_freq \
	    set1/challenge3/tests/test_single_xor

PROGRAMS += $(CURRPROGS)
TESTS	 += $(CURRTESTS)

PHONYS += set1/challenge3 set1/challenge3/tests

set1/challenge3: $(CURRPROGS) $(CURRTESTS)

set1/challenge3/tests: $(CURRTESTS)

set1/challenge3/main: set1/challenge3/main.o set1/challenge3/single_xor.o \
	set1/challenge3/freq.o set1/challenge1/hex.o $(UTILDIR)/div.o

set1/challenge3/tests/test_freq: set1/challenge3/tests/test_freq.o \
	cTest/lib/test.a

set1/challenge3/tests/test_single_xor: set1/challenge3/tests/test_single_xor.o \
	set1/challenge3/freq.o set1/challenge1/hex.o $(UTILDIR)/div.o \
	cTest/lib/test.a

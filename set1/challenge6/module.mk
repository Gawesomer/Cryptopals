CURRPROGS := set1/challenge6/main
CURRTESTS := set1/challenge6/tests/test_ham \
	set1/challenge6/tests/test_break_repeatxor

PROGRAMS += $(CURRPROGS)
TESTS	 += $(CURRTESTS)

PHONYS += set1/challenge6 set1/challenge6/tests

set1/challenge6: $(CURRPROGS) $(CURRTESTS)

set1/challenge6/tests: $(CURRTESTS)

set1/challenge6/main: set1/challenge6/main.o set1/challenge1/base64.o \
	set1/challenge1/hex.o set1/challenge6/break_repeatxor.o \
	set1/challenge5/repeat_xor.o \
	set1/challenge3/single_xor.o set1/challenge3/freq.o set1/challenge2/xor.o \
	set1/challenge6/ham.o $(UTILDIR)/arr.o $(UTILDIR)/div.o

set1/challenge6/tests/test_ham: set1/challenge6/tests/test_ham.o \
	cTest/lib/test.a

set1/challenge6/tests/test_break_repeatxor: set1/challenge6/tests/test_break_repeatxor.o \
	set1/challenge3/single_xor.o set1/challenge3/freq.o set1/challenge2/xor.o \
	set1/challenge5/repeat_xor.o \
	set1/challenge6/ham.o $(UTILDIR)/arr.o $(UTILDIR)/div.o cTest/lib/test.a

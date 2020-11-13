CURRPROGS := set1/challenge3/main set1/challenge3/tests/test_freq \
	    set1/challenge3/tests/test_single_xor

PROGRAMS += $(CURRPROGS)

PHONYS += set1/challenge3

set1/challenge3: $(CURRPROGS)

set1/challenge3/main: set1/challenge3/main.o set1/challenge3/single_xor.o \
	set1/challenge3/freq.o set1/challenge1/hex.o $(UTILDIR)/div.o

set1/challenge3/tests/test_freq: set1/challenge3/tests/test_freq.o \
	$(UTILDIR)/test.a

set1/challenge3/tests/test_single_xor: set1/challenge3/tests/test_single_xor.o \
	set1/challenge3/freq.o set1/challenge1/hex.o $(UTILDIR)/div.o \
	$(UTILDIR)/test.a

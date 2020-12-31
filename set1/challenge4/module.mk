CURRPROGS := set1/challenge4/main
CURRTESTS := 

PROGRAMS += $(CURRPROGS)
TESTS	 += $(CURRTESTS)

PHONYS += set1/challenge4 set1/challenge4/tests

set1/challenge4: $(CURRPROGS) $(CURRTESTS)

set1/challenge4/tests: $(CURRTESTS)

set1/challenge4/main: set1/challenge4/main.o set1/challenge3/freq.o \
	set1/challenge3/single_xor.o set1/challenge1/hex.o $(UTILDIR)/div.o

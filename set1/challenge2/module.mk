PROGRAMS += set1/challenge2/main set1/challenge2/tests/test_xor

set1/challenge2/main: set1/challenge2/main.o set1/challenge2/xor.o \
	set1/challenge1/hex.o $(UTILDIR)/div.o

set1/challenge2/tests/test_xor: set1/challenge2/tests/test_xor.o \
	set1/challenge1/hex.o $(UTILDIR)/div.o $(UTILDIR)/cassert.o

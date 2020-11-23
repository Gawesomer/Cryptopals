CURRPROGS := set1/challenge1/main
CURRTESTS := set1/challenge1/tests/test_base64 set1/challenge1/tests/test_hex

PROGRAMS += $(CURRPROGS)
TESTS	 += $(CURRTESTS)

PHONYS += set1/challenge1 set1/challenge1/tests

set1/challenge1: $(CURRPROGS) $(CURRTESTS)

set1/challenge1/tests: $(CURRTESTS)

set1/challenge1/main: set1/challenge1/main.o set1/challenge1/base64.o \
	set1/challenge1/hex.o $(UTILDIR)/div.o

set1/challenge1/tests/test_base64: set1/challenge1/tests/test_base64.o \
	set1/challenge1/hex.o $(UTILDIR)/div.o $(UTILDIR)/test.a

set1/challenge1/tests/test_hex: set1/challenge1/tests/test_hex.o \
	$(UTILDIR)/div.o $(UTILDIR)/test.a

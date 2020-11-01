CC	 = gcc
CFLAGS	 = -g -ggdb3
CPPFLAGS = -Wall -pedantic -I ./include -MMD -MP

ARFLAGS  = rvu

.PHONY: all clean

SRCS = $(shell find . -name "*.c")
OBJS = $(SRCS:%.c=%.o)
DEPS = $(OBJS:%.o=%.d)

PROGRAMS=set1/challenge1/main set1/challenge1/tests/test_base64 \
	 set1/challenge1/tests/test_hex set1/challenge2/tests/test_xor \
	 set1/challenge2/main set1/challenge3/tests/test_freq \
	 set1/challenge3/tests/test_single_xor

all: $(PROGRAMS)

set1/challenge1/main: set1/challenge1/main.o set1/challenge1/base64.o \
	set1/challenge1/hex.o util/div.o

set1/challenge1/tests/test_base64: set1/challenge1/tests/test_base64.o \
	set1/challenge1/hex.o util/div.o util/cassert.o

set1/challenge1/tests/test_hex: set1/challenge1/tests/test_hex.o util/div.o \
	util/cassert.o

set1/challenge2/tests/test_xor: set1/challenge2/tests/test_xor.o \
	set1/challenge1/hex.o util/div.o util/cassert.o

set1/challenge2/main: set1/challenge2/main.o set1/challenge2/xor.o \
	set1/challenge1/hex.o util/div.o

set1/challenge3/tests/test_freq: set1/challenge3/tests/test_freq.o \
	util/cassert.o

set1/challenge3/tests/test_single_xor: set1/challenge3/tests/test_single_xor.o \
	util/cassert.o

clean: 
	$(RM) *.o *.a $(PROGRAMS) $(OBJS) $(DEPS)

-include $(DEPS)

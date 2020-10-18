CC	 = gcc
CFLAGS	 = -g -ggdb3
CPPFLAGS = -Wall -pedantic

ARFLAGS  = rvu

.PHONEY: all clean

all: test_hex test_base64

test_hex: test_hex.o div.o

test_base64: test_base64.o hex.o div.o

clean: 
	rm -f *.o *.a test_hex test_base64

UTILDIR = ./util

CC	 := gcc
CFLAGS	 := -g -ggdb3 -Wall -Wextra -Werror -pedantic
CPPFLAGS := -I ./include -MMD -MP

ARFLAGS  := rvu

.PHONY: all clean

SRCS := $(shell find . -name "*.c")
OBJS := $(SRCS:%.c=%.o)
DEPS := $(OBJS:%.o=%.d)

# each module will add to this
PROGRAMS =

include $(shell find . -name "module.mk")

-include $(DEPS)

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS) $(OBJS) $(DEPS)

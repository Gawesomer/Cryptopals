UTILDIR    := ./util
INCLUDEDIR := ./include

CC	 := gcc
CFLAGS	 := -g -ggdb3 -Wall -Wextra -Werror -pedantic
CPPFLAGS := -I $(INCLUDEDIR) -MMD -MP
ARFLAGS  := rvu

SRCS := $(shell find . -name "*.c")
OBJS := $(SRCS:%.c=%.o)
DEPS := $(OBJS:%.o=%.d)

# each module will add to these
PROGRAMS :=
TESTS	 :=
PHONYS   :=

include $(shell find . -name "module.mk")

-include $(DEPS)

all: $(PROGRAMS) $(TESTS)

tests: $(TESTS)

clean:
	$(RM) $(PROGRAMS) $(TESTS) $(OBJS) $(DEPS)

.PHONY: all tests clean $(PHONYS)

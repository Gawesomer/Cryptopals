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
PHONYS   :=

include $(shell find . -name "module.mk")

-include $(DEPS)

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS) $(OBJS) $(DEPS)

.PHONY: all clean $(PHONYS)

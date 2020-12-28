# Build system inspired from Peter Miller's paper
# "Recursive make considered harmful".
#
# Each module of the project defines a `module.mk` which is included by this
# Makefile in order to use a single Makefile for the project.
# Git submodules (which will be referred to as subprojects) are identified and
# built individually using recursive make.
#
# Usage:
# - `make all` should be used instead of `make` when building the whole project
#   as a simple `make` would simply build the first rule of the first module.
# - `make tests` builds all tests
# - module.mk's often declare directory targets to build submodules
#   individually
#   e.g.
#   	make set1/challenge1
#   	make set1/challenge1/tests
# - Submodules are built in `all` and cleaned in `clean`. They also have
#   individual build and clean targets; `submodule` and `clean-submodule`

UTILDIR     := ./util
INCLUDEDIRS := ./include ./cTest/include

INCLUDES    := $(addprefix -I , $(INCLUDEDIRS))

CC	 := gcc
CFLAGS	 := -std=gnu11 -g -ggdb3 -Wall -Wextra -Werror -pedantic
CPPFLAGS := $(INCLUDES) -MMD -MP
ARFLAGS  := rvu
RM	 := rm -rf

# make sure to escape the `$`
SUBPROJECTS := $(shell git submodule status | awk '{print $$2}')
PREFIXEDSUBPROJECTS := $(addprefix ./, $(SUBPROJECTS))

# ignore subprojects
SRCS := $(shell find . -path $(PREFIXED_SUBPROJECTS) -prune -false -o -name "*.c")
OBJS := $(SRCS:%.c=%.o)
DEPS := $(OBJS:%.o=%.d)
DSYM := $(shell find . -path $(PREFIXED_SUBPROJECTS) -prune -false -o -name "*.dSYM")

# each module will add to these
PROGRAMS :=
TESTS	 :=
PHONYS   :=

include $(shell find . -path $(PREFIXED_SUBPROJECTS) -prune -false -o -name "module.mk")

-include $(DEPS)

all: $(SUBPROJECTS) $(PROGRAMS) $(TESTS)

$(SUBPROJECTS):
	$(MAKE) all -C $@

$(SUBPROJECTS:%=clean-%):
	$(MAKE) clean -C $(@:clean-%=%)

# cTest
cTest/lib/test.a: cTest

tests: $(TESTS)

clean: $(SUBPROJECTS:%=clean-%)
	$(RM) $(PROGRAMS) $(TESTS) $(OBJS) $(DEPS) $(DSYM)

.PHONY: all tests clean $(PHONYS) $(SUBPROJECTS) $(SUBPROJECTS:%=clean-%)

CURRPROGS := util/test.a util/tests/test_div util/tests/test_cassert \
	util/tests/test_cmp util/tests/test_displ

PROGRAMS += $(CURRPROGS)

PHONYS += util

util: $(CURRPROGS)

util/test.a: util/test.a(util/cassert.o util/cmp.o util/displ.o)

util/tests/test_div: util/tests/test_div.o util/test.a

util/tests/test_cassert: util/tests/test_cassert.o util/cmp.o util/displ.o

util/tests/test_cmp: util/tests/test_cmp.o

util/tests/test_displ: util/tests/test_displ.o

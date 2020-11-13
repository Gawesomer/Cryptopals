CURRPROGS := util/tests/test_div util/tests/test_cassert util/tests/test_cmp

PROGRAMS += $(CURRPROGS)

PHONYS += util

util: $(CURRPROGS)

util/tests/test_div: util/tests/test_div.o util/cassert.o util/cmp.o

util/tests/test_cassert: util/tests/test_cassert.o util/cmp.o

util/tests/test_cmp: util/tests/test_cmp.o

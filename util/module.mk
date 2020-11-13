CURRPROGS := util/tests/test_div util/tests/test_cassert

PROGRAMS += $(CURRPROGS)

PHONYS += util

util: $(CURRPROGS)

util/tests/test_div: util/tests/test_div.o util/cassert.o

util/tests/test_cassert: util/tests/test_cassert.o

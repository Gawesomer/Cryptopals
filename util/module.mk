CURRPROGS := util/tests/test_div

PROGRAMS += $(CURRPROGS)

PHONYS += util

util: $(CURRPROGS)

util/tests/test_div: util/tests/test_div.o util/cassert.o

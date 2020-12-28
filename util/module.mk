CURRTESTS := util/tests/test_div

TESTS	 += $(CURRTESTS)

PHONYS += util/tests

util: $(CURRTESTS)

util/tests: $(CURRTESTS)

util/tests/test_div: util/tests/test_div.o cTest/lib/test.a

CURRTESTS := util/tests/test_div util/tests/test_arr

TESTS	 += $(CURRTESTS)

PHONYS += util/tests

util: $(CURRTESTS)

util/tests: $(CURRTESTS)

util/tests/test_div: util/tests/test_div.o cTest/lib/test.a

util/tests/test_arr: util/tests/test_arr.o cTest/lib/test.a

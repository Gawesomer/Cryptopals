INCLUDEDIRS := ./include ./cTest/include
UTILDIR     := ./util

cTest/lib/test.a: cTest

runtests:
	./run_tests.py --valgrind

PHONYS := runtests

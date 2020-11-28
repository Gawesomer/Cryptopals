#ifndef _TEST_FRAMEWORK_H_
#define _TEST_FRAMEWORK_H_

#include <stdio.h>
#include <stdlib.h>

/* These are the internal test functions.
 * They should not be called directly and should instead by used by utilizing
 * their respective wrapper macros defined below
 */
int register_test(const char *name, int (*fun)(void));
int run_tests(const char *filename);

/* Registers a test to be run by `RUN_TESTS`
 * params:
 * 	- fun: test function to run
 * 	       a test function is an integer function that returns 0 on success
 * 	       and nonzero otherwise, it takes no arguments
 * returns:
 * 	0 on success, nonzero otherwise
 */
#define REGISTER_TEST(fun)	register_test(#fun, fun)

/* Runs all registered tests and prints the results to STDOUT
 * params:
 * 	none
 * returns:
 * 	number of tests that failed
 */
#define RUN_TESTS()	run_tests(__FILE__)

#endif

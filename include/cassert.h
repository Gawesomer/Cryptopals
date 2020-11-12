#ifndef _CASSERT_H_
#define _CASSERT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <assert.h>

/* Assert that `expected` and `actual` floats are equal
 * params:
 * 	- expected: float to compare to
 * 	- actual: float to be compared
 * 	- eps: positive epsilon to specify the acceptable range within which
 * 	       floats may be considered equal
 * returns:
 * 	ends execution on failure
 * 	otherwise nothing
 */
void assert_floats_eq(float expected, float actual, float eps);

/* Assert that `expected` and `actual` byte arrays are pairwise equal
 * params:
 * 	- expectedlen: length of `expected`
 * 	- expected: byte array to compare to
 * 	- actual: byte array to be compared
 * returns:
 * 	ends execution on failure
 * 	otherwise nothing
 * notes:
 * 	fails to notice that `actual` may be larger than `expected`
 */
void assert_bytes_eq(size_t expectedlen, const uint8_t *expected, \
		     const uint8_t *actual);

/* Assert that `expected` and `actual` float arrays are pairwise equal
 * params:
 * 	- expectedlen: length of `expected`
 * 	- expected: float array to compare to
 * 	- actual: float array to be compared
 * 	- eps: positive epsilon to specify the acceptable range within which
 * 	       floats may be considered equal
 * returns:
 * 	ends execution on failure
 * 	otherwise nothing
 * notes:
 * 	fails to notice that `actual` may be larger than `expected`
 */
void assert_farrs_eq(size_t expectedlen, const float *expected, \
		     const float *actual, float eps);

/* These are the internal test functions.
 * They should not be called directly and should instead by used by utilizing
 * their respective wrapper macros defined below
 */
int test_true(const char *f, int l, const char *fun, const char *tk, int exp);
int test_int_eq(const char *f, int l, const char *fun, \
		const char *a_tk, const char *b_tk, int a, int b);

/* Tests boolean to be true, prints error message if `exp` is false
 * params:
 * 	- exp: boolean expression
 * returns:
 * 	1 if `exp` is true, 0 otherwise
 */
#define TEST_TRUE(exp)	test_true(__FILE__, __LINE__, __FUNCTION__, #exp, exp)

/* Tests integers to be equal, prints error message if `a` is not equal to `b`
 * params:
 * 	- a: integer
 * 	- b: integer
 * returns:
 * 	1 if `a` == `b`, 0 otherwise
 */
#define TEST_INT_EQ(a, b)	test_int_eq(__FILE__, __LINE__, __FUNCTION__, \
					#a, #b, a, b)

#endif

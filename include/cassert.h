#ifndef _CASSERT_H_
#define _CASSERT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <string.h>
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
int test_bytes_eq(const char *f, int l, const char *fun, \
		  const char *len_tk, const char *a_tk, const char *b_tk, \
		  size_t len, const uint8_t *a, const uint8_t *b);
int test_str_eq(const char *f, int l, const char *fun, \
		  const char *s1_tk, const char *s2_tk, \
		  const char *s1, const char *s2);

/* Tests boolean to be true, prints error message if `exp` is false
 * params:
 * 	- exp: boolean expression
 * returns:
 * 	0 if `exp` is true, 1 otherwise
 */
#define TEST_TRUE(exp)	test_true(__FILE__, __LINE__, __FUNCTION__, #exp, exp)

/* Tests integers to be equal, prints error message if `a` is not equal to `b`
 * params:
 * 	- a: integer
 * 	- b: integer
 * returns:
 * 	0 if `a` == `b`, 1 otherwise
 */
#define TEST_INT_EQ(a, b)	test_int_eq(__FILE__, __LINE__, __FUNCTION__, \
					#a, #b, a, b)

/* Tests byte arrays to be equal, prints error message if `a` is not equal to
 * `b`
 * params:
 * 	- len: integer length of both `a` and `b`
 * 	- a: uint8_t byte array
 * 	- b: uint8_t byte array
 * returns:
 * 	0 if `a` == `b`, 1 otherwise
 * notes:
 * 	assumes that both `a` and `b` are of size `len`;
 * 	in the case where one is shorter, it will cause a read out of bounds,
 * 	in the case where on is longer, it will fail to notice it, possibly
 * 	resulting in false positives
 */
#define TEST_BYTES_EQ(len, a, b)	test_bytes_eq(__FILE__, __LINE__, \
					__FUNCTION__, #len, #a, #b, len, a, b)

/* Tests C-strings to be equal, prints error message if `s1` is not equal to \
 * `s2`
 * params:
 *	- s1: C-string
 *	- s2: C-string
 * returns:
 * 	0 if `s1` == `s2`, 1 otherwise
 */
#define TEST_STR_EQ(s1, s2)	test_str_eq(__FILE__, __LINE__, \
				__FUNCTION__, #s1, #s2, s1, s2)

#endif

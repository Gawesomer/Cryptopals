#ifndef _CASSERT_H_
#define _CASSERT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <string.h>

/* These are the internal test functions.
 * They should not be called directly and should instead by used by utilizing
 * their respective wrapper macros defined below
 */
int test_true(const char *f, int l, const char *fun, const char *tk, int exp);
int test_int_eq(const char *f, int l, const char *fun, \
		const char *a_tk, const char *b_tk, int a, int b);
int test_float_eq(const char *f, int l, const char *fun, \
		  const char *a_tk, const char *b_tk, const char *exp_tk, \
		  float a, float b, float eps);
int test_bytes_eq(const char *f, int l, const char *fun, \
		  const char *a_tk, const char *b_tk, const char *len_tk, \
		  const uint8_t *a, const uint8_t *b, size_t len);
int test_int_arr_eq(const char *f, int l, const char *fun, \
		    const char *a_tk, const char *b_tk, const char *len_tk, \
		    const int *a, const int *b, size_t len);
int test_float_arr_eq(const char *f, int l, const char *fun, \
		      const char *a_tk, const char *b_tk, \
		      const char *eps_tk, const char *len_tk, \
		      const float *a, const float *b, float eps, size_t len);
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

/* Tests floats to be equal, prints error message if `a` is not equal to `b`
 * params:
 * 	- a: float
 * 	- b: float
 * 	- eps: positive epsilon to specify the acceptable range within which
 * 	       floats may be considered equal
 * returns:
 * 	0 if `a` == `b`, 1 otherwise
 */
#define TEST_FLOAT_EQ(a, b, eps)	test_float_eq(__FILE__, __LINE__, \
					__FUNCTION__, #a, #b, #eps, a, b, eps)

/* Tests byte arrays to be equal, prints error message if `a` is not equal to
 * `b`
 * params:
 * 	- a: uint8_t byte array
 * 	- b: uint8_t byte array
 * 	- len: size_t length of both `a` and `b`
 * returns:
 * 	0 if `a` == `b`, 1 otherwise
 * notes:
 * 	assumes that both `a` and `b` are of size `len`;
 * 	in the case where one is shorter, it will cause a read out of bounds,
 * 	in the case where one is longer, it will fail to notice it, possibly
 * 	resulting in false positives
 */
#define TEST_BYTES_EQ(a, b, len)	test_bytes_eq(__FILE__, __LINE__, \
					__FUNCTION__, #a, #b, #len, a, b, len)

/* Tests integer arrays to be equal, prints error message if `a` is not equal
 * to `b`
 * params:
 * 	- a: integer array
 * 	- b: integer array
 * 	- len: size_t length of both `a` and `b`
 * returns:
 * 	0 if `a` == `b`, 1 otherwise
 * notes:
 * 	assumes that both `a` and `b` are of size `len`;
 * 	in the case where one is shorter, it will cause a read out of bounds,
 * 	in the case where one is longer, it will fail to notice it, possibly
 * 	resulting in false positives
 */
#define TEST_INT_ARR_EQ(a, b, len)	test_int_arr_eq(__FILE__, __LINE__, \
					__FUNCTION__, #a, #b, #len, a, b, len)

/* Tests float arrays to be equal, prints error message if `a` is not equal
 * to `b`
 * params:
 * 	- a: float array
 * 	- b: float array
 * 	- eps: positive epsilon to specify the acceptable range within which
 * 	       floats may be considered equal
 * 	- len: size_t length of both `a` and `b`
 * returns:
 * 	0 if `a` == `b`, 1 otherwise
 * notes:
 * 	assumes that both `a` and `b` are of size `len`;
 * 	in the case where one is shorter, it will cause a read out of bounds,
 * 	in the case where one is longer, it will fail to notice it, possibly
 * 	resulting in false positives
 */
#define TEST_FLOAT_ARR_EQ(a, b, eps, len)	test_float_arr_eq(__FILE__, \
						__LINE__, __FUNCTION__, \
						#a, #b, #eps, #len, \
						a, b, eps, len)

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

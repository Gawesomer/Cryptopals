#ifndef _CASSERT_H_
#define _CASSERT_H_

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

#endif

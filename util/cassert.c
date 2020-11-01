#include "cassert.h"
#include <stdio.h>

void assert_floats_eq(float expected, float actual, float eps)
{
	float lower, upper;

	if ((FLT_MAX-eps) <= expected)
		upper = FLT_MAX;
	else
		upper = expected+eps;

	if ((-1)*(FLT_MAX+eps) >= expected)
		lower = (-1)*FLT_MAX;
	else
		lower = expected-eps;

	assert(lower <= actual && actual <= upper);
}

void assert_bytes_eq(size_t expectedlen, const uint8_t *expected, \
		     const uint8_t *actual)
{
	int i;
	for (i = 0; i < expectedlen; ++i)
		assert(actual[i] == expected[i]);
}

void assert_farrs_eq(size_t expectedlen, const float *expected,
		     const float *actual, float eps)
{
	int i;
	for (i = 0; i < expectedlen; ++i)
		assert_floats_eq(expected[i], actual[i], eps);
}

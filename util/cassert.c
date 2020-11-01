#include "cassert.h"

void assert_floats_eq(float expected, float actual, float eps)
{
	assert((expected-eps) <= actual);
	assert(actual <= (expected+eps));
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

#include "cassert.h"

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
	for (i = 0; (size_t)i < expectedlen; ++i)
		assert(actual[i] == expected[i]);
}

void assert_farrs_eq(size_t expectedlen, const float *expected,
		     const float *actual, float eps)
{
	int i;
	for (i = 0; (size_t)i < expectedlen; ++i)
		assert_floats_eq(expected[i], actual[i], eps);
}

int test_true(const char *f, int l, const char *fun, const char *tk, int exp)
{
	if (exp)
		return 1;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf("\t\tTEST_TRUE(%s)\n", tk);
	printf("\t\t\t`%s` not true\n", tk);
	printf("----------------------------------------------------------\n");

	return 0;
}

int test_int_eq(const char *f, int l, const char *fun, \
		const char *a_tk, const char *b_tk, int a, int b)
{
	if (a == b)
		return 1;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf ("\t\tTEST_INT_EQ(%s, %s)\n", a_tk, b_tk);
	printf("\t\t\t%d != %d\n", a, b);
	printf("----------------------------------------------------------\n");

	return 0;
}

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
		return 0;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf("\t\tTEST_TRUE(%s)\n", tk);
	printf("\t\t\t`%s` not true\n", tk);
	printf("----------------------------------------------------------\n");

	return 1;
}

int test_int_eq(const char *f, int l, const char *fun, \
		const char *a_tk, const char *b_tk, int a, int b)
{
	if (a == b)
		return 0;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf ("\t\tTEST_INT_EQ(%s, %s)\n", a_tk, b_tk);
	printf("\t\t\t%d != %d\n", a, b);
	printf("----------------------------------------------------------\n");

	return 1;
}

int test_bytes_eq(const char *f, int l, const char *fun, \
		  const char *len_tk, const char *a_tk, const char *b_tk, \
		  size_t len, const uint8_t *a, const uint8_t *b)
{
	int i;

	if (!a && !b) {
		return 0;
	} else if (a && b) {
		for (i = 0; (size_t)i < len && a[i] == b[i]; ++i)
			;

		if ((size_t)i == len)
			return 0;
	}

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf("\t\tTEST_BYTES_EQ(%s, %s, %s)\n", len_tk, a_tk, b_tk);
	if (a) {
		printf("\t\t\t[");
		for (i = 0; (size_t)i < len-1; ++i)
			printf("%x%s", a[i], ((size_t)i == len-1) ? "" : ", ");
		printf("]\n");
	} else {
		printf("\t\t\tNULL\n");
	}
	if (b) {
		printf("\t\t!=\t[");
		for (i = 0; (size_t)i < len; ++i)
			printf("%x%s", b[i], ((size_t)i == len-1) ? "" : ", ");
		printf("]\n");
	} else {
		printf("\t\t!=\tNULL\n");
	}
	printf("----------------------------------------------------------\n");

	return 1;
}

int test_str_eq(const char *f, int l, const char *fun, \
		 const char *s1_tk, const char *s2_tk, \
		 const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return 0;
	if ((s1 && s2) && strcmp(s1, s2) == 0)
		return 0;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf("\t\tTEST_STRS_EQ(%s, %s)\n", s1_tk, s2_tk);
	if (s1)
		printf("\t\t\t\"%s\"\n", s1);
	else
		printf("\t\t\tNULL\n");
	if (s2)
		printf("\t\t!=\t\"%s\"\n", s2);
	else
		printf("\t\t!=\tNULL\n");
	printf("----------------------------------------------------------\n");

	return 1;
}

#include "cassert.h"

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
	if (intcmp(&a, &b) == 0)
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

int test_float_eq(const char *f, int l, const char *fun, \
		  const char *a_tk, const char *b_tk, \
		  float a, float b)
{
	if (floatcmp(&a, &b) == 0)
		return 0;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf ("\t\tTEST_FLOAT_EQ(%s, %s)\n", a_tk, b_tk);
	printf("\t\t\t%f != %f\n", a, b);
	printf("----------------------------------------------------------\n");

	return 1;
}

int test_bytes_eq(const char *f, int l, const char *fun, \
		  const char *a_tk, const char *b_tk, const char *len_tk, \
		  const uint8_t *a, const uint8_t *b, size_t len)
{
	if (arrcmp(a, b, len, sizeof(uint8_t), bytecmp) == 0)
		return 0;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf("\t\tTEST_BYTES_EQ(%s, %s, %s)\n", a_tk, b_tk, len_tk);
	printf("\t\t\t");
	arr_displ(stdout, a, len, sizeof(uint8_t), byte_displ);
	printf("\n");
	printf("\t\t!=\t");
	arr_displ(stdout, b, len, sizeof(uint8_t), byte_displ);
	printf("\n");
	printf("----------------------------------------------------------\n");

	return 1;
}

int test_int_arr_eq(const char *f, int l, const char *fun, \
		  const char *a_tk, const char *b_tk, const char *len_tk, \
		  const int *a, const int *b, size_t len)
{
	if (arrcmp(a, b, len, sizeof(int), intcmp) == 0)
		return 0;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf("\t\tTEST_INT_ARR_EQ(%s, %s, %s)\n", a_tk, b_tk, len_tk);
	printf("\t\t\t");
	arr_displ(stdout, a, len, sizeof(int), int_displ);
	printf("\n");
	printf("\t\t!=\t");
	arr_displ(stdout, b, len, sizeof(int), int_displ);
	printf("\n");
	printf("----------------------------------------------------------\n");

	return 1;
}

int test_float_arr_eq(const char *f, int l, const char *fun, \
		const char *a_tk, const char *b_tk, const char *len_tk, \
		const float *a, const float *b, size_t len)
{
	if (arrcmp(a, b, len, sizeof(float), floatcmp) == 0)
		return 0;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf("\t\tTEST_FLOAT_ARR_EQ(%s, %s, %s)\n", a_tk, b_tk, len_tk);
	printf("\t\t\t");
	arr_displ(stdout, a, len, sizeof(float), float_displ);
	printf("\n");
	printf("\t\t!=\t");
	arr_displ(stdout, b, len, sizeof(float), float_displ);
	printf("\n");
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
	printf("\t\tTEST_STR_EQ(%s, %s)\n", s1_tk, s2_tk);
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

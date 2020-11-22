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

int test_float_eq(const char *f, int l, const char *fun, \
		  const char *a_tk, const char *b_tk, \
		  float a, float b)
{
	if (float_eq(a, b) == 0)
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
	int i;

	if (arrcmp(a, b, len, sizeof(uint8_t), bytecmp) == 0)
		return 0;

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf("\t\tTEST_BYTES_EQ(%s, %s, %s)\n", a_tk, b_tk, len_tk);
	if (a) {
		printf("\t\t\t[");
		for (i = 0; (size_t)i < len; ++i)
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

int test_int_arr_eq(const char *f, int l, const char *fun, \
		  const char *a_tk, const char *b_tk, const char *len_tk, \
		  const int *a, const int *b, size_t len)
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
	printf("\t\tTEST_INT_ARR_EQ(%s, %s, %s)\n", a_tk, b_tk, len_tk);
	if (a) {
		printf("\t\t\t[");
		for (i = 0; (size_t)i < len; ++i)
			printf("%d%s", a[i], ((size_t)i == len-1) ? "" : ", ");
		printf("]\n");
	} else {
		printf("\t\t\tNULL\n");
	}
	if (b) {
		printf("\t\t!=\t[");
		for (i = 0; (size_t)i < len; ++i)
			printf("%d%s", b[i], ((size_t)i == len-1) ? "" : ", ");
		printf("]\n");
	} else {
		printf("\t\t!=\tNULL\n");
	}
	printf("----------------------------------------------------------\n");

	return 1;
}

int test_float_arr_eq(const char *f, int l, const char *fun, \
		const char *a_tk, const char *b_tk, const char *len_tk, \
		const float *a, const float *b, size_t len)
{
	int i;

	if (!a && !b) {
		return 0;
	} else if (a && b) {
		for (i=0; (size_t)i<len && float_eq(a[i],b[i])==0; ++i)
			;
		if ((size_t)i == len)
			return 0;
	}

	printf("==========================================================\n");
	printf("FAIL: %s\n", fun);
	printf("----------------------------------------------------------\n");
	printf("\tFile \"%s\", line %d:\n", f, l);
	printf("\t\tTEST_FLOAT_ARR_EQ(%s, %s, %s)\n", a_tk, b_tk, len_tk);
	if (a) {
		printf("\t\t\t[");
		for (i = 0; (size_t)i < len; ++i)
			printf("%f%s", a[i], ((size_t)i == len-1) ? "" : ", ");
		printf("]\n");
	} else {
		printf("\t\t\tNULL\n");
	}
	if (b) {
		printf("\t\t!=\t[");
		for (i = 0; (size_t)i < len; ++i)
			printf("%f%s", b[i], ((size_t)i == len-1) ? "" : ", ");
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

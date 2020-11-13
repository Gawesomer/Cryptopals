#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../cmp.c"

/*** intcmp ***/

void test_intcmp_eq(void)
{
	printf("%s\n", __func__);

	int a, b;

	a = b = 7;

	assert(intcmp(&a, &b) == 0);
}

void test_intcmp_lt(void)
{
	printf("%s\n", __func__);

	int a, b;

	a = 5;
	b = 7;

	assert(intcmp(&a, &b) < 0);
}

void test_intcmp_gt(void)
{
	printf("%s\n", __func__);

	int a, b;

	a = 7;
	b = 5;

	assert(intcmp(&a, &b) > 0);
}

void test_intcmp_null(void)
{
	printf("%s\n", __func__);

	int e = 0;

	assert(intcmp(&e, NULL) > 0);
	assert(intcmp(NULL, &e) < 0);
	assert(intcmp(NULL, NULL) == 0);
}

/*** arrcmp ***/

void test_arrcmp_eq(void)
{
	printf("%s\n", __func__);

	int a_arr[] = {0, 1, 2};
	int b_arr[] = {0, 1, 2};

	assert(arrcmp(a_arr, b_arr, 3, sizeof(int), intcmp) == 0);
}

void test_arrcmp_neq(void)
{
	printf("%s\n", __func__);

	int a_arr[] = {0, 2, 1};
	int b_arr[] = {0, 1, 2};

	assert(arrcmp(a_arr, b_arr, 3, sizeof(int), intcmp) != 0);
}

void test_arrcmp_null(void)
{
	printf("%s\n", __func__);

	int arr[] = {0, 1, 2};

	assert(arrcmp(arr, NULL, 3, sizeof(int), intcmp) != 0);
	assert(arrcmp(NULL, arr, 3, sizeof(int), intcmp) != 0);
	assert(arrcmp(NULL, NULL, 0, sizeof(int), intcmp) == 0);
}

int main(void)
{
	printf("--- %s ---\n", __FILE__);

	test_intcmp_eq();
	test_intcmp_lt();
	test_intcmp_gt();
	test_intcmp_null();

	test_arrcmp_eq();
	test_arrcmp_neq();
	test_arrcmp_null();

	return EXIT_SUCCESS;
}

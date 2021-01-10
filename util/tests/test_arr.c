#include <stdio.h>
#include <stdlib.h>

#include "cTest.h"
#include "../arr.c"

/*** slice ***/

int test_slice_null(void)
{
	size_t res_size;

	return TEST_INT_ARR_EQ(slice(NULL, 1, 1, 1, 1, &res_size), NULL, 0);
}

int test_slice_empty_arr(void)
{
	int status = 0;
	int arr[] = {0};
	size_t res_size;

	status += TEST_INT_ARR_EQ(slice(arr, 0, sizeof(int), 1, 1, &res_size), NULL, 0);
	status += TEST_INT_EQ(0, res_size);

	return status;
}

int test_slice_zero_data_size(void)
{
	int status = 0;
	int arr[] = {0};
	size_t res_size;

	status += TEST_INT_ARR_EQ(slice(arr, 1, 0, 1, 0, &res_size), NULL, 0);
	status += TEST_INT_EQ(0, res_size);

	return status;
}

int test_slice_empty_block(void)
{
	int status = 0;
	int arr[] = {0};
	size_t res_size;

	status += TEST_INT_ARR_EQ(slice(arr, 1, sizeof(int), 0, 0, &res_size), NULL, 0);
	status += TEST_INT_EQ(0, res_size);

	return status;
}

int test_slice_negative_block_num(void)
{
	int status = 0;
	int arr[] = {0};
	size_t res_size;

	status += TEST_INT_ARR_EQ(slice(arr, 1, sizeof(int), 1, -1, &res_size), NULL, 0);
	status += TEST_INT_EQ(0, res_size);

	return status;
}

int test_slice_block_num_exactly_over_bounds(void)
{
	int status = 0;
	int arr[] = {1, 2, 3};
	int *expected = NULL;
	int *actual;
	size_t expected_size = 0;
	size_t res_size = 1;

	actual = slice(arr, 3, sizeof(int), 1, 3, &res_size);

	status += TEST_INT_EQ(expected_size, res_size);
	status += TEST_INT_ARR_EQ(expected, actual, expected_size);

	return status;
}

int test_slice_block_num_way_over_bounds(void)
{
	int status = 0;
	int arr[] = {1, 2, 3};
	int *expected = NULL;
	int *actual;
	size_t expected_size = 0;
	size_t res_size = 1;

	actual = slice(arr, 3, sizeof(int), 1, 4, &res_size);

	status += TEST_INT_EQ(expected_size, res_size);
	status += TEST_INT_ARR_EQ(expected, actual, expected_size);

	return status;
}

int test_slice_get_whole_array(void)
{
	int status = 0;
	int arr[] = {1, 2, 3};
	int *expected = arr;
	int *actual;
	size_t expected_size = 3;
	size_t res_size;

	actual = slice(arr, 3, sizeof(int), 3, 0, &res_size);

	status += TEST_INT_EQ(expected_size, res_size);
	status += TEST_INT_ARR_EQ(expected, actual, expected_size);

	return status;
}

int test_slice_get_first_block(void)
{
	int status = 0;
	int arr[] = {1, 2, 3, 4, 5};
	int *expected = arr;
	int *actual;
	size_t expected_size = 2;
	size_t res_size;

	actual = slice(arr, 5, sizeof(int), 2, 0, &res_size);

	status += TEST_INT_EQ(expected_size, res_size);
	status += TEST_INT_ARR_EQ(expected, actual, expected_size);

	return status;
}

int test_slice_get_middle_block(void)
{
	int status = 0;
	int arr[] = {1, 2, 3, 4, 5};
	int *expected = &arr[2];
	int *actual;
	size_t expected_size = 2;
	size_t res_size;

	actual = slice(arr, 5, sizeof(int), 2, 1, &res_size);

	status += TEST_INT_EQ(expected_size, res_size);
	status += TEST_INT_ARR_EQ(expected, actual, expected_size);

	return status;
}

int test_slice_get_block_smaller_than_expected(void)
{
	int status = 0;
	int arr[] = {1, 2, 3, 4, 5};
	int *expected = &arr[4];
	int *actual;
	size_t expected_size = 1;
	size_t res_size;

	actual = slice(arr, 5, sizeof(int), 2, 2, &res_size);

	status += TEST_INT_EQ(expected_size, res_size);
	status += TEST_INT_ARR_EQ(expected, actual, expected_size);

	return status;
}

int main(void)
{
	REGISTER_TEST(test_slice_null);
	REGISTER_TEST(test_slice_empty_arr);
	REGISTER_TEST(test_slice_zero_data_size);
	REGISTER_TEST(test_slice_empty_block);
	REGISTER_TEST(test_slice_negative_block_num);
	REGISTER_TEST(test_slice_block_num_exactly_over_bounds);
	REGISTER_TEST(test_slice_block_num_way_over_bounds);
	REGISTER_TEST(test_slice_get_whole_array);
	REGISTER_TEST(test_slice_get_first_block);
	REGISTER_TEST(test_slice_get_middle_block);
	REGISTER_TEST(test_slice_get_block_smaller_than_expected);

	return RUN_TESTS();
}

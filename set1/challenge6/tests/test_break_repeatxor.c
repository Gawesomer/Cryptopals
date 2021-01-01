#include <stdio.h>
#include <stdlib.h>

#include "cTest.h"
#include "../break_repeatxor.c"

/*** get_block ***/

int test_get_block_null_arr_returns_null(void)
{
	return TEST_BYTE_ARR_EQ(get_block(NULL, 0, 0, 0), NULL, 0);
}

int test_get_block_blk_size_larger_than_array_returns_null(void)
{
	uint8_t arr[] = {1, 2, 3};

	return TEST_BYTE_ARR_EQ(get_block(arr, 3, 4, 0), NULL, 0);
}

int test_get_block_zero_blk_size_returns_null(void)
{
	uint8_t arr[] = {1, 2, 3};

	return TEST_BYTE_ARR_EQ(get_block(arr, 3, 0, 0), NULL, 0);
}

int test_get_block_n_oob_returns_null(void)
{
	int status = 0;
	uint8_t arr[] = {1, 2, 3};

	status += TEST_BYTE_ARR_EQ(get_block(arr, 3, 3, -1), NULL, 0);
	status += TEST_BYTE_ARR_EQ(get_block(arr, 3, 3, 4), NULL, 0);

	return status;
}

int test_get_block_get_first_block(void)
{
	int status;
	uint8_t arr[] = {1, 2, 3};
	uint8_t expectedblock[] = {1, 2};
	uint8_t *actualblock = get_block(arr, 3, 2, 0);

	status = TEST_BYTE_ARR_EQ(expectedblock, actualblock, 2);

	free(actualblock);

	return status;
}

int test_get_block_last_block_of_smaller_size(void)
{
	int status;
	uint8_t arr[] = {1, 2, 3};
	uint8_t expectedblock[] = {3};
	uint8_t *actualblock = get_block(arr, 3, 2, 1);

	status = TEST_BYTE_ARR_EQ(expectedblock, actualblock, 1);

	free(actualblock);

	return status;
}

int main(void)
{
	REGISTER_TEST(test_get_block_null_arr_returns_null);
	REGISTER_TEST(test_get_block_blk_size_larger_than_array_returns_null);
	REGISTER_TEST(test_get_block_zero_blk_size_returns_null);
	REGISTER_TEST(test_get_block_n_oob_returns_null);
	REGISTER_TEST(test_get_block_get_first_block);
	REGISTER_TEST(test_get_block_last_block_of_smaller_size);

	return RUN_TESTS();
}

#include <stdio.h>
#include <stdlib.h>

#include "cTest.h"
#include "../break_repeatxor.c"

/*** find_keysize ***/

int test_find_keysize_null(void)
{
	return TEST_INT_EQ(find_keysize(NULL, 1), 0);
}

int test_find_keysize_empty(void)
{
	uint8_t bits[] = {0};

	return TEST_INT_EQ(find_keysize(bits, 0), 0);
}

int test_find_keysize_singlebyte(void)
{
	uint8_t bits[] = {0};

	return TEST_INT_EQ(find_keysize(bits, 1), 0);
}

int test_find_keysize_less_than_eight_bytes(void)
{
	uint8_t bits[] = {1, 2, 3, 4, 5, 6};

	return TEST_INT_EQ(find_keysize(bits, 6), 0);
}

int test_find_keysize_cryptopals(void)
{
	char encrypted[] = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272"
		"a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

	return TEST_INT_EQ(find_keysize((uint8_t *)encrypted, sizeof(encrypted)-1), 22);
}

/*** transpose_blocks ***/

int test_transpose_blocks_null(void)
{
	if (transpose_blocks(NULL, 1, 1))
		return 1;
	return 0;
}

int test_transpose_blocks_empty(void)
{
	uint8_t bits[] = {0};

	if (transpose_blocks(bits, 0, 1))
		return 1;
	return 0;
}

int test_transpose_blocks_blksize_of_one(void)
{
	int status = 0;
	uint8_t bits[] = {1, 2, 3, 4};
	uint8_t expected[1][4] = {
		{1, 2, 3, 4},
	};
	uint8_t **actual;
	int i;

	actual = transpose_blocks(bits, 4, 1);

	for (i = 0; i < 1; i++) {
		status += TEST_BYTE_ARR_EQ(expected[i], actual[i], 4);
		free(actual[i]);
	}
	free(actual);

	return status;
}

int test_transpose_blocks_blocks_divide_evenly(void)
{
	int status = 0;
	uint8_t bits[] = {1, 2, 3, 4};
	uint8_t expected[2][2] = {
		{1, 3},
		{2, 4},
	};
	uint8_t **actual;
	int i;

	actual = transpose_blocks(bits, 4, 2);

	for (i = 0; i < 2; i++) {
		status += TEST_BYTE_ARR_EQ(expected[i], actual[i], 2);
		free(actual[i]);
	}
	free(actual);

	return status;
}

int test_transpose_blocks_blocks_do_not_divide_evenly(void)
{
	int status = 0;
	uint8_t bits[] = {1, 2, 3, 4};
	uint8_t expected[3][1] = {
		{1},
		{2},
		{3},
	};
	uint8_t **actual;
	int i;

	actual = transpose_blocks(bits, 4, 3);

	for (i = 0; i < 3; i++) {
		status += TEST_BYTE_ARR_EQ(expected[i], actual[i], 1);
		free(actual[i]);
	}
	free(actual);

	return status;
}

/*** decrypt_repeatxor ***/

int test_decrypt_repeatxor_null(void)
{
	return TEST_BYTE_ARR_EQ(decrypt_repeatxor(NULL, 1, 1), NULL, 0);
}

int test_decrypt_repeatxor_empty(void)
{
	uint8_t bits[] = {0};

	return TEST_BYTE_ARR_EQ(decrypt_repeatxor(bits, 0, 1), NULL, 0);
}

int test_decrypt_repeatxor_invalid_keysize(void)
{
	int status = 0;
	uint8_t bits[] = {0};

	status += TEST_BYTE_ARR_EQ(decrypt_repeatxor(bits, 1, -1), NULL, 0);
	status += TEST_BYTE_ARR_EQ(decrypt_repeatxor(bits, 1, 0), NULL, 0);

	return status;
}

int main(void)
{
	REGISTER_TEST(test_find_keysize_null);
	REGISTER_TEST(test_find_keysize_empty);
	REGISTER_TEST(test_find_keysize_singlebyte);
	REGISTER_TEST(test_find_keysize_less_than_eight_bytes);
	REGISTER_TEST(test_find_keysize_cryptopals);

	REGISTER_TEST(test_transpose_blocks_null);
	REGISTER_TEST(test_transpose_blocks_empty);
	REGISTER_TEST(test_transpose_blocks_blksize_of_one);
	REGISTER_TEST(test_transpose_blocks_blocks_divide_evenly);
	REGISTER_TEST(test_transpose_blocks_blocks_do_not_divide_evenly);

	REGISTER_TEST(test_decrypt_repeatxor_null);
	REGISTER_TEST(test_decrypt_repeatxor_empty);
	REGISTER_TEST(test_decrypt_repeatxor_invalid_keysize);

	return RUN_TESTS();
}

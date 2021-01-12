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

int main(void)
{
	REGISTER_TEST(test_find_keysize_null);
	REGISTER_TEST(test_find_keysize_empty);
	REGISTER_TEST(test_find_keysize_singlebyte);
	REGISTER_TEST(test_find_keysize_less_than_eight_bytes);
	REGISTER_TEST(test_find_keysize_cryptopals);

	return RUN_TESTS();
}

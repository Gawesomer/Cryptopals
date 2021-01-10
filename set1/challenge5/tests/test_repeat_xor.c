#include <stdio.h>
#include <stdlib.h>

#include "cTest.h"
#include "../repeat_xor.c"

/*** xor_repeating ***/

int test_xor_repeating_null(void)
{
	uint8_t bits[] = {0};
	uint8_t expected[] = {0};

	xor_repeating(NULL, 1, bits, 1);
	xor_repeating(bits, 1, NULL, 1);
	xor_repeating(NULL, 1, NULL, 1);

	return TEST_BYTE_ARR_EQ(expected, bits, 1);
}

int test_xor_repeating_empty(void)
{
	uint8_t bits[] = {0};
	uint8_t expected[] = {0};

	xor_repeating(bits, 0, bits, 1);
	xor_repeating(bits, 1, bits, 0);
	xor_repeating(bits, 0, bits, 0);

	return TEST_BYTE_ARR_EQ(expected, bits, 1);
}

int test_xor_repeating_single_input_byte(void)
{
	uint8_t bits[] = {'B'};
	uint8_t key[] = {'I'};
	uint8_t expected[] = {0x0B};

	xor_repeating(bits, 1, key, 1);

	return TEST_BYTE_ARR_EQ(expected, bits, 1);
}

int test_xor_repeating_multiple_input_bytes_single_key_byte(void)
{
	uint8_t bits[] = {'B', 'u', 'r', 'n'};
	uint8_t key[] = {'I'};
	uint8_t expected[] = {0x0B, 0x3C, 0x3B, 0x27};

	xor_repeating(bits, 4, key, 1);

	return TEST_BYTE_ARR_EQ(expected, bits, 4);
}

int test_xor_repeating_multiple_input_bytes_multiple_key_bytes(void)
{
	uint8_t bits[] = {'B', 'u', 'r', 'n', 'i', 'n', 'g'};
	uint8_t key[] = {'I', 'C', 'E'};
	uint8_t expected[] = {0x0b, 0x36, 0x37, 0x27, 0x2a, 0x2b, 0x2e};

	xor_repeating(bits, 7, key, 3);

	return TEST_BYTE_ARR_EQ(expected, bits, 7);
}

int main(void)
{
	REGISTER_TEST(test_xor_repeating_null);
	REGISTER_TEST(test_xor_repeating_single_input_byte);
	REGISTER_TEST(test_xor_repeating_multiple_input_bytes_single_key_byte);
	REGISTER_TEST(test_xor_repeating_multiple_input_bytes_multiple_key_bytes);

	return RUN_TESTS();
}

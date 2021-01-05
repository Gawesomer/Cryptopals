#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cTest.h"
#include "../xor.c"

/*** xor_binary ***/

int test_xor_binary_null(void)
{
	uint8_t bits[] = {0xFF};
	uint8_t orig[] = {0xFF};

	xor_binary(bits, NULL, 1);
	xor_binary(NULL, bits, 1);

	return TEST_BYTE_ARR_EQ(bits, orig, 1);
}

int test_xor_binary_empty(void)
{
	uint8_t bits[] = {0xFF};
	uint8_t orig[] = {0xFF};

	xor_binary(bits, bits, 0);

	return TEST_BYTE_ARR_EQ(bits, orig, 1);
}

int test_xor_binary_single_byte(void)
{
	uint8_t a[] = {0xFF};
	uint8_t b[] = {0xAA};
	uint8_t expected[] = {0x55};

	xor_binary(a, b, 1);

	return TEST_BYTE_ARR_EQ(expected, a, 1);
}

int test_xor_binary_two_bytes(void)
{
	uint8_t a[] = {0x12, 0x34};
	uint8_t b[] = {0x56, 0x78};
	uint8_t expected[] = {0x44, 0x4C};

	xor_binary(a, b, 2);

	return TEST_BYTE_ARR_EQ(expected, a, 2);
}


int main(void)
{
	REGISTER_TEST(test_xor_binary_null);
	REGISTER_TEST(test_xor_binary_empty);
	REGISTER_TEST(test_xor_binary_single_byte);
	REGISTER_TEST(test_xor_binary_two_bytes);

	return RUN_TESTS();
}

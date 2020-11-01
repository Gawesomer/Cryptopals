#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "cassert.h"
#include "../single_xor.c"

/*** xor_binary_singlebyte ***/

void test_xor_binary_singlebyte_null(void)
{
	printf("%s\n", __func__);

	assert(xor_binary_singlebyte(NULL, 0, 0x00) == NULL);
}

void test_xor_binary_singlebyte_empty(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0};

	assert(xor_binary_singlebyte(bits, 0, 0x00) == NULL);
}

void test_xor_binary_singlebyte_single_byte(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0xFF};
	uint8_t byte = 0xAA;
	uint8_t *actual;
	uint8_t expected[] = {0x55};

	actual = xor_binary_singlebyte(bits, 1, byte);

	assert_bytes_eq(1, expected, actual);

	free(actual);
}

void test_xor_binary_singlebyte_multiple_bytes(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0x12, 0x34, 0xFF, 0xAA};
	uint8_t byte = 0xAA;
	uint8_t *actual;
	uint8_t expected[] = {0xB8, 0x9E, 0x55, 0x00};

	actual = xor_binary_singlebyte(bits, 4, byte);

	assert_bytes_eq(4, expected, actual);

	free(actual);
}

int main(void)
{
	test_xor_binary_singlebyte_null();
	test_xor_binary_singlebyte_empty();
	test_xor_binary_singlebyte_single_byte();
	test_xor_binary_singlebyte_multiple_bytes();

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cTest.h"
#include "../xor.c"

/*** xor_binarrays ***/

int test_xor_binarrays_null(void)
{
	int status = 0;
	uint8_t bits[] = {0xFF};

	status += TEST_BYTE_ARR_EQ(xor_binarrays(NULL, NULL, 0), NULL, 0);
	status += TEST_BYTE_ARR_EQ(xor_binarrays(bits, NULL, 1), NULL, 0);
	status += TEST_BYTE_ARR_EQ(xor_binarrays(NULL, bits, 1), NULL, 0);

	return status;
}

int test_xor_binarrays_single_byte(void)
{
	int status;
	uint8_t a[] = {0xFF};
	uint8_t b[] = {0xAA};
	uint8_t expected[] = {0x55};
	uint8_t *actual = xor_binarrays(a, b, 1);

	status = TEST_BYTE_ARR_EQ(expected, actual, 1);

	free(actual);

	return status;
}

int test_xor_binarrays_two_bytes(void)
{
	int status;
	uint8_t a[] = {0x12, 0x34};
	uint8_t b[] = {0x56, 0x78};
	uint8_t expected[] = {0x44, 0x4C};
	uint8_t *actual = xor_binarrays(a, b, 2);

	status = TEST_BYTE_ARR_EQ(expected, actual, 2);

	free(actual);

	return status;
}

/*** xor_hexstrs ***/

int test_xor_hexstrs_null(void)
{
	int status = 0;

	status += TEST_STR_EQ(xor_hexstrs(NULL, NULL), NULL);
	status += TEST_STR_EQ(xor_hexstrs("a", NULL), NULL);
	status += TEST_STR_EQ(xor_hexstrs(NULL, "b"), NULL);

	return status;
}

int test_xor_hexstrs_empty(void)
{
	int status = 0;

	status += TEST_STR_EQ(xor_hexstrs("", "b"), NULL);
	status += TEST_STR_EQ(xor_hexstrs("a", ""), NULL);

	return status;
}

int test_xor_hexstrs_single_bytes(void)
{
	int status;
	char *res;

	res = xor_hexstrs("FF", "AA");
	status = TEST_STR_EQ(res, "55");

	free(res);

	return status;
}

int test_xor_hexstrs_results_in_letters(void)
{
	int status;
	char *res;

	res = xor_hexstrs("00", "BC");
	status = TEST_STR_EQ(res, "BC");

	free(res);

	return status;
}

int test_xor_hexstrs_lowercase(void)
{
	int status;
	char *res;

	res = xor_hexstrs("ff", "aa");
	status = TEST_STR_EQ(res, "55");

	free(res);

	return status;
}

int test_xor_hexstrs_different_sizes(void)
{
	int status = 0;
	char *res;

	res = xor_hexstrs("FFAA", "AAFFCC");
	status += TEST_STR_EQ(res, "5555");
	free(res);

	res = xor_hexstrs("AAFFCC", "FFAA");
	status += TEST_STR_EQ(res, "5555");
	free(res);

	return status;
}

int test_xor_hexstrs_odd_length(void)
{
	int status;
	char *res;

	res = xor_hexstrs("FFF", "AAA");
	status = TEST_STR_EQ(res, "555");

	free(res);

	return status;
}

int test_xor_hexstrs_cryptopals_example(void)
{
	int status;
	char a[] = "1c0111001f010100061a024b53535009181c";
	char b[] = "686974207468652062756c6c277320657965";
	char expected[] = "746865206B696420646F6E277420706C6179";
	char *actual = xor_hexstrs(a, b);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int main(void)
{
	REGISTER_TEST(test_xor_binarrays_null);
	REGISTER_TEST(test_xor_binarrays_single_byte);
	REGISTER_TEST(test_xor_binarrays_two_bytes);

	REGISTER_TEST(test_xor_hexstrs_null);
	REGISTER_TEST(test_xor_hexstrs_empty);
	REGISTER_TEST(test_xor_hexstrs_single_bytes);
	REGISTER_TEST(test_xor_hexstrs_results_in_letters);
	REGISTER_TEST(test_xor_hexstrs_lowercase);
	REGISTER_TEST(test_xor_hexstrs_different_sizes);
	REGISTER_TEST(test_xor_hexstrs_odd_length);
	REGISTER_TEST(test_xor_hexstrs_cryptopals_example);

	return RUN_TESTS();
}

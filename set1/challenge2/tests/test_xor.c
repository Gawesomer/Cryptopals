#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cassert.h"
#include "../xor.c"

/*** xor_binarrays ***/

void test_xor_binarrays_null(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0xFF};

	TEST_BYTES_EQ(0, xor_binarrays(NULL, NULL, 0), NULL);
	TEST_BYTES_EQ(0, xor_binarrays(bits, NULL, 1), NULL);
	TEST_BYTES_EQ(0, xor_binarrays(NULL, bits, 1), NULL);
}

void test_xor_binarrays_single_byte(void)
{
	printf("%s\n", __func__);

	uint8_t a[] = {0xFF};
	uint8_t b[] = {0xAA};
	uint8_t expected[] = {0x55};
	uint8_t *actual = xor_binarrays(a, b, 1);

	TEST_BYTES_EQ(1, expected, actual);

	free(actual);
}

void test_xor_binarrays_two_bytes(void)
{
	printf("%s\n", __func__);

	uint8_t a[] = {0x12, 0x34};
	uint8_t b[] = {0x56, 0x78};
	uint8_t expected[] = {0x44, 0x4C};
	uint8_t *actual = xor_binarrays(a, b, 2);

	TEST_BYTES_EQ(2, expected, actual);

	free(actual);
}

/*** xor_hexstrs ***/

void test_xor_hexstrs_null(void)
{
	printf("%s\n", __func__);

	TEST_STR_EQ(xor_hexstrs(NULL, NULL), NULL);
	TEST_STR_EQ(xor_hexstrs("a", NULL), NULL);
	TEST_STR_EQ(xor_hexstrs(NULL, "b"), NULL);
}

void test_xor_hexstrs_empty(void)
{
	printf("%s\n", __func__);

	TEST_STR_EQ(xor_hexstrs("", "b"), NULL);
	TEST_STR_EQ(xor_hexstrs("a", ""), NULL);
}

void test_xor_hexstrs_single_bytes(void)
{
	printf("%s\n", __func__);

	char *res;

	res = xor_hexstrs("FF", "AA");
	TEST_STR_EQ(res, "55");

	free(res);
}

void test_xor_hexstrs_results_in_letters(void)
{
	printf("%s\n", __func__);

	char *res;

	res = xor_hexstrs("00", "BC");
	TEST_STR_EQ(res, "BC");

	free(res);
}

void test_xor_hexstrs_lowercase(void)
{
	printf("%s\n", __func__);

	char *res;

	res = xor_hexstrs("ff", "aa");
	TEST_STR_EQ(res, "55");

	free(res);
}

void test_xor_hexstrs_different_sizes(void)
{
	printf("%s\n", __func__);

	char *res;

	res = xor_hexstrs("FFAA", "AAFFCC");
	TEST_STR_EQ(res, "5555");
	free(res);

	res = xor_hexstrs("AAFFCC", "FFAA");
	TEST_STR_EQ(res, "5555");
	free(res);
}

void test_xor_hexstrs_odd_length(void)
{
	printf("%s\n", __func__);

	char *res;

	res = xor_hexstrs("FFF", "AAA");
	TEST_STR_EQ(res, "555");

	free(res);
}

void test_xor_hexstrs_cryptopals_example(void)
{
	printf("%s\n", __func__);

	char a[] = "1c0111001f010100061a024b53535009181c";
	char b[] = "686974207468652062756c6c277320657965";
	char expected[] = "746865206B696420646F6E277420706C6179";
	char *actual = xor_hexstrs(a, b);

	TEST_STR_EQ(expected, actual);

	free(actual);
}

int main(void)
{
	test_xor_binarrays_null();
	test_xor_binarrays_single_byte();
	test_xor_binarrays_two_bytes();

	test_xor_hexstrs_null();
	test_xor_hexstrs_empty();
	test_xor_hexstrs_single_bytes();
	test_xor_hexstrs_results_in_letters();
	test_xor_hexstrs_lowercase();
	test_xor_hexstrs_different_sizes();
	test_xor_hexstrs_odd_length();
	test_xor_hexstrs_cryptopals_example();

	return EXIT_SUCCESS;
}

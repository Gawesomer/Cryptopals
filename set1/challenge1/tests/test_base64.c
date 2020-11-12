#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "cassert.h"
#include "../base64.c"

/*** binarytobase64 ***/

void test_binarytobase64_null(void)
{
	printf("%s\n", __func__);

	assert(binarytobase64(NULL, 0) == NULL);
}

void test_binarytobase64_wholebyte(void)
{
	printf("%s\n", __func__);

	uint8_t binary[1] = {0x49};
	uint8_t expectedbase64[2] = {18, 16};
	uint8_t *actualbase64 = binarytobase64(binary, 1);

	TEST_BYTES_EQ(2, expectedbase64, actualbase64);

	free(actualbase64);
}

void test_binarytobase64_halfbyte(void)
{
	printf("%s\n", __func__);

	uint8_t binary[1] = {0xA};
	uint8_t expectedbase64[2] = {2, 32};
	uint8_t *actualbase64 = binarytobase64(binary, 1);

	TEST_BYTES_EQ(2, expectedbase64, actualbase64);

	free(actualbase64);
}

void test_binarytobase64_twobytes(void)
{
	printf("%s\n", __func__);

	uint8_t binary[2] = {0x49, 0x27};
	uint8_t expectedbase64[3] = {18, 18, 28};
	uint8_t *actualbase64 = binarytobase64(binary, 2);

	TEST_BYTES_EQ(3, expectedbase64, actualbase64);

	free(actualbase64);
}

/*** base64_tostring ***/

void test_base64_tostring_null(void)
{
	printf("%s\n", __func__);

	TEST_STR_EQ(base64_tostring(NULL, 0), NULL);
}

void test_base64_tostring_twobytes(void)
{
	printf("%s\n", __func__);

	uint8_t base64[2] = {18, 16};
	char expectedbase64str[] = "SQ";
	char *actualbase64str = base64_tostring(base64, 2);

	TEST_STR_EQ(expectedbase64str, actualbase64str);

	free(actualbase64str);
}

void test_base64_tostring_lowercase(void)
{
	printf("%s\n", __func__);

	uint8_t base64[1] = {34};
	char expectedbase64str[] = "i";
	char *actualbase64str = base64_tostring(base64, 1);

	TEST_STR_EQ(expectedbase64str, actualbase64str);

	free(actualbase64str);
}

void test_base64_tostring_digit(void)
{
	printf("%s\n", __func__);

	uint8_t base64[1] = {56};
	char expectedbase64str[] = "4";
	char *actualbase64str = base64_tostring(base64, 1);

	TEST_STR_EQ(expectedbase64str, actualbase64str);

	free(actualbase64str);
}

void test_base64_tostring_invalidbyte(void)
{
	printf("%s\n", __func__);

	uint8_t base64[1] = {65};
	
	TEST_STR_EQ(base64_tostring(base64, 1), NULL);
}

/*** hextobase64 ***/

void test_hextobase64_null(void)
{
	printf("%s\n", __func__);

	TEST_STR_EQ(hextobase64(NULL), NULL);
}

void test_hextobase64_empty(void)
{
	printf("%s\n", __func__);

	TEST_STR_EQ(hextobase64(""), NULL);
}

void test_hextobase64_wholebyte(void)
{
	printf("%s\n", __func__);

	char hexstr[] = "89";
	char expectedstr[] = "iQ==";
	char *base64str = hextobase64(hexstr);

	TEST_STR_EQ(expectedstr, base64str);

	free(base64str);
}

void test_hextobase64_halfbyte(void)
{
	printf("%s\n", __func__);

	char hexstr[] = "A";
	char expectedstr[] = "Cg==";
	char *base64str = hextobase64(hexstr);

	TEST_STR_EQ(expectedstr, base64str);

	free(base64str);
}

void test_hextobase64_lowercase(void)
{
	printf("%s\n", __func__);

	char hexstr[] = "a";
	char expectedstr[] = "Cg==";
	char *base64str = hextobase64(hexstr);

	TEST_STR_EQ(expectedstr, base64str);

	free(base64str);
}

void test_hextobase64_invalidhex(void)
{
	printf("%s\n", __func__);

	TEST_STR_EQ(hextobase64("G"), NULL);
}

void test_hextobase64_cryptopals_example(void)
{
	printf("%s\n", __func__);

	char hexstr[] = "49276d206b696c6c696e6720796f757220627261696e206c696" \
			"b65206120706f69736f6e6f7573206d757368726f6f6d";
	char expectedstr[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc2" \
			     "9ub3VzIG11c2hyb29t";
	char *base64str = hextobase64(hexstr);

	TEST_STR_EQ(expectedstr, base64str);

	free(base64str);
}

int main(void)
{
	test_binarytobase64_null();
	test_binarytobase64_wholebyte();
	test_binarytobase64_halfbyte();
	test_binarytobase64_twobytes();

	test_base64_tostring_null();
	test_base64_tostring_twobytes();
	test_base64_tostring_lowercase();
	test_base64_tostring_digit();
	test_base64_tostring_invalidbyte();

	test_hextobase64_null();
	test_hextobase64_empty();
	test_hextobase64_wholebyte();
	test_hextobase64_halfbyte();
	test_hextobase64_lowercase();
	test_hextobase64_invalidhex();
	test_hextobase64_cryptopals_example();

	return EXIT_SUCCESS;
}

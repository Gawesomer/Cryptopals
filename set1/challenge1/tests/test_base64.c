#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cTest.h"
#include "../base64.c"

/*** binarytobase64 ***/

int test_binarytobase64_null(void)
{
	return TEST_BYTE_ARR_EQ(binarytobase64(NULL, 0), NULL, 0);
}

int test_binarytobase64_wholebyte(void)
{
	int status;
	uint8_t binary[1] = {0x49};
	uint8_t expectedbase64[2] = {18, 16};
	uint8_t *actualbase64 = binarytobase64(binary, 1);

	status = TEST_BYTE_ARR_EQ(expectedbase64, actualbase64, 2);

	free(actualbase64);

	return status;
}

int test_binarytobase64_halfbyte(void)
{
	int status;
	uint8_t binary[1] = {0xA};
	uint8_t expectedbase64[2] = {2, 32};
	uint8_t *actualbase64 = binarytobase64(binary, 1);

	status = TEST_BYTE_ARR_EQ(expectedbase64, actualbase64, 2);

	free(actualbase64);

	return status;
}

int test_binarytobase64_twobytes(void)
{
	int status;
	uint8_t binary[2] = {0x49, 0x27};
	uint8_t expectedbase64[3] = {18, 18, 28};
	uint8_t *actualbase64 = binarytobase64(binary, 2);

	status = TEST_BYTE_ARR_EQ(expectedbase64, actualbase64, 3);

	free(actualbase64);

	return status;
}

/*** base64_tostring ***/

int test_base64_tostring_null(void)
{
	return TEST_STR_EQ(base64_tostring(NULL, 0), NULL);
}

int test_base64_tostring_twobytes(void)
{
	int status;
	uint8_t base64[2] = {18, 16};
	char expectedbase64str[] = "SQ";
	char *actualbase64str = base64_tostring(base64, 2);

	status = TEST_STR_EQ(expectedbase64str, actualbase64str);

	free(actualbase64str);

	return status;
}

int test_base64_tostring_lowercase(void)
{
	int status;
	uint8_t base64[1] = {34};
	char expectedbase64str[] = "i";
	char *actualbase64str = base64_tostring(base64, 1);

	status = TEST_STR_EQ(expectedbase64str, actualbase64str);

	free(actualbase64str);

	return status;
}

int test_base64_tostring_digit(void)
{
	int status;
	uint8_t base64[1] = {56};
	char expectedbase64str[] = "4";
	char *actualbase64str = base64_tostring(base64, 1);

	status = TEST_STR_EQ(expectedbase64str, actualbase64str);

	free(actualbase64str);

	return status;
}

int test_base64_tostring_invalidbyte(void)
{
	uint8_t base64[1] = {65};
	
	return TEST_STR_EQ(base64_tostring(base64, 1), NULL);
}

/*** hextobase64 ***/

int test_hextobase64_null(void)
{
	return TEST_STR_EQ(hextobase64(NULL), NULL);
}

int test_hextobase64_empty(void)
{
	return TEST_STR_EQ(hextobase64(""), NULL);
}

int test_hextobase64_wholebyte(void)
{
	int status;
	char hexstr[] = "89";
	char expectedstr[] = "iQ==";
	char *base64str = hextobase64(hexstr);

	status = TEST_STR_EQ(expectedstr, base64str);

	free(base64str);

	return status;
}

int test_hextobase64_halfbyte(void)
{
	int status;
	char hexstr[] = "A";
	char expectedstr[] = "Cg==";
	char *base64str = hextobase64(hexstr);

	status = TEST_STR_EQ(expectedstr, base64str);

	free(base64str);

	return status;
}

int test_hextobase64_lowercase(void)
{
	int status;
	char hexstr[] = "a";
	char expectedstr[] = "Cg==";
	char *base64str = hextobase64(hexstr);

	status = TEST_STR_EQ(expectedstr, base64str);

	free(base64str);

	return status;
}

int test_hextobase64_invalidhex(void)
{
	return TEST_STR_EQ(hextobase64("G"), NULL);
}

int test_hextobase64_cryptopals_example(void)
{
	int status;
	char hexstr[] = "49276d206b696c6c696e6720796f757220627261696e206c696" \
			"b65206120706f69736f6e6f7573206d757368726f6f6d";
	char expectedstr[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc2" \
			     "9ub3VzIG11c2hyb29t";
	char *base64str = hextobase64(hexstr);

	status = TEST_STR_EQ(expectedstr, base64str);

	free(base64str);

	return status;
}

int main(void)
{
	REGISTER_TEST(test_binarytobase64_null);
	REGISTER_TEST(test_binarytobase64_wholebyte);
	REGISTER_TEST(test_binarytobase64_halfbyte);
	REGISTER_TEST(test_binarytobase64_twobytes);

	REGISTER_TEST(test_base64_tostring_null);
	REGISTER_TEST(test_base64_tostring_twobytes);
	REGISTER_TEST(test_base64_tostring_lowercase);
	REGISTER_TEST(test_base64_tostring_digit);
	REGISTER_TEST(test_base64_tostring_invalidbyte);

	REGISTER_TEST(test_hextobase64_null);
	REGISTER_TEST(test_hextobase64_empty);
	REGISTER_TEST(test_hextobase64_wholebyte);
	REGISTER_TEST(test_hextobase64_halfbyte);
	REGISTER_TEST(test_hextobase64_lowercase);
	REGISTER_TEST(test_hextobase64_invalidhex);
	REGISTER_TEST(test_hextobase64_cryptopals_example);

	return RUN_TESTS();
}

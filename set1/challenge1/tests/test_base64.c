#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cTest.h"
#include "../base64.c"

/*** base64_encode ***/

int test_base64_encode_null(void)
{
	return TEST_STR_EQ(base64_encode(NULL, 0), NULL);
}

int test_base64_encode_wholebyte(void)
{
	int status;
	uint8_t binary[1] = {0x49};
	const char expectedbase64[] = "SQ";
	char *actualbase64 = base64_encode(binary, 1);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

int test_base64_encode_halfbyte(void)
{
	int status;
	uint8_t binary[1] = {0xA};
	const char expectedbase64[] = "Cg";
	char *actualbase64 = base64_encode(binary, 1);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

int test_base64_encode_twobytes(void)
{
	int status;
	uint8_t binary[2] = {0x49, 0x27};
	const char expectedbase64[] = "SSc";
	char *actualbase64 = base64_encode(binary, 2);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

int test_base64_encode_lowercase(void)
{
	int status;
	uint8_t binary[1] = {0x88};
	const char expectedbase64[] = "iA";
	char *actualbase64 = base64_encode(binary, 1);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

int test_base64_encode_digit(void)
{
	int status;
	uint8_t binary[1] = {0xE8};
	const char expectedbase64[] = "6A";
	char *actualbase64= base64_encode(binary, 1);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
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
	REGISTER_TEST(test_base64_encode_null);
	REGISTER_TEST(test_base64_encode_wholebyte);
	REGISTER_TEST(test_base64_encode_halfbyte);
	REGISTER_TEST(test_base64_encode_twobytes);
	REGISTER_TEST(test_base64_encode_lowercase);
	REGISTER_TEST(test_base64_encode_digit);

	REGISTER_TEST(test_hextobase64_null);
	REGISTER_TEST(test_hextobase64_empty);
	REGISTER_TEST(test_hextobase64_wholebyte);
	REGISTER_TEST(test_hextobase64_halfbyte);
	REGISTER_TEST(test_hextobase64_lowercase);
	REGISTER_TEST(test_hextobase64_invalidhex);
	REGISTER_TEST(test_hextobase64_cryptopals_example);

	return RUN_TESTS();
}

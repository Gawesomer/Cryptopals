#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cTest.h"
#include "../base64.c"


/*** b64fromb2_size ***/

int test_b64fromb2_size_zero(void)
{
	return TEST_INT_EQ(b64fromb2_size(0), 0);
}

int test_b64fromb2_size_no_padding(void)
{
	return TEST_INT_EQ(b64fromb2_size(3), 4);
}

int test_b64fromb2_size_one_pad(void)
{
	return TEST_INT_EQ(b64fromb2_size(2), 4);
}

int test_b64fromb2_size_two_pads(void)
{
	return TEST_INT_EQ(b64fromb2_size(1), 4);
}

/*** base64_encode ***/

int test_base64_encode_null(void)
{
	return TEST_STR_EQ(base64_encode(NULL, 0), NULL);
}

int test_base64_encode_empty(void)
{
	uint8_t binary[] = {0};

	return TEST_STR_EQ(base64_encode(binary, 0), NULL);
}

int test_base64_encode_wholebyte(void)
{
	int status;
	uint8_t binary[1] = {0x49};
	const char expectedbase64[] = "SQ==";
	char *actualbase64 = base64_encode(binary, 1);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

int test_base64_encode_halfbyte(void)
{
	int status;
	uint8_t binary[1] = {0xA};
	const char expectedbase64[] = "Cg==";
	char *actualbase64 = base64_encode(binary, 1);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

int test_base64_encode_twobytes(void)
{
	int status;
	uint8_t binary[2] = {0x49, 0x27};
	const char expectedbase64[] = "SSc=";
	char *actualbase64 = base64_encode(binary, 2);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

int test_base64_encode_lowercase(void)
{
	int status;
	uint8_t binary[1] = {0x88};
	const char expectedbase64[] = "iA==";
	char *actualbase64 = base64_encode(binary, 1);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

int test_base64_encode_digit(void)
{
	int status;
	uint8_t binary[1] = {0xE8};
	const char expectedbase64[] = "6A==";
	char *actualbase64 = base64_encode(binary, 1);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

int test_base64_encode_no_padding(void)
{
	int status;
	uint8_t binary[3] = {0x4D, 0x61, 0x6E};
	const char expectedbase64[] = "TWFu";
	char *actualbase64 = base64_encode(binary, 3);

	status = TEST_STR_EQ(expectedbase64, actualbase64);

	free(actualbase64);

	return status;
}

/*** b2fromb64_size ***/

int test_b2fromb64_size_null(void)
{
	return TEST_INT_EQ(b2fromb64_size(NULL), 0);
}

int test_b2fromb64_size_empty(void)
{
	const char s[] = "";

	return TEST_INT_EQ(b2fromb64_size(s), 0);
}

int test_b2fromb64_size_single_char(void)
{
	const char s[] = "c";

	return TEST_INT_EQ(b2fromb64_size(s), 0);
}

int test_b2fromb64_size_two_chars(void)
{
	const char s[] = "bc";

	return TEST_INT_EQ(b2fromb64_size(s), 1);
}

int test_b2fromb64_size_three_chars(void)
{
	const char s[] = "abc";

	return TEST_INT_EQ(b2fromb64_size(s), 2);
}

int test_b2fromb64_size_four_chars(void)
{
	const char s[] = "abcd";

	return TEST_INT_EQ(b2fromb64_size(s), 3);
}

int test_b2fromb64_size_one_pad(void)
{
	const char s[] = "abc=";

	return TEST_INT_EQ(b2fromb64_size(s), 2);
}

int test_b2fromb64_size_two_pads(void)
{
	const char s[] = "ab==";

	return TEST_INT_EQ(b2fromb64_size(s), 1);
}

/*** base64_decode ***/

int test_base64_decode_null(void)
{
	return TEST_BYTE_ARR_EQ(base64_decode(NULL), NULL, 0);
}

int test_base64_decode_empty(void)
{
	const char base64[] = "";

	return TEST_BYTE_ARR_EQ(base64_decode(base64), NULL, 0);
}

int test_base64_decode_two_chars_no_pad(void)
{
	int status;
	const char base64[] = "SQ";
	uint8_t expectedbinary[1] = {0x49};
	uint8_t *actualbinary = base64_decode(base64);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 1);

	free(actualbinary);

	return status;
}

int test_base64_decode_three_chars_no_pad(void)
{
	int status;
	const char base64[] = "SSc";
	uint8_t expectedbinary[2] = {0x49, 0x27};
	uint8_t *actualbinary = base64_decode(base64);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 2);

	free(actualbinary);

	return status;
}

int test_base64_decode_four_chars_no_pad(void)
{
	int status;
	const char base64[] = "TWFu";
	uint8_t expectedbinary[3] = {0x4D, 0x61, 0x6E};
	uint8_t *actualbinary = base64_decode(base64);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 3);

	free(actualbinary);

	return status;
}

int test_base64_decode_one_pad(void)
{
	int status;
	const char base64[] = "TWE=";
	uint8_t expectedbinary[2] = {0x4D, 0x61};
	uint8_t *actualbinary = base64_decode(base64);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 2);

	free(actualbinary);

	return status;
}

int test_base64_decode_two_pads(void)
{
	int status;
	const char base64[] = "TQ==";
	uint8_t expectedbinary[1] = {0x4D};
	uint8_t *actualbinary = base64_decode(base64);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 1);

	free(actualbinary);

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
	REGISTER_TEST(test_b64fromb2_size_zero);
	REGISTER_TEST(test_b64fromb2_size_no_padding);
	REGISTER_TEST(test_b64fromb2_size_one_pad);
	REGISTER_TEST(test_b64fromb2_size_two_pads);

	REGISTER_TEST(test_base64_encode_null);
	REGISTER_TEST(test_base64_encode_empty);
	REGISTER_TEST(test_base64_encode_wholebyte);
	REGISTER_TEST(test_base64_encode_halfbyte);
	REGISTER_TEST(test_base64_encode_twobytes);
	REGISTER_TEST(test_base64_encode_lowercase);
	REGISTER_TEST(test_base64_encode_digit);
	REGISTER_TEST(test_base64_encode_no_padding);

	REGISTER_TEST(test_b2fromb64_size_null);
	REGISTER_TEST(test_b2fromb64_size_empty);
	REGISTER_TEST(test_b2fromb64_size_single_char);
	REGISTER_TEST(test_b2fromb64_size_two_chars);
	REGISTER_TEST(test_b2fromb64_size_three_chars);
	REGISTER_TEST(test_b2fromb64_size_four_chars);
	REGISTER_TEST(test_b2fromb64_size_one_pad);
	REGISTER_TEST(test_b2fromb64_size_two_pads);

	REGISTER_TEST(test_base64_decode_null);
	REGISTER_TEST(test_base64_decode_empty);
	REGISTER_TEST(test_base64_decode_two_chars_no_pad);
	REGISTER_TEST(test_base64_decode_three_chars_no_pad);
	REGISTER_TEST(test_base64_decode_four_chars_no_pad);
	REGISTER_TEST(test_base64_decode_one_pad);
	REGISTER_TEST(test_base64_decode_two_pads);

	REGISTER_TEST(test_hextobase64_null);
	REGISTER_TEST(test_hextobase64_empty);
	REGISTER_TEST(test_hextobase64_wholebyte);
	REGISTER_TEST(test_hextobase64_halfbyte);
	REGISTER_TEST(test_hextobase64_lowercase);
	REGISTER_TEST(test_hextobase64_invalidhex);
	REGISTER_TEST(test_hextobase64_cryptopals_example);

	return RUN_TESTS();
}

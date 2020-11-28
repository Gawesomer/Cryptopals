#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "test_framework.h"
#include "cassert.h"
#include "../hex.c"

/*** hextobinary ***/

int test_hextobinary_null(void)
{
	return TEST_BYTE_ARR_EQ(hextobinary(NULL), NULL, 0);
}

int test_hextobinary_empty(void)
{
	return TEST_BYTE_ARR_EQ(hextobinary(""), NULL, 0);
}

int test_hextobinary_wholebyte(void)
{
	int status;
	char hexstr[] = "49";
	uint8_t expectedbinary[1] = {0x49};
	uint8_t *actualbinary = hextobinary(hexstr);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 1);

	free(actualbinary);

	return status;
}

int test_hextobinary_halfbyte(void)
{
	int status;
	char hexstr[] = "A";
	uint8_t expectedbinary[1] = {0x0A};
	uint8_t *actualbinary = hextobinary(hexstr);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 1);

	free(actualbinary);

	return status;
}

int test_hextobinary_lowercase(void)
{
	int status;
	char hexstr[] = "a";
	uint8_t expectedbinary[1] = {0x0a};
	uint8_t *actualbinary = hextobinary(hexstr);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 1);

	free(actualbinary);

	return status;
}

int test_hextobinary_odd_length(void)
{
	int status;
	char hexstr[] = "FFF";
	uint8_t expectedbinary[] = {0x0F, 0xFF};
	uint8_t *actualbinary = hextobinary(hexstr);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 2);

	free(actualbinary);

	return status;
}

int test_hextobinary_invalidhex(void)
{
	return TEST_BYTE_ARR_EQ(hextobinary("G"), NULL, 0);
}

int test_hextobinary_cryptopals_example(void)
{
	int status;
	char hexstr[] = "49276d206b696c6c696e6720796f757220627261696e206c696" \
			"b65206120706f69736f6e6f7573206d757368726f6f6d";
	uint8_t expectedbinary[48] = {0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, \
		0x6c, 0x6c, 0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f, 0x75, 0x72, \
		0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c, 0x69, 0x6b, \
		0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f, 0x6e, \
		0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, \
		0x6f, 0x6d};
	uint8_t *actualbinary = hextobinary(hexstr);

	status = TEST_BYTE_ARR_EQ(expectedbinary, actualbinary, 48);

	free(actualbinary);

	return status;
}

/*** binarytohex ***/

int test_binarytohex_null(void)
{
	return TEST_STR_EQ(binarytohex(NULL, 0), NULL);
}

int test_binarytohex_wholebyte(void)
{
	int status;
	uint8_t binary[1] = {0x49};
	char expectedhex[] = "49";
	char *actualhex = binarytohex(binary, 1);

	status = TEST_STR_EQ(expectedhex, actualhex);

	free(actualhex);

	return status;
}

int test_binarytohex_letter(void)
{
	int status;
	uint8_t binary[1] = {0xCF};
	char expectedhex[] = "CF";
	char *actualhex = binarytohex(binary, 1);

	status = TEST_STR_EQ(expectedhex, actualhex);

	free(actualhex);

	return status;
}

int test_binarytohex_cryptopals_example(void)
{
	int status;
	uint8_t binary[48] = {0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, \
		0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f, 0x75, 0x72, 0x20, 0x62, \
		0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c, 0x69, 0x6b, 0x65, 0x20, \
		0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f, 0x6e, 0x6f, 0x75, \
		0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d};
	char expectedhex[] = "49276D206B696C6C696E6720796F757220627261696E20" \
			"6C696B65206120706F69736F6E6F7573206D757368726F6F6D";
	char *actualhex = binarytohex(binary, 48);

	status = TEST_STR_EQ(expectedhex, actualhex);

	free(actualhex);

	return status;
}

/*** hextoascii ***/

int test_hextoascii_null(void)
{
	return TEST_STR_EQ(hextoascii(NULL), NULL);
}

int test_hextoascii_empty(void)
{
	return TEST_STR_EQ(hextoascii(""), NULL);
}

int test_hextoascii_halfbyte(void)
{
	int status;
	char hexstr[] = "9";
	char expected[] = "\t";
	char *actual;

	actual = hextoascii(hexstr);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int test_hextoascii_wholebyte(void)
{
	int status;
	char hexstr[] = "4B";
	char expected[] = "K";
	char *actual;

	actual = hextoascii(hexstr);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int test_hextoascii_lowercase(void)
{
	int status;
	char hexstr[] = "4b";
	char expected[] = "K";
	char *actual;

	actual = hextoascii(hexstr);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int test_hextoascii_odd_length(void)
{
	int status;
	char hexstr[] = "94b";
	char expected[] = "\tK";
	char *actual;

	actual = hextoascii(hexstr);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int test_hextoascii_invalidhex(void)
{
	return TEST_STR_EQ(hextoascii("G"), NULL);
}

int test_hextoascii_multiple_bytes(void)
{
	int status;
	char hexstr[] = "48656C6C6F20776F726C6421";
	char expected[] = "Hello world!";
	char *actual;

	actual = hextoascii(hexstr);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

/*** asciitohex ***/

int test_asciitohex_null(void)
{
	return TEST_STR_EQ(asciitohex(NULL), NULL);
}

int test_asciitohex_empty(void)
{
	return TEST_STR_EQ(asciitohex(""), NULL);
}

int test_asciitohex_single_letter(void)
{
	int status;
	char ascii[] = "A";
	char expected[] = "41";
	char *actual;

	actual = asciitohex(ascii);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int test_asciitohex_multiple_letters(void)
{
	int status;
	char ascii[] = "Hello world!";
	char expected[] = "48656C6C6F20776F726C6421";
	char *actual;

	actual = asciitohex(ascii);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int main(void)
{
	REGISTER_TEST(test_hextobinary_null);
	REGISTER_TEST(test_hextobinary_empty);
	REGISTER_TEST(test_hextobinary_wholebyte);
	REGISTER_TEST(test_hextobinary_halfbyte);
	REGISTER_TEST(test_hextobinary_lowercase);
	REGISTER_TEST(test_hextobinary_odd_length);
	REGISTER_TEST(test_hextobinary_invalidhex);
	REGISTER_TEST(test_hextobinary_cryptopals_example);

	REGISTER_TEST(test_binarytohex_null);
	REGISTER_TEST(test_binarytohex_wholebyte);
	REGISTER_TEST(test_binarytohex_letter);
	REGISTER_TEST(test_binarytohex_cryptopals_example);

	REGISTER_TEST(test_hextoascii_null);
	REGISTER_TEST(test_hextoascii_empty);
	REGISTER_TEST(test_hextoascii_halfbyte);
	REGISTER_TEST(test_hextoascii_wholebyte);
	REGISTER_TEST(test_hextoascii_lowercase);
	REGISTER_TEST(test_hextoascii_odd_length);
	REGISTER_TEST(test_hextoascii_invalidhex);
	REGISTER_TEST(test_hextoascii_multiple_bytes);

	REGISTER_TEST(test_asciitohex_null);
	REGISTER_TEST(test_asciitohex_empty);
	REGISTER_TEST(test_asciitohex_single_letter);
	REGISTER_TEST(test_asciitohex_multiple_letters);

	return RUN_TESTS();
}

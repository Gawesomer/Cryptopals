#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "base64.c"


void assert_bytes_eq(size_t expectedlen, uint8_t *expected, uint8_t *actual)
{
	int i;
	for (i = 0; i < expectedlen; ++i)
		assert(actual[i] == expected[i]);
}

/*** hextobinary ***/

void test_hextobinary_null(void)
{
	printf("%s\n", __func__);

	assert(hextobinary(NULL) == NULL);
}

void test_hextobinary_empty(void)
{
	printf("%s\n", __func__);

	assert(hextobinary("") == NULL);
}

void test_hextobinary_wholebyte(void)
{
	printf("%s\n", __func__);

	char *hexstr = "49";
	uint8_t expectedbinary[1] = {0x49};
	uint8_t *actualbinary = hextobinary(hexstr);

	assert_bytes_eq(1, expectedbinary, actualbinary);

	free(actualbinary);
}

void test_hextobinary_halfbyte(void)
{
	printf("%s\n", __func__);

	char *hexstr = "A";
	uint8_t expectedbinary[1] = {0x0A};
	uint8_t *actualbinary = hextobinary(hexstr);

	assert_bytes_eq(1, expectedbinary, actualbinary);

	free(actualbinary);
}

void test_hextobinary_lowercase(void)
{
	printf("%s\n", __func__);

	char *hexstr = "a";
	uint8_t expectedbinary[1] = {0x0a};
	uint8_t *actualbinary = hextobinary(hexstr);

	assert_bytes_eq(1, expectedbinary, actualbinary);

	free(actualbinary);
}

void test_hextobinary_invalidhex(void)
{
	printf("%s\n", __func__);

	assert(hextobinary("G") == NULL);
}

void test_hextobinary_cryptopals_example(void)
{
	printf("%s\n", __func__);

	char *hexstr = "49276d206b696c6c696e6720796f757220627261696e206c696b" \
			"65206120706f69736f6e6f7573206d757368726f6f6d";
	uint8_t expectedbinary[48] = {0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, \
		0x6c, 0x6c, 0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f, 0x75, 0x72, \
		0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c, 0x69, 0x6b, \
		0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f, 0x6e, \
		0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, \
		0x6f, 0x6d};
	uint8_t *actualbinary = hextobinary(hexstr);

	assert_bytes_eq(48, expectedbinary, actualbinary);

	free(actualbinary);
}

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
	uint8_t *actualbase64 = binarytobase64(binary, 2);

	assert_bytes_eq(2, expectedbase64, actualbase64);

	free(actualbase64);
}

void test_binarytobase64_halfbyte(void)
{
	printf("%s\n", __func__);

	uint8_t binary[1] = {0xA};
	uint8_t expectedbase64[2] = {2, 32};
	uint8_t *actualbase64 = binarytobase64(binary, 2);

	assert_bytes_eq(1, expectedbase64, actualbase64);

	free(actualbase64);
}

/*** base64stringify ***/

void test_base64stringify_null(void)
{
	printf("%s\n", __func__);

	assert(base64stringify(NULL, 0) == NULL);
}

void test_base64stringify_twobytes(void)
{
	printf("%s\n", __func__);

	uint8_t base64[2] = {18, 16};
	char *expectedbase64str = "SQ";
	char *actualbase64str = base64stringify(base64, 2);

	assert(strcmp(expectedbase64str, actualbase64str) == 0);

	free(actualbase64str);
}

void test_base64stringify_invalidbyte(void)
{
	printf("%s\n", __func__);

	uint8_t base64[1] = {65};
	
	assert(base64stringify(base64, 1) == NULL);
}

/*** hextobase64 ***/

void test_hextobase64_null(void)
{
	printf("%s\n", __func__);

	assert(hextobase64(NULL) == NULL);
}

void test_hextobase64_empty(void)
{
	printf("%s\n", __func__);

	assert(strcmp(hextobase64(""), "") == 0);
}

void test_hextobase64_wholebyte(void)
{
	printf("%s\n", __func__);

	char *hexstr = "89";
	char *expectedstr = "iQ==";
	char *base64str = hextobase64(hexstr);

	assert(strcmp(expectedstr, base64str) == 0);

	free(base64str);
}

void test_hextobase64_halfbyte(void)
{
	printf("%s\n", __func__);

	char *hexstr = "A";
	char *expectedstr = "Cg==";
	char *base64str = hextobase64(hexstr);

	assert(strcmp(expectedstr, base64str) == 0);

	free(base64str);
}

void test_hextobase64_lowercase(void)
{
	printf("%s\n", __func__);

	char *hexstr = "a";
	char *expectedstr = "Cg==";
	char *base64str = hextobase64(hexstr);

	assert(strcmp(expectedstr, base64str) == 0);

	free(base64str);
}

void test_hextobase64_invalidhex(void)
{
	printf("%s\n", __func__);

	assert(hextobase64("G") == NULL);
}

void test_hextobase64_cryptopals_example(void)
{
	printf("%s\n", __func__);

	char *hexstr = "49276d206b696c6c696e6720796f757220627261696e206c696b" \
			"65206120706f69736f6e6f7573206d757368726f6f6d";
	char *expectedstr = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29" \
			     "ub3VzIG11c2hyb29t";
	char *base64str = hextobase64(hexstr);

	assert(strcmp(expectedstr, base64str) == 0);

	free(base64str);
}

int main(void)
{
	test_hextobinary_null();
	test_hextobinary_empty();
	test_hextobinary_wholebyte();
	test_hextobinary_halfbyte();
	test_hextobinary_lowercase();
	test_hextobinary_invalidhex();
	test_hextobinary_cryptopals_example();

	test_binarytobase64_null();
	test_binarytobase64_wholebyte();
	test_binarytobase64_halfbyte();

	test_base64stringify_null();
	test_base64stringify_twobytes();
	test_base64stringify_invalidbyte();

	test_hextobase64_null();
	test_hextobase64_empty();
	test_hextobase64_wholebyte();
	test_hextobase64_halfbyte();
	test_hextobase64_lowercase();
	test_hextobase64_invalidhex();
	test_hextobase64_cryptopals_example();

	return EXIT_SUCCESS;
}

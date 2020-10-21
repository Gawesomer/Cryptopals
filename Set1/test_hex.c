#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cassert.h"
#include "hex.c"

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

	char hexstr[] = "49";
	uint8_t expectedbinary[1] = {0x49};
	uint8_t *actualbinary = hextobinary(hexstr);

	assert_bytes_eq(1, expectedbinary, actualbinary);

	free(actualbinary);
}

void test_hextobinary_halfbyte(void)
{
	printf("%s\n", __func__);

	char hexstr[] = "A";
	uint8_t expectedbinary[1] = {0x0A};
	uint8_t *actualbinary = hextobinary(hexstr);

	assert_bytes_eq(1, expectedbinary, actualbinary);

	free(actualbinary);
}

void test_hextobinary_lowercase(void)
{
	printf("%s\n", __func__);

	char hexstr[] = "a";
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

	char hexstr[] = "49276d206b696c6c696e6720796f757220627261696e206c696" \
			"b65206120706f69736f6e6f7573206d757368726f6f6d";
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

/*** binarytohex ***/

void test_binarytohex_null(void)
{
	printf("%s\n", __func__);

	assert(binarytohex(NULL, 0) == NULL);
}

void test_binarytohex_wholebyte(void)
{
	printf("%s\n", __func__);

	uint8_t binary[1] = {0x49};
	char expectedhex[] = "49";
	char *actualhex = binarytohex(binary, 1);

	assert(strcmp(expectedhex, actualhex) == 0);

	free(actualhex);
}

void test_binarytohex_letter(void)
{
	printf("%s\n", __func__);

	uint8_t binary[1] = {0xCF};
	char expectedhex[] = "CF";
	char *actualhex = binarytohex(binary, 1);

	assert(strcmp(expectedhex, actualhex) == 0);

	free(actualhex);
}

void test_binarytohex_cryptopals_example(void)
{
	printf("%s\n", __func__);

	uint8_t binary[48] = {0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, \
		0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f, 0x75, 0x72, 0x20, 0x62, \
		0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c, 0x69, 0x6b, 0x65, 0x20, \
		0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f, 0x6e, 0x6f, 0x75, \
		0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d};
	char expectedhex[] = "49276d206b696c6c696e6720796f757220627261696e20" \
			"6c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	char *actualhex = binarytohex(binary, 48);

	assert(strcmp(expectedhex, actualhex) == 0);

	free(actualhex);
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

	test_binarytohex_null();
	test_binarytohex_wholebyte();
	test_binarytohex_letter();
	test_binarytohex_cryptopals_example();

	return EXIT_SUCCESS;
}

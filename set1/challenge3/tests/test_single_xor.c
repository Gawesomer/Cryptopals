#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cassert.h"
#include "../single_xor.c"

/* English letter frequency duplicate of `ENGLISH_LETTER_FREQ` from `freq.h`
 * so that tests do not fail if `ENGLISH_LETTER_FREQ` is changed
 */
const float TEST_LETTER_FREQ[26] = {
	8.12f,	// A
	1.49f,	// B
	2.71f,	// C
	4.32f,	// D
	12.02f,	// E
	2.30f,	// F
	2.03f,	// G
	5.92f,	// H
	7.31f,	// I
	0.10f,	// J
	0.69f,	// K
	3.98f,	// L
	2.61f,	// M
	6.95f,	// N
	7.68f,	// O
	1.82f,	// P
	0.11f,	// Q
	6.02f,	// R
	6.28f,	// S
	9.10f,	// T
	2.88f,	// U
	1.11f,	// V
	2.09f,	// W
	0.17f,	// X
	2.11f,	// Y
	0.07f,	// Z
};

/*** xor_binary_singlebyte ***/

void test_xor_binary_singlebyte_null(void)
{
	printf("%s\n", __func__);

	TEST_BYTE_ARR_EQ(xor_binary_singlebyte(NULL, 0, 0x00), NULL, 0);
}

void test_xor_binary_singlebyte_empty(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0};

	TEST_BYTE_ARR_EQ(xor_binary_singlebyte(bits, 0, 0x00), NULL, 0);
}

void test_xor_binary_singlebyte_single_byte(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0xFF};
	uint8_t byte = 0xAA;
	uint8_t *actual;
	uint8_t expected[] = {0x55};

	actual = xor_binary_singlebyte(bits, 1, byte);

	TEST_BYTE_ARR_EQ(expected, actual, 1);

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

	TEST_BYTE_ARR_EQ(expected, actual, 4);

	free(actual);
}

/*** decrypt_singlebytexor_on_hex ***/

void test_decrypt_singlebytexor_on_hex_null(void)
{
	printf("%s\n", __func__);

	char hex[] = "00";

	TEST_STR_EQ(decrypt_singlebytexor_on_hex(NULL, TEST_LETTER_FREQ), \
			NULL);
	TEST_STR_EQ(decrypt_singlebytexor_on_hex(hex, NULL), NULL);
	TEST_STR_EQ(decrypt_singlebytexor_on_hex(NULL, NULL), NULL);
}

void test_decrypt_singlebytexor_on_hex_empty(void)
{
	printf("%s\n", __func__);

	TEST_STR_EQ(decrypt_singlebytexor_on_hex("", TEST_LETTER_FREQ), NULL);
}

void test_decrypt_singlebytexor_on_hex_all_letters(void)
{
	printf("%s\n", __func__);

	// "THISISARANDOMENGLISHSENTENCE" ^ 'A'
	char hex[] = "1509081208120013000F050E0C040F060D08120912040F15040F0204";
	char *actual;
	// "THISISARANDOMENGLISHSENTENCE"
	char expected[] = "5448495349534152414E444F4D454E474C49534853454E54454E4345";

	actual = decrypt_singlebytexor_on_hex(hex, TEST_LETTER_FREQ);

	TEST_STR_EQ(expected, actual);

	free(actual);
}

int main(void)
{
	test_xor_binary_singlebyte_null();
	test_xor_binary_singlebyte_empty();
	test_xor_binary_singlebyte_single_byte();
	test_xor_binary_singlebyte_multiple_bytes();

	test_decrypt_singlebytexor_on_hex_null();
	test_decrypt_singlebytexor_on_hex_empty();
	test_decrypt_singlebytexor_on_hex_all_letters();

	return EXIT_SUCCESS;
}

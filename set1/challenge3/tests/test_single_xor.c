#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cTest.h"
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

int test_xor_binary_singlebyte_null(void)
{
	xor_binary_singlebyte(NULL, 0, 0x00);

	return 0;
}

int test_xor_binary_singlebyte_empty(void)
{
	uint8_t bits[] = {0};

	xor_binary_singlebyte(bits, 0, 0x00);

	return 0;
}

int test_xor_binary_singlebyte_single_byte(void)
{
	uint8_t bits[] = {0xFF};
	uint8_t byte = 0xAA;
	uint8_t expected[] = {0x55};

	xor_binary_singlebyte(bits, 1, byte);

	return TEST_BYTE_ARR_EQ(expected, bits, 1);
}

int test_xor_binary_singlebyte_multiple_bytes(void)
{
	uint8_t bits[] = {0x12, 0x34, 0xFF, 0xAA};
	uint8_t byte = 0xAA;
	uint8_t expected[] = {0xB8, 0x9E, 0x55, 0x00};

	xor_binary_singlebyte(bits, 4, byte);

	return TEST_BYTE_ARR_EQ(expected, bits, 4);
}

/*** decrypt_singlebytexor_on_hex ***/

int test_decrypt_singlebytexor_on_hex_null(void)
{
	int status = 0;
	char hex[] = "00";

	status += TEST_STR_EQ(decrypt_singlebytexor_on_hex(NULL, TEST_LETTER_FREQ), \
			NULL);
	status += TEST_STR_EQ(decrypt_singlebytexor_on_hex(hex, NULL), NULL);
	status += TEST_STR_EQ(decrypt_singlebytexor_on_hex(NULL, NULL), NULL);

	return status;
}

int test_decrypt_singlebytexor_on_hex_empty(void)
{
	return TEST_STR_EQ(decrypt_singlebytexor_on_hex("", TEST_LETTER_FREQ), \
			NULL);
}

int test_decrypt_singlebytexor_on_hex_all_letters(void)
{
	int status;
	// "THISISARANDOMENGLISHSENTENCE" ^ 'A'
	char hex[] = "1509081208120013000F050E0C040F060D08120912040F15040F0204";
	char *actual;
	// "THISISARANDOMENGLISHSENTENCE"
	char expected[] = "5448495349534152414E444F4D454E474C49534853454E54454E4345";

	actual = decrypt_singlebytexor_on_hex(hex, TEST_LETTER_FREQ);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int test_decrypt_singlebytexor_on_hex_some_null_chars(void)
{
	int status;
	// "nOWTHATTHEPARTYISJUMPING*" ^ 'F'
	char hex[] = "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f";
	char *actual;
	// "nOWTHATTHEPARTYISJUMPING*"
	char expected[] = "6E4F57145448415414544845145041525459144953144A554D50494E472A";

	actual = decrypt_singlebytexor_on_hex(hex, TEST_LETTER_FREQ);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int main(void)
{
	REGISTER_TEST(test_xor_binary_singlebyte_null);
	REGISTER_TEST(test_xor_binary_singlebyte_empty);
	REGISTER_TEST(test_xor_binary_singlebyte_single_byte);
	REGISTER_TEST(test_xor_binary_singlebyte_multiple_bytes);

	REGISTER_TEST(test_decrypt_singlebytexor_on_hex_null);
	REGISTER_TEST(test_decrypt_singlebytexor_on_hex_empty);
	REGISTER_TEST(test_decrypt_singlebytexor_on_hex_all_letters);
	REGISTER_TEST(test_decrypt_singlebytexor_on_hex_some_null_chars);

	return RUN_TESTS();
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cTest.h"
#include "../single_xor.c"

/* English letter frequency duplicate of `ENGLISH_LETTER_FREQ` from `freq.h`
 * so that tests do not fail if `ENGLISH_LETTER_FREQ` is changed
 */
const int TEST_LETTER_FREQ[27] = {
	812,	// A
	149,	// B
	271,	// C
	432,	// D
	1202,	// E
	230,	// F
	203,	// G
	592,	// H
	731,	// I
	10,	// J
	69,	// K
	398,	// L
	261,	// M
	695,	// N
	768,	// O
	182,	// P
	11,	// Q
	602,	// R
	628,	// S
	910,	// T
	288,	// U
	111,	// V
	209,	// W
	17,	// X
	211,	// Y
	7,	// Z
	1800,	// Space
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

/*** decrypt_singlebytexor ***/

int test_decrypt_singlebytexor_null(void)
{
	int status = 0;
	uint8_t bits[] = {0};

	status += TEST_INT_EQ(decrypt_singlebytexor(NULL, 1, TEST_LETTER_FREQ), 0);
	status += TEST_INT_EQ(decrypt_singlebytexor(bits, 1, NULL), 0);
	status += TEST_INT_EQ(decrypt_singlebytexor(NULL, 1, NULL), 0);

	return status;
}

int test_decrypt_singlebytexor_empty(void)
{
	uint8_t bits[] = {0};

	return TEST_INT_EQ(decrypt_singlebytexor(bits, 0, TEST_LETTER_FREQ), 0);
}

int test_decrypt_singlebytexor_all_letters(void)
{
	int status = 0;
	// "THIS IS A RANDOM ENGLISH SENTENCE" ^ 'A'
	uint8_t bits[] = {0x15, 0x9, 0x8, 0x12, 0x61, 0x8, 0x12, 0x61, 0x0, \
		0x61, 0x13, 0x0, 0xF, 0x5, 0xE, 0xC, 0x61, 0x4, 0xF, 0x6, \
		0xD, 0x8, 0x12, 0x9, 0x61, 0x12, 0x4, 0xF, 0x15, 0x4, 0xF, \
		0x2, 0x4};
	// "THISISARANDOMENGLISHSENTENCE"
	char expected[] = "THIS IS A RANDOM ENGLISH SENTENCE";
	uint8_t actual_key;
	uint8_t expected_key = 'A';

	actual_key = decrypt_singlebytexor(bits, sizeof(bits), TEST_LETTER_FREQ);

	status += TEST_INT_EQ(expected_key, actual_key);
	status += TEST_BYTE_ARR_EQ(expected, bits, sizeof(bits));

	return status;
}

int main(void)
{
	REGISTER_TEST(test_xor_binary_singlebyte_null);
	REGISTER_TEST(test_xor_binary_singlebyte_empty);
	REGISTER_TEST(test_xor_binary_singlebyte_single_byte);
	REGISTER_TEST(test_xor_binary_singlebyte_multiple_bytes);

	REGISTER_TEST(test_decrypt_singlebytexor_null);
	REGISTER_TEST(test_decrypt_singlebytexor_empty);
	REGISTER_TEST(test_decrypt_singlebytexor_all_letters);

	return RUN_TESTS();
}

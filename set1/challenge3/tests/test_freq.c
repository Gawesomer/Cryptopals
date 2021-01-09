#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cTest.h"
#include "../freq.c"


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

/*** freq_score ***/

int test_freq_score_null_returns_zero(void)
{
	int status = 0;
	uint8_t bits[] = {0};

	status += TEST_INT_EQ(freq_score(NULL, 1, TEST_LETTER_FREQ), 0);
	status += TEST_INT_EQ(freq_score(bits, 1, NULL), 0);
	status += TEST_INT_EQ(freq_score(NULL, 1, NULL), 0);

	return status;
}

int test_freq_score_empty_returns_zero(void)
{
	uint8_t bits[] = {0};

	return TEST_INT_EQ(freq_score(bits, 0, TEST_LETTER_FREQ), 0);
}

int test_freq_score_single_lowercase(void)
{
	uint8_t bits[] = {'a'};
	int actual_score;
	int expected_score = TEST_LETTER_FREQ[0];

	actual_score = freq_score(bits, 1, TEST_LETTER_FREQ);

	return TEST_INT_EQ(expected_score, actual_score);
}

int test_freq_score_single_uppercase(void)
{
	uint8_t bits[] = {'A'};
	int actual_score;
	int expected_score = TEST_LETTER_FREQ[0];

	actual_score = freq_score(bits, 1, TEST_LETTER_FREQ);

	return TEST_INT_EQ(expected_score, actual_score);
}

int test_freq_score_space(void)
{
	uint8_t bits[] = {' '};
	int actual_score;
	int expected_score = TEST_LETTER_FREQ[26];

	actual_score = freq_score(bits, 1, TEST_LETTER_FREQ);

	return TEST_INT_EQ(expected_score, actual_score);
}

int test_freq_score_invalid_character(void)
{
	uint8_t bits[] = {'*'};
	int actual_score;
	int expected_score = 0;

	actual_score = freq_score(bits, 1, TEST_LETTER_FREQ);

	return TEST_INT_EQ(expected_score, actual_score);
}

int test_freq_score_multiple_letters_bothcases(void)
{
	uint8_t bits[] = {'H', 'i', ' ', 'y', 'o', 'u', '!'};
	int actual_score;
	int expected_score = 4390;

	actual_score = freq_score(bits, sizeof(bits), TEST_LETTER_FREQ);

	return TEST_INT_EQ(expected_score, actual_score);
}

int main(void)
{
	REGISTER_TEST(test_freq_score_null_returns_zero);
	REGISTER_TEST(test_freq_score_empty_returns_zero);
	REGISTER_TEST(test_freq_score_single_lowercase);
	REGISTER_TEST(test_freq_score_single_uppercase);
	REGISTER_TEST(test_freq_score_space);
	REGISTER_TEST(test_freq_score_invalid_character);
	REGISTER_TEST(test_freq_score_invalid_character);
	REGISTER_TEST(test_freq_score_multiple_letters_bothcases);

	return RUN_TESTS();
}

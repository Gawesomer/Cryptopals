#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>

#include "test_framework.h"
#include "cassert.h"
#include "../freq.c"


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

/*** occmap_from_binary ***/

int test_occmap_from_binary_null(void)
{
	return TEST_INT_ARR_EQ(occmap_from_binary(NULL, 0), NULL, 0);
}

int test_occmap_from_binary_empty(void)
{
	int status;
	uint8_t bits[] = {0};
	int *actual_map;
	int expected_map[26] = {0};

	actual_map = occmap_from_binary(bits, 0);

	status = TEST_INT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

int test_occmap_from_binary_single_byte(void)
{
	int status;
	uint8_t bits[] = {'E'};
	int *actual_map;
	int expected_map[26] = {0};
	expected_map[4] = 1;

	actual_map = occmap_from_binary(bits, 1);

	status = TEST_INT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

int test_occmap_from_binary_lowercase(void)
{
	int status;
	uint8_t bits[] = {'e'};
	int *actual_map;
	int expected_map[26] = {0};
	expected_map[4] = 1;

	actual_map = occmap_from_binary(bits, 1);

	status = TEST_INT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

int test_occmap_from_binary_nonletter(void)
{
	int status;
	uint8_t bits[] = {'7'};
	int *actual_map;
	int expected_map[26] = {0};

	actual_map = occmap_from_binary(bits, 1);

	status = TEST_INT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

int test_occmap_from_binary_multiple_bytes(void)
{
	int status;
	uint8_t bits[] = {'h', 'e', 'y', ',', ' ', 'b', 'y', 'e', '.'};
	int *actual_map;
	int expected_map[26] = {0};
	expected_map[1] = 1;
	expected_map[4] = 2;
	expected_map[7] = 1;
	expected_map[24] = 2;

	actual_map = occmap_from_binary(bits, 9);

	status = TEST_INT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

/*** occmap_to_freqmap ***/

int test_occmap_to_freqmap_null(void)
{
	return TEST_FLOAT_ARR_EQ(occmap_to_freqmap(NULL), NULL, 0);
}

int test_occmap_to_freqmap_empty(void)
{
	int status;
	int occmap[26] = {0};
	float *actual_freq;
	float expected_freq[26] = {0.00f};

	actual_freq = occmap_to_freqmap(occmap);

	status = TEST_FLOAT_ARR_EQ(expected_freq, actual_freq, 26);

	free(actual_freq);

	return status;
}

int test_occmap_to_freqmap_single_letter(void)
{
	int status;
	int occmap[26] = {0};
	occmap[4] = 1;
	float *actual_freq;
	float expected_freq[26] = {0.00f};
	expected_freq[4] = 100.00f;

	actual_freq = occmap_to_freqmap(occmap);

	status = TEST_FLOAT_ARR_EQ(expected_freq, actual_freq, 26);

	free(actual_freq);

	return status;
}

int test_occmap_to_freqmap_negative_occ(void)
{
	int occmap[26] = {0};
	occmap[4] = -1;

	return TEST_FLOAT_ARR_EQ(occmap_to_freqmap(occmap), NULL, 0);
}

int test_occmap_to_freqmap_multiple_bytes(void)
{
	int status;
	int occmap[26] = {0};
	occmap[1] = 1;
	occmap[4] = 2;
	occmap[7] = 1;
	occmap[24] = 2;
	float *actual_freq;
	float expected_freq[26] = {0.00f};
	expected_freq[1] = 16.67f;
	expected_freq[4] = 33.33f;
	expected_freq[7] = 16.67f;
	expected_freq[24] = 33.33f;

	actual_freq = occmap_to_freqmap(occmap);

	status = TEST_FLOAT_ARR_EQ(expected_freq, actual_freq, 26);

	free(actual_freq);

	return status;
}

/*** freqmap_from_binary ***/

int test_freqmap_from_binary_null(void)
{
	return TEST_FLOAT_ARR_EQ(freqmap_from_binary(NULL, 0), NULL, 0);
}

int test_freqmap_from_binary_empty(void)
{
	int status;
	uint8_t bits[] = {0};
	float *actual_map;
	float expected_map[26] = {0.00f};

	actual_map = freqmap_from_binary(bits, 0);

	status = TEST_FLOAT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

int test_freqmap_from_binary_single_byte(void)
{
	int status;
	uint8_t bits[] = {'E'};
	float *actual_map;
	float expected_map[26] = {0.00f};
	expected_map[4] = 100.00f;

	actual_map = freqmap_from_binary(bits, 1);

	status = TEST_FLOAT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

int test_freqmap_from_binary_lowercase(void)
{
	int status;
	uint8_t bits[] = {'e'};
	float *actual_map;
	float expected_map[26] = {0.00f};
	expected_map[4] = 100.00f;

	actual_map = freqmap_from_binary(bits, 1);

	status = TEST_FLOAT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

int test_freqmap_from_binary_nonletter(void)
{
	int status;
	uint8_t bits[] = {'7'};
	float *actual_map;
	float expected_map[26] = {0.00f};

	actual_map = freqmap_from_binary(bits, 1);

	status = TEST_FLOAT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

int test_freqmap_from_binary_multiple_bytes(void)
{
	int status;
	uint8_t bits[] = {'h', 'e', 'y', ',', ' ', 'b', 'y', 'e', '.'};
	float *actual_map;
	float expected_map[26] = {0.00f};
	expected_map[1] = 16.67f;
	expected_map[4] = 33.33f;
	expected_map[7] = 16.67f;
	expected_map[24] = 33.33f;

	actual_map = freqmap_from_binary(bits, 9);

	status = TEST_FLOAT_ARR_EQ(expected_map, actual_map, 26);

	free(actual_map);

	return status;
}

/*** freq_score ***/

int test_freq_score_null(void)
{
	int status = 0;
	float freq[26] = {0.00f};
	
	status += TEST_FLOAT_EQ(freq_score(freq, NULL), FLT_MAX);
	status += TEST_FLOAT_EQ(freq_score(NULL, freq), FLT_MAX);
	status += TEST_FLOAT_EQ(freq_score(NULL, NULL), FLT_MAX);

	return status;
}

int test_freq_score_empty(void)
{
	float freq[26] = {0.00f};
	float actual_score;
	float expected_score = 99.99f;

	actual_score = freq_score(freq, TEST_LETTER_FREQ);

	return TEST_FLOAT_EQ(expected_score, actual_score);
}

int test_freq_score_single_letter(void)
{
	float freq[26] = {0.00f};
	freq[4] = 100.00f;
	float actual_score;
	float expected_score = 175.95f;

	actual_score = freq_score(freq, TEST_LETTER_FREQ);

	return TEST_FLOAT_EQ(expected_score, actual_score);
}

int test_freq_score_multiple_letters(void)
{
	float freq[26] = {0.00f};
	freq[1] = 16.67f;
	freq[4] = 33.33f;
	freq[7] = 16.67f;
	freq[24] = 33.33f;
	float actual_score;
	float expected_score = 156.91f;

	actual_score = freq_score(freq, TEST_LETTER_FREQ);

	return TEST_FLOAT_EQ(expected_score, actual_score);
}

int main(void)
{
	REGISTER_TEST(test_occmap_from_binary_null);
	REGISTER_TEST(test_occmap_from_binary_empty);
	REGISTER_TEST(test_occmap_from_binary_single_byte);
	REGISTER_TEST(test_occmap_from_binary_lowercase);
	REGISTER_TEST(test_occmap_from_binary_nonletter);
	REGISTER_TEST(test_occmap_from_binary_multiple_bytes);

	REGISTER_TEST(test_occmap_to_freqmap_null);
	REGISTER_TEST(test_occmap_to_freqmap_empty);
	REGISTER_TEST(test_occmap_to_freqmap_single_letter);
	REGISTER_TEST(test_occmap_to_freqmap_negative_occ);
	REGISTER_TEST(test_occmap_to_freqmap_multiple_bytes);

	REGISTER_TEST(test_freqmap_from_binary_null);
	REGISTER_TEST(test_freqmap_from_binary_empty);
	REGISTER_TEST(test_freqmap_from_binary_single_byte);
	REGISTER_TEST(test_freqmap_from_binary_lowercase);
	REGISTER_TEST(test_freqmap_from_binary_nonletter);
	REGISTER_TEST(test_freqmap_from_binary_multiple_bytes);

	REGISTER_TEST(test_freq_score_null);
	REGISTER_TEST(test_freq_score_empty);
	REGISTER_TEST(test_freq_score_single_letter);
	REGISTER_TEST(test_freq_score_multiple_letters);

	return RUN_TESTS();
}

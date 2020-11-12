#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <assert.h>

#include "cassert.h"
#include "../freq.c"


#define	FLOAT_EPS	0.01f
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

void test_occmap_from_binary_null(void)
{
	printf("%s\n", __func__);

	TEST_INT_ARR_EQ(0, occmap_from_binary(NULL, 0), NULL);
}

void test_occmap_from_binary_empty(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0};
	int *actual_map;
	int expected_map[26] = {0};

	actual_map = occmap_from_binary(bits, 0);

	TEST_INT_ARR_EQ(26, expected_map, actual_map);

	free(actual_map);
}

void test_occmap_from_binary_single_byte(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'E'};
	int *actual_map;
	int expected_map[26] = {0};
	expected_map[4] = 1;

	actual_map = occmap_from_binary(bits, 1);

	TEST_INT_ARR_EQ(26, expected_map, actual_map);

	free(actual_map);
}

void test_occmap_from_binary_lowercase(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'e'};
	int *actual_map;
	int expected_map[26] = {0};
	expected_map[4] = 1;

	actual_map = occmap_from_binary(bits, 1);

	TEST_INT_ARR_EQ(26, expected_map, actual_map);

	free(actual_map);
}

void test_occmap_from_binary_nonletter(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'7'};
	int *actual_map;
	int expected_map[26] = {0};

	actual_map = occmap_from_binary(bits, 1);

	TEST_INT_ARR_EQ(26, expected_map, actual_map);

	free(actual_map);
}

void test_occmap_from_binary_multiple_bytes(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'h', 'e', 'y', ',', ' ', 'b', 'y', 'e', '.'};
	int *actual_map;
	int expected_map[26] = {0};
	expected_map[1] = 1;
	expected_map[4] = 2;
	expected_map[7] = 1;
	expected_map[24] = 2;

	actual_map = occmap_from_binary(bits, 9);

	TEST_INT_ARR_EQ(26, expected_map, actual_map);

	free(actual_map);
}

/*** occmap_to_freqmap ***/

void test_occmap_to_freqmap_null(void)
{
	printf("%s\n", __func__);

	assert(occmap_to_freqmap(NULL) == NULL);
}

void test_occmap_to_freqmap_empty(void)
{
	printf("%s\n", __func__);

	int occmap[26] = {0};
	float *actual_freq;
	float expected_freq[26] = {0.00f};

	actual_freq = occmap_to_freqmap(occmap);

	assert_farrs_eq(26, expected_freq, actual_freq, FLOAT_EPS);

	free(actual_freq);
}

void test_occmap_to_freqmap_single_letter(void)
{
	printf("%s\n", __func__);

	int occmap[26] = {0};
	occmap[4] = 1;
	float *actual_freq;
	float expected_freq[26] = {0.00f};
	expected_freq[4] = 100.00f;

	actual_freq = occmap_to_freqmap(occmap);

	assert_farrs_eq(26, expected_freq, actual_freq, FLOAT_EPS);

	free(actual_freq);
}

void test_occmap_to_freqmap_negative_occ(void)
{
	printf("%s\n", __func__);

	int occmap[26] = {0};
	occmap[4] = -1;

	assert(occmap_to_freqmap(occmap) == NULL);
}

void test_occmap_to_freqmap_multiple_bytes(void)
{
	printf("%s\n", __func__);

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

	assert_farrs_eq(26, expected_freq, actual_freq, FLOAT_EPS);

	free(actual_freq);
}

/*** freqmap_from_binary ***/

void test_freqmap_from_binary_null(void)
{
	printf("%s\n", __func__);

	assert(freqmap_from_binary(NULL, 0) == NULL);
}

void test_freqmap_from_binary_empty(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0};
	float *actual_map;
	float expected_map[26] = {0.00f};

	actual_map = freqmap_from_binary(bits, 0);

	assert_farrs_eq(26, expected_map, actual_map, FLOAT_EPS);

	free(actual_map);
}

void test_freqmap_from_binary_single_byte(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'E'};
	float *actual_map;
	float expected_map[26] = {0.00f};
	expected_map[4] = 100.00f;

	actual_map = freqmap_from_binary(bits, 1);

	assert_farrs_eq(26, expected_map, actual_map, FLOAT_EPS);

	free(actual_map);
}

void test_freqmap_from_binary_lowercase(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'e'};
	float *actual_map;
	float expected_map[26] = {0.00f};
	expected_map[4] = 100.00f;

	actual_map = freqmap_from_binary(bits, 1);

	assert_farrs_eq(26, expected_map, actual_map, FLOAT_EPS);

	free(actual_map);
}

void test_freqmap_from_binary_nonletter(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'7'};
	float *actual_map;
	float expected_map[26] = {0.00f};

	actual_map = freqmap_from_binary(bits, 1);

	assert_farrs_eq(26, expected_map, actual_map, FLOAT_EPS);

	free(actual_map);
}

void test_freqmap_from_binary_multiple_bytes(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'h', 'e', 'y', ',', ' ', 'b', 'y', 'e', '.'};
	float *actual_map;
	float expected_map[26] = {0.00f};
	expected_map[1] = 16.67f;
	expected_map[4] = 33.33f;
	expected_map[7] = 16.67f;
	expected_map[24] = 33.33f;

	actual_map = freqmap_from_binary(bits, 9);

	assert_farrs_eq(26, expected_map, actual_map, FLOAT_EPS);

	free(actual_map);
}

/*** freq_score ***/

void test_freq_score_null(void)
{
	printf("%s\n", __func__);

	float freq[26] = {0.00f};
	
	assert_floats_eq(freq_score(freq, NULL), FLT_MAX, FLOAT_EPS);
	assert_floats_eq(freq_score(NULL, freq), FLT_MAX, FLOAT_EPS);
	assert_floats_eq(freq_score(NULL, NULL), FLT_MAX, FLOAT_EPS);
}

void test_freq_score_empty(void)
{
	printf("%s\n", __func__);

	float freq[26] = {0.00f};
	float actual_score;
	float expected_score = 99.99f;

	actual_score = freq_score(freq, TEST_LETTER_FREQ);

	assert_floats_eq(expected_score, actual_score, FLOAT_EPS);
}

void test_freq_score_single_letter(void)
{
	printf("%s\n", __func__);

	float freq[26] = {0.00f};
	freq[4] = 100.00f;
	float actual_score;
	float expected_score = 175.95f;

	actual_score = freq_score(freq, TEST_LETTER_FREQ);

	assert_floats_eq(expected_score, actual_score, FLOAT_EPS);
}

void test_freq_score_multiple_letters(void)
{
	printf("%s\n", __func__);

	float freq[26] = {0.00f};
	freq[1] = 16.67f;
	freq[4] = 33.33f;
	freq[7] = 16.67f;
	freq[24] = 33.33f;
	float actual_score;
	float expected_score = 156.91f;

	actual_score = freq_score(freq, TEST_LETTER_FREQ);

	assert_floats_eq(expected_score, actual_score, FLOAT_EPS);
}

int main(void)
{
	test_occmap_from_binary_null();
	test_occmap_from_binary_empty();
	test_occmap_from_binary_single_byte();
	test_occmap_from_binary_lowercase();
	test_occmap_from_binary_nonletter();
	test_occmap_from_binary_multiple_bytes();

	test_occmap_to_freqmap_null();
	test_occmap_to_freqmap_empty();
	test_occmap_to_freqmap_single_letter();
	test_occmap_to_freqmap_negative_occ();
	test_occmap_to_freqmap_multiple_bytes();

	test_freqmap_from_binary_null();
	test_freqmap_from_binary_empty();
	test_freqmap_from_binary_single_byte();
	test_freqmap_from_binary_lowercase();
	test_freqmap_from_binary_nonletter();
	test_freqmap_from_binary_multiple_bytes();

	test_freq_score_null();
	test_freq_score_empty();
	test_freq_score_single_letter();
	test_freq_score_multiple_letters();

	return EXIT_SUCCESS;
}

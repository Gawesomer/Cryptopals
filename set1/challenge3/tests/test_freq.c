#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "cassert.h"
#include "../freq.c"


#define	FLOAT_EPS	0.01f

/*** occmap_from_binary ***/

void test_occmap_from_binary_null(void)
{
	printf("%s\n", __func__);

	assert(occmap_from_binary(NULL, 0) == NULL);
}

void test_occmap_from_binary_empty(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0};
	int *actual_map;
	int expected_map[26] = {0};

	actual_map = occmap_from_binary(bits, 0);

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);

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

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);

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

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);

	free(actual_map);
}

void test_occmap_from_binary_nonletter(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'7'};
	int *actual_map;
	int expected_map[26] = {0};

	actual_map = occmap_from_binary(bits, 1);

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);

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

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);

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

	return EXIT_SUCCESS;
}

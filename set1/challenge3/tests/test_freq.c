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

	uint8_t bits[] = {0};
	int numletters;

	assert(occmap_from_binary(NULL, 0, &numletters) == NULL);
	assert(occmap_from_binary(bits, 0, NULL) == NULL);
	assert(occmap_from_binary(NULL, 0, NULL) == NULL);
}

void test_occmap_from_binary_empty(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {0};
	int actual_letters;
	int *actual_map;
	int expected_letters = 0;
	int expected_map[26] = {0};

	actual_map = occmap_from_binary(bits, 0, &actual_letters);

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);
	assert(expected_letters == actual_letters);

	free(actual_map);
}

void test_occmap_from_binary_single_byte(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'E'};
	int actual_letters;
	int *actual_map;
	int expected_letters = 1;
	int expected_map[26] = {0};
	expected_map[4] = 1;

	actual_map = occmap_from_binary(bits, 1, &actual_letters);

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);
	assert(expected_letters == actual_letters);

	free(actual_map);
}

void test_occmap_from_binary_lowercase(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'e'};
	int actual_letters;
	int *actual_map;
	int expected_letters = 1;
	int expected_map[26] = {0};
	expected_map[4] = 1;

	actual_map = occmap_from_binary(bits, 1, &actual_letters);

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);
	assert(expected_letters == actual_letters);

	free(actual_map);
}

void test_occmap_from_binary_nonletter(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'7'};
	int actual_letters;
	int *actual_map;
	int expected_letters = 0;
	int expected_map[26] = {0};

	actual_map = occmap_from_binary(bits, 1, &actual_letters);

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);
	assert(expected_letters == actual_letters);

	free(actual_map);
}

void test_occmap_from_binary_multiple_bytes(void)
{
	printf("%s\n", __func__);

	uint8_t bits[] = {'h', 'e', 'y', ',', ' ', 'b', 'y', 'e', '.'};
	int actual_letters;
	int *actual_map;
	int expected_letters = 6;
	int expected_map[26] = {0};
	expected_map[1] = 1;
	expected_map[4] = 2;
	expected_map[7] = 1;
	expected_map[24] = 2;

	actual_map = occmap_from_binary(bits, 9, &actual_letters);

	assert_bytes_eq(26*sizeof(int), (uint8_t *)expected_map, \
			(uint8_t *)actual_map);
	assert(expected_letters == actual_letters);

	free(actual_map);
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

	test_freqmap_from_binary_null();

	return EXIT_SUCCESS;
}

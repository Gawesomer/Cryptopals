#include <limits.h>

#include "ham.h"

#define MIN_KEYSIZE	2
#define MAX_KEYSIZE	40


/* Return nth block of `blk_size` in `arr` */
uint8_t *get_block(const uint8_t *arr, size_t arr_size, size_t blk_size, int n)
{
	uint8_t *res;
	int i, j;

	if (!arr || n < 0 || blk_size == 0)
		return NULL;

	i = blk_size*n;
	if ((size_t)i >= arr_size || blk_size > arr_size)
		return NULL;

	res = calloc(blk_size, sizeof(uint8_t));

	j = 0;
	do {
		res[j] = arr[i];
		i++;
		j++;
	} while (i%blk_size != 0 && (size_t)i < arr_size);

	return res;
}

int find_keysize(const uint8_t *encrypted, size_t size)
{
	int curr_keysize = MIN_KEYSIZE;
	int curr_norm;
	int min_key;
	int min_norm = INT_MAX;
	uint8_t *blk1, *blk2, *blk3, *blk4;
	int h1, h2, h3, h4, h5, h6;

	while (curr_keysize <= MAX_KEYSIZE) {
		blk1 = get_block(encrypted, size, curr_keysize, 0);
		blk2 = get_block(encrypted, size, curr_keysize, 1);
		blk3 = get_block(encrypted, size, curr_keysize, 2);
		blk4 = get_block(encrypted, size, curr_keysize, 3);
		if (!blk4) {
			free(blk1);
			free(blk2);
			free(blk3);
			free(blk4);
			break;
		}
		h1 = hamming_dist_str((char *)blk1, (char *)blk2)/curr_keysize;
		h2 = hamming_dist_str((char *)blk1, (char *)blk3)/curr_keysize;
		h3 = hamming_dist_str((char *)blk1, (char *)blk4)/curr_keysize;
		h4 = hamming_dist_str((char *)blk2, (char *)blk3)/curr_keysize;
		h5 = hamming_dist_str((char *)blk2, (char *)blk4)/curr_keysize;
		h6 = hamming_dist_str((char *)blk3, (char *)blk4)/curr_keysize;
		curr_norm = (h1+h2+h3+h4+h5+h6)/6;
		if (curr_norm < min_norm) {
			min_norm = curr_norm;
			min_key = curr_keysize;
		}
		curr_keysize++;
	}

	return min_key;
}

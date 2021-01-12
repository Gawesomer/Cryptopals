#include <limits.h>
#include <float.h>
#include <stdint.h>
#include <stdlib.h>

#include "arr.h"
#include "break_repeatxor.h"
#include "ham.h"

#define MIN_KEYSIZE	2
#define MAX_KEYSIZE	40


int find_keysize(uint8_t *encrypted, size_t size)
{
	int curr_keysize;
	float curr_norm;
	int min_key = 0;
	float min_norm = FLT_MAX;
	uint8_t *blk1, *blk2, *blk3, *blk4;
	size_t blk1_size, blk2_size, blk3_size, blk4_size;

	if (!encrypted || size == 0)
		return 0;

	for (curr_keysize = MIN_KEYSIZE; curr_keysize <= MAX_KEYSIZE; curr_keysize++) {
		blk1 = slice(encrypted, size, sizeof(uint8_t), curr_keysize, 0, &blk1_size);
		blk2 = slice(encrypted, size, sizeof(uint8_t), curr_keysize, 1, &blk2_size);
		blk3 = slice(encrypted, size, sizeof(uint8_t), curr_keysize, 2, &blk3_size);
		blk4 = slice(encrypted, size, sizeof(uint8_t), curr_keysize, 3, &blk4_size);
		if ((int)blk4_size != curr_keysize)
			break;
		curr_norm = (
			hamming_dist(blk1, blk2, curr_keysize)+
			hamming_dist(blk2, blk3, curr_keysize)+
			hamming_dist(blk3, blk4, curr_keysize)+
			hamming_dist(blk1, blk3, curr_keysize)+
			hamming_dist(blk1, blk4, curr_keysize)+
			hamming_dist(blk2, blk4, curr_keysize)
			)/(6.0f*curr_keysize);
		if (curr_norm < min_norm) {
			min_norm = curr_norm;
			min_key = curr_keysize;
		}
	}

	return min_key;
}

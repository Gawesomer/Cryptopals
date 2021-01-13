#include <limits.h>
#include <float.h>
#include <stdint.h>
#include <stdlib.h>

#include "arr.h"
#include "break_repeatxor.h"
#include "div.h"
#include "freq.h"
#include "ham.h"
#include "repeat_xor.h"
#include "single_xor.h"

#define MIN_KEYSIZE	2
#define MAX_KEYSIZE	40


/* Find likely keysize of message encrypted using repeating-key XOR
 * params:
 * 	- bits: binary array
 * 	- size: size of `bits`
 * returns:
 * 	likely size of encryption key
 */
int find_keysize(uint8_t *bits, size_t size)
{
	int curr_keysize;
	float curr_norm;
	int min_key = 0;
	float min_norm = FLT_MAX;
	uint8_t *blk1, *blk2, *blk3, *blk4;
	size_t blk1_size, blk2_size, blk3_size, blk4_size;

	if (!bits || size == 0)
		return 0;

	for (curr_keysize = MIN_KEYSIZE; curr_keysize <= MAX_KEYSIZE; curr_keysize++) {
		blk1 = slice(bits, size, sizeof(uint8_t), curr_keysize, 0, &blk1_size);
		blk2 = slice(bits, size, sizeof(uint8_t), curr_keysize, 1, &blk2_size);
		blk3 = slice(bits, size, sizeof(uint8_t), curr_keysize, 2, &blk3_size);
		blk4 = slice(bits, size, sizeof(uint8_t), curr_keysize, 3, &blk4_size);
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

/* Transpose blocks of `bits`
 * Make a block that is the first byte of every block, and a block that is the
 * second byte of every block, and so on.
 * params:
 * 	- bits: binary array
 * 	- bits_size: size of `bits`
 * 	- blk_size: size of a block
 * returns:
 * 	Array of binary arrays (there will be `blk_size` amount of them)
 * 	binary arrays will be of size `bits_size/blk_size`
 * 	returned array has been dynamically allocated and should be freed
 * 	by user (don't forget to free the binary arrays individually)
 * note:
 * 	all blocks returned will be of the size of the smallest block
 * 	i.e. some blocks may be smaller than should be
 * 	this is to use the same size for all blocks
 */
uint8_t **transpose_blocks(uint8_t *bits, size_t bits_size, size_t blk_size)
{
	uint8_t **res;
	int i, j;

	if (!bits || bits_size == 0)
		return NULL;

	res = calloc(blk_size, sizeof(uint8_t *));

	for (i = 0; (size_t)i < blk_size; i++)
		res[i] = calloc(bits_size/blk_size, sizeof(uint8_t));

	for (i = 0; (size_t)i < blk_size; i++)
		for (j = 0; (size_t)j < (bits_size/blk_size); j++)
			res[i][j] = bits[(j*blk_size)+i];

	return res;
}

/* Decrypt binary data that has undergone repeating-key XOR encryption
 * params:
 * 	- bits: binary array
 * 	- bits_size: size of `bits`
 * 	- key_size: guessed key size
 * returns:
 * 	most likely encryption key
 * 	returned array has been dynamically allocated and should be freed
 * 	by user
 * side-effect:
 * 	`bits` has been altered to contain the likely decrypted result
 */
uint8_t *decrypt_repeatxor(uint8_t *bits, size_t bits_size, int key_size)
{
	uint8_t **transposed;
	size_t transposed_blksize;
	uint8_t *likely_key;
	int i;

	if (!bits || bits_size == 0 || key_size <= 0)
		return NULL;

	likely_key = calloc(key_size, sizeof(uint8_t));

	transposed = transpose_blocks(bits, bits_size, key_size);
	transposed_blksize = bits_size/key_size;

	for (i = 0; i < key_size; i++)
		likely_key[i] = decrypt_singlebytexor(transposed[i], transposed_blksize, ENGLISH_LETTER_FREQ);

	xor_repeating(bits, bits_size, likely_key, key_size);

	return likely_key;
}

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "freq.h"
#include "single_xor.h"
#include "xor.h"


/* XOR binary array with single byte
 * params:
 * 	- bits: binary array
 * 	- size: size of `bits`
 * 	- byte: single byte
 * returns:
 * 	nothing
 * side-effect:
 * 	`bits` has been updated to contain the result of `bits` XORed with `byte`
 */
void xor_singlebyte(uint8_t *bits, size_t size, uint8_t byte)
{
	uint8_t *operand;

	if (!bits || size == 0)
		return;

	operand = calloc(size, sizeof(uint8_t));
	memset(operand, byte, size);

	xor_binary(bits, operand, size);

	free(operand);
}

/* Decrypt binary data that has undergone a single-byte-xor based on language
 * frequency map
 * params:
 * 	- bits: binary array
 * 	- size: size of `bits`
 * 	- lang_freq: language frequency map of size 27 that should be compared
 * 		     to when determining the likeliness of the original message
 * returns:
 * 	most likely encryption/decryption key
 * side-effect:
 * 	`bits` has been altered to contain the likely decrypted result
 */
uint8_t decrypt_singlebytexor(uint8_t *bits, size_t size, const int lang_freq[27])
{
	uint8_t likely_key;
	int byte;
	int max_score, curr_score;

	if (!bits || size == 0 || !lang_freq)
		return 0;

	max_score = 0;
	for (byte = 0; byte < 256; byte++) {
		xor_singlebyte(bits, size, byte);
		curr_score = freq_score(bits, size, lang_freq);
		xor_singlebyte(bits, size, byte);
		if (max_score < curr_score) {
			max_score = curr_score;
			likely_key = byte;
		}
	}
	xor_singlebyte(bits, size, likely_key);

	return likely_key;
}

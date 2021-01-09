#include <float.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hex.h"
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
void xor_binary_singlebyte(uint8_t *bits, size_t size, uint8_t byte)
{
	uint8_t *operand;

	if (!bits || size == 0)
		return;

	operand = calloc(size, sizeof(uint8_t));
	memset(operand, byte, size);

	xor_binary(bits, operand, size);

	free(operand);
}

/* Replace '\0's with ' 's */
void replace_null_w_space(uint8_t *bits, size_t size)
{
	int i;

	if (!bits)
		return;

	for (i = 0; (size_t)i < size; i++)
		if (bits[i] == 0)
			bits[i] = 20;
}

/* Decrypt hex string that has undergone a single-byte-xor based on language
 * frequency map
 * params:
 * 	- hex: C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 	       representing a hex string
 * 	- lang_freq: language frequency map of size 26 that should be compared
 * 		     to when determining the likeliness of the original string
 * returns:
 * 	hex string of the same length as `hex` representing the most likely
 * 	decryption based on character frequency
 * 	or NULL if `hex` is NULL or is an invalid hex string
 * 	returned C-string has been dynamically allocated and should be freed by
 * 	user
 */
char *decrypt_singlebytexor_on_hex(const char *hex, const float lang_freq[26])
{
	char *plain;
	uint8_t *bin;
	unsigned int byte;
	size_t binsize;
	float min_freqscore, curr;
	uint8_t min_key;

	if (!hex || !lang_freq || hex[0] == '\0')
		return NULL;

	bin = hex_decode(hex);
	if (!bin)
		return NULL;

	binsize = b2fromhex_size(hex);

	min_freqscore = FLT_MAX;
	for (byte = 1; byte < 256; ++byte) {
		xor_binary_singlebyte(bin, binsize, byte);
		curr = freq_score_from_binary(bin, binsize, lang_freq);
		xor_binary_singlebyte(bin, binsize, byte);
		if (curr < min_freqscore) {
			min_freqscore = curr;
			min_key = byte;
		}
	}

	xor_binary_singlebyte(bin, binsize, min_key);

	replace_null_w_space(bin, binsize);

	plain = hex_encode(bin, binsize);
	free(bin);

	return plain;
}

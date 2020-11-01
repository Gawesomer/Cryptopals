#include "single_xor.h"

/* XOR binary array with single byte
 * params:
 * 	- bits: binary array
 * 	- size: size of `bits`
 * 	- byte: single byte
 * returns:
 * 	uint8_t binary array of size `size` containing the result of XORing
 * 	every byte of `bits` with `byte`
 * 	or NULL if `bits` is NULL or `size` is zero
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
uint8_t *xor_binary_singlebyte(const uint8_t *bits, size_t size, uint8_t byte)
{
	uint8_t *res;
	int i;

	if (!bits || size == 0)
		return NULL;

	res = calloc(size, sizeof(uint8_t));

	for (i = 0; i < size; ++i)
		res[i] = bits[i] ^ byte;

	return res;
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
	return NULL;
}

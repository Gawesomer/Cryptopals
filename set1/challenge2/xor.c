#include <stdlib.h>
#include <string.h>

#include "xor.h"

/* XOR two equal length binary arrays
 * params:
 * 	- a: binary array
 * 	- b: binary array
 * 	- size: size of `a` and `b`
 * returns:
 * 	uint8_t binary array of size `size` containing the result of a^b,
 * 	or NULL if either `a` or `b` is NULL
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
uint8_t *xor_binarrays(const uint8_t *a, const uint8_t *b, size_t size)
{
	uint8_t *res;
	int i;

	if (!a || !b)
		return NULL;

	res = calloc(size, sizeof(uint8_t));
	for (i = 0; (size_t)i < size; ++i)
		res[i] = a[i] ^ b[i];

	return res;
}

/* XOR two equal length C-string representing hex strings
 * params:
 * 	- a: C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 	     representing a hex string
 * 	- b: C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 	     representing a hex string
 * returns:
 * 	C-string of the same length as the smallest of either `a` or `b`
 * 	containing the result of a^b
 * 	or NULL if either `a` or `b` is NULL
 * 	or if either `a` or `b` is an invalid hex string
 * 	returned C-string has been dynamically allocated and should be freed by
 * 	user
 */
char *xor_hexstrs(const char *a, const char *b)
{
	char *res, *resoddlen;
	uint8_t *a_bin, *b_bin;
	size_t a_len, b_len, min_len;
	size_t a_bin_size, b_bin_size, min_size;
	uint8_t *res_bin;

	if (!a || !b)
		return NULL;

	a_bin = hextobinary(a);
	b_bin = hextobinary(b);

	if (!a_bin || !b_bin) {
		if (!a_bin && b_bin)
			free(b_bin);
		else if (!b_bin && a_bin)
			free(a_bin);
		return NULL;
	}

	a_len = strlen(a);
	b_len = strlen(b);
	min_len = (a_len <= b_len) ? a_len : b_len;

	a_bin_size = binaryfromhex_size(a_len);
	b_bin_size = binaryfromhex_size(b_len);
	min_size = (a_bin_size <= b_bin_size) ? a_bin_size : b_bin_size;

	res_bin = xor_binarrays(a_bin, b_bin, min_size);
	free(a_bin);
	free(b_bin);

	res = binarytohex(res_bin, min_size);
	free(res_bin);

	if (min_len%2 != 0) {
		resoddlen = calloc(min_len+1, sizeof(char));
		strcpy(resoddlen, res+1);
		free(res);
		return resoddlen;
	}

	return res;
}

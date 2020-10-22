/* XOR two equal length binary arrays
 * params:
 * 	- a: binary array of size `size`
 * 	- b: binary array of size `size`
 * 	- size: size of `a` and `b`
 * returns:
 * 	uint8_t binary array of size `size` containing the result of a^b,
 * 	or NULL if either `a` or `b` is NULL
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
uint8_t *xor_binarrays(const uint8_t *a, const uint8_t *b, size_t size)
{
	return NULL;
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
	return NULL;
}

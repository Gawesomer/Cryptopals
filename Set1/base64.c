/* Returns size in bytes of binary translation from hex for given `hexlen` */
size_t binaryfromhex_size(size_t hexlen)
{
	return 0;
}

/* Convert hex string to binary representation
 * params:
 * 	- hexstr: C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 		  representing a hex string 
 * returns:
 * 	uint8_t array of size `binaryfromhex_size` representing binary
 * 	translation of `hexstr`, or NULL if `hexstr` is NULL or contains
 * 	invalid hex codes.
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
uint8_t *hextobinary(char *hexstr)
{
	return NULL;
}

/* Returns size in bytes of base64 translation from binary for given
 * `numbytes`
 */
size_t base64frombinary_size(size_t numbytes)
{
	return 0;
}

/* Convert binary representation to base64
 * params:
 * 	- bits: bits to translate to base64
 * 	- numbytes: size of `bits` array
 * returns:
 * 	uint8_t array of size `base64frombinary_size` representing base64
 * 	translation of `bits` or NULL if `bits` is NULL
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
uint8_t *binarytobase64(uint8_t *bits, size_t numbytes)
{
	return NULL;
}

/* Encodes uint8_t array in base64 representation to base64 encoding
 * params:
 * 	- base64: uint8_t array in base64 representation (i.e. all elements are
 * 		  in the range [0-63])
 * 	- numbytes: size in bytes of `base64`
 * returns:
 * 	C-string base64 encoding of `base64`, or NULL if `base64` is NULL or
 * 	contains elements not in range [0-63]
 * 	returned C-string has been dynamically allocated and should be freed by
 * 	user
 */
char *base64stringify(uint8_t *base64, size_t numbytes)
{
	return NULL;
}

/* Returns length of base64 translated string for given `hexlen` */
size_t base64fromhex_len(size_t hexlen)
{
	return 0;
}

/* Convert hex string to base64 string
 * params:
 * 	- hexstr: C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 		  representing a hex string
 * returns:
 * 	C-string representing base64 translation of `hexstr`,
 * 	or NULL if `hexstr` is NULL or contains invalid hex codes.
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
char *hextobase64(char *hexstr)
{
	return NULL;
}

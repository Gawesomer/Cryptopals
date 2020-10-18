#ifndef _HEX_H_
#define _HEX_H_


/* Returns size in bytes of binary translation from hex for given `hexlen` */
size_t binaryfromhex_size(size_t hexlen);

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
uint8_t *hextobinary(char *hexstr);

#endif

#include <stdlib.h>
#include <string.h>

#include "div.h"
#include "hex.h"

/* Returns size in bytes of base64 translation from binary for given
 * `numbytes`
 */
size_t base64frombinary_size(size_t numbytes)
{
	return round_up_div(numbytes*4, 3);
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
	uint8_t *base64;
	size_t base64size;
	uint8_t base64mask, binarymask;
	int ibase64, ibin;

	if (!bits || numbytes == 0)
		return NULL;

	base64size = base64frombinary_size(numbytes);
	base64 = calloc(base64size, sizeof(uint8_t));

	base64mask = 1<<5;
	binarymask = 1<<7;
	ibase64 = ibin = 0;
	while (ibin < numbytes) {
		if (bits[ibin]&binarymask)
			base64[ibase64] |= base64mask;
		base64mask >>= 1;
		if (!base64mask) {
			base64mask = 1<<5;
			++ibase64;
		}
		binarymask >>= 1;
		if (!binarymask) {
			binarymask = 1<<7;
			++ibin;
		}
	}

	return base64;
}

/* Returns char representation of `i` if within range [0, 63], otherwise '\0' */
char base64_inttochar(uint8_t i)
{
	if (0 <= i && i <= 25)
		return i+'A';
	if (26 <= i && i <= 51)
		return i+'a'-26;
	if (52 <= i && i <= 61)
		return i+'0'-52;
	if (i == 62)
		return '+';
	if (i == 63)
		return '/';
	return '\0';
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
char *base64_tostring(uint8_t *base64, size_t numbytes)
{
	char *base64str;
	char base64char;
	int i;

	if (!base64)
		return NULL;

	base64str = calloc(numbytes+1, sizeof(char));

	for (i = 0; i < numbytes; ++i) {
		base64char = base64_inttochar(base64[i]);
		if (base64char == '\0') {
			free(base64str);
			return NULL;
		}
		base64str[i] = base64char;
	}
	base64str[i] = '\0';

	return base64str;
}

/* Returns amount of padding that should be added to a base64 string of length
 * `base64len` */
size_t base64padding_len(size_t base64len)
{
	return (base64len%4) ? 4-(base64len%4) : 0;
}

/* Convert hex string to base64 string
 * params:
 * 	- hexstr: C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 		  representing a hex string
 * returns:
 * 	C-string representing base64 translation of `hexstr`,
 * 	or NULL if `hexstr` is NULL, empty or contains invalid hex codes.
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
char *hextobase64(char *hexstr)
{
	size_t hexlen, binarysize, base64size, base64padding;
	uint8_t *binary, *base64;
	char *base64str, *base64padded;
	int i;

	if (!hexstr)
		return NULL;
	hexlen = strlen(hexstr);

	binarysize = binaryfromhex_size(hexlen);
	binary = hextobinary(hexstr);

	base64size = base64frombinary_size(binarysize);
	base64 = binarytobase64(binary, binarysize);
	free(binary);

	base64str = base64_tostring(base64, base64size);
	free(base64);

	if (!base64str)
		return NULL;

	base64padding = base64padding_len(base64size);
	if (base64padding != 0)
		base64padded = realloc(base64str, base64size+base64padding+1);
	else
		base64padded = base64str;

	for (i = 0; i < base64padding; ++i)
		base64padded[base64size+i] = '=';
	base64padded[base64size+base64padding] = '\0';

	return base64padded;
}

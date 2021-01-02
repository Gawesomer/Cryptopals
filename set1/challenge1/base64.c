#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"
#include "div.h"
#include "hex.h"

/* Return size in bytes of base64 translation from binary for given
 * `numbytes`
 */
size_t base64_bytesize(size_t numbytes)
{
	return round_up_div(numbytes*4, 3);
}

/* Return char representation of `i` if within range [0, 63], otherwise '\0' */
char base64char_encode(uint8_t i)
{
	if (i <= 25)
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

/* Convert binary data to base64 string
 * params:
 * 	- bits: bits to translate to base64
 * 	- numbytes: size of `bits` array
 * returns:
 * 	C-string with characters in range
 * 	[A, ..., Z, a, ..., z, 0, ..., 9, +, /]
 * 	corresponding to base64 representation of `bits`,
 * 	or NULL if `bits` is NULL
 * 	returned C-string has been dynamically allocated and should be freed
 * 	by user
 */
char *base64_encode(const uint8_t *bits, size_t numbytes)
{
	char *base64;
	char base64char;
	size_t base64size;
	uint8_t base64mask, bitsmask;
	int ibase64, ibits, i;

	if (!bits || numbytes == 0)
		return NULL;

	base64size = base64_bytesize(numbytes);
	base64 = calloc(base64size+1, sizeof(char));

	base64mask = 1<<5;
	bitsmask = 1<<7;
	ibase64 = ibits = 0;
	while ((size_t)ibits < numbytes) {
		if (bits[ibits]&bitsmask)
			base64[ibase64] |= base64mask;
		base64mask >>= 1;
		if (!base64mask) {
			base64mask = 1<<5;
			++ibase64;
		}
		bitsmask >>= 1;
		if (!bitsmask) {
			bitsmask = 1<<7;
			++ibits;
		}
	}

	for (i = 0; (size_t)i < base64size; ++i) {
		base64char = base64char_encode(base64[i]);
		if (base64char == '\0') {
			free(base64);
			return NULL;
		}
		base64[i] = base64char;
	}
	base64[i] = '\0';

	return base64;
}

/* Return amount of padding that should be added to a base64 string of length
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
char *hextobase64(const char *hexstr)
{
	size_t hexlen, binarysize, base64size, base64padding;
	uint8_t *binary;
	char *base64, *base64padded;
	int i;

	if (!hexstr)
		return NULL;
	hexlen = strlen(hexstr);

	binarysize = hex_bytesize(hexlen);
	binary = hex_decode(hexstr);

	base64size = base64_bytesize(binarysize);
	base64 = base64_encode(binary, binarysize);
	free(binary);

	if (!base64)
		return NULL;

	base64padding = base64padding_len(base64size);
	if (base64padding != 0)
		base64padded = realloc(base64, base64size+base64padding+1);
	else
		base64padded = base64;

	for (i = 0; (size_t)i < base64padding; ++i)
		base64padded[base64size+i] = '=';
	base64padded[base64size+base64padding] = '\0';

	return base64padded;
}

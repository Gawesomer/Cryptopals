#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"
#include "div.h"
#include "hex.h"

/* Return size in bytes of base64 translation from binary for given
 * `numbytes`
 */
size_t b64fromb2_size(size_t numbytes)
{
	size_t res;

	res = round_up_div(numbytes*4, 3);
	while (res%4 != 0)
		res++;

	return res;
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

	base64size = b64fromb2_size(numbytes);
	base64 = calloc(base64size+1, sizeof(char));

	/* split into right-padded sextets */
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

	/* translate to ASCII characters */
	if (base64mask < (1<<5))
		ibase64++;

	for (i = 0; i < ibase64; ++i) {
		base64char = base64char_encode(base64[i]);
		if (base64char == '\0') {
			free(base64);
			return NULL;
		}
		base64[i] = base64char;
	}

	/* add padding */
	for (; (size_t)i < base64size; i++)
		base64[i] = '=';
	base64[i] = '\0';

	return base64;
}

/* Return size in bytes of binary translation from base64 for given
 * `numbytes`
 */
size_t b2fromb64_size(const char *base64)
{
	size_t len;
	size_t res;

	if (!base64)
		return 0;

	len = strlen(base64);
	if (len <= 1)
		return 0;

	if ((len%4) != 0)
		return (len*3)/4;	// round down

	res = (len*3)/4;
	if (base64[len-1] == '=') {
		res--;
		if (base64[len-2] == '=')
			res--;
	}

	return res;
}

/* Return base64 value of `c` if within range
 * [A, ..., Z, a, ..., z, 0, ..., 9, +, /],
 * otherwise 255 */
uint8_t base64char_decode(char c)
{
	if ('A' <= c && c <= 'Z')
		return c-'A';
	if ('a' <= c && c <= 'z')
		return c-'a'+26;
	if ('0' <= c && c <= '9')
		return c-'0'+52;
	if (c == '+')
		return 62;
	if (c == '/')
		return 63;
	if (c == '=')
		return 0;
	return 255;
}

/* Convert base64 string to binary data
 * Accounts for padding
 * In the case where `base64`'s length is not a multiple of four, only the
 * first valid octets are converted, extraneous bits are disreguarded
 * params:
 * 	- base64: C-string with characters in range
 * 		  [A, ..., Z, a, ..., z, 0, ..., 9, +, /],
 * 		  representing a hex string
 * returns:
 * 	uint8_t array of size `b2fromb64_size` representing binary
 * 	representation of `base64`, or NULL if `base64` is NULL or contains
 * 	invalid base64 codes.
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
uint8_t *base64_decode(const char *base64)
{
	uint8_t *bits, *base64_raw;
	size_t len;
	uint8_t base64char;
	size_t binarysize;
	uint8_t base64mask, binarymask;
	int ibase64, ibits, i;

	if (!base64)
		return NULL;

	len = strlen(base64);
	binarysize = b2fromb64_size(base64);
	if (binarysize == 0)
		return NULL;

	base64_raw = calloc(len, sizeof(uint8_t));

	/* translate from ASCII */
	for (i = 0; (size_t)i < len; i++) {
		base64char = base64char_decode(base64[i]);
		if (base64char > 63) {
			free(base64_raw);
			return NULL;
		}
		base64_raw[i] = base64char;
	}

	bits = calloc(binarysize, sizeof(uint8_t));

	/* split into octets */
	base64mask = 1<<5;
	binarymask = 1<<7;
	ibase64 = ibits = 0;
	while ((size_t)ibits < binarysize) {
		if (base64_raw[ibase64]&base64mask)
			bits[ibits] |= binarymask;
		binarymask >>= 1;
		if (!binarymask) {
			binarymask = 1<<7;
			++ibits;
		}
		base64mask >>= 1;
		if (!base64mask) {
			base64mask = 1<<5;
			++ibase64;
		}
	}
	free(base64_raw);

	return bits;
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
	uint8_t *binary;
	char *base64;

	binary = hex_decode(hexstr);

	base64 = base64_encode(binary, b2fromhex_size(hexstr));
	free(binary);

	return base64;
}

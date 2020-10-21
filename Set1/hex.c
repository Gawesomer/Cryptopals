#include <stdlib.h>
#include <string.h>

#include "div.h"

/* Returns size in bytes of binary translation from hex for given `hexlen` */
size_t binaryfromhex_size(size_t hexlen)
{
	return round_up_div(hexlen, 2);
}

/* Returns hex value of `c` if within range [0x0, 0xF], otherwise 255 */
uint8_t hex_chartoint(char c)
{
	if ('0' <= c && c <= '9')
		return c-'0';
	if ('A' <= c && c <= 'F')
		return c-'A'+10;
	if ('a' <= c && c <= 'f')
		return c-'a'+10;
	return 255;
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
uint8_t *hextobinary(const char *hexstr)
{
	uint8_t *bits;
	size_t numbytes;
	uint8_t hexchar;
	int ihex, ibin;

	if (!hexstr)
		return NULL;

	numbytes = binaryfromhex_size(strlen(hexstr));

	if (numbytes == 0)
		return NULL;

	bits = calloc(numbytes, sizeof(uint8_t));

	ibin = ihex = 0;
	while (hexstr[ihex] != '\0') {
		hexchar = hex_chartoint(hexstr[ihex]);
		if (hexchar > 15) {
			free(bits);
			return NULL;
		}
		bits[ibin] += hexchar;

		if (ihex%2 == 0)
			bits[ibin] <<= 4;
		else
			++ibin;
		++ihex;
	}
	if (ibin%2 == 0)
		bits[ibin] >>= 4;

	return bits;
}

/* Returns char representation of hex value if within range [0x0, 0xF],
 * otherwise '\0' */
char hex_inttochar(uint8_t i)
{
	if (0 <= i && i <= 9)
		return i+'0';
	if (10 <= i && i <= 15)
		return i+'A'-10;
	return '\0';
}

/* Convert binary to hex string
 * params:
 * 	- bits: bits to translate to hex
 * 	- numbytes: size of `bits` array
 * returns:
 * 	C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 	representing hex translation of `bits`, or NULL if `bits` is NULL
 * 	returned C-string has been dynamically allocated and shoould be freed
 * 	by user
 */
char *binarytohex(const uint8_t *bits, size_t numbytes)
{
	char *hexstr;
	char hexchar;
	int i;

	if (!bits)
		return NULL;

	hexstr = calloc((2*numbytes)+1, sizeof(char));

	for (i = 0; i < 2*numbytes; ++i) {
		hexchar = hex_inttochar(bits[i]>>4);
		if (hexchar == '\0') {
			free(hexstr);
			return NULL;
		}
		hexstr[2*i] = hexchar;
		hexchar = hex_inttochar(bits[i]&0xF);
		if (hexchar == '\0') {
			free(hexstr);
			return NULL;
		}
		hexstr[(2*i)+1] = hexchar;
	}
	hexstr[i] = '\0';

	return hexstr;
}

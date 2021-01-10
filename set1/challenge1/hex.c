#include <stdlib.h>
#include <string.h>

#include "div.h"
#include "hex.h"


/* Return size in bytes of binary translation from hex for given `hexlen` */
size_t b2fromhex_size(const char *hexstr)
{
	size_t len;

	if (!hexstr)
		return 0;
	len = strlen(hexstr);

	return round_up_div(len, 2);
}

/* Return hex value of `c` if within range [0x0, 0xF], otherwise 255 */
uint8_t hexchar_decode(char c)
{
	if ('0' <= c && c <= '9')
		return c-'0';
	if ('A' <= c && c <= 'F')
		return c-'A'+10;
	if ('a' <= c && c <= 'f')
		return c-'a'+10;
	return 255;
}

/* Convert hex string to binary data
 * params:
 * 	- hexstr: C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 		  representing a hex string 
 * returns:
 * 	uint8_t array of size `b2fromhex_size` representing binary
 * 	representation of `hexstr`, or NULL if `hexstr` is NULL or contains
 * 	invalid hex codes.
 * 	note, array will be padded right (i.e. will begin with four zero bits)
 * 	if the length of `hexstr` is odd
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
uint8_t *hex_decode(const char *hexstr)
{
	uint8_t *bits;
	size_t numbytes;
	uint8_t hexchar;
	int ihex, ibits;
	int oddlen;
	size_t len;

	if (!hexstr)
		return NULL;

	len = strlen(hexstr);
	oddlen = (len%2 != 0);
	numbytes = b2fromhex_size(hexstr);

	if (numbytes == 0)
		return NULL;

	bits = calloc(numbytes, sizeof(uint8_t));

	ibits = ihex = 0;
	while (hexstr[ihex] != '\0') {
		hexchar = hexchar_decode(hexstr[ihex]);
		if (hexchar > 0xF) {
			free(bits);
			return NULL;
		}
		bits[ibits] += hexchar;

		if ((ihex+oddlen)%2 == 0)
			bits[ibits] <<= 4;
		else
			++ibits;
		++ihex;
	}

	return bits;
}

/* Return size in bytes of hex translation from binary for given `numbytes` */
size_t hexfromb2_size(size_t numbytes)
{
	return 2*numbytes;
}

/* Return char representation of hex value if within range [0x0, 0xF],
 * otherwise '\0' */
char hexchar_encode(uint8_t i)
{
	if (i <= 9)
		return i+'0';
	if (0xA <= i && i <= 0xF)
		return i+'A'-10;
	return '\0';
}

/* Convert binary data to hex string
 * params:
 * 	- bits: bits to translate to hex
 * 	- numbytes: size of `bits` array
 * returns:
 * 	C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 	corresponding to hex representation of `bits`,
 * 	or NULL if `bits` is NULL
 * 	returned C-string has been dynamically allocated and should be freed
 * 	by user
 */
char *hex_encode(const uint8_t *bits, size_t numbytes)
{
	char *hexstr;
	char hexchar;
	int i, j;

	if (!bits)
		return NULL;

	numbytes = hexfromb2_size(numbytes);
	hexstr = calloc(numbytes+1, sizeof(char));

        i = j = 0;
        while ((size_t)i < numbytes) {
                hexchar = hexchar_encode(bits[j]>>4);
                if (hexchar == '\0') {
                        free(hexstr);
                        return NULL;
                }
                hexstr[i++] = hexchar;
                hexchar = hexchar_encode(bits[j]&0xF);
                if (hexchar == '\0') {
                        free(hexstr);
                        return NULL;
                }
                hexstr[i++] = hexchar;
                j++;
        }
        hexstr[i] = '\0';

	return hexstr;
}

/* Convert hex string to ASCII representation
 * params:
 * 	- hexstr: C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 		  representing a hex string 
 * returns:
 * 	C-string representing ascii translation of `hexstr`
 * 	or NULL if `hexstr` is NULL or empty, or contains invalid hex codes.
 * 	returned C-string has been dynamically allocated and should be freed by
 * 	user
 * notes:
 * 	does not support extended ASCII, translation of hex values larger than
 * 	`7F` should not be expected to be correct
 * 	this is due to the fact that whether `char` is signed or unsigned is
 * 	machine dependent hence, values larger than 127 may be negated
 */
char *hextoascii(const char *hexstr)
{
	char *ascii;
	size_t ascii_len;
	uint8_t *binary;
	int i;

	binary = hex_decode(hexstr);
	if (!binary || hexstr[0] == '\0')
		return NULL;

	ascii_len = b2fromhex_size(hexstr);
	ascii = calloc(ascii_len+1, sizeof(char));

	for (i = 0; (size_t)i < ascii_len; ++i)
		ascii[i] = binary[i];
	ascii[i] = '\0';

	free(binary);

	return ascii;
}

/* Convert ASCII string to hex string
 * params:
 * 	- ascii: C-string
 * returns:
 * 	C-string with characters in range [0, 1, ..., 9, A, ..., F]
 * 	representing the hex translation of `ascii`
 * 	or NULL if `ascii` is NULL or empty
 * 	returned C-string has been dynamically allocated and should be freed by
 * 	user
 */
char *asciitohex(const char *ascii)
{
	char *hex;
	size_t len;
	uint8_t *binary;
	int i;

	if (!ascii || ascii[0] == '\0')
		return NULL;

	len = strlen(ascii);

	binary = calloc(len, sizeof(uint8_t));
	for (i = 0; (size_t)i < len; ++i)
		binary[i] = ascii[i];

	hex = hex_encode(binary, len);

	free(binary);

	return hex;
}

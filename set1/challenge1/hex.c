#include "hex.h"

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
 * 	note, array will be padded right (i.e. will begin with four zero bits)
 * 	if the length of `hexstr` is odd
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
uint8_t *hextobinary(const char *hexstr)
{
	uint8_t *bits;
	size_t numbytes;
	uint8_t hexchar;
	int ihex, ibin;
	int oddlen;
	size_t len;

	if (!hexstr)
		return NULL;

	len = strlen(hexstr);
	oddlen = (len%2 != 0);
	numbytes = binaryfromhex_size(len);

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

		if ((ihex+oddlen)%2 == 0)
			bits[ibin] <<= 4;
		else
			++ibin;
		++ihex;
	}

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
	int i, j;

	if (!bits)
		return NULL;

	hexstr = calloc((2*numbytes)+1, sizeof(char));

        i = j = 0;
        while (i < 2*numbytes) {
                hexchar = hex_inttochar(bits[j]>>4);
                if (hexchar == '\0') {
                        free(hexstr);
                        return NULL;
                }
                hexstr[i++] = hexchar;
                hexchar = hex_inttochar(bits[j]&0xF);
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

	binary = hextobinary(hexstr);
	if (!binary || hexstr[0] == '\0')
		return NULL;

	ascii_len = binaryfromhex_size(strlen(hexstr));
	ascii = calloc(ascii_len+1, sizeof(char));

	for (i = 0; i < ascii_len; ++i) {
		ascii[i] = binary[i];
	}
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
	for (i = 0; i < len; ++i)
		binary[i] = ascii[i];

	hex = binarytohex(binary, len);

	free(binary);

	return hex;
}

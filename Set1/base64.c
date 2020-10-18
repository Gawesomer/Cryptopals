/* Returns integer division a/b rounded up. Returns 0 if b is 0 */
size_t round_up_div(size_t a, size_t b)
{
	if (a == 0 || b == 0)
		return 0;
	return ((a-1)/b)+1;
}

/* Returns size in bytes of binary translation from hex for given `hexlen` */
size_t binaryfromhex_size(size_t hexlen)
{
	return round_up_div(hexlen, 2);
}

/* Returns hex value of `c` if within range [0x0, 0xF] ortherwise 255 */
uint8_t hexchar_destringify(char c)
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
uint8_t *hextobinary(char *hexstr)
{
	uint8_t *bits;
	size_t numbytes;
	uint8_t c;
	int ihex, ibin;

	if (!hexstr)
		return NULL;

	numbytes = binaryfromhex_size(strlen(hexstr));

	if (numbytes == 0)
		return NULL;

	bits = calloc(numbytes, sizeof(uint8_t));

	ibin = ihex = 0;
	while (hexstr[ihex] != '\0') {
		c = hexchar_destringify(hexstr[ihex]);
		if (c > 15) {
			free(bits);
			return NULL;
		}
		bits[ibin] += c;

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

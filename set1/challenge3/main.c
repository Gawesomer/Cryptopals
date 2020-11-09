#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "single_xor.h"
#include "freq.h"
#include "hex.h"

int main(void)
{
	char encoded[] = "1b37373331363f78151b7f2b783431333d78397828372d363c" \
			  "78373e783a393b3736";
	char *decoded = decrypt_singlebytexor_on_hex(encoded, \
				ENGLISH_LETTER_FREQ);

	uint8_t *binary = hextobinary(decoded);
	size_t binsize = binaryfromhex_size(strlen(decoded));
	free(decoded);

	for (int i = 0; (size_t)i < binsize; ++i)
		printf("%c", binary[i]);
	printf("\n");

	free(binary);
}

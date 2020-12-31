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
	char *ascii = hextoascii(decoded);

	free(decoded);

	printf("%s\n", ascii);

	free(ascii);

	return EXIT_SUCCESS;
}

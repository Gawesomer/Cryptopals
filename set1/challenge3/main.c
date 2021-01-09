#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "freq.h"
#include "hex.h"
#include "single_xor.h"
#include "xor.h"

int main(void)
{
	char hex[] = "1b37373331363f78151b7f2b783431333d78397828372d363c" \
			  "78373e783a393b3736";
	uint8_t *binary;
	size_t size;
	uint8_t key;
	int i;

	binary = hex_decode(hex);
	size = b2fromhex_size(hex);

	key = decrypt_singlebytexor(binary, size, ENGLISH_LETTER_FREQ);

	printf("key: %x\tdecrypted: '", key);
	for (i = 0; (size_t)i < size; i++)
		printf("%c", binary[i]);
	printf("'\n");
	free(binary);

	return EXIT_SUCCESS;
}

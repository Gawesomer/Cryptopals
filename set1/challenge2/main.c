#include <stdio.h>
#include <stdlib.h>

#include "hex.h"
#include "xor.h"

int main(void)
{
	const char a_hex[] = "1c0111001f010100061a024b53535009181c";
	const char b_hex[] = "686974207468652062756c6c277320657965";
	uint8_t *a_binary, *b_binary;
	size_t binary_size;
	char *xor_hex;

	binary_size = b2fromhex_size(a_hex);

	a_binary = hex_decode(a_hex);
	b_binary = hex_decode(b_hex);

	xor_binary(a_binary, b_binary, binary_size);
	free(b_binary);

	xor_hex = hex_encode(a_binary, binary_size);
	free(a_binary);

	printf("%s\n^\n%s\n=\n%s\n", a_hex, b_hex, xor_hex);
	printf("expected:\n746865206b696420646f6e277420706c6179\n");
	free(xor_hex);

	return EXIT_SUCCESS;
}

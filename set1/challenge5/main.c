#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repeat_xor.h"


int main(void)
{
	const char plain[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
	char *encrypted = xor_repeating(plain, "ICE");

	printf("expect: 0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272"
		"a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f\n");

	printf("cipher: ");
	for (int i = 0; (size_t)i < strlen(plain); i++)
		printf("%02x", encrypted[i]);
	printf("\n");

	free(encrypted);

	return EXIT_SUCCESS;
}

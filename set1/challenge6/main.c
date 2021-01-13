#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "base64.h"
#include "break_repeatxor.h"

#define MSGSIZE	60*64

/* Remove newline character from string if present */
void strip_newline(char *s)
{
	int len;

	if (!s)
		return;

	len = strlen(s);

	if (s[len-1] == '\n')
		s[len-1] = '\0';
}

int main(void)
{
	FILE *input_file;
	char wholestr[MSGSIZE] = {0};	// base64 encoded
	uint8_t *binary;		// decoded binary data
	size_t binary_size;
	char *lineptr = NULL;
	size_t linesize = 0;
	int likely_keysize;
	uint8_t *likely_key;
	int i;

	lineptr = calloc(linesize, sizeof(char));
	input_file = fopen("./input", "r");
	if (!input_file)
		perror("fopen");

	while (getline(&lineptr, &linesize, input_file) != -1) {
		strip_newline(lineptr);
		strcat(wholestr, lineptr);
	}

	free(lineptr);
	fclose(input_file);

	printf("--- base64 encoded string ---\n");
	printf("%s\n", wholestr);

	binary = base64_decode(wholestr);
	binary_size = b2fromb64_size(wholestr);

	printf("--- base64 decoded ---\n");
	for (i = 0; (size_t)i < binary_size; i++)
		printf("%c", binary[i]);
	printf("\n");

	likely_keysize = find_keysize(binary, binary_size);
	printf("--- likely_keysize ---\n");
	printf("%d\n", likely_keysize);

	likely_key = decrypt_repeatxor(binary, binary_size, likely_keysize);
	printf("--- likely_key ---\n");
	for (i = 0; i < likely_keysize; i++)
		printf("%c", likely_key[i]);
	printf("\n");

	printf("--- likely decrypted message ---\n");
	for (i = 0; (size_t)i < binary_size; i++)
		printf("%c", binary[i]);
	printf("\n");

	free(likely_key);
	free(binary);

	return EXIT_SUCCESS;
}

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freq.h"
#include "hex.h"
#include "single_xor.h"

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
	char *lineptr = NULL;
	size_t linesize = 0;
	uint8_t *binary;
	size_t binary_size;
	uint8_t *likely_decrypted = NULL;
	int max_score, curr_score;
	int i;

	lineptr = calloc(linesize, sizeof(char));
	input_file = fopen("./input", "r");
	if (!input_file)
		perror("fopen");

	max_score = 0;
	while (getline(&lineptr, &linesize, input_file) != -1) {
		strip_newline(lineptr);

		binary = hex_decode(lineptr);
		binary_size = b2fromhex_size(lineptr);

		decrypt_singlebytexor(binary, binary_size, ENGLISH_LETTER_FREQ);
		curr_score = freq_score(binary, binary_size, ENGLISH_LETTER_FREQ);

		if (max_score < curr_score) {
			max_score = curr_score;
			if (likely_decrypted)
				free(likely_decrypted);
			likely_decrypted = binary;
		} else
			free(binary);
	}

	free(lineptr);
	fclose(input_file);

	printf("max_score: %d\tdecrypted: '", max_score);
	for (i = 0; (size_t)i < binary_size; i++)
		printf("%c", likely_decrypted[i]);
	printf("'\n");
	free(likely_decrypted);

	return EXIT_SUCCESS;
}

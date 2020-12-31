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
	float curr_score;
	float min_score = FLT_MAX;
	char *decrypted = NULL;
	char *ascii;

	lineptr = calloc(linesize, sizeof(char));
	input_file = fopen("./input", "r");
	if (!input_file)
		perror("fopen");

	while (getline(&lineptr, &linesize, input_file) != -1) {
		strip_newline(lineptr);
		curr_score = freq_score_from_hex(lineptr, ENGLISH_LETTER_FREQ);
		if (curr_score < min_score) {
			min_score = curr_score;
			if (decrypted)
				free(decrypted);
			decrypted = decrypt_singlebytexor_on_hex(lineptr, \
					ENGLISH_LETTER_FREQ);
		}
	}

	free(lineptr);
	fclose(input_file);

	ascii = hextoascii(decrypted);
	free(decrypted);

	printf("min_score: %f\tdecrypted: '%s'\n", min_score, ascii);
	free(ascii);

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "base64.h"

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
	uint8_t *decodedstr;
	char *lineptr = NULL;
	size_t linesize = 0;

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

	printf("%s\n", wholestr);

	decodedstr = base64_decode(wholestr);

	printf("%s\n", decodedstr);
	free(decodedstr);

	return EXIT_SUCCESS;
}

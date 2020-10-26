#include <stdio.h>
#include <stdlib.h>

#include "base64.h"

int main(void)
{
	char hexstr[] = "49276d206b696c6c696e6720796f757220627261696e206c696" \
			"b65206120706f69736f6e6f7573206d757368726f6f6d";
	char *base64str = hextobase64(hexstr);

	printf("hexstr:    '%s'\n", hexstr);
	printf("base64str: '%s'\n", base64str);

	free(base64str);
}

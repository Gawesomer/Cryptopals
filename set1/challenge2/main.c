#include <stdio.h>
#include <stdlib.h>

#include "xor.h"

int main(void)
{
	char a[] = "1c0111001f010100061a024b53535009181c";
	char b[] = "686974207468652062756c6c277320657965";
	char *res = xor_hexstrs(a, b);

	printf("XOR(\"%s\", \"%s\") = \"%s\"\n", a, b, res);

	free(res);
}

#include <stdio.h>
#include <stdlib.h>

#include "cTest.h"
#include "../ham.c"

/*** hamming_dist ***/

int test_hamming_dist_null(void)
{
	int status = 0;
	uint8_t bits[] = {0};

	status += TEST_INT_EQ(hamming_dist(NULL, NULL, 1), -1);
	status += TEST_INT_EQ(hamming_dist(bits, NULL, 1), -1);
	status += TEST_INT_EQ(hamming_dist(NULL, bits, 1), -1);

	return status;
}

int test_hamming_dist_empty(void)
{
	uint8_t bits[] = {0};

	return TEST_INT_EQ(hamming_dist(bits, bits, 0), 0);
}

int test_hamming_dist_cryptopals(void)
{
	const char s1[] = "this is a test";
	const char s2[] = "wokka wokka!!!";

	return TEST_INT_EQ(hamming_dist((uint8_t *)s1, (uint8_t *)s2, 14), 37);
}

int main(void)
{
	REGISTER_TEST(test_hamming_dist_null);
	REGISTER_TEST(test_hamming_dist_empty);
	REGISTER_TEST(test_hamming_dist_cryptopals);

	return RUN_TESTS();
}

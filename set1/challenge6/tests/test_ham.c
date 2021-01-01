#include <stdio.h>
#include <stdlib.h>

#include "cTest.h"
#include "../ham.c"

/*** hamming_dist_str ***/

int test_hamming_dist_str_null(void)
{
	int status = 0;

	status += TEST_INT_EQ(hamming_dist_str(NULL, NULL), -1);
	status += TEST_INT_EQ(hamming_dist_str("s", NULL), -1);
	status += TEST_INT_EQ(hamming_dist_str(NULL, "s"), -1);

	return status;
}

int test_hamming_dist_str_empty(void)
{
	return TEST_INT_EQ(hamming_dist_str("", ""), 0);
}

int test_hamming_dist_str_cryptopals(void)
{
	const char s1[] = "this is a test";
	const char s2[] = "wokka wokka!!!";

	return TEST_INT_EQ(hamming_dist_str(s1, s2), 37);
}

int main(void)
{
	REGISTER_TEST(test_hamming_dist_str_null);
	REGISTER_TEST(test_hamming_dist_str_empty);
	REGISTER_TEST(test_hamming_dist_str_cryptopals);

	return RUN_TESTS();
}

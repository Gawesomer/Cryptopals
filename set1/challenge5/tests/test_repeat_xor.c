#include <stdio.h>
#include <stdlib.h>

#include "cTest.h"
#include "../repeat_xor.c"

/*** xor_repeating ***/

int test_xor_repeating_null(void)
{
	int status = 0;
	char s[] = "something";

	status += TEST_STR_EQ(xor_repeating(NULL, NULL), NULL);
	status += TEST_STR_EQ(xor_repeating(s, NULL), NULL);
	status += TEST_STR_EQ(xor_repeating(NULL, s), NULL);

	return status;
}

int test_xor_repeating_single_input_byte(void)
{
	int status;
	char plain[] = "B";
	char key[] = "I";
	char *actual;
	char expected[] = {0x0B, 0x00};

	actual = xor_repeating(plain, key);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int test_xor_repeating_multiple_input_bytes_single_key_byte(void)
{
	int status;
	char plain[] = "Burn";
	char key[] = "I";
	char *actual;
	char expected[] = {0x0B, 0x3C, 0x3B, 0x27, 0x00};

	actual = xor_repeating(plain, key);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int test_xor_repeating_multiple_input_bytes_multiple_key_bytes(void)
{
	int status;
	char bits[] = "Burning";
	char key[] = "ICE";
	char *actual;
	char expected[] = {0x0b, 0x36, 0x37, 0x27, 0x2a, 0x2b, 0x2e, 0x00};

	actual = xor_repeating(bits, key);

	status = TEST_STR_EQ(expected, actual);

	free(actual);

	return status;
}

int main(void)
{
	REGISTER_TEST(test_xor_repeating_null);
	REGISTER_TEST(test_xor_repeating_single_input_byte);
	REGISTER_TEST(test_xor_repeating_multiple_input_bytes_single_key_byte);
	REGISTER_TEST(test_xor_repeating_multiple_input_bytes_multiple_key_bytes);

	return RUN_TESTS();
}

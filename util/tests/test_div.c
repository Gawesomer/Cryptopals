#include <stdio.h>
#include <stdlib.h>

#include "cTest.h"
#include "../div.c"

/*** round_up_div ***/

int test_round_up_div_both_zero(void)
{
	return TEST_INT_EQ(round_up_div(0, 0), 0);
}

int test_round_up_div_zero_numerator(void)
{
	return TEST_INT_EQ(round_up_div(0, 1), 0);
}

int test_round_up_div_zero_denominator(void)
{
	return TEST_INT_EQ(round_up_div(1, 0), 0);
}

int test_round_up_div_zero_remainder(void)
{
	return TEST_INT_EQ(round_up_div(256, 128), 2);
}

int test_round_up_div_nonzero_remainder(void)
{
	return TEST_INT_EQ(round_up_div(3, 2), 2);
}

int test_round_up_div_negative_numerator(void)
{
	return TEST_INT_EQ(round_up_div(-3, 2), -1);
}

int test_round_up_div_negative_denominator(void)
{
	return TEST_INT_EQ(round_up_div(3, -2), -1);
}

int test_round_up_div_both_negative(void)
{
	return TEST_INT_EQ(round_up_div(-3, -2), 2);
}

int main(void)
{
	REGISTER_TEST(test_round_up_div_both_zero);
	REGISTER_TEST(test_round_up_div_zero_numerator);
	REGISTER_TEST(test_round_up_div_zero_denominator);
	REGISTER_TEST(test_round_up_div_zero_remainder);
	REGISTER_TEST(test_round_up_div_nonzero_remainder);
	REGISTER_TEST(test_round_up_div_negative_numerator);
	REGISTER_TEST(test_round_up_div_negative_denominator);
	REGISTER_TEST(test_round_up_div_both_negative);

	return RUN_TESTS();
}

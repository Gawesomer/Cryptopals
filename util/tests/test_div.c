#include <stdio.h>
#include <stdlib.h>

#include "cassert.h"
#include "../div.c"

/*** round_up_div ***/

void test_round_up_div_both_zero(void)
{
	printf("%s\n", __func__);

	TEST_INT_EQ(round_up_div(0, 0), 0);
}

void test_round_up_div_zero_numerator(void)
{
	printf("%s\n", __func__);

	TEST_INT_EQ(round_up_div(0, 1), 0);
}

void test_round_up_div_zero_denominator(void)
{
	printf("%s\n", __func__);

	TEST_INT_EQ(round_up_div(1, 0), 0);
}

void test_round_up_div_zero_remainder(void)
{
	printf("%s\n", __func__);

	TEST_INT_EQ(round_up_div(256, 128), 2);
}

void test_round_up_div_nonzero_remainder(void)
{
	printf("%s\n", __func__);

	TEST_INT_EQ(round_up_div(3, 2), 2);
}

void test_round_up_div_negative_numerator(void)
{
	printf("%s\n", __func__);

	TEST_INT_EQ(round_up_div(-3, 2), -1);
}

void test_round_up_div_negative_denominator(void)
{
	printf("%s\n", __func__);

	TEST_INT_EQ(round_up_div(3, -2), -1);
}

void test_round_up_div_both_negative(void)
{
	printf("%s\n", __func__);

	TEST_INT_EQ(round_up_div(-3, -2), 2);
}

int main(void)
{
	printf("--- %s ---\n", __FILE__);

	test_round_up_div_both_zero();
	test_round_up_div_zero_numerator();
	test_round_up_div_zero_denominator();
	test_round_up_div_zero_remainder();
	test_round_up_div_nonzero_remainder();
	test_round_up_div_negative_numerator();
	test_round_up_div_negative_denominator();
	test_round_up_div_both_negative();

	printf("----------------------------------------------------------\n");
	printf("\nOK\n");

	return EXIT_SUCCESS;
}

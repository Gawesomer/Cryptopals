#include <stdio.h>
#include <stdlib.h>

#include "cTest.h"
#include "../break_repeatxor.c"

/*** get_block ***/

int test_get_block_null(void)
{
	return TEST_BYTE_ARR_EQ(get_block(NULL, 0, 0, 0), NULL, 0);
}

int main(void)
{
	REGISTER_TEST(test_get_block_null);

	return RUN_TESTS();
}

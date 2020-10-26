#include "cassert.h"

void assert_bytes_eq(size_t expectedlen, const uint8_t *expected, const uint8_t *actual)
{
	int i;
	for (i = 0; i < expectedlen; ++i)
		assert(actual[i] == expected[i]);
}


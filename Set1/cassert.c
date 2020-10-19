#include <stdlib.h>
#include <assert.h>

void assert_bytes_eq(size_t expectedlen, uint8_t *expected, uint8_t *actual)
{
	int i;
	for (i = 0; i < expectedlen; ++i)
		assert(actual[i] == expected[i]);
}


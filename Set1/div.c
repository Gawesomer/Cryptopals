#include <stdlib.h>

/* Returns integer division a/b rounded up. Returns 0 if b is 0 */
size_t round_up_div(size_t a, size_t b)
{
	if (a == 0 || b == 0)
		return 0;
	return ((a-1)/b)+1;
}

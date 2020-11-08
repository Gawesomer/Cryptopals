#include "div.h"

/* Returns integer division a/b rounded up. Returns 0 if b is 0 */
int round_up_div(int a, int b)
{
	if (a == 0 || b == 0)
		return 0;
	if (b < 0) {
		a *= -1;
		b *= -1;
	}
	return ((a-1)/b)+1;
}

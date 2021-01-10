#include <stdlib.h>
#include <string.h>

#include "hex.h"
#include "xor.h"

/* XOR two equal length binary arrays
 * params:
 * 	- a: binary array (will be updated)
 * 	- b: binary array (unchanged)
 * 	- size: size of `a` and `b`
 * returns:
 * 	nothing
 * side-effect:
 * 	`a` has been updated to contain the result of `a` XORed with `b`
 */
void xor_binary(uint8_t *a, const uint8_t *b, size_t size)
{
	int i;

	if (!a || !b || size == 0)
		return;

	for (i = 0; (size_t)i < size; ++i)
		a[i] ^= b[i];
}

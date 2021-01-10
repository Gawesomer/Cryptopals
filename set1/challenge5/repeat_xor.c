#include <stdlib.h>
#include <string.h>

#include "arr.h"
#include "xor.h"


/* XOR binary array with repeating key
 * params:
 * 	- bits: binary array
 * 	- bits_size: size of `bits`
 * 	- key: binary array
 *	- key_size: size of `key`
 * returns:
 * 	nothing
 * side-effect:
 * 	`bits` has been updated to contain the result of `bits` XORed with
 * 	`key` by cycling through the key
 */
void xor_repeating(uint8_t *bits, size_t bits_size, const uint8_t *key, size_t key_size)
{
	uint8_t *blk;
	size_t res_size;
	int i;

	if (!bits || bits_size == 0 || !key || key_size == 0)
		return;

	i = 0;
	while ((blk = slice(bits, bits_size, sizeof(uint8_t), key_size, i, &res_size)) != NULL) {
		xor_binary(blk, key, res_size);
		i++;
	}
}

#include <stdint.h>

#include "ham.h"


/* Compute hamming distance between two bytes
 * params:
 * 	b1: byte
 * 	b2: byte
 * returns:
 * 	number of differing bits between b1 and b2
 */
int hamming_dist_byte(uint8_t b1, uint8_t b2)
{
	int res = 0;

	while (b1 || b2) {
		if ((b1&1) != (b2&1))
			res += 1;
		b1 >>= 1;
		b2 >>= 1;
	}

	return res;
}

/* Compute Hamming Distance between two binary arrays of equal size
 * params:
 * 	arr1: binary array
 * 	arr2: binary array
 * 	size: size of arrays
 * returns:
 * 	Number of differing bits between `arr1` and `arr2`
 * 	-1 if either `arr1` or `arr2` is NULL
 */
int hamming_dist(const uint8_t *arr1, const uint8_t *arr2, size_t size)
{
	int res;
	int i;

	if (!arr1 || !arr2)
		return -1;

	res = 0;
	for (i = 0; (size_t)i < size; i++)
		res += hamming_dist_byte(arr1[i], arr2[i]);

	return res;
}

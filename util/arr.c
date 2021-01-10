#include <stdlib.h>

#include "arr.h"


/* Slice a block from an array
 * params:
 * 	arr: array
 * 	arr_size: size of `arr` in units of `data_size`
 * 	data_size: size of data in `arr`
 * 	blk_size: number of elements in a block
 * 	blk_num: index of block to acquire (0-indexed)
 * 	res_size: pointer to allocated size_t variable, into which size of
 * 		  retreived block will be stored
 * returns:
 * 	pointer to start of block
 * 	or NULL if invalid request
 * side-effect:
 * 	`res_size` contains size of retreived block,
 * 	usually equal to `blk_size` but may be smaller if `arr` too small
 * e.g.
 * 	arr -> [1, 2, 3, 4, 5]
 * 	slice(arr, 5, sizeof(int), 2, 1) -> [3, 4]
 * 	res_size -> 2
 */
void *slice(void *arr, size_t arr_size, size_t data_size, size_t blk_size, int blk_num, size_t *res_size)
{
	int index;
	char *res = arr;

	if (!arr || arr_size == 0 || data_size == 0 || blk_size == 0 || blk_num < 0 || !res_size) {
		*res_size = 0;
		return NULL;
	}

	if (blk_size*blk_num >= arr_size) {
		*res_size = 0;
		return NULL;
	}

	*res_size = arr_size - blk_size*blk_num;
	if (*res_size > blk_size)
		*res_size = blk_size;

	index = data_size * blk_size * blk_num;

	return res+index;
}


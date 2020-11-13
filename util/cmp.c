#include "cmp.h"

/* Compare two integers
 * params:
 * 	- pa: integer pointer
 * 	- pb: integer pointer
 * returns:
 * 	integer greater than, equal to, or less than 0, accordingly as the
 * 	integer pointed to by `pa` is greater than, equal to, or less than the
 * 	integer pointed to by `pb`
 * notes:
 * 	a NULL-pointer will be considered as the smallest element
 */
int intcmp(const void *pa, const void *pb)
{
	const int *a = (int *)pa;
	const int *b = (int *)pb;

	if (!a && !b)
		return 0;
	else if (!a)
		return -1;
	else if (!b)
		return 1;

	if (*a == *b)
		return 0;
	if (*a < *b)
		return -1;
	return 1;
}

/* Compare two arrays
 * params:
 * 	- a_arr: array
 * 	- b_arr: array
 * 	- nel: number of elements in `a_arr` and `b_arr`
 * 	- width: size of an element of the given arrays
 * 	- compare: comparison function for the type of elements in the arrays
 * returns:
 * 	0 if all elements of `a_arr` and `b_arr` are equal, non-zero otherwise
 * notes:
 * 	assumes that both `a_arr` and `b_arr` are of size `nel`;
 * 	in the case where one is shorter, it will cause a read out of bounds,
 * 	in the case where one is longer, it will fail to notice it, possibly
 * 	resulting in false positives
 */
int arrcmp(const void *a_arr, const void *b_arr, size_t nel, size_t width, \
		int (*compare)(const void *, const void *))
{
	char *pa, *pb;
	int i;

	if (!a_arr && !b_arr)
		return 0;
	else if (!a_arr || !b_arr)
		return 1;

	pa = (char *)a_arr;
	pb = (char *)b_arr;
	i = 0;
	while ((size_t)i < nel) {
		if ((*compare)((void *)pa, (void *)pb) != 0)
			return 1;
		pa += width;
		pb += width;
		i++;
	}

	return 0;
}

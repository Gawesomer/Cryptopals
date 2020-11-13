#include "cmp.h"

/* Checks that pointers given are not NULL
 * params:
 * 	- pa: void pointer
 * 	- pb: void pointer
 * returns:
 * 	0 if neither `pa` nor `pb` are NULL,
 * 	1 if both `pa` and `pb` are NULL,
 * 	-1 if only `pa` is NULL,
 * 	2 if only `pb` is NULL
 * notes:
 * 	intended to remove code duplication from comparator functions.
 * 	should be used as follows at the start of a comparator function in
 * 	order to check for NULL-pointers:
 * 		int c;
 * 		if ((c = check_null(pa, pb)) != 0)
 * 			return c-1;
 */
int check_null(const void *pa, const void *pb)
{
	if (!pa && !pb)
		return 1;
	else if (!pa)
		return -1;
	else if (!pb)
		return 2;
	return 0;
}

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
	int c;
	const int *a;
	const int *b;

	if ((c = check_null(pa, pb)) != 0)
		return c-1;

	a = (int *)pa;
	b = (int *)pb;
	if (*a == *b)
		return 0;
	if (*a < *b)
		return -1;
	return 1;
}

/* Compare two bytes
 * params:
 * 	- pa: uint8_t pointer
 * 	- pb: uint8_t pointer
 * returns:
 * 	integer greater than, equal to, or less than 0, accordingly as the
 * 	byte pointed to by `pa` is greater than, equal to, or less than the
 * 	byte pointed to by `pb`
 * notes:
 * 	a NULL-pointer will be considered as the smallest element
 */
int bytecmp(const void *pa, const void *pb)
{
	int c;
	const uint8_t *a;
	const uint8_t *b;

	if ((c = check_null(pa, pb)) != 0)
		return c-1;

	a = (uint8_t *)pa;
	b = (uint8_t *)pb;
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
	int i, c;

	if ((c = check_null(a_arr, b_arr)) != 0)
		return c-1;

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

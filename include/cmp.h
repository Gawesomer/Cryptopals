#ifndef _CMP_H_
#define _CMP_H_

int intcmp(const void *pa, const void *pb);

int arrcmp(const void *a_arr, const void *b_arr, size_t nel, size_t width, \
		int (*compare)(const void *, const void *));

#endif

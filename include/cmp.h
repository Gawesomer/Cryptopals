#ifndef _CMP_H_
#define _CMP_H_

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int intcmp(const void *pa, const void *pb);

int bytecmp(const void *pa, const void *pb);

int float_eq(float a, float b, float eps);

int arrcmp(const void *a_arr, const void *b_arr, size_t nel, size_t width, \
		int (*compare)(const void *, const void *));

#endif

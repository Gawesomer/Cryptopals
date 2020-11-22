#ifndef _DISPL_H_
#define _DISPL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void int_displ(FILE *stream, const void *pe);

void byte_displ(FILE *stream, const void *pe);

void float_displ(FILE *stream, const void *pe);

void arr_displ(FILE *stream, const void *arr, size_t nel, size_t width,
		void (*display)(FILE *, const void *));

#endif

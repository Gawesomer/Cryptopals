#ifndef _XOR_H_
#define _XOR_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hex.h"

uint8_t *xor_binarrays(const uint8_t *a, const uint8_t *b, size_t size);

char *xor_hexstrs(const char *a, const char *b);

#endif

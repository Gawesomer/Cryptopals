#ifndef _CASSERT_H_
#define _CASSERT_H_

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

void assert_bytes_eq(size_t expectedlen, const uint8_t *expected, const uint8_t *actual);

#endif

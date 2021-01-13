#ifndef _BREAK_REPEATXOR_H_
#define _BREAK_REPEATXOR_H_

#include <stdint.h>
#include <stdlib.h>

int find_keysize(uint8_t *encrypted, size_t size);

uint8_t *decrypt_repeatxor(uint8_t *bits, size_t bits_size, int key_size);

#endif

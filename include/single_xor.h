#ifndef _SINGLE_XOR_H_
#define _SINGLE_XOR_H_

#include <stdint.h>

void xor_singlebyte(uint8_t *bits, size_t size, uint8_t byte);

uint8_t decrypt_singlebytexor(uint8_t *bits, size_t size, const int lang_freq[27]);

#endif

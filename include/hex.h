#ifndef _HEX_H_
#define _HEX_H_

#include <stdint.h>


size_t b2fromhex_size(const char *hexstr);

uint8_t *hex_decode(const char *hexstr);

size_t hexfromb2_size(size_t numbytes);

char *hex_encode(const uint8_t *bits, size_t numbytes);

char *hextoascii(const char *hexstr);

char *asciitohex(const char *ascii);

#endif

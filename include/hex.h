#ifndef _HEX_H_
#define _HEX_H_

#include <stdint.h>


size_t hex_bytesize(size_t hexlen);

uint8_t *hex_decode(const char *hexstr);

char *hex_encode(const uint8_t *bits, size_t numbytes);

char *hextoascii(const char *hexstr);

char *asciitohex(const char *ascii);

#endif

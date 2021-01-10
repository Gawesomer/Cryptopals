#ifndef _BASE64_H_
#define _BASE64_H_

#include <stdint.h>

size_t b64fromb2_size(size_t numbytes);

char *hextobase64(const char *hexstr);

size_t b2fromb64_size(const char *base64);

char *base64_encode(const uint8_t *bits, size_t numbytes);

uint8_t *base64_decode(const char *base64);

#endif

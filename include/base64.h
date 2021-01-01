#ifndef _BASE64_H_
#define _BASE64_H_

#include <stdint.h>

uint8_t *base64tobinary(const uint8_t *bits, size_t numbytes);

char *hextobase64(const char *hexstr);

#endif

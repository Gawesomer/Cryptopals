#ifndef _BASE64_H_
#define _BASE64_H_

char *hextobase64(const char *hexstr);

char *base64_encode(const uint8_t *bits, size_t numbytes);

#endif

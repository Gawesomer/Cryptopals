#ifndef _HEX_H_
#define _HEX_H_

size_t binaryfromhex_size(size_t hexlen);

uint8_t *hextobinary(const char *hexstr);

char *binarytohex(const uint8_t *bits, size_t numbytes);

#endif

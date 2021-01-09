#ifndef _FREQ_H_
#define _FREQ_H_

#include <stdint.h>

extern const int ENGLISH_LETTER_FREQ[27];

int freq_score(const uint8_t *bits, size_t size, const int lang_freq[27]);

#endif

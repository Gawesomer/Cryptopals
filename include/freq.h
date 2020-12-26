#ifndef _FREQ_H_
#define _FREQ_H_

#include <stdint.h>

extern const float ENGLISH_LETTER_FREQ[26];

float *freqmap_from_binary(const uint8_t *bits, size_t size);

float freq_score(const float actual_freq[26], const float lang_freq[26]);

#endif

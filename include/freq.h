#ifndef _FREQ_H_
#define _FREQ_H_

#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <math.h>

/* English letter frequency based on a sample of 40,000 words obtained from:
 * http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
 */
const float ENGLISH_LETTER_FREQ[26] = {
	8.12f,	// A
	1.49f,	// B
	2.71f,	// C
	4.32f,	// D
	12.02f,	// E
	2.30f,	// F
	2.03f,	// G
	5.92f,	// H
	7.31f,	// I
	0.10f,	// J
	0.69f,	// K
	3.98f,	// L
	2.61f,	// M
	6.95f,	// N
	7.68f,	// O
	1.82f,	// P
	0.11f,	// Q
	6.02f,	// R
	6.28f,	// S
	9.10f,	// T
	2.88f,	// U
	1.11f,	// V
	2.09f,	// W
	0.17f,	// X
	2.11f,	// Y
	0.07f,	// Z
};

float *freqmap_from_binary(const uint8_t *bits, size_t size);

float freq_score(const float actual_freq[26], const float lang_freq[26]);

#endif

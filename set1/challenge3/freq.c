#include <stdint.h>
#include <stdlib.h>

#include "freq.h"


/* English letter frequency based on a sample of 40,000 words obtained from:
 * http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
 * Normalized to integers (Ratio: 1/10,000)
 * Also contains a frequency for the space character
 */
const int ENGLISH_LETTER_FREQ[27] = {
	812,	// A
	149,	// B
	271,	// C
	432,	// D
	1202,	// E
	230,	// F
	203,	// G
	592,	// H
	731,	// I
	10,	// J
	69,	// K
	398,	// L
	261,	// M
	695,	// N
	768,	// O
	182,	// P
	11,	// Q
	602,	// R
	628,	// S
	910,	// T
	288,	// U
	111,	// V
	209,	// W
	17,	// X
	211,	// Y
	7,	// Z
	1800,	// Space
};

/* Compute frequency score of `bits` relative to `lang_freq`
 * params:
 * 	- bits: binary array
 * 	- lang_freq: language frequency map of size 27 to which `bits`
 * 		     should be compared to in computing it's score
 * returns:
 * 	frequency score
 * notes:
 * 	a higher frequency score indicates a closer resemblence to the given
 * 	language frequency
 */
int freq_score(const uint8_t *bits, size_t size, const int lang_freq[27])
{
	int score;
	int i;

	if (!bits || size == 0 || !lang_freq)
		return 0;

	score = 0;
	for (i = 0; (size_t)i < size; i++)
		if ('A' <= bits[i] && bits[i] <= 'Z')
			score += lang_freq[bits[i]-'A'];
		else if ('a' <= bits[i] && bits[i] <= 'z')
			score += lang_freq[bits[i]-'a'];
		else if (bits[i] == ' ')
			score += lang_freq[26];

	return score;
}

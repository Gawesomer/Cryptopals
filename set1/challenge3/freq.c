#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "freq.h"

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

/* Compute character occurence of binary array
 * params:
 * 	- bits: binary array
 * 	- size: size of `bits`
 * returns:
 * 	int array of size 26 with values at index `i` set to the number of
 * 	occurences of the `i`th letter in the latin alphabet, in `bits`
 * 	or NULL if `bits` is NULL
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
int *occmap_from_binary(const uint8_t *bits, size_t size)
{
	int *occmap;
	int i, c;

	if (!bits)
		return NULL;

	occmap = calloc(26, sizeof(int));

	for (i = 0; (size_t)i < size; ++i) {
		if ('A' <= bits[i] && bits[i] <= 'Z')
			c = bits[i] - 'A';
		else if ('a' <= bits[i] && bits[i] <= 'z')
			c = bits[i] - 'a';
		else
			continue;
		occmap[c]++;
	}

	return occmap;
}

/* Compute frequency map for given occurence map
 * params:
 * 	- occmap: occupation map for latin alphabet
 * returns:
 * 	float array of size 26 with values at index `i` set to the frequency
 * 	of the `i`th letter in the latin alphabet
 * 	or NULL if `occmap` is NULL or contains negative elements,
 */
float *occmap_to_freqmap(const int occmap[26])
{
	float *freqmap;
	int numletters;
	int i;

	if (!occmap)
		return NULL;

	numletters = 0;
	for (i = 0; i < 26; ++i) {
		if (occmap[i] < 0)
			return NULL;
		numletters += occmap[i];
	}

	freqmap = calloc(26, sizeof(float));

	if (numletters == 0)
		return freqmap;

	for (i = 0; i < 26; ++i)
		freqmap[i] = ((float)occmap[i])/numletters*100.00f;

	return freqmap;
}

/* Compute character frequency of binary array
 * params:
 * 	- bits: binary array
 * 	- size: size of `bits`
 * returns:
 * 	float array of size 26 with values at index `i` set to the frequency
 * 	of the `i`th letter in the latin alphabet, in `bits`
 * 	or NULL if `bits` is NULL
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
float *freqmap_from_binary(const uint8_t *bits, size_t size)
{
	int *occmap;
	float *freqmap;

	occmap = occmap_from_binary(bits, size);
	freqmap = occmap_to_freqmap(occmap);

	if (occmap)
		free(occmap);

	return freqmap;
}

/* Compute frequency score of `actual_freq` relative to `lang_freq`
 * params:
 * 	- actual_freq: frequency map of size 26 for which score should be
 * 		       computed
 * 	- lang_freq: language frequency map of size 26 to which `actual_freq`
 * 		     should be compared to in computing it's score
 * returns:
 * 	float frequency score computed by summing the difference in frequency
 * 	of the letters in the latin alphabet between `actual_freq` and
 * 	`lang_freq`
 * 	or FLT_MAX if either `actual_freq` or `lang_freq` is NULL
 * notes:
 * 	a lower frequency score indicates a closer resemblence to the given
 * 	language frequency
 */
float freq_score(const float actual_freq[26], const float lang_freq[26])
{
	float score = 0.00f;
	int i;

	if (!actual_freq || !lang_freq)
		return FLT_MAX;

	for (i = 0; i < 26; ++i)
		score += fabs(lang_freq[i] - actual_freq[i]);

	return score;
}

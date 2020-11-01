#include "freq.h"

/* Compute character occurence of binary array
 * params:
 * 	- bits: binary array
 * 	- size: size of `bits`
 * 	- numletters: return buffer will hold number of letters found in `bits`
 * returns:
 * 	int array of size 26 with values at index `i` set to the number of
 * 	occurences of the `i`th letter in the latin alphabet, in `bits`
 * 	or NULL if `bits` or `numletters` is NULL
 * 	`numletters` will have been set to the number of latin letters found in
 * 	`bits`
 * 	returned array has been dynamically allocated and should be freed by
 * 	user
 */
int *occmap_from_binary(const uint8_t *bits, size_t size, int *numletters)
{
	int *occmap;
	int i, c;

	if (!bits || !numletters)
		return NULL;

	occmap = calloc(26, sizeof(int));
	(*numletters) = 0;

	for (i = 0; i < size; ++i) {
		if ('A' <= bits[i] && bits[i] <= 'Z')
			c = bits[i] - 'A';
		else if ('a' <= bits[i] && bits[i] <= 'z')
			c = bits[i] - 'a';
		else
			continue;
		occmap[c]++;
		(*numletters)++;
	}

	return occmap;
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
	return NULL;
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
 * 	or NULL if either `actual_freq` or `lang_freq` is NULL
 * notes:
 * 	a lower frequency score indicates a closer resemblence to the given
 * 	language frequency
 */
float freq_score(const float actual_freq[26], const float lang_freq[26])
{
	return 0;
}
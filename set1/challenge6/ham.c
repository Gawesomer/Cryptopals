/* Compute hamming distance between two bytes
 * params:
 * 	b1: byte
 * 	b2: byte
 * returns:
 * 	number of differing bits between b1 and b2
 */
int hamming_dist_byte(uint8_t b1, uint8_t b2)
{
	int res = 0;

	while (b1 || b2) {
		if ((b1&1) != (b2&1))
			res += 1;
		b1 >>= 1;
		b2 >>= 1;
	}

	return res;
}

/* Compute Hamming Distance between two strings of equal length
 * If strings are not of equal length, only compares them for length of
 * the shortest string.
 * params:
 * 	s1: C-String
 * 	s2: C-String
 * returns:
 * 	Number of differing bits between s1 and s2
 * 	-1 if either s1 or s2 is NULL
 */
int hamming_dist_str(const char *s1, const char *s2)
{
	int res;
	int i;

	if (!s1 || !s2)
		return -1;

	res = 0;
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0') {
		res += hamming_dist_byte(s1[i], s2[i]);
		i += 1;
	}

	return res;
}

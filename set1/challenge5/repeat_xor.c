#include <stdlib.h>
#include <string.h>


/* XOR string with repeating key
 * params:
 * 	- plain: plain text to encrypt
 * 	- key: key to use for encryption
 * returns:
 * 	C-String of same size of `plain` containing the result of XORing every
 * 	byte of `plain` with `key` by cycling through the key
 * 	or NULL if `plain` or `key` is NULL
 * 	returned string has been dynamically allocated and should be freed by
 * 	user
 */
char *xor_repeating(const char *plain, const char *key)
{
	char *res;
	size_t input_size, key_size;
	int i, j;

	if (!plain || !key)
		return NULL;

	input_size = strlen(plain);
	key_size = strlen(key);

	res = calloc(input_size+1, sizeof(char));

	i = 0;
	j = 0;
	while ((size_t)i < input_size) {
		res[i] = plain[i] ^ key[j];
		j = (j+1)%key_size;
		i++;
	}

	return res;
}

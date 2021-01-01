#define MIN_KEYSIZE	2
#define MAX_KEYSIZE	40


/* Return nth block of `blk_size` in `arr` */
uint8_t *get_block(const uint8_t *arr, size_t arr_size, size_t blk_size, int n)
{
	uint8_t *res;
	int i, j;

	if (!arr || n < 0 || blk_size == 0)
		return NULL;

	i = blk_size*n;
	if ((size_t)i >= arr_size || blk_size > arr_size)
		return NULL;

	res = calloc(blk_size, sizeof(uint8_t));

	j = 0;
	do {
		res[j] = arr[i];
		i++;
		j++;
	} while (i%blk_size != 0 && (size_t)i < arr_size);

	return res;
}

/*
int find_keysize(const uint8_t *encrypted, size_t size)
{
	int curr = MIN_KEYSIZE;
	int min_key;
	float min_normalized = FLT_MAX;

	while (curr <= MAX_KEYSIZE && (size_t)curr <= size/2) {

		curr++;
	}

	return min_key;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include "../cassert.c"

#define BUFFSIZE	1024

void test_TEST_INT_EQ_eq(void)
{
	printf("%s\n", __func__);

	assert(TEST_INT_EQ(0, 0) == 0);
	assert(TEST_INT_EQ(7, 7) == 0);
	assert(TEST_INT_EQ(-1, -1) == 0);
	assert(TEST_INT_EQ(INT_MAX, INT_MAX) == 0);
	assert(TEST_INT_EQ(INT_MIN, INT_MIN) == 0);
}

void test_TEST_INT_EQ_eq_w_expr(void)
{
	printf("%s\n", __func__);

	assert(TEST_INT_EQ(-8+10, 2) == 0);
	assert(TEST_INT_EQ(2, -8+10) == 0);
	assert(TEST_INT_EQ(-8+10, -8+10) == 0);
	assert(TEST_INT_EQ(TEST_INT_EQ(7, 7), 0) == 0);
	assert(TEST_INT_EQ(0, TEST_INT_EQ(7, 7)) == 0);
	assert(TEST_INT_EQ(TEST_INT_EQ(4, 4), TEST_INT_EQ(7, 7)) == 0);
}

void test_TEST_INT_EQ_not_eq(void)
{
	printf("%s\n", __func__);

	FILE *devnull, *tmp;

	// Execute with STDOUT redirected to /dev/null
	devnull = fopen("/dev/null", "w");
	tmp = stdout;
	stdout = devnull;

	assert(TEST_INT_EQ(0, 1) != 0);
	assert(TEST_INT_EQ(-1, 1) != 0);
	assert(TEST_INT_EQ(INT_MAX, INT_MIN) != 0);

	stdout = tmp;
	fclose(devnull);
}

void test_TEST_INT_EQ_not_eq_w_expr(void)
{
	printf("%s\n", __func__);

	FILE *devnull, *tmp;

	// Execute with STDOUT redirected to /dev/null
	devnull = fopen("/dev/null", "w");
	tmp = stdout;
	stdout = devnull;

	assert(TEST_INT_EQ(-8+10, 1) != 0);
	assert(TEST_INT_EQ(1, -8+10) != 0);
	assert(TEST_INT_EQ(-8+10, 8-10) != 0);
	assert(TEST_INT_EQ(TEST_INT_EQ(7, 7), 1) != 0);
	assert(TEST_INT_EQ(1, TEST_INT_EQ(7, 7)) != 0);
	assert(TEST_INT_EQ(TEST_INT_EQ(1, 2), TEST_INT_EQ(7, 7)) != 0);

	stdout = tmp;
	fclose(devnull);
}

void test_TEST_INT_EQ_stacktrace(void)
{
	printf("%s\n", __func__);

	char *actualstr;
	char expectedstr[BUFFSIZE];
	FILE *buffer, *tmp;

	/* args:
	 * 	- function name
	 * 	- file name
	 * 	- execution line number (i.e. when macro is called)
	 * 	- first expression passed to macro
	 * 	- second expression passed to macro
	 * 	- integer value of first expression
	 * 	- integer value of second expression
	 */
	snprintf(expectedstr, BUFFSIZE, \
		"==========================================================\n"
		"FAIL: %s\n"
		"----------------------------------------------------------\n"
		"\tFile \"%s\", line %d:\n"
		"\t\tTEST_INT_EQ(%s, %s)\n"
		"\t\t\t%d != %d\n"
		"----------------------------------------------------------\n", \
		__FUNCTION__, __FILE__, __LINE__ + 8, "0", "1", 0, 1);
	actualstr = calloc(BUFFSIZE, sizeof(char));
	buffer = fmemopen(actualstr, BUFFSIZE, "w");

	// Execute with STDOUT redirected to `actualstr`
	tmp = stdout;
	stdout = buffer;

	TEST_INT_EQ(0, 1);

	stdout = tmp;
	fclose(buffer);

	assert(strcmp(actualstr, expectedstr) == 0);

	free(actualstr);
}

void test_TEST_INT_EQ_stacktrace_w_expr(void)
{
	printf("%s\n", __func__);

	char *actualstr;
	char expectedstr[BUFFSIZE];
	FILE *buffer, *tmp;

	snprintf(expectedstr, BUFFSIZE, \
		"==========================================================\n"
		"FAIL: %s\n"
		"----------------------------------------------------------\n"
		"\tFile \"%s\", line %d:\n"
		"\t\tTEST_INT_EQ(%s, %s)\n"
		"\t\t\t%d != %d\n"
		"----------------------------------------------------------\n", \
		__FUNCTION__, __FILE__, __LINE__ + 8, "-8+10", "8-10", 2, -2);
	actualstr = calloc(BUFFSIZE, sizeof(char));
	buffer = fmemopen(actualstr, BUFFSIZE, "w");

	// Execute with STDOUT redirected to `actualstr`
	tmp = stdout;
	stdout = buffer;

	TEST_INT_EQ(-8+10, 8-10);

	stdout = tmp;
	fclose(buffer);

	assert(strcmp(actualstr, expectedstr) == 0);

	free(actualstr);
}

int main(void)
{
	printf("--- %s ---\n", __FILE__);

	test_TEST_INT_EQ_eq();
	test_TEST_INT_EQ_eq_w_expr();
	test_TEST_INT_EQ_not_eq();
	test_TEST_INT_EQ_not_eq_w_expr();
	test_TEST_INT_EQ_stacktrace();
	test_TEST_INT_EQ_stacktrace_w_expr();

	return EXIT_SUCCESS;
}

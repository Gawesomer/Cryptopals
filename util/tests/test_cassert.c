#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include "../cassert.c"

#define BUFFSIZE	1024

/*** TEST_TRUE ***/

void test_TEST_TRUE_true(void)
{
	printf("%s\n", __func__);

	assert(TEST_TRUE(1) == 0);
	assert(TEST_TRUE(INT_MAX) == 0);
	assert(TEST_TRUE(INT_MIN) == 0);
}

void test_TEST_TRUE_true_w_expr(void)
{
	printf("%s\n", __func__);

	assert(TEST_TRUE(3*4 == 12) == 0);
	assert(TEST_TRUE(0 != 1) == 0);
}

void test_TEST_TRUE_false(void)
{
	printf("%s\n", __func__);

	FILE *devnull, *tmp;

	// Execute with STDOUT redirected to /dev/null
	devnull = fopen("/dev/null", "w");
	tmp = stdout;
	stdout = devnull;

	// Note: We will still see `assert`'s stacktrace despite the STDOUT
	// redirection as `assert` prints to STDERR
	assert(TEST_TRUE(0) != 0);

	stdout = tmp;
	fclose(devnull);
}

void test_TEST_TRUE_false_w_expr(void)
{
	printf("%s\n", __func__);

	FILE *devnull, *tmp;

	devnull = fopen("/dev/null", "w");
	tmp = stdout;
	stdout = devnull;

	assert(TEST_TRUE(3*4 == 13) != 0);

	stdout = tmp;
	fclose(devnull);
}

void test_TEST_TRUE_stacktrace(void)
{
	printf("%s\n", __func__);

	char *actualstr;
	char expectedstr[BUFFSIZE];
	FILE *buffer, *tmp;

	/* args:
	 * 	- function name
	 * 	- file name
	 * 	- execution line number (i.e. when macro is called)
	 * 	- expressions passed to macro
	 */
	snprintf(expectedstr, BUFFSIZE, \
		"==========================================================\n"
		"FAIL: %s\n"
		"----------------------------------------------------------\n"
		"\tFile \"%s\", line %d:\n"
		"\t\tTEST_TRUE(%s)\n"
		"\t\t\t`%s` not true\n"
		"----------------------------------------------------------\n", \
		__FUNCTION__, __FILE__, __LINE__ + 8, "0", "0");
	actualstr = calloc(BUFFSIZE, sizeof(char));
	buffer = fmemopen(actualstr, BUFFSIZE, "w");

	// Execute with STDOUT redirected to `actualstr`
	tmp = stdout;
	stdout = buffer;

	TEST_TRUE(0);

	stdout = tmp;
	fclose(buffer);

	assert(strcmp(actualstr, expectedstr) == 0);

	free(actualstr);
}

void test_TEST_TRUE_stacktrace_w_expr(void)
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
		"\t\tTEST_TRUE(%s)\n"
		"\t\t\t`%s` not true\n"
		"----------------------------------------------------------\n", \
		__FUNCTION__, __FILE__, __LINE__ + 7, "0 == 1", "0 == 1");
	actualstr = calloc(BUFFSIZE, sizeof(char));
	buffer = fmemopen(actualstr, BUFFSIZE, "w");

	tmp = stdout;
	stdout = buffer;

	TEST_TRUE(0 == 1);

	stdout = tmp;
	fclose(buffer);

	assert(strcmp(actualstr, expectedstr) == 0);

	free(actualstr);
}


/*** TEST_INT_EQ ***/

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

	snprintf(expectedstr, BUFFSIZE, \
		"==========================================================\n"
		"FAIL: %s\n"
		"----------------------------------------------------------\n"
		"\tFile \"%s\", line %d:\n"
		"\t\tTEST_INT_EQ(%s, %s)\n"
		"\t\t\t%d != %d\n"
		"----------------------------------------------------------\n", \
		__FUNCTION__, __FILE__, __LINE__ + 7, "0", "1", 0, 1);
	actualstr = calloc(BUFFSIZE, sizeof(char));
	buffer = fmemopen(actualstr, BUFFSIZE, "w");

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
		__FUNCTION__, __FILE__, __LINE__ + 7, "-8+10", "8-10", 2, -2);
	actualstr = calloc(BUFFSIZE, sizeof(char));
	buffer = fmemopen(actualstr, BUFFSIZE, "w");

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

	test_TEST_TRUE_true();
	test_TEST_TRUE_true_w_expr();
	test_TEST_TRUE_false();
	test_TEST_TRUE_false_w_expr();
	test_TEST_TRUE_stacktrace();
	test_TEST_TRUE_stacktrace_w_expr();

	test_TEST_INT_EQ_eq();
	test_TEST_INT_EQ_eq_w_expr();
	test_TEST_INT_EQ_not_eq();
	test_TEST_INT_EQ_not_eq_w_expr();
	test_TEST_INT_EQ_stacktrace();
	test_TEST_INT_EQ_stacktrace_w_expr();

	return EXIT_SUCCESS;
}

#include "main.h"

/**
 * get_flags - Eumerates active flags
 * @format: Format string in which to print the arguments
 * @a: Take parameter
 * Return: Flags (success)
 */
int get_flags(const char *format, int *a)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int i, curr_a;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_a = *a + 1; format[curr_a] != '\0'; curr_a++)
	{
		for (i = 0; FLAGS_CH[i] != '\0'; i++)
			if (format[curr_a] == FLAGS_CH[i])
			{
				flags |= FLAGS_ARR[i];
				break;
			}

		if (FLAGS_CH[i] == 0)
			break;
	}

	*a = curr_a - 1;

	return (flags);
}


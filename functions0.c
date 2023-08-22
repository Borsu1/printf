#include "main.h"

/* PRINT CHAR */
/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags: Computes active flags
 * @width: Width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars to be printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/* PRINT A STRING */
/**
 * print_string - Prints a string
 * @buffer: Buffer array to handle print
 * @types: List the types of arguments
 * @width: Width
 * @precision: Precision specified
 * @size: Size specified
 * @flags: Flags calculated
 *
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, j;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/* PRINT PERCENT SIGN */
/**
 * print_percent - Prints a percent sign
 * @flags: Enumerate active flags
 * @buffer: Buffer array to handle print
 * @types: List of arguments
 * @width: Width
 * @size: Size specifier
 * @precision: Precision specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* PRINT INT */
/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Enumerates active flags
 * @width: Width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_number(is_negative, j, buffer, flags, width, precision, size));
}

/* PRINT BINARY */
/**
 * print_binary - Prints an unsigned number
 * @buffer: Buffer array to handle print
 * @flags:  Enumerates active flags
 * @width: Width
 * @precision: Precision specifier
 * @types: List of the arguments
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int e, f, g, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	e = va_arg(types, unsigned int);
	f = 2147483648; /* (2 ^ 31) */
	a[0] = e / f;
	for (g = 1; g < 32; g++)
	{
		f /= 2;
		a[g] = (e / f) % 2;
	}
	for (g = 0, sum = 0, count = 0; g < 32; g++)
	{
		sum += a[g];
		if (sum || g == 31)
		{
			char m = '0' + a[g];

			write(1, &m, 1);
			count++;
		}
	}
	return (count);
}


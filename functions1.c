#include "main.h"

/* PRINT UNSIGNED NUMBER */
/**
 * print_unsigned - Prints an unsigned number
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @types: List of the arguments
 * @size: Size specifier
 * @width: Width
 * @precision: Precision specifier
 * Return: Number of chars printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int f = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[f--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[f--] = (num % 10) + '0';
		num /= 10;
	}

	f++;

	return (write_unsgnd(0, f, buffer, flags, width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN OCTAL */
/**
 * print_octal - Prints the an unsigned number in octal notation
 * @buffer: Buffer array to handle print
 * @types: List of the arguments
 * @flags: Enumerates active flags
 * @size: Size specifier
 * @precision: Precision specifier
 * @width: Width
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[a--] = '0';

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN HEXADECIMAL */
/**
 * print_hexadecimal - Prints the an unsigned number in hexadecimal notation
 * @types: List of the arguments
 * @buffer: Buffer array to handle print
 * @width: Width
 * @flags:  Enumerates active flags
 * @size: Size specifier
 * @precision: Precision specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL */
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @flags: Enumerates active flags
 * @types: List of the arguments
 * @buffer: Buffer array to handle print
 * @precision: Precision specifier
 * @width: Width
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/* PRINT HEXX NUM IN LOWER OR UPPER */
/**
 * print_hexa - Prints the hexadecimal number in lower or upper
 * @buffer: Buffer array to handle print
 * @types: List of the arguments
 * @map_to: Array of the values to map the number to
 * @flag_ch: Enumerates active flags
 * @flags:  Enumerates active flags
 * @precision: Precision specifier
 * @size: Size specifier
 * @width: Width
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}


#include "main.h"
#include <limits.h>

/**
 * base_format - print number
 * @number: number to print
 * @base: base to convert
 * @uppercase: to uppercase
 * Return: number of caracter
 */
int base_format(unsigned int number, int base, int uppercase)
{
	int len = 0;
	char digit;

	if (number / base)
		len += base_format(number / base, base, uppercase);

	digit = number % base;
	if (digit > 9)
		digit = (uppercase ? 'A' : 'a') + digit - 10;
	else
		digit += '0';

	cprintf(&digit, 1);
	len++;

	return (len);
}

/**
 * base_u - format to base 10
 * @count: current character printer to screen
 * @args: arguments list
 * Return: count
 */
int base_u(int *count, va_list args)
{
	*count += base_format(va_arg(args, unsigned int), 10, 0);
	return (*count);
}

/**
 * base_o - format to base 8
 * @count: current character printer to screen
 * @args: arguments list
 * Return: count
 */
int base_o(int *count, va_list args)
{
	*count += base_format(va_arg(args, unsigned int), 8, 0);
	return (*count);
}

/**
 * base_x - format to base 16 lowercase
 * @count: current character printer to screen
 * @args: arguments list
 * Return: count
 */
int base_x(int *count, va_list args)
{
	*count += base_format(va_arg(args, unsigned int), 16, 0);
	return (*count);
}

/**
 * base_X - format to base 16 uppercase
 * @count: current character printer to screen
 * @args: arguments list
 * Return: count
 */
int base_X(int *count, va_list args)
{
	*count += base_format(va_arg(args, unsigned int), 16, 1);
	return (*count);
}

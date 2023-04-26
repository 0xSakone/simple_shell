#include "main.h"

/**
 * character_format - character formater
 * @count: character count
 * @args: arugment list
 * Return: number of character
 */
int character_format(int *count, va_list args)
{
	char c;

	c = va_arg(args, int);
	*count += 1;
	return (cprintf(&c, 1));
}

/**
 * perc_format - percent formater
 * @count: character count
 * @args: arugment list
 * Return: number of character
 */
int perc_format(int *count, __attribute__((unused)) va_list args)
{
	char c = '%';

	*count += 1;
	return (cprintf(&c, 1));
}

#include "main.h"

/**
 * _1bit - printf function simulator
 * @count: text format
 * @c: character
 * Return: number of character
 */
int _1bit(int *count, char c)
{
	*count += 1;
	cprintf(&c, 1);
	return (*count);
}

/**
 * dispatch - printf function simulator
 * @count: counter
 * @args: argument
 * @fm: character
 * Return: formater array
 */
int dispatch(int *count, va_list args, char *fm)
{
	int _dispatcher = 0, i = 0, find = 0;

	func _f[] = {
		{'c', character_format}, {'s', string_format}, {'d', number_format},
		{'i', number_format}, {'b', binary_format}, {'%', perc_format}, {'\0', NULL},
		{'u', base_u}, {'o', base_o}, {'x', base_x}, {'X', base_X},
		{'S', big_string_format}
	};
	while (*fm)
	{
		if (*fm == '%')
		{
			find = 0;
			fm++;
			if (*fm == '0')
				fm++;
			else if (*fm == '\0')
				return (-1);
			for (i = 0; i < (int)(sizeof(_f) / sizeof(func)); i++)
			{
				if (*fm == _f[i].c)
				{
					_dispatcher = _f[i].call(count, args);
					find = 1;
					if (_dispatcher == -1)
						return (-1);
				}
			}
			if (find == 0)
			{
				_1bit(count, '%');
				_1bit(count, *fm);
			}
		}
		else
			_1bit(count, *fm);
		fm++;
	}
	return (*count);
}

/**
 * _printf - printf function simulator
 * @format: text format
 * Return: number of character
 */
int _printf(const char * const format, ...)
{
	char *fm;
	int count = 0;
	va_list args;

	if (!format)
		return (-1);
	va_start(args, format);

	fm = (char *)format;
	count = dispatch(&count, args, fm);
	if (count == -1)
		return (-1);
	va_end(args);
	return (count);
}

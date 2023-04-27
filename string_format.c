#include "main.h"

/**
 * _sch - search if a char is inside a string
 * @s: string to review
 * @c: char to find
 * Return: 1 if success 0 if not
 */
int _sch(char *s, char c)
{
	int cont = 0;

	while (s[cont] != '\0')
	{
		if (s[cont] == c)
		{
			break;
		}
		cont++;
	}
	if (s[cont] == c)
		return (1);
	else
		return (0);
}
/**
 * _strtok - function that cut a string into tokens depending of the delimit
 * @s: string to cut in parts
 * @d: delimiters
 * Return: first partition
 */
char *_strtok(char *s, char *d)
{
	static char *ultimo;
	int i = 0, j = 0;

	if (!s)
		s = ultimo;
	while (s[i] != '\0')
	{
		if (_sch(d, s[i]) == 0 && s[i + 1] == '\0')
			i++;
		else if (_sch(d, s[i]) == 0 && _sch(d, s[i + 1]) == 0)
			i++;
		else if (_sch(d, s[i]) == 0 && _sch(d, s[i + 1]) == 1)
		{
			ultimo = s + i + 1;
			*ultimo = '\0';
			ultimo++;
			s = s + j;
			return (s);
		}
		else if (_sch(d, s[i]) == 1)
		{
			j++;
			i++;
		}
	}
	return (NULL);
}
/**
* _strtok2 - function tokenizaition with ;
* @s: string to cut in parts
* @d: delimiters
* Return: first partition
*/
char *_strtok2(char *s, char *d)
{
	static char *ultimo;
	int i = 0, j = 0;

	if (!s)
		s = ultimo;
	while (s[i] != '\0')
	{
		if (_sch(d, s[i]) == 0 && s[i + 1] == '\0')
			i++;
		else if (_sch(d, s[i]) == 0 && _sch(d, s[i + 1]) == 0)
			i++;
		else if (_sch(d, s[i]) == 0 && _sch(d, s[i + 1]) == 1)
		{
			ultimo = s + i + 1;
			*ultimo = '\0';
			ultimo++;
			s = s + j;
			return (s);
		}
		else if (_sch(d, s[i]) == 1)
		{
			j++;
			i++;
		}
	}
	return (NULL);
}

/**
 * string_format - string text formater
 * @count: current character count
 * @args: arguments
 * Return: number of character
 */
int string_format(int *count, va_list args)
{
	char *s;

	s = va_arg(args, char *);
	if (s == NULL)
		s = "(null)";
	while (*s)
	{
		cprintf(s, 1);
		s++;
		*count += 1;
	}
	return (*count);
}

/**
 * big_string_format - string text formater
 * @count: current character count
 * @args: arguments
 * Return: number of character
 */
int big_string_format(int *count, va_list args)
{
	char *s, hex[2];
	int temp;

	s = va_arg(args, char *);
	if (s == NULL)
		s = "(null)";
	while (*s)
	{
		if (*s > 32 && *s < 126)
		{
			cprintf(s, 1);
			*count += 1;
		}
		else
		{
			cprintf("\\x", 2);
			temp = ((unsigned char)*s) / 16;
			hex[0] = (temp < 10) ? (temp + '0') : (temp - 10 + 'A');
			temp = ((unsigned char)*s) % 16;
			hex[1] = (temp < 10) ? (temp + '0') : (temp - 10 + 'A');
			cprintf(hex, 2);
			*count += 4;
		}
		s++;
	}
	return (*count);
}

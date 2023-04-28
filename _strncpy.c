#include "head.h"
/**
 * _strncpy - copies a string
 * @dest: destination,
 * @src: source.
 * @n: amount of bytes from src.
 * Return: the pointer to dest.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: less than 0 if s1 is less than s2, 0 if they are
 * equal, more than 0 if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _checkExit - compares two strings
 * @s1: first string to compare
 *
 * Return: less than 0 or -1
 */
int _checkExit(char *s1)
{
	if (s1[0] == 'e' && s1[1] == 'x' && s1[2] == 'i'
		&& s1[3] == 't') {
		if (s1[4] == ' ' || s1[4] == '\n')
			return (1);
	}
	return (-1);
}

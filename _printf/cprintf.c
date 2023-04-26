#include "main.h"

/**
 * cprintf - display character to standart output
 * @buf: string buffer
 * @len: lenght of given format text
 * Return: number of caracter;
 */
int cprintf(char *buf, int len)
{
	return (write(1, buf, len));
}

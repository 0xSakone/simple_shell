#ifndef MAIN_HEADER_FILE
#define MAIN_HEADER_FILE

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

/*
 * typedef caller - Type de pointeur de fonction
 * @int: entier en argument
 * @va_list: fonction à appeler
 */
typedef int (*caller)(int*, va_list);

/**
 * struct funct - func type dfd fdkfbd dfjnd
 * @c: charaxcter
 * @call: function to call
 * Description: sdfg dn sdkfjn
 */
typedef struct funct
{
	char c;
	caller call;
} func;

/*
 * charater_Formatter
 */
int character_format(int *count, va_list args);
int perc_format(int *count, va_list args);
/*
 * print character
 */
int cprintf(char *buf, int len);
/*
 * print number
 */
int print_number(int n);
int print_binary(unsigned int number);
int number_format(int *count, va_list args);
int binary_format(int *count, va_list args);
int base_u(int *count, va_list args);
int base_o(int *count, va_list args);
int base_x(int *count, va_list args);
int base_X(int *count, va_list args);
int base_format(unsigned int number, int base, int uppercase);
/*
 * string Formatter
 */
int string_format(int *count, va_list args);
int big_string_format(int *count, va_list args);

int _printf(const char * const format, ...);
int _strlen(char *s);


#endif

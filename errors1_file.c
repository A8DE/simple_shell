#include "shell.h"

/**
 * _erratoi - Function Converts String Integer
 * @st: String Converted
 * Return: Numbers in string O,Or converted number
 *        Or Error -1
 */

int _erratoi(char *st)
{
	int in = 0;
	unsigned long int res = 0;

	if (*st == '+')
	st++;
	for (in = 0;  st[in] != '\0'; in++)
	{
		if (st[in] >= '0' && st[in] <= '9')
		{
			res *= 10;
			res += (st[in] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - Function Prints Error Message
 * @inf:  Parameter Return info struct
 * @est: string containe Specified Error
 * Return: Numbers in string 0, Or converted number
 * Error -1
 */

void print_error(info_t *inf, char *est)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(est);
}

/**
 * print_d - Function Prints Decimal Number
 * @inp: theParameter Input
 * @file_d: the filedescriptor to write to
 * Return: number of characters printed
 */
int print_d(int inp, int file_d)
{
	int (*putc)(char) = _putchar;
	int in, count = 0;
	unsigned int v, cur;

	if (file_d == STDERR_FILENO)
		putc = _eputchar;
	if (inp < 0)
	{
		v = -inp;
			putc('-');
			count++;
	}
	else
	 v = inp;
	cur = v;
	for (in = 1000000000; in > 1; in /= 10)
	{
		if  (v / in)
		{
			putc('0' + cur / in);
			count++;
		}
		cur %= in;
	}
	putc('0' + cur);
	count++;

	return (count);
}

/**
 * convert_number - Function Converter
 * @nu: Number
 * @b: Base
 * @f: Argument Flags
 * Return: string
 */


char *convert_number(long int nu, int b, int f)
{
	static char *arr;
	static char buf[50];
	char si = 0;
	char *p;
	unsigned long n = nu;

	if (!(f & CONVERT_UNSIGNED) && nu < 0)
	{
		n = -nu;
		si = '-';

	}
	arr = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do	{
		*--p = arr[n % b];
		n /= b;
	} while (n != 0);

	if (si)
		*--p = si;
	return (p);
}


/**
 * remove_comments - Function Replaces First Instance Of # With \0
 * @buf: address of the string to modify
 * Return: 0;
 */

void remove_comments(char *buf)
{
	int in;

	for (in = 0; buf[in] != '\0'; in++)
		if (buf[in] == '#' && (!in || buf[in - 1] == ' '))
		{
			buf[in] = '\0';
			break;
		}
}


#include "shell.h"

/**
 * _eputs - Function Prints Input string
 * @st: String Printed
 */

void _eputs(char *st)
{
	int in = 0;

	if (!st)
		return;
	while (st[in] != '\0')
	{
		_eputchar(st[in]);
		in++;
	}
}

/**
 * _eputchar - Function Writes Character To Stderr
 * @ch: Parameter Character  Print
 * Return: Success 1.Error, -1 .
 */
int _eputchar(char ch)
{
	static int in;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(2, buf, in);
		in = 0;
	}
	if (ch != BUF_FLUSH)
		buf[in++] = ch;
	return (1);
}


/**
 * _putfd - Function Writes Character c To Given fd
 * @ch:  Character To rint
 * @file_d:  File Descriptor  *
 * Return: Success 1, Error -1.
 */

int _putfd(char ch, int file_d)
{
	static int in;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(file_d, buf, in);
		in = 0;
	}
	if (ch != BUF_FLUSH)
		buf[in++] = ch;
	return (1);
}


/**
 * _putsfd - Function prints an input string
 * @st: String To  Printed
 * @file_d: File Descriptor
 *  Return: Numb Of Ch
 */

int _putsfd(char *st, int file_d)
{
	int in = 0;

	if (!st)
		return (0);
	while (*st)
	{
		in += _putfd(*st++, file_d);
	}
	return (in);
}


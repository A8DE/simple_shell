#include "shell.h"

/**
 * _strcpy - copies a string
 * @des: the desination
 * @src: the source
 * Return: pointer to desination
 */

char *_strcpy(char *des, char *src)
{
	int i = 0;

	if (des == src || src == 0)
		return (des);
	while (src[i])
	{
		des[i] = src[i];
		i++;
	}
	des[i] = 0;
	return (des);
}

/**
 * _strdup - duplicates a string
 * @st: the sting to duplicate
 * Return: Pointer To The Duplicated Sting
 */

char *_strdup(const char *st)
{
	int leng = 0;
	char *ret;

	if (st == NULL)
		return (NULL);
	while (*st++)
		leng++;
	ret = malloc(sizeof(char) * (leng + 1));
	if (!ret)
		return (NULL);
	for (leng++; leng--;)
		ret[leng] = *--st;
	return (ret);
}

/**
 * _puts - Function Prints Input Sting
 * @st: Sting To Be Printed
 * Return: Not
 */

void _puts(char *st)
{
	int i = 0;

	if (!st)
		return;
	while (st[i] != '\0')
	{
		_putchar(st[i]);
		i++;
	}
}


/**
 * _putchar - Function Writes Character c Stdout
 * @ch: Character Print
 * Return: Success 1.
 * Error Returned -1, Errno Set Appropriately.
 */

int _putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}


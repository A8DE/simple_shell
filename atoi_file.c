#include "shell.h"


/**
 * interactive - Function Returns True If Shell Interactive Mode
 * @inf: Struct Address
 * Return: interactive Mode 1,0
 */

int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}



/**
 * is_delim - Function Character Delimeter
 * @ch: Parameter  char to check
 * @del: the delimeter string
 * Return: True 1, False 0
 */

int is_delim(char ch, char *del)
{
	while (*del)
		if (*del++ == ch)
			return (1);
	return (0);
}



/**
 * _isalpha - Function Alphabetic Character
 * @ch: Parameter Character Input
 * Return: True 1, False 0
 */

int _isalpha(int ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return (1);
	else
		return (0);
}



/**
 * _atoi - Converts String To Integer
 * @st: String To Converted
 * Return:  No Numbers 0 , Converted Number
 */

int _atoi(char *st)
{
	int in, sig = 1, fla = 0, out;
	unsigned int res = 0;

	for (in = 0; st[in] != '\0' && fla != 2; in++)
	{
		if (st[in] >= '0' && st[in] <= '9')
		{
			fla = 1;
			res *= 10;
			res += (st[in] - '0');
		}
		else if (fla == 1)
			fla = 2;

		if (st[in] == '-')
			sig *= -1;
	}

	if (sig == -1)
		out = -res;
	else
		out = res;

	return (out);
}


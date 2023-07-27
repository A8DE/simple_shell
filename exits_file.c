#include "shell.h"

/**
 *_strncpy - Function Copies String
 *@des: Destination String Copied
 *@sr: Source string
 *@ch: Amount of characters to Copied
 *Return: Concatenate String
 */

char *_strncpy(char *des, char *sr, int ch)
{
	int in, v;
	char *p = des;

	in = 0;
	while (sr[in] != '\0' && in < ch - 1)
	{
		des[in] = sr[in];
		in++;
	}
	if (in < ch)
	{
		v = in;
		while (v < n)
		{
			des[v] = '\0';
			v++;
		}
	}
	return (p);
}


/**
 *_strncat - concatenate Two String
 *@des: First String
 *@sr: Second String
 *@am: Amount Bytes to Maximally Used
 *Return:  Concatenated String
 */

char *_strncat(char *des, char *sr, int am)
{
	int x, y;
	char *c = des;

	x = 0;
	y = 0;
	while (des[x] != '\0')
		x++;
	while (sr[y] != '\0' && y < am)
	{
		des[x] = sr[y];
		x++;
		y++;
	}
	if (y < n)
		des[x] = '\0';
	return (c);
}


/**
 * _strchr - Function locates Character String
 *@st: String Parsed
 *@ch: Character Look For
 *Return: Pointer Memory Area s
 */

char *_strchr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}


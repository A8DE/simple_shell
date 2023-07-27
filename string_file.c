#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @st: the string whose length to check
 * Return: integer length of string
 */
int _strlen(char *st)
{
	int i = 0;

	if (!st)
		return (0);

	while (*st++)
		i++;
	return (i);
}

/**
 * _strcmp - Function Performs Lexicogarphic Comparison Of Two Ttrangs.
 * @st1: First Strang
 * @st2: Second Strang
 * Return: Negative If st1 < s2, Posit if st1 > st2, Zero if st1 equal st2
 */

int _strcmp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * starts_with - Function Checks If Needl Starts With Haystack
 * @haysta: String Search
 * @needl: Substring Find
 * Return: address of next char of haysta or NULL
 */

char *starts_with(const char *haysta, const char *needl)
{
	while (*needl)
	if (*needl++ != *haysta++)
	return (NULL);
	return ((char *)haysta);
}


/**
 * _strcat - Function concatenates two strings
 * @des: Desination buffer
 * @src: Source buffer
 * Return: pointer to desination buffer
 */

char *_strcat(char *des, char *src)
{
	char *ret = des;

	while (*des)
		des++;
	while (*src)
		*des++ = *src++;
	*des = *src;
	return (ret);
}



#include "shell.h"

/**
 * strtow - Function splits Sting Words.Repeat Delimiters
 * @st: The Input Sting
 * @d: Delimeter Sting
 * Return: Pointer To Array Stings, NULL on Failure
 */

char **strtow(char *st, char *d)
{
	int x, y, k, m, num_words = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; st[x] != '\0'; x++)
		if (!is_delim(st[x], d) && (is_delim(st[x + 1], d) || !st[x + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
		while (is_delim(st[x], d))
			x++;
		k = 0;
		while (!is_delim(st[x + k], d) && st[x + k])
			k++;
		s[y] = malloc((k + 1) * sizeof(char));
		if (!s[y])
		{
			for (k = 0; k < y; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[y][m] = st[x++];
		s[y][m] = 0;
	}
	s[y] = NULL;
	return (s);
}

/**
 * **strtow2 - Function splits Sting Into Words
 * @st: Input Sting
 * @d: Delimeter
 * Return: Pointer Array Stings,Failure 0
 */

char **strtow2(char *st, char d)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (i = 0; st[i] != '\0'; i++)
		if ((st[i] != d && st[i + 1] == d) ||
				    (st[i] != d && !st[i + 1]) || st[i + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (st[i] == d && st[i] != d)
			i++;
		k = 0;
		while (st[i + k] != d && st[i + k] && st[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = st[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


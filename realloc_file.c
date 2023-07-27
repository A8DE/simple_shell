#include "shell.h"

/**
 * _memset - Functin Fills Memory With Constant Byte
 * @m: Pointer Memory Area
 * @b: Byte Fill *s With
 * @p: Amount Bytes Filled
 * Return: Pointer To Memor Area s
 */

char *_memset(char *m, char b, unsigned int p)
{
	unsigned int i;

	for (i = 0; i < p; i++)
		m[i] = b;
	return (m);
}

/**
 * ffree -Function Frees String Of Strings
 * @ss: String Of Strings
 */

void ffree(char **ss)
{
	char **a = ss;

	if (!ss)
		return;

	while (*ss)
		free(*ss++);

	free(a);
}

/**
 * _realloc -Function Reallocates Bblock Memory
 * @pt: Pointer Previous Malloc
 * @old_s: Byte Size Of Previous Block
 * @new_s: Byte Size Of New Block
 * Return: Pointer Da Block
 */

void *_realloc(void *pt, unsigned int old_s, unsigned int new_s)
{
	char *po;

	if (!pt)
		return (malloc(new_s));
	if (!new_s)
		return (free(pt), NULL);
	if (new_s == old_s)
		return (pt);

	po = malloc(new_s);

	if (!po)
	return (NULL);

	old_s = old_s < new_s ? old_s : new_s;

	while (old_s--)
		p[old_s] = ((char *)pt)[old_s];
	free(pt);
	return (po);
}


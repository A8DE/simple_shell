#include "shell.h"

/**
 * bfree - Function Frees Pointer NULLs Address
 * @pt: Pointer To Free
 * Return: Free 1,0.
 */
int bfree(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}


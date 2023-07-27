#include "shell.h"

/**
 * list_len - Function Determines Length Linked List
 * @he: pointer to first node
 * Return: Size List
 */

size_t list_len(const list_t *he)
{
	size_t in = 0;

	while (he)
	{
		he = he->next;
		in++;
	}
	return (in);
}


/**
 * list_to_strings - Returns Array Strings List->str
 * @he: Pointer First Node
 * Return: Array Strings
 */

char **list_to_strings(list_t *he)
{
	list_t *nod = he;
	size_t x = list_len(he), y;
	char *str;
	char **strs;

	if (!he || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (i = 0; nod; nod = nod->next, i++)
	{
		str = malloc(_strlen(nod->str) + 1);
		if (!str)
		{
			for (x = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * print_list - Function Prints All Elements List_t Linked List
 * @he: Pointer First Node
 * Return: size of list
 */

size_t print_list(const list_t *he)
{
	size_t i = 0;

	while (he)
	{
		_puts(convert_number(he->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(he->str ? he->str : "(nil)");
		_puts("\n");
		he = he->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - Function Return Node Whose String Starts with Pre
 * @nod: Pointer  List Head
 * @pre: String To Match
 * @ch: Next Character After Pre To Patch
 * Return: Match Nod Null
 */

list_t *node_starts_with(list_t *nod, char *pre, char ch)
{
	char *po = NULL;

	while (nod)
	{
		po = starts_with(nod->str, pre);
		if (po && ((ch == -1) || (*po == ch)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets Index Of ode
 * @hea: Pointer Head
 * @nod: Pointer Node
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *hea, list_t *nod)
{
	size_t i = 0;

	while (hea)
	{
		if (hea == nod)
			return (i);
		hea = hea->next;
		i++;
	}
	return (-1);
}


#include "shell.h"

/**
 * add_node -Function Add Node The Start Of list
 * @he: Address Pointer Hed Node
 * @st: Str Field Node
 * @n: Node Index Used History
 * Return: Size List
 */

list_t *add_node(list_t **he, const char *st, int n)
{
	list_t *new_he;

	if (!he)
		return (NULL);
	new_he = malloc(sizeof(list_t));
	if (!new_he)
		return (NULL);
	_memset((void *)new_he, 0, sizeof(list_t));
	new_he->num = n;
	if (st)	
	{
		new_he->str = _strdup(st);
		if (!new_he->str)
		{
			free(new_he);
			return (NULL);
		}
	}
	new_he->next = *he;
	*he = new_he;
	return (new_he);
}

/**
 * add_node_end - FunctionAadds Node End Of  List
 * @he: address of pointer to he node
 * @st: str field of node
 * @n: node index used by history
 * Return: size of list
 */
list_t *add_node_end(list_t **he, const char *st, int n)
{
	list_t *new_nod, *nod;

	if (!he)
		return (NULL);

	nod = *he;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	_memset((void *)new_nod, 0, sizeof(list_t));
	new_nod->num = n;
	if (st)
	{
		new_nod->str = _strdup(st);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*he = new_nod;
	return (new_nod);
}

/**
 * print_list_str -Function Prints Oonly Str Element Of List_t Linked List
 * @po: Pointer First Node
 * Return: Size List
 */
size_t print_list_str(const list_t *po)
{
	size_t i = 0;

	while (po)
	{
		_puts(po->str ? po->str : "(nil)");
		_puts("\n");
		po = po->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index -Function Deletes Node Given Index
 * @he: Address Of Pointer To first Node
 * @in: Index Of Node Delete
 * Return: Success 1, Failure 0
 */

int delete_node_at_index(list_t **he, unsigned int in)
{
	list_t *nod, *prev_nod;
	unsigned int i = 0;

	if (!he || !*he)
		return (0);

	if (!in)
	{
		nod = *he;
		*he = (*he)->next;
		free(nod->str);
		free(nod);
		return (1);
	}
	nod = *he;
	while (nod)
	{
		if (i == in)
		{
			prev_nod->next = nod->next;
			free(nod->str);
			free(nod);
			return (1);
		}
		i++;
		prev_nod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * free_list - Function Free all Nodes
 * @head_p: Address Pointer Head Node
 * Return: void
 */
void free_list(list_t **head_p)
{
	list_t *nod, *next_nod, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	nod = head;
	while (nod)
	{
		next_nod = nod->next;
		free(nod->str);
		free(nod);
		nod = next_nod;
	}
	*head_p = NULL;
}



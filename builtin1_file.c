#include "shell.h"

/**
 * _myhistory - Function Displays History List, Command line, Preceded
 * Numbers, Starting 0.
 * @inf: Structure Used MaintainConstant function Prototype.
 *  Return: 0
 */

int _myhistory(info_t *inf)
{
	print_list(inf->history);
	return (0);
}


/**
 * unset_alias - Functio Sets Alias To String
 * @inf: Structer
 * @st: String Alias
 * Return: Success 0, Error 1
 */

int unset_alias(info_t *inf, char *st)
{
	char *po, t;
	int re;

	po = _strchr(st, '=');
	if (!po)
		return (1);
	t = *po;
	*po = 0;
	re = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, st, -1)));
	*po = t;
	return (re);
}

/**
 * set_alias - Sets Alias To String
 * @inf: Structer
 * @st: String Alias
 * Return: Success 0, Error 1
 */

int set_alias(info_t *inf, char *st)
{
	char *po;

	po = _strchr(st, '=');
	if (!*++po)
		return (unset_alias(inf, st));
	if (!po)
		return (1);

	unset_alias(inf, st);
	return (add_node_end(&(inf->alias), st, 0) == NULL);
}

/**
 * print_alias - Function Prints Alias String
 * @nod:  Alias Nod
 * Return: Success 0, Error 1
 */
int print_alias(list_t *nod)
{
	char *po = NULL, *a = NULL;

	if (nod)
	{
		po = _strchr(nod->str, '=');
		for (a = nod->str; a <= po; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(po + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 *  _myalias - Function Mimics Alias Builtin
 *  @inf: Structure Used Maintain Constant function prototype.
 *  Return: 0
 */

int _myalias(info_t *inf)
{
	int i = 0;
	char *po = NULL;
	list_t *nod = NULL;

	if (inf->argc == 1)
	{
		nod = inf->alias;
		while (nod)
		{
			print_alias(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		po = _strchr(inf->argv[i], '=');
		if (po)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}


#include "shell.h"

/**
 * _myenv -Function  Prints Current Environment
 * @inf: Structure
 * Return:  0
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}


/**
 * _getenv - Function Gets Value Environ Variable
 * @inf: Structure
 * @nam: Parameter
 * Return: Value
 */

char *_getenv(info_t *inf, const char *nam)
{
	list_t *nod = inf->env;
	char *po;

	while (nod)
	{
		po = starts_with(nod->str, nam);
		if (po && *po)
			return (po);
		nod = nod->next;
	}
	return (NULL);
}


/**
 * _mysetenv - Function Initialize New Environment Variable,
 *Modify Existing One
 * @inf: Structure
 *Return:  0
 */

int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Function Remove Environment Variable
 * @info: Structure
 * Return:  0
 */

int _myunsetenv(info_t *inf)
{
	int in;

	if (inf->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; in <= inf->argc; in++)
		_unsetenv(inf, inf->argv[in]);

	return (0);
}

/**
 * populate_env_list - Functio Populates Env Linked List
 * @inf: Structure
 * Return:  0
 */
int populate_env_list(info_t *inf)
{
	list_t *nod = NULL;
	size_t in;

	for (in = 0; environ[in]; in++)
		add_node_end(&nod, environ[in], 0);
		inf->env = nod;
		return (0);
}



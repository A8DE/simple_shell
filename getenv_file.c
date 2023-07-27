#include "shell.h"

/**
 * get_environ -Function Returns String Array Copy Our Environ
 * @inf: Structure  Used to maintain Constant Function Prototype.
 * Return: 0
 */

char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Function Remove Environment Variable
 * @inf: Structure Containing Used Maintain
 *  Constant Function Prototype.
 *  Return: Delete 1,0
 * @var: String Envr Var Propert
 */

int _unsetenv(info_t *inf, char *var)
{
	list_t *nod = inf->env;
	size_t z = 0;
	char *po;

	if (!nod || !var)
		return (0);

	while (nod)
	{
		po = starts_with(nod->str, var);
		if (po && *po == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), z);
			z = 0;
			nod = inf->env;
			continue;
		}
		nod = nod->next;
		z++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Function  Initialize New Environment Variable,
 * Modify Existing
 * @inf: Structure .
 * @var: String Env Var Property
 * @val: String Env Value
 *  Return: 0
 */

int _setenv(info_t *inf, char *var, char *val)
{
	char *buff = NULL;
	list_t *nod;
	char *po;

	if (!var || !val)
		return (0);

	buff = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, val);
	nod = inf->env;
	while (nod)
	{
		po = starts_with(nod->str, var);
		if (po && *po == '=')
		{
			free(nod->str);
			nod->str = buff;
			inf->env_changed = 1;
			return (0);
		}
		nod = nod->next;
	}
	add_node_end(&(inf->env), buff, 0);
	free(buff);
	inf->env_changed = 1;
	return (0);
}



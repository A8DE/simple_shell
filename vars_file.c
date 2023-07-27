#include "shell.h"

/**
 * is_chain - test if current char in bufffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char bufffer
 * @p: address of current position in buff
 * Return: Chain Delimeter 1, 0
 */

int is_chain(info_t *inf, char *buff, size_t *p)
{
	size_t j = *p;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_OR;
	}

	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}

	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Checks Should Continue Chaining Based Last Status
 * @inf:Parameter Struct
 * @buff: Char Buffer
 * @po: Address Current Position Buf
 * @i: Starting Position Buf
 * @leng: Length Buf
 * Return: Void
 */

void check_chain(info_t *inf, char *buff, size_t *po, size_t i, size_t leng)
{
	size_t j = *po;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[i] = 0;
			j = leng;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[i] = 0;
			j = leng;
		}
	}

	*po = j;
}


/**
 * replace_alias - Replaces Aliases In Tokenized String
 * @inf: Parameter Struct
 * Return:Replaced 1, 0
 */
int replace_alias(info_t *inf)
{
	int i;
	list_t *nod;
	char *po;

	for (i = 0; i < 10; i++)
	{
		nod = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!nod)
			return (0);
		free(inf->argv[0]);
		po = _strchr(nod->str, '=');
		if (!po)
			return (0);
		po = _strdup(po + 1);
		if (!po)
			return (0);
		inf->argv[0] = po;
	}
	return (1);
}

/**
 * replace_vars - Function Replaces Var Tokenized String
 * @inf: Parameter Struct
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(info_t *inf)
{
	int i = 0;
	list_t *nod;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_strcmp(inf->argv[i], "$?"))
		{
			replace_string(&(inf->argv[i]),
					_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			replace_string(&(inf->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nod = node_starts_with(inf->env, &inf->argv[i][1], '=');
		if (nod)
		{
			replace_string(&(inf->argv[i]),
					_strdup(_strchr(nod->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string -Function Replaces String
 * @ol: Address Of Old String
 * @ne: New String
 * Return: Replaced 1, 0
 */
int replace_string(char **ol, char *ne)
{
	free(*ol);
	*ol = ne;
	return (1);
}


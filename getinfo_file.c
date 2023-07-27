#include "shell.h"

/**
 * clear_info - Function Initializes info_t Struct
 * @inf: struct address
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info -Function Initializes info_t Struct
 * @inf: Struct Addres
 * @ar: Argument Vector
 */
void set_info(info_t *inf, char **ar)
{
	int in = 0;

	info->fname = ar[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = maloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (in = 0; info->argv && info->argv[in]; in++)
			;
		info->argc = in;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * free_info - Function Frees info struct Field
 * @inf: Struct Address
 * @al: true if freeing al fields
 */
void free_info(info_t *inf, int al)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (al)
	{
		if (inf->env)
			free_list(&(inf->env));
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
			inf->environ = NULL;
		bfree((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}


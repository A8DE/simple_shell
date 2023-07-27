#include "shell.h"

/**
 * is_cmd - Determines If a file Is Executable Command
 * @inf: the info struct
 * @pat: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *inf, char *pat)
{
	struct stat s;

	(void)inf;
	if (!pat || stat(pat, &s))
		return (0);

	if (s.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Function Duplicates Characters
 * @path_str: PATH String
 * @sta: Starting Index
 * @sto: Stopping Index
 * Return: Pointer To New Buffer
 */

char *dup_chars(char *path_str, int sta, int sto)
{
	static char buf[1024];
	int x = 0, k = 0;

	for (k = 0, x = sta; x < sto; x++)
		if (path_str[x] != ':')
			buf[k++] = path_str[x];
	buf[k] = 0;
	return (buf);
}


/**
 * find_path - Function Finds This Cmd In The PATH String
 * @inf: Info Struct
 * @path_str:  PATH string
 * @cmd:  cmd Find
 * Return: Full Path Cmd Found or NULL
 */

char *find_path(info_t *inf, char *path_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *pat;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			pat = dup_chars(path_str, curr_pos, i);
			if (!*pat)
				_strcat(pat, cmd);
			else
			{
				_strcat(pat, "/");
				_strcat(pat, cmd);
			}
			if (is_cmd(inf, pat))
				return (pat);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}


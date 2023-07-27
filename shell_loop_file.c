#include "shell.h"

/**
 * hsh - Main Shell loop
 * @inf: Parameter & Return Info Struct
 * @v: Argument Vector From main()
 * Return: success 0, Error 1, or error code
 */

int hsh(info_t *inf, char **v)
{
	ssize_t r = 0;
	int builtin_r = 0;

	while (r != -1 && builtin_r != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(inf);
		if (r != -1)
		{
			set_info(inf, v);
			builtin_r = find_builtin(inf);
			if (builtin_r == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && info->status)
		exit(inf->status);
	if (builtin_r == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_r);
}

/**
 * find_builtin - Finds Builtin Command
 * @inf: Parameter & Return Info Struct
 * Return: Builtin Not Found -1,
 * executed successfully 0,
 * found but not successful 1 ,
 * signals exit() 2,
 */

int find_builtin(info_t *inf)
{
	int i, built_inret = -1;
	builtin_table builtin_tbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtin_tbl[i].type; i++)
		if (_strcmp(info->argv[0], builtin_tbl[i].type) == 0)
		{
			inf->line_count++;
			built_inret = builtin_tbl[i].func(inf);
			break;
		}
	return (built_inret);
}

/**
 * find_cmd -Function Finds Command In PATH
 * @inf: Parameter Rturn inf Struct
 * Return: void
 */

void find_cmd(info_t *inf)
{
	char *pat = NULL;
	int i, k;

	inf->pat = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
		if (!is_delim(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	pat = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (pat)
	{
		inf->pat = pat;
		fork_cmd(inf);
	}
	else
	{
		if (_getenv(inf, "PATH=") || (interactive(inf)
					|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "Not Found\n");
		}
	}
}

/**
 * fork_cmd - Function Forks Exec Thread Run Cmd
 * @inf: Parameter Return Info Struct
 * Return: void
 */

void fork_cmd(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}


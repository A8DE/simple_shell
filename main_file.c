#include "shell.h"

/**
 * main - Function Entry Point
 * @c: Arg Count
 * @v: Arg Vector
 * Return: Success 0, Error 1
 */
int main(int c, char **v)
{
	info_t inf[] = {INFO_INIT};
	int f = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f)
			: "r" (f));

	if (c == 2)
	{
		f = open(v[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(v[0]);
				_eputs(": 0:  Cant Open ");
				_eputs(v[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = f;
	}
	populate_env_list(inf);
	read_history(inf);
	hsh(inf, v);
	return (EXIT_SUCCESS);
}


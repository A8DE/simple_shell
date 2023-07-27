#include "shell.h"

/**
 * _myexit - Function Exit Shell
 * @inf: Structur Containing Potential Argument. Used Maintain
 * Constant Function Prototype.
 * Return: If info.argv[0] != "exit" 0
 */
int _myexit(info_t *inf)
{
	int exit_check;

	if (inf->argv[1])
	{
		exit_check = _erratoi(inf->argv[1]);

		if (exit_check == -1)
		{
			inf->status = 2;

			print_error(inf, "Illega Numbe: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');

			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);

		return (-2);
	}

	inf->err_num = -1;
	return (-2);
}
/**
 * _mycd - Function Changes Current Directory
 * @inf: Structure Containing Potential Arguments.
 * Constant Function Prototype.
 * Return: 0
 */
int _mycd(info_t *inf)
{
	char *p, *di, buffer[1024];
	int chd_ret;

	p = getcwd(buffer, 1024);

	if (!inf->argv[1])
	{
		di = _getenv(inf, "HOME=");
		if (!di)
			chd_ret = chdir((di = _getenv(inf, "PWD=")) ? di : "/");
		else
			chd_ret = chdir(di);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(p);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		chd_ret = chdir((di = _getenv(inf, "OLDPWD=")) ? di : "/");
	}
	else
		chd_ret = chdir(inf->argv[1]);
		s
	if (chd_ret == -1)
	{
		print_error(inf, "cant CD ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	if (!p)
		_puts("TODO: >>getcwd Fail emsg Her<<\n");
	return (0);
}
/**
 * _myhelp - Functtion Changes Current Directory
 * @inf: Structure containing Arguments. Used Constant
 * Function Prototype.
 * Return:  0
 */
int _myhelp(info_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts(" Function Not Yet Implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
	}


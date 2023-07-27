#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @inf: Parameter struct
 * @buf: Address Buffer
 * @le: Address len Var
 * Return: Bytes Read
 */

ssize_t input_buf(info_t *inf, char **buf, size_t *le)
{
	ssize_t v = 0;
	size_t le_p = 0;

	if (!*le)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		v = getline(buf, &le_p, stdin);
#else
		v = _getline(inf, buf, &le_p);
#endif
		if (v > 0)
		{
			if ((*buf)[v - 1] == '\n')
			{
				(*buf)[v - 1] = '\0';
				v--;
			}
			inf->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(inf, *buf, inf->histcount++);
			{
				*le = v;
				inf->cmd_buf = buf;
			}
		}
	}
	return (v);
}

/**
 * get_input - Function Gets Line Minus Newline
 * @inf: Parameter Struct
 * Return: Bytes Read
 */
ssize_t get_input(info_t *inf)
{
	static char *buf;
	static size_t x, y, le;
	ssize_t v = 0;
	char **buf_p = &(inf->arg), *po;

	_putchar(BUF_FLUSH);
	v = input_buf(inf, &buf, &le);
	if (v == -1)
	return (-1);
	if (le)
	{
		y = x;
		po = buf + x;
		check_chain(inf, buf, &y, x, le);
		while (y < le)
		{
			if (is_chain(inf, buf, &y))
				break;
			j++;
		}

		x = y + 1;
		if (x >= le)
		{
			x = le = 0;
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = po;
		return (_strle(po));
	}

	*buf_p = buf;
	return (v);
}

/**
 * read_buf - Function Reads Buffer
 * @inf: Parameter Struct
 * @buf: Buffer
 * @z: Size
 *
 * Return: r
 */
ssize_t read_buf(info_t *inf, char *buf, size_t *z)
{
	ssize_t v = 0;

	if (*z)
		return (0);
	v = read(inf->readfd, buf, READ_BUF_SIZE);
	if (v >= 0)
		*z = v;
	return (v);
}

/**
 * _getline - Function Gets Next Line Input From STDIN
 * @inf: Parameter Struct
 * @ptr: Address  Pointer Buffer, Preallocated Or NULL
 * @leg: Size Preallocated Ptr Buffer If Not NULL
 * Return: s
 */
int _getline(info_t *inf, char **ptr, size_t *leg)
{
	static char buf[READ_BUF_SIZE];
	static size_t z, le;
	size_t t;
	ssize_t v = 0, s = 0;
	char *po = NULL, *new_po = NULL, *ch;

	po = *ptr;
	if (po && leg)
		s = *leg;
	if (z == le)
		z = le = 0;

	v = read_buf(inf, buf, &le);
	if (v == -1 || (v == 0 && le == 0))
		return (-1);

	ch = _strchr(buf + z, '\n');
	t = ch ? 1 + (unsigned int)(ch - buf) : le;
	new_po = _realloc(po, s, s ? s + t : t + 1);
	if (!new_po)
		return (po ? free(po), -1 : -1);

	if (s)
		_strncat(new_po, buf + z, t - z);
	else
		_strncpy(new_po, buf + z, t - z + 1);

	s += t - i;
	z = t;
	po = new_po;

	if (leg)
		*leg = s;
	*ptr = po;
	return (s);
}

/**
 * sigintHandler -fUNCTION Blocks Ctrl-C
 * @sig_n: Signal Number
 * Return: void
 */


void sigintHandler(__attribute__((unused))int sig_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}


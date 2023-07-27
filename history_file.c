#include "shell.h"

/**
 * get_history_file - Function Gets Distory File
 * @inf: Parameter Struct
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *inf)
{
	char *buff, *dire;

	dire = _getenv(inf, "HOME=");
	if (!dire)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dire) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dire);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}


/**
 * write_history -Function Creates File, Appends Existing File
 * @inf: Parameter Struct
 * Return: Success 1,-1
 */
int write_history(info_t *inf)
{
	ssize_t f;
	char *file_n = get_history_file(inf);
	list_t *nod = NULL;

	if (!file_n)
		return (-1);

	f = open(file_n, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_n);
	if (f == -1)
		return (-1);
	for (nod = inf->history; nod; nod = nod->next)
	{
		_putsfd(nod->str, f);
		_putfd('\n', f);
	}
	_putfd(BUF_FLUSH, f);
	close(f);
	return (1);
}


/**
 * read_history -Function Reads History From File
 * @inf: Parameter Struct
 * Return: Success histcount, 0
 */
int read_history(info_t *inf)
{
	int i, line_c = 0, las = 0;
	ssize_t f, rdle, f_size = 0;
	struct stat st;
	char *buff = NULL, *file_n = get_history_file(inf);

	if (!file_n)
	return (0);
	f = open(file_n, O_RDONLY);
	free(file_n);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	rdle = read(f, buff, f_size);
	buff[f_size] = 0;
	if (rdle <= 0)
		return (free(buff), 0);
	close(f);
	for (i = 0; i < f_size; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history_list(inf, buff + las, line_c++);
			las = i + 1;
		}
	if (las != i)
		build_history_list(inf, buff + las, line_c++);
	free(buff);
	inf->histcount = line_c;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);
	return (inf->histcount);
}

/**
 * build_history_list -Function Adds Entry History Linked list
 * @inf: Structur
 * @buff: Buffer
 * @line_c: History Linecount, Histcount
 * Return:  0
 */

int build_history_list(info_t *inf, char *buff, int line_c)
{
	list_t *nod = NULL;

	if (inf->history)
		nod = inf->history;
	add_node_end(&nod, buff, line_c);

	if (!inf->history)
		inf->history = nod;
	return (0);
}

/**
 * renumber_history - Function Renumbers History Linked List After Changes
 * @inf: Structure
 * Return: New Histcount
 */

int renumber_history(info_t *inf)
{
	list_t *nod = inf->history;
	int i = 0;

	while (nod)
	{
		nod->num = i++;
		nod = nod->next;
	}
	return (inf->histcount = i);
}


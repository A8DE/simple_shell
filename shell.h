#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

/* For Read/Write Buffers */
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024


/*For Command Chaining */
#define CMD_NORM	0
#define CMD_AND		2
#define CMD_CHAIN	3
#define CMD_OR		1

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0



/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"

extern char **environ;


/**
 * struct liststr - Function Singly Linked List
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Struct  Pseudo Arguements To Pass Into a function,
 * Allowing Uniform Prototype For Function Pointer
 * @arg: String  From Getline Containing Arguements
 * @argv:Array Strings Generated Arg
 * @path: String Path For Current Command
 * @argc: Argument count
 * @line_count: Error Count
 * @err_num: Error For exit()s
 * @linecount_flag: If Count This Line Input
 * @fname: Program Filename
 * @env: Linked List Local Copy Environ
 * @environ: Custom Modified copy Environ From  env
 * @history: History Node
 * @alias: Alias Node
 * @env_changed: If Environ Was Changed
 * @status: Return Status The Last Execd Command
 * @cmd_buf:  Address Of Pointer To cmd_buf, On If Chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fdfrom Which To Read Line Iinput
 * @histcount:  History Line Number Count
 */
typedef struct passinfo
{

	char **argv;
	int argc;
	char *arg;
	char *path;
	unsigned int line_count;
	int linecount_flag;
	char *fname;
	int err_num;
	list_t *history;
	list_t *env;
	list_t *alias;
	int env_changed;
	char **environ;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* atoi_file.c */
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);

/* builtin_file.c */
int _myhelp(info_t *);
int _mycd(info_t *);
int _myexit(info_t *);

/* builtin1_file.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/* environ_file.c */
int _myenv(info_t *);
int _mysetenv(info_t *);
char *_getenv(info_t *, const char *);
int populate_env_list(info_t *);
int _myunsetenv(info_t *);

/* errors_file.c */
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
void _eputs(char *);
int _eputchar(char);

/* exits_file.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* getinfo_file.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

/* getenv_file.c */
int _unsetenv(info_t *, char *);
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);

/*getline_file.c */
ssize_t get_input(info_t *);
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);

/* history_file.c */
int write_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
char *get_history_file(info_t *info);
int read_history(info_t *info);
int renumber_history(info_t *info);

/* lists_file.c */
list_t *add_node_end(list_t **, const char *, int);
list_t *add_node(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
size_t print_list_str(const list_t *);
void free_list(list_t **);

/* errors1_file.c */
void print_error(info_t *, char *);
char *convert_number(long int, int, int);
int _erratoi(char *);
int print_d(int, int);
void remove_comments(char *);

/* shloop_file.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser_file.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh_file.c */
int loophsh(char **);

/* string_file.c */
int _strcmp(char *, char *);
int _strlen(char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1_file.c */
char *_strdup(const char *);
char *_strcpy(char *, char *);
void _puts(char *);
int _putchar(char);


/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc_file.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory_file.c */
int bfree(void **);

/* lists1_file.c */
size_t list_len(const list_t *);
size_t print_list(const list_t *);
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);

/* vars_file.c */
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
int replace_string(char **, char *);

#endif


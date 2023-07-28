#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


/* Read Write Bufer */
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024


/* Command Chaining */
#define CMD_NORM	0
#define CMD_AND		2
#define CMD_OR		1
#define CMD_CHAIN	3

/* Convert Number */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1

/* Using System Getline() : 1 */
#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"

extern char **environ;


/**
 * struct liststr -  struct Singly Linked List
 * @num: the number field
 * @str: String
 * @next: Points Next Node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - struct Arguements Pass Into Function,
 *		Allowing Function Pointer Struct
 *@arg: String Generated From Getline
 *@argv: Array Strings Generated From arg
 *@path: String Path Current Command
 *@argc: Argument Count
 *@line_count: Error Count
 *@err_num: Error Code Exit()s
 *@linecount_flag: Count This Line Of Input
 *@fname: Program Filename
 *@env: Linked List Local Copy Of Environ
 *@environ: Modified Copy Environ From env
 *@history: history Node
 *@alias: Alias Node
 *@env_changed: If Environ Was Changed
 *@status: Return Status Of The Last ExecD Command
 *@cmd_buf: Address Of Pointer cmd_buf, Chaining
 *@cmd_buf_type: CMD_type &&,|| ;
 *@readfd: From Which Read Line Input
 *@histcount: History line Number Count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
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
 *struct builtin - Struct Contains Builtin String Related Function
 *@type: Builtin Command Flag
 *@func: Function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* loophsh.c */
int loophsh(char **);

/* Shloop_File.c */
int hsh(info_t *, char **);
void find_cmd(info_t *);
int find_builtin(info_t *);
void fork_cmd(info_t *);

/* Parser_file.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);

/* errors_file.c */
void _eputs(char *);
int _putfd(char c, int fd);
int _eputchar(char);
int _putsfd(char *str, int fd);

/* string_file.c */
int _strlen(char *);
char *starts_with(const char *, const char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);

/* exits_file.c */
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);

/* String1_file.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
int _putchar(char);
void _puts(char *);

/* tokenizer_file.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_memory.c */
int bfree(void **);

/* realloc_file.c */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);

/* atoi_file.c */
int interactive(info_t *);
int _isalpha(int);
int _atoi(char *);
int is_delim(char, char *);

/* builtin_file.c */
int _myexit(info_t *);
int _myhelp(info_t *);
int _mycd(info_t *);

/* errors1_file.c */
int _erratoi(char *);
int print_d(int, int);
void print_error(info_t *, char *);
void remove_comments(char *);
char *convert_number(long int, int, int);


/*getline_file.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);


/*builtin1_file.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/* getinfo_file.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

/* getenv_file.c */
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

/* environ.c_file */
char *_getenv(info_t *, const char *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _myenv(info_t *);

/* lists_file.c */
list_t *add_node(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node_end(list_t **, const char *, int);

/* history_file.c */
char *get_history_file(info_t *inf);
int read_history(info_t *inf);
int build_history_list(info_t *inf, char *buff, int line_c);
int renumber_history(info_t *inf);
int write_history(info_t *inf);

/* vars_file.c */
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_string(char **, char *);

/* lists1_file.c */
size_t list_len(const list_t *);
size_t print_list(const list_t *);
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);

#endif

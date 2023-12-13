#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read and write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

/* command */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 when using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @no: number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int no;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: string generated from getline with arguements
 * @argv: string arr generated from arg
 * @path: path of string for the current command
 * @argc: argument count
 * @line_count: rror count
 * @err_no: error code for exit(s)
 * @linecount_flag: count this line of input
 * @fname: program filenames
 * @env: linked local copy list of environment
 * @environ: modified custm copy of environ from LL env
 * @history: node history
 * @alias: node alias
 * @env_changed: on if environment was changed
 * @status: return status of last exec'd command
 * @cmd_buf: address of ptr to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to read line input
 * @histcount: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_no;
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
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shell_loop.c */
int hsh(info_t *, char **);
int find_bltin(info_t *);
void find_cmmd(info_t *);
void fork_cmmd(info_t *);

/* parser.c */
int is_cmmd(info_t *, char *);
char *dupl_chars(char *, int, int);
char *find_pth(info_t *, char *, char *);

/* hsh_loop.c */
int loophsh(char **);

/* errors0.c */
void eputs(char *);
int eputchar(char);
int putfd(char ch, int fld);
int putsfld(char *st, int fld);

/* errors1.c */
int err_atoi(char *);
void prints_error(info_t *, char *);
int prints_d(int, int);
char *convert_num(long int, int, int);
void rem_comments(char *);

/* string.c */
int str_len(char *);
int str_cmp(char *, char *);
char *starts_wth(const char *, const char *);
char *str_cat(char *, char *);

/* string1.c */
char *str_cpy(char *, char *);
char *str_dup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *string_cpy(char *, char *, int);
char *string_cat(char *, char *, int);
char *string_chr(char *, char);

/* tokenizer.c */
char **split(char *, char *);
char **split2(char *, char);

/* real_loc.c */
char *_memset(char *, char, unsigned int);
void free_string(char **);
void *real_loc(void *, unsigned int, unsigned int);

/* memory.c */
int free_memory(void **);

/* _atoi.c */
int inter_active(info_t *);
int is_delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);

/* builtin.c */
int my_exit(info_t *);
int my_cdr(info_t *);
int my_help(info_t *);

/* builtin1.c */
int my_history(info_t *);
int _unset_alias(info_t *, char *);
int _set_alias(info_t *, char *);
int _print_alias(list_t *);
int my_alias(info_t *);

/* getline.c */
ssize_t get_inp(info_t *);
ssize_t input_buffr(info_t *, char **, size_t *);
ssize_t read_buffr(info_t *, char *, size_t *);
int get_line(info_t *, char **, size_t *);
void sigint_handler(int);

/* getinfo.c */
void clear_infor(info_t *);
void set_infor(info_t *, char **);
void free_infor(info_t *, int);

/* environment.c */
char *get_env(info_t *, const char *);
int my_environ(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int popul_environ_list(info_t *);

/* getenv.c */
char **get_envi(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* history.c */
char *get_hist_file(info_t *inform);
int write_hist(info_t *inform);
int read_hist(info_t *inform);
int build_hist_list(info_t *inform, char *buffr, int linecnt);
int re_number_hist(info_t *inform);

/* lists.c */
list_t *adds_node(list_t **, const char *, int);
list_t *adds_node_end(list_t **, const char *, int);
size_t prints_list_str(const list_t *);
int deletes_node_index(list_t **, unsigned int);
void frees_list(list_t **);

/* lists1.c */
size_t list_length(const list_t *);
char **list_arr_strings(list_t *);
size_t prints_lists(const list_t *);
list_t *nodes_starts_wth(list_t *, char *, char);
ssize_t get_node_indexes(list_t *, list_t *);

/* variable.c */
int is_chains(info_t *, char *, size_t *);
void check_chains(info_t *, char *, size_t *, size_t, size_t);
int repl_alias(info_t *);
int repl_variable(info_t *);
int repl_string(char **, char *);

#endif /* _MAIN_H_ */

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>

#define DLMT " \t\n"

extern char **environ;

/**
 * struct built_in - Defines the builtins functions.
 * @built: The name of the build in command.
 * @func: A pointer to the right builtin function.
 */
typedef struct built_in
{
	char *built;
	void (*func)(char **, char *);
} built_in_t;

/* test func */
void print_commands(char **cmd);

/* handle errors */
void handle_exec_err(char *argv[], char *commands[], int cmd_counter);

/* modes */
void batch(char *argv[], char *env[]);
void interactive(char *argv[], char *env[]);

/* parse and execute functions */
char *read_line(void);
int count_token(char *line, const char *dlmt);
char **parse_line(char *line, const char *delimiter);
int execute_args(char **args);
void create_process(char **commands, char *env[]);

/* Builtin functions */
void our_cd(char **args, char *line);
void our_exit(char **args, char *line);
void our_env(char **a, char *b);
void our_setenv(char *args[], char *line);
void our_unsetenv(char *args[], char *line);
int is_built_in(char **args, char *line);
void (*check_built_ins(char *str))(char **, char *);

/*path functions*/
int find_path_index(char *env);
char *build_full_path(char *path, char *command);
char *search_full_path(char *command);
char **parse_path(int index, char *str);

/* alx functions */
void set_env(char *name, char *value);
char *_strdup(char *src);
int _strcmp(char *s1, char *s2);
int _putchar(char c);
int _strlen(char *s);
void _puts(char *s);
void free_arr(char *arr[]);
void print_number(int n);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
int _isdigit(int c);
int _isupper(int c);
#endif

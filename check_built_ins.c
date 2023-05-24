#include "shell.h"
/**
 * check_built_ins - Finds the right function needed for execution.
 * @str: The name of the function that is needed also args[0].
 * Return: Upon sucess a pointer to a void function. Otherwise NULL.
 */
void (*check_built_ins(char *str))(char **, char *)
{
	int i;

	built_in_t buildin[] = {
		{"unsetenv", our_unsetenv},
		{"setenv", our_setenv},
		{"exit", our_exit},
		{"env", our_env},
		{"cd", our_cd},
		{NULL, NULL}
	};

	for (i = 0; buildin[i].built != NULL; i++)
	{
		if (_strcmp(str, buildin[i].built) == 0)
		{
			return (buildin[i].func);
		}
	}
	return (NULL);
}

/**
 * is_built_in - Checks for builtin functions.
 * @args: the command and its flags
 * @line: A string representing the input from the user.
 * Return: If function is found 0. Otherwise -1.
 */
int is_built_in(char **args, char *line)
{
	if (check_built_ins(args[0]) == NULL)
		return (0);
	check_built_ins(args[0])(args, line);
	return (1);
}

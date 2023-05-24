#include "shell.h"

/**
 * our_cd - Changes the current working directory to
 * the directory passed to it.
 * if no parameter is passed it will change directory to HOME.
 * @args: the command and its flags
 * @line: A string representing the input from the user.
 */

void our_cd(char **args, __attribute__((unused)) char *line)
{
	char *buf = NULL;
	size_t size = 0;
	int index;
	char *pwd = getcwd(buf, size);

	if (args[1] == NULL)
	{
		index = find_path_index("HOME");
		chdir((environ[index]) + 5);
	}
	else if (_strcmp(args[1], "-") == 0)
	{
		index = find_path_index("OLDPWD");
		if (index != -1)
			chdir((environ[index]) + 7);
		else
			perror("cd: ");
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			perror("error: ");
		}
	}
	set_env("OLDPWD", pwd);
	free(buf);
	free(pwd);
}

/**
 * our_env - Prints all the environmental variables in the current shell.
 * @a: the command and its flags , but not used here
 * @b: A string representing the input from the user. also not used.
 */
void our_env(__attribute__((unused)) char **a, __attribute__((unused)) char *b)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}
}

/**
 * our_exit - Exits the shell. After freeing allocated resources.
 * @args: the command and its flags
 * @line: A string representing the input from the user.
 */
void our_exit(char **args, char *line)
{
	int status = EXIT_SUCCESS;
	int i = 0;

	if (args[1])
	{
		while (args[1][i])
		{
			if (!_isdigit(args[1][i]))
				break;
			i++;
		}
		if (i == _strlen(args[1]))
			status = _atoi(args[1]);
	}
	else
		status = EXIT_SUCCESS;

	free(line);
	free_arr(args);
	exit(status);
}

#include "shell.h"

/**
 * our_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @args: the variables array
 * @line: the input from the user
 */
void our_setenv(char *args[], __attribute__((unused)) char *line)
{
	char *name, *value;

	if (!args[2] || !args[1])
	{
		perror("setenv()");
		return;
	}
	name = args[1];
	value = args[2];
	set_env(name, value);
}
/**
 * our_unsetenv - unset the environment variable name
 * @args: array of tokens containing the var name to unset args[1].
 * @line: the input typed by the user or given by non-interactive mode.
 */
void our_unsetenv(char *args[], __attribute__((unused)) char *line)
{
	int index;
	char *name = args[1];

	if (!name)
		return;
	index = find_path_index(name);
	if (index != -1)
	{
		environ[index] = environ[index + 1];
	}
	else
		perror("unsetenv() ");
}

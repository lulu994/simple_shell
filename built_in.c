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
	cd_setenv("OLDPWD", pwd);
	free(buf);
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
	char *str, *name, *value;
	int index, name_len, value_len, len, i = 0;

	if (!args[1] || !args[2])
	{
		perror("set: ");
		return;
	}
	name = args[1], value = args[2], name_len = _strlen(name);
	value_len = _strlen(value);
	len = name_len + value_len + 2;
	if (!name_len || !value_len)
	{
		perror("set: ");
		return;
	}
	while (name[i])
	{
		if (!isupper(name[i]) || name[i] != '_')
		{
			perror("Invalid name:");
			return;
		}
	} str = malloc(len * sizeof(char));
	if (!str)
	{
		perror("Allocations fails: ");
		return;
	}
	_strcpy(str, name), _strcat(str, "="), _strcat(str, value);
	index = find_path_index(name);
	if (index != -1)
		environ[index] = str;
	else
	{
		while (environ[i])
			i++;
		environ[i] = str, environ[i + 1] = NULL;
	}
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
	while (name[i])
	{
		if (!isupper(name[i]) || name[i] != '_')
			return;
	}
	index = find_path_index(name);
	if (index != -1)
	{
		environ[index] = environ[index + 1];
	}
	else
		perror("unsetenv :");
}


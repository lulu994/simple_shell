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
		cd_setenv("OLDPWD", pwd);
	}
	else if (_strcmp(args[1], "-") == 0)
	{
		index = find_path_index("OLDPWD");
		if (index != -1)
		{
			chdir((environ[index]) + 7);
			cd_setenv("OLDPWD", pwd);
		}
		else
		{
			_puts("cd: OLDPWD not set\n");
			cd_setenv("OLDPWD", pwd);
		}
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			_puts("[File Name]: cd: No such file or directory\n");
		}
	}
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
	int status = 0;
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
		status = 0;

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
	int index;
	char *str, *name, *value;
	int name_len, value_len, len, i = 0;

	if (!args[1] || !args[2])
	{
		_puts("can't set enpty variable\n");
		return;
	}
	name = args[1], value = args[2];
        name_len = _strlen(name);
        value_len = _strlen(value);
        len = name_len + value_len + 2;
	if (!name_len || !value_len || ((name_len == 1) && (*name == '=')))
	{
		_puts("can't set enpty variable\n");
		return;
	}
	str = malloc(len * sizeof(char));
	if (!str)
	{
		_puts("Allocations fails");
		return;
	}
	_strcpy(str, name), _strcat(str, "="), _strcat(str, value);
	index = find_path_index(name);
	if (index != -1 )
		environ[index] = _strdup(str);
	else
	{
		while (environ[i])
			i++;
		environ[i] = _strdup(str);
		environ[++i] = NULL;
	}
	free(str);
}

/**
 * our_unsetenv - unset the environment variable name
 * @name: the var to unset
 * Return: 0 on success otherwise -1
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
		while (environ[index])
		{
			environ[index] = environ[index + 1];
			index++;
		}
	}
	else
		_puts("Can't unset non exist environment variable\n");
}


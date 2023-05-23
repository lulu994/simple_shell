#include "shell.h"
/**
 * search_full_path - searches for a valid path for the command
 * @command: the comand to look for in the path
 * Return: the fullpath if found , NULL otherwise.
 */

char *search_full_path(char *command)
{
	char *full_path;
	char **path_tokens;
	int i = 0, var_index;

	var_index = find_path_index("PATH");
	if (var_index == -1)
		return (NULL);
	path_tokens = parse_path(var_index, "PATH");
	if (!path_tokens)
		return (NULL);

	while (path_tokens[i])
	{
		full_path = (build_full_path(path_tokens[i], command));
		if (!full_path)
		{
			free_arr(path_tokens);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_arr(path_tokens);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_arr(path_tokens);
	return (NULL);
}

/**
 * parse_path - finds environment variable in the environ and
 * split it into tokens.
 * @index: Index of the environment variable.
 * @str: representing the environment variable.
 * Return: on success an array of token, on fail NULL is returned.
 */
char **parse_path(int index, char *str)
{
	char *env_var; /*getenv("PATH");*/
	char **path_tokens;
	int len;
	const char *dlmtr = ":";

	len = _strlen(str);
	env_var = environ[index] + (len + 1);
	path_tokens = parse_line(env_var, dlmtr);
	if (path_tokens == NULL)
		return (NULL);
	return (path_tokens);
}
/**
 * build_full_path - Combines a token in the tokens PATH array with a command.
 * @path: Represents a token of the environment variable PATH.
 * @command: the command.
 * Return: On success a full path of the command, Otherwise NULL.
 */
char *build_full_path(char *path, char *command)
{
	int path_len;
	int command_len;
	int len;
	char *built;

	if (path == NULL || command == NULL)
		return (NULL);
	path_len = _strlen(path);
	command_len = _strlen(command);
	len = path_len + command_len + 2;

	built = malloc(sizeof(char) * len);
	if (built == NULL)
		return (NULL);
	_strcpy(built, path);
	_strcat(built, "/");
	_strcat(built, command);
	return (built);
}

/**
 * find_path_index - Finds the index of an environmental variable.
 * @env: Environment variable that needs to be found.
 * Return: on success returns the index of the environment variable.
 * otherwise returns -1.
 */
int find_path_index(char *env)
{
	int i;
	int len;
	int j;

	len = _strlen(env);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (environ[i][j] != env[j])
				break;
		}
		if (j == len && environ[i][j] == '=')
			return (i);
	}
	return (-1);
}

#include "shell.h"

/**
 * main - Entry point of the program
 * @argc: arg count
 * @argv: arg vector
 * @env: the inviron variable.
 * Return: Always 0 on success.
 */
int main(__attribute__((unused)) int argc, char *argv[], char *env[])
{
	signal(SIGINT, SIG_IGN);
	if (isatty(STDIN_FILENO) == 1)
	{
		interactive(argv, env);
	}
	else
		batch(argv, env);
	return (0);
}

/**
 * interactive - execute command on the mode interactive.
 * @argv: argument vector
 * @env: environ variable.
 */
void interactive(char *argv[], char *env[])
{
	char *line, **args, *cmd_full_path;
	int cmd_counter = 1;
	struct stat statbuf;

	while (1)
	{
		write(STDOUT_FILENO, "#Home$ ", 7);
		fflush(stdout);
		line = read_line(), args = parse_line(line, DLMT);
		if (!args[0])
		{
			free(line), free_arr(args);
			continue;
		}
		else if (!is_built_in(args, line))
		{
			cmd_full_path = search_full_path(args[0]);
			if (cmd_full_path || (stat(args[0], &statbuf) == 0) ||
					(access(args[0], X_OK) == 0))
			{
				if (cmd_full_path)
				{
					args[0] = _strdup(cmd_full_path);
					free(cmd_full_path);
				}
				create_process(args, env);
			}
			else
				handle_exec_err(argv, args, cmd_counter);
			free(line), free_arr(args), cmd_counter++;
		}
		else
		{
			free(line), free_arr(args);
		}
	}
}

/**
 * batch - execute command on the mode non-interactive.
 * @argv: argument vector
 * @env: environ variable.
 */

void batch(char *argv[], char *env[])
{
	char *line, **args, *cmd_full_path;
	int cmd_counter = 1;
	struct stat statbuf;

	line = read_line();
	args = parse_line(line, DLMT);
	if (!args[0])
	{
		free(line);
		free_arr(args);
	}
	else if (!is_built_in(args, line))
	{
		cmd_full_path = search_full_path(args[0]);
		if (cmd_full_path || (stat(args[0], &statbuf) == 0) ||
				(access(args[0], X_OK) == 0))
		{
			if (cmd_full_path)
			{
				free(args[0]);
				args[0] = _strdup(cmd_full_path);
				free(cmd_full_path);
			}
		create_process(args, env);
		}
		else
			handle_exec_err(argv, args, cmd_counter);
		free(line);
		free_arr(args);
		cmd_counter++;
	}
	else
	{
		free(line);
		free_arr(args);
	}
}

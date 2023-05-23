#include "shell.h"

/**
 * read_line - read a line from terminal
 * Return: pointer that points to a str with the line content
 */

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1) /* if getline fails */
	{
		_puts("\n");
		free(line);
		exit(EXIT_FAILURE);
	}
	return (line);
}

/**
 * count_token - count tokens in a given input.
 * @line: the string input to split
 * @dlmt: delimiter specify where to cut the input
 * Return: number of tokens.
 */

int count_token(char *line, const char *dlmt)
{
	char *line_cp;
	char *token;
	int i;

	line_cp = _strdup(line);
	if (line_cp == NULL)
		return (-1);
	token = strtok(line_cp, dlmt);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, dlmt);
	free(line_cp);
	return (i);
}

/**
 * parse_line - parse input from the user and make an array of strings
 * @input: the command line input
 * @delimiter: separater where strtok can split the string
 * Return: an array of strings parsed from command line input.
 */

char **parse_line(char *input, const char *delimiter)
{
	char **command_arr;
	char *token;
	char *input_cp;
	int t_count;
	int i = 0;

	t_count = count_token(input, delimiter);
	if (t_count == -1)
	{
		free(input);
		exit(1);
	}
	if (input == NULL)
		return (NULL);
	input_cp = _strdup(input);

	if (input_cp == NULL)
		return (NULL);
	command_arr = malloc((t_count + 1) * sizeof(char *));
	if (!command_arr)
	{
		free(input);
		perror("Allocation fails");
		exit(EXIT_FAILURE);
	}

	token = strtok(input_cp, delimiter);
	while (token)
	{
		if (token[0] == '#')
			break;
		command_arr[i] = _strdup(token);
		token = strtok(NULL, delimiter);
		i++;
	}
	command_arr[i] = NULL;
	free(input_cp);
	return (command_arr);
}


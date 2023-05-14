#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

#define MAX_LINE 1024

/**
  *my_getline() - name of the function that takes no arguments
  *my_getline:a line of text from the input source
  *Return:pointer to a character, which represents a string
  *@void: It means that takes no arguments
  */
char *my_getline(void)
{
	char buf[MAX_LINE];
	int pos = 0;
	int size = 0;

	char *line = NULL;

	while (1)
	{
		if (pos >= size)
		{
			size = read(STDIN_FILENO, buf, MAX_LINE);

			if (size <= 0)
			{
				return (NULL);
			}
			pos = 0;
		}

		if (buf[pos] == '\n')

			buf[pos] = '\0';
			line = malloc(pos + 1);

			if (line == NULL)
			{
				perror("malloc failed");
				exit(EXIT_FAILURE);
			}
			strncpy(line, buf, pos + 1);
			pos++;
			return (line);
			pos++;
	}
}

#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point
 *
 * Return: always 0
 */

int main (void)
{
	char *command;
	size_t command_len = 0;


	for (;;)
	{
		printf("$ ");
		fflush(stdout);
		if (getline(&command, &command_len, stdin) == -1)
		{
			printf("Can't read\n");
			exit (1);
		}
		printf("%s", command);
	}
	return (0);
}

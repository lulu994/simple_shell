#include <stdio.h>


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
		getline(&comman, &command_len, stdin);
		printf("%s", command);
	}
	return (0);
}

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
		getline();
		printf("%s", command);
	}
	return (0);
}

#include "shell.h"

/**
 * print_commands - print elements of an array
 * @cmd: the array
 */
void print_commands(char **cmd)
{
	int i = 0;

	while (cmd[i])
	{
		printf("%s--------\n", cmd[i]);
		i++;
	}
}

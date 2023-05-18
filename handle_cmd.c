#include "shell.h"

/**
  *main - entry point
  *
  *@argc: number of command-line arguments passed to the program
  *@argv: It is an array of strings
  *REturn: always 0
  */
int main(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++)
	{
		int m = 0;

		while (argv[i][m] != '\0')
		{
			write(STDOUT_FILENO, &argv[i][m], 1);
		m++;
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}

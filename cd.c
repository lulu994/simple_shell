#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"

/**
  *cd - changes the working directory using the chdir() system call
  *@path: argument
  *If no argument is given, it uses the HOME environment variablea
  *as the target directory
  *If the argument is -, it uses the OLDPWD environment variable
  *as the target directory and prints it
  */
void cd(char *path)
{
	char *dir;

	if (path == NULL)
	{
		dir = getenv("HOME");
	}
	else if (strcmp(path, "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (dir == NULL)
		{
			perror("No previous directory set.");
			return;
		}
	}
	else
	{
		dir = path;
	}

	if (chdir(dir) != 0)
	{
		perror("chdir() error");
	}
	else
	{
		char cwd[1024];

		if (getcwd(cwd, sizeof(cwd)) == NULL) {
			perror("getcwd() error");
			return;
		}

		if (setenv("OLDPWD", getenv("PWD"), 1) == -1)
		{
			perror("setenv() error");
			return;
		}
		
		if (setenv("PWD", cwd, 1) == -1)
		{
			perror("setenv() error");
			return;
		}
	}
}
/**
  *main - the function entry
  *@argc: integer that represents the number of command-line arguments
  *@argv: an array that hold the command-line arguments
  *Return: you can call cd() with the first command line argument
  *or NULL if no argument is given
  */
int main(int argc, char *argv[])
{

	if (argc == 1)
	{
		cd(NULL);
	}
	else
	{
		cd(argv[1]);
	}
	return (0);
}

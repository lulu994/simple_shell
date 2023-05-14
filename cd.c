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
		printf("%s\n", dir);
	}
	else
	{
		dir = path;
	}

	if (chdir(dir) != 0)
	{
		fprintf(stderr, "cd: %s: No such file or directory\n", dir);
	}
	else
	{
		char cwd[1024];

		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
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

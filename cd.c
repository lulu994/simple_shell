#include "shell.h"

/**
  *cd - changes the current working directory
  *
  @path: argument that represents the directory path to change to
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
		write(STDERR_FILENO, dir, _strlen(dir));
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		dir = path;
	}
	
	if (chdir(dir) != 0)
	{
		char error_message[1024];

		sprintf(error_message, "cd: %s: No such file or directory\n", dir);
		write(STDERR_FILENO, error_message, _strlen(error_message));
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
  * main -  entry point
  * @argc: arg count
  * @argv: arg vector
  * * Return: 0 on success
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

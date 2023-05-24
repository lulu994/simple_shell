#include "shell.h"


/**
 * create_process - create a child process which passed the command execute in
 * @args: array contains the command and its arguments
 * @env: environ variable
 * Return: same as execve.
 */


void create_process(char **args, char *env[])
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror("Execve(): ");
		}
	}
	else if (pid == -1)
	{
		perror("Fork():");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}


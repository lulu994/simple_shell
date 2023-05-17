#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_COMMAND_LENGTH 1024

extern char **environ;

/**
  *prompt - display the current working directory
  *and a $ prompt symbol
  *
  */
void prompt(void)
{
	char cwd[1024];
	
	getcwd(cwd, sizeof(cwd));
	write(STDOUT_FILENO, cwd, strlen(cwd));
	write(STDOUT_FILENO, "$ ", 2);
}
/**
  *execute_command - takes a single argument command
  *to be executed
  *@command: single parameter
  *Return: the function does not return a value
  */
void execute_command(char *command)
{
	char* args[] = {command, NULL};
	if (execve(command, args, environ) == -1)
		 write(STDERR_FILENO, "Error executing command\n", sizeof("Error executing command\n") - 1);
	 exit(1);
}
/**
  *main - entry point
  *
  *Return: 0
  */

int main(void)
{
	char *command = NULL;
	size_t command_len = 0;
	ssize_t read_len;

	for (;;)
	{
		prompt();
		read_len = getline(&command, &command_len, stdin);
		if (read_len <= 0) {
			break;
		}

		if (command[read_len - 1] == '\n')
			command[read_len - 1] = '\0';

		if (strcmp(command, "exit") == 0)
            break;
		execute_command(command);
		prompt();
	}
	free(command);

    return (0);
}

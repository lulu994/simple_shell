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
	char *args[MAX_COMMAND_LENGTH];
	char *token;
	int i = 0;
	token = strtok(command, " \t\n");

	while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    pid_t pid = fork();

    if (pid == 0)
    {
	    execve(args[0], args, environ);
	    exit(1);
    }
    else if (pid < 0) {
		 write(1, "Fork failed.\n", 13);
		 exit(1);
		 } else {
			 int status;
			 waitpid(pid, &status, 0);
			 if (status != 0) {
				   write(1, "Command execution failed.\n", 26);
			 }
		 }
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

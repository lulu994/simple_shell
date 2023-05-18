#include "shell.h"

int main(void) {
    char *command = NULL;
    size_t command_length = 0;
    ssize_t read;

    for (;;) {
         const char *prompt = "$ ";
        write(STDOUT_FILENO, prompt, strlen(prompt));

        read = getline(&command, &command_length, stdin);

        if (read == -1) {
            if (command == NULL) {
                perror("Error reading command");
            } else {
                write(STDOUT_FILENO, "End of file reached\n", 21);
            }
            break;
        }
	pid_t pid = fork();
        
	if (pid == -1) {
            perror("Error forking process");
            continue;
        } else if (pid == 0) {

            char *args[] = {command, NULL};
            execve(command, args, environ);
	    write(STDOUT_FILENO, "Command not found: ", 19);
            write(STDOUT_FILENO, command, strlen(command));
            write(STDOUT_FILENO, "\n", 1);
            _exit(1);
        } else {
		int status;
            waitpid(pid, &status, 0);
	    if (status != 0) {
                write(STDOUT_FILENO, "Command not found: ", 19);
                write(STDOUT_FILENO, command, strlen(command));
                write(STDOUT_FILENO, "\n", 1);
            }
        }
    }

    free(command);

    return 0;
}

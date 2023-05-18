#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int main() {
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
                write(STDOUT_FILENO, "End of file reached. Exiting...\n", 31);
            }
            break;
        }

        // Remove the newline character at the end
        command[strcspn(command, "\n")] = '\0';

        pid_t pid = fork();
        if (pid == -1) {
            perror("Error forking process");
            continue;
        } else if (pid == 0) {
            // Child process
            // Execute the command using execve()
            char *args[] = {command, NULL};
            execve(command, args, environ);

            // If execve returns, there was an error
            write(STDOUT_FILENO, "Command not found: ", 19);
            write(STDOUT_FILENO, command, strlen(command));
            write(STDOUT_FILENO, "\n", 1);
            _exit(1);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            // Check if the child process terminated
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

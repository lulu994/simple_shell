#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>

int main() {
    char *command = "ls";
    char *path = getenv("PATH");

    if (path != NULL) {
        size_t path_max_length = strlen(path);
        char *path_copy = malloc((path_max_length + 1) * sizeof(char));
        strcpy(path_copy, path);

        char *dir = strtok(path_copy, ":");
        while (dir != NULL) {
            size_t command_path_length = strlen(dir) + strlen(command) + 2;
            char *command_path = malloc(command_path_length * sizeof(char));
            strcpy(command_path, dir);
            strcat(command_path, "/");
            strcat(command_path, command);

            if (access(command_path, X_OK) == 0) {
                pid_t pid = fork();
                if (pid == 0) {
                    // Child process
                    char *argv[] = {command_path, NULL};
                    execve(command_path, argv, NULL);
                    perror("execve");
                    _exit(1);
                } else if (pid > 0) {
                    // Parent process
                    int status;
                    waitpid(pid, &status, 0);
                    // Handle child process termination status if needed
                    break;
                } else {
                    perror("fork");
                    exit(1);
                }
            }

            free(command_path);
            dir = strtok(NULL, ":");
        }

        free(path_copy);
    } else {
        write(STDOUT_FILENO, "The PATH variable is not set.\n", 29);
    }

    return 0;
}

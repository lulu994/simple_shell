#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void print_environment() {
    for (char **env = environ; *env != NULL; env++) {
        size_t len = strlen(*env);
        write(STDOUT_FILENO, *env, len);
        write(STDOUT_FILENO, "\n", 1);
    }
}

int main() {
    print_environment();
    return 0;
}

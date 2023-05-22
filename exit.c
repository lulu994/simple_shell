#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void exit_shell() {
    _exit(0);
}

int main() {
    char *input = NULL;
    size_t input_size = 0;
    
    write(STDOUT_FILENO, "Enter a command: ", 17);
    
    while (1) {
        ssize_t bytes_read = getline(&input, &input_size, stdin);
        
        // Remove the trailing newline character
        if (input[bytes_read - 1] == '\n') {
            input[bytes_read - 1] = '\0';
        }
        
        if (strcmp(input, "exit") == 0) {
            exit_shell();
        }
        
        // Process other commands...
        // ...
        
        write(STDOUT_FILENO, "Enter a command: ", 17);
    }
    
    free(input);
    return 0;
}

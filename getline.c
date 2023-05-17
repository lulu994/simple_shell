#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
/**
  *customGetLine - name of the function
  *
  * Rwturn: pointer to a character, which represents a string
  */
char *customGetLine(void)
{
	static char buffer[BUFFER_SIZE];
	static int position = 0;
	static int bufferLength = 0;

	char *line = NULL;

	while (1)
	{
		if (position >= bufferLength)
		{
			bufferLength = read(STDIN_FILENO, buffer, BUFFER_SIZE);

			if (bufferLength <= 0)
			{
				return (NULL);
			}

            position = 0;
        }

	if (buffer[position] == '\n')
	{
		buffer[position] = '\0';
		line = malloc(position + 1);

            if (line == NULL)
            {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
	    strncpy(line, buffer, position + 1);
            position++;
            return (line);
        }
	position++;
    }
}

int main(void)
{
    printf("Enter a line of text: ");

    char *line = customGetLine();

    if (line != NULL)
    {
	    printf("Line: %s\n", line);
	    free(line);
    }
    else
    {
	    printf("No input received.\n");
    }
    return (0);
}

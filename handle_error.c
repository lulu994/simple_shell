#include "shell.h"

/**
 * handle_exec_err - peints error when execve .. fails.
 * @argv: arg vector.
 * @commands: command and its arguments.
 * @cmd_counter: counts thw how much time a command was entered.
 */

void handle_exec_err(char *argv[], char *commands[], int cmd_counter)
{
	_puts(argv[0]);
	_puts(": ");
	print_number(cmd_counter);
	_puts(": ");
	_puts(commands[0]);
	_puts(": not found\n");
}

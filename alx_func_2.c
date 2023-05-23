#include "shell.h"
/**
 * _puts - prints a string
 * @s: string
 * Return: void
 */
void _puts(char *s)
{
	if (*s != '\0')
	{
		_putchar(*s);
		_puts(s + 1);
	}
}

/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: lrngth
 */
int _strlen(char *s)
{
	if (*s != '\0')
		return (1 + _strlen(s + 1));
	else
		return (0);
}

/**
 * free_arr - free array
 * @arr: array to free
 */
void free_arr(char **arr)
{
	int i;

	for (i = 0; arr[i]; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

/**
 * print_number - capitalizes all words of a string.
 * @n: num
 * Return: void
 */

void print_number(int n)
{
	unsigned int n1;

	n1 = n;
	if (n < 0)
	{
		_putchar('-');
		n1 = -n;
	}
	if (n1 / 10)
	{
		print_number(n1 / 10);
	}
	_putchar(n1 % 10 + '0');
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}


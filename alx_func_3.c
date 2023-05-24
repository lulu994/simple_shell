#include "shell.h"

/**
 * _isdigit - checks for a digit
 *@c: num
 * Return: Always 0.
 */

int _isdigit(int c)
{
	if (c <= 57 && c >= 48)
		return (1);
	return (0);
}

/**
 * set_env - sets an environment variable with a value.
 * if it exist it modifies it if not it sets it.
 * @name: name of the variable.
 * @value: the value to set to the var name.
 */

void set_env(char *name, char *value)
{
	int index;
	char *str;
	char **envp = environ;
	int name_len, value_len, len;

	if (!name || !value)
	{
		perror("setenv()");
		return;
	}
	name_len = _strlen(name);
	value_len = _strlen(value);
	len = name_len + value_len + 2;

	str = malloc(len * sizeof(char));
	if (!str)
	{
		perror("Allocations fails");
		return;
	}
	_strcpy(str, name), _strcat(str, "="), _strcat(str, value);
	index = find_path_index(name);
	if (index != -1)
		environ[index] = str;
	else
	{
		while (*envp)
			envp++;
		*envp = str;
		envp++;
		*envp = NULL;
	}
}

/**
 * _atoi - convert a string to an integer
 * @s: str
 * Return: 0 if no number found and number otherwise
 */

int _atoi(char *s)
{
	int i, d, n, len, f, digit;

	i = 0;
	d = 0;
	n = 0;
	len = 0;
	f = 0;
	digit = 0;

	while (s[len] != '\0')
		len++;

	while (i < len && f == 0)
	{
		if (s[i] == '-')
			++d;

		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}
	if (f == 0)
		return (0);

	return (n);
}

/**
 * _isupper - checks for uppercase character
 * @c: char
 * Return: Always 0.
 */

int _isupper(int c)
{
	if (c <= 90 && c >= 65)
		return (1);

	return (0);
}

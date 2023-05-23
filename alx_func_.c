#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if strings match. -1 Otherwise.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	if (_strlen(s1) != _strlen(s2))
		return (-1);
	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	return (0);
}

/**
 * _strdup - create a copy of a string
 * @src: the original string
 * Return: the copy of the string src
 */
char *_strdup(char *src)
{
	int i;
	int len;
	char *dest;

	len = _strlen(src);
	dest = malloc(sizeof(char) * (len + 1));

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * *_strcat - concatenates two strings
 * @dest: destination
 * @src: source
 * Return: a pointer to the resulting string dest
 */

char *_strcat(char *dest, char *src)
{
	char *pt = dest;

	while (*pt != '\0')
	{
		pt++;
	}
	while (*src != '\0')
	{
		*pt++ = *src++;
	}
	*pt++ = '\0';
	return (dest);
}


/**
 * _strcpy - copies the string
 * @dest: ptr
 * @src: ptr too
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i, j;

	i = 0;
	while (src[i])
		i++;

	for (j = 0; j <= i; j++)
	{
		dest[j] = src[j];
	}

	return (dest);
}

/**
 * cd_setenv - sets environment variable name
 * @name: name of the environment variable we need to set
 * @value: the value to assign to the name variable
 */
void cd_setenv(char *name, char *value)
{
	int index;
	char *str;
	int name_len, value_len, len, i = 0;

	if (!name || !value)
	{
		_puts("can't set enpty variable\n");
		return;
	}
	name_len = _strlen(name);
	value_len = _strlen(value);
	len = name_len + value_len + 2;
	if (!name_len || !value_len || ((name_len == 1) && (*name == '=')))
	{
		_puts("can't set enpty variable\n");
		return;
	}
	str = malloc(len * sizeof(char));
	if (!str)
	{
		_puts("Allocations fails");
		return;
	}
	_strcpy(str, name), _strcat(str, "="), _strcat(str, value);
	index = find_path_index(name);
	if (index != -1)
		environ[index] = str;
	else
	{
		while (environ[i])
			i++;
		environ[i] = str;
		environ[++i] = NULL;
	}
}

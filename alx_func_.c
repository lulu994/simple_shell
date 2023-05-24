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

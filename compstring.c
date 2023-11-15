#include "shell.h"

/**
 * _strcpy - A function that copies a string
 * @dest: the destination to go
 * @src: the source available
 *
 * Return: The resultant pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - This function duplicates a string
 * @str: the avaiable string to be duplicated
 *
 * Return: The pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int w = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		w++;
	ret = malloc(sizeof(char) * (w + 1));
	if (!ret)
		return (NULL);
	for (w++; w--;)
		ret[w] = *--str;
	return (ret);
}

/**
 * _puts - This function prints an input string
 * @str: the available string to be printed
 *
 * Return: Nothing or null
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - A function that writes the character c to stdout
 * @c: The character to print out
 *
 * Return: 1 (success) Or error, -1
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

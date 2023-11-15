#include "shell.h"

/**
 * _eputs - A Function that prints an input string
 * @str: the string to be printed exactly
 *
 * Return: Nothing of value
 *
 */
void _eputs(char *str)
{
	int g = 0;

	if (!str)
		return;
	while (str[g] != '\0')
	{
		_eputchar(str[g]);
		g++;
	}
}

/**
 * _eputchar - A function that writes the character c to stderr
 * @c: The character to print
 *
 * Return: 1 (success)
 *
 * On error, -1 is returned or error number
 */
int _eputchar(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 * _putfd - A Function that writes the character c to given fd
 *
 * @c: The character to be printed
 * @fd: The filedescriptor to write to
 *
 * Return: 0 (success)
 * On error, -1 is returned or error value
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - A Function that prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int l = 0;

	if (!str)
		return (0);
	while (*str)
	{
		l += _putfd(*str++, fd);
	}
	return (l);
}

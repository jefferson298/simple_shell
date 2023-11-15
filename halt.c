#include "shell.h"

/**
 **_strncpy - A Function that copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string value
 */
char *_strncpy(char *dest, char *src, int n)
{
	int d, j;
	char *s = dest;

	d = 0;
	while (src[d] != '\0' && d < n - 1)
	{
		dest[d] = src[d];
		d++;
	}
	if (d < n)
	{
		j = d;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - A Function that concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, m;
	char *s = dest;

	i = 0;
	m = 0;
	while (dest[i] != '\0')
		i++;
	while (src[m] != '\0' && m < n)
	{
		dest[i] = src[m];
		i++;
		m++;
	}
	if (m < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - A Funtion that locates a character in a string
 *@s: the given string to be parsed
 *@c: the great character to look for

 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

#include "shell.h"

/**
 * _len - This returns the length of a string
 * @s: the given string whose length to check
 *
 * Return: The integer length of string
 *
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _cmp - This performs lexicogarphic comparison of two strangs.
 * @s1: the first given strang
 * @s2: the second string string
 *
 * Return: negative if the value s1 < s2
 * positive thus if s1 > s2, zero if s1 == s2
 */
int _cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - This checks if needle starts with haystack
 * @haystack: string given to search
 * @needle: the substring needed to be found
 *
 * Return: The address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - This concatenates two strings
 * @dest: the available destination buffer
 * @src: the available source buffer
 *
 * Return: The pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

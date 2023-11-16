#include "shell.h"

/**
 * _strlen - This returns the length of a string
 * @s: the given string whose length to check
 *
 * Return: The resultant integer length of string
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
 * _strcmp - A function that performs
 * lexicogarphic comparison of two strangs.
 * @s1: the first strang available
 * @s2: the second strang available
 *
 * Return: negative if s1 < s2
 * positive if s1 > s2, zero if s1 == s2
 *
 */
int _strcmp(char *s1, char *s2)
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
 * starts_with - This function checks if needle starts with haystack
 * @haystack: The string to be searched
 * @needle: the substring about to be found
 *
 * Return: address of next char of haystack or NULL
 *
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - This function concatenates two strings
 * @dest: the destination buffer resultant
 *
 * @src: the available source buffer
 *
 * Return: A given pointer to destination buffer
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

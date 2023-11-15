#include "shell.h"

/**
 * **strtow - s function splits a string into words
 * @str: the available input string
 *
 * @d: Delimeter string
 * Return: a pointer to an array of strings else null
 */

char **strtow(char *str, char *d)
{
	int f, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (f = 0; str[f] != '\0'; f++)
		if (!is_delim(str[f], d) && (is_delim(str[f + 1], d) || !str[f + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (f = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[f], d))
			f++;
		k = 0;
		while (!is_delim(str[f + k], d) && str[f + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[f++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - a function that breaks a  string into words
 * @str: the input string to be split
 * @d: the delimeter available
 *
 * Return: a pointer to an array of strings else null
 *
 */
char **strtow2(char *str, char d)
{
	int i, j, n, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		n = 0;
		while (str[i + n] != d && str[i + n] && str[i + n] != d)
			n++;
		s[j] = malloc((n + 1) * sizeof(char));
		if (!s[j])
		{
			for (n = 0; n < j; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < n; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

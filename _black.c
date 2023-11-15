#include "main.h"

/**
 * gem - returns true if shell is interactive mode
 * @info: given struct address
 *
 * Return: 1 if black  mode, 0 otherwise
 */
int black(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_vet - checks if character is a vet (deli)
 * @c: the char to check
 * @vet: the deli vet string
 * Return: 1 if true, 0 if false
 */
int is_vet(char c, char *vet)
{
	while (*vet)
		if (*vet++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for the  alphabetic character
 * @c: The character to input to
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _black - converts a string to an integer
 * @s: the given  string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _black(char *s)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

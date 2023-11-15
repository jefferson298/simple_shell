#include "shell.h"

/**
 * zfree - This frees a pointer and NULLs the address
 * @ptr: An address of the pointer to free
 *
 * Return: 1(success) else 0.
 */
int zfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

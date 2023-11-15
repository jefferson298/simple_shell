#include "shell.h"

/**
 * _comp - This prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _comp(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - This gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value required
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - This Initialize a new environment variable.
 * @info: containing potential argument.
 *  Return: 0 (success)
 *
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _rmcomp - Remove an environment variable
 * @info: Structure containing potential argument.
 * Return: Always 0
 */
int _rmcomp(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);

	return (0);
}

/**
 * incrementlist - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0 (success)
 */
int incrementlist(info_t *info)
{
	list_t *node = NULL;
	size_t g;

	for (g = 0; environ[g]; g++)
		add_node_end(&node, environ[g], 0);
	info->env = node;
	return (0);
}

#include "shell.h"

/**
 * _valin - displays the history list
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _valin(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_altern - sets alternative name to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_altern(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_altern - sets altern to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_altern(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_altern(info, str));

	unset_altern(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_altern - prints an altern string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_altern(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _altern - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _altern(info_t *info)
{
	int g = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_altern(node);
			node = node->next;
		}
		return (0);
	}
	for (g = 1; info->argv[g]; g++)
	{
		p = _strchr(info->argv[g], '=');
		if (p)
			set_altern(info, info->argv[g]);
		else
			print_altern(node_starts_with(info->alias, info->argv[g], '='));
	}

	return (0);
}

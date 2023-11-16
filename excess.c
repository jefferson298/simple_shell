#include "shell.h"

/**
 * is_chain - This function will test
 * if current char in buffer is a chain delimeter
 * @info: the parameter struct given
 * @buf: the required char buffer
 * @p: The address of the current position in buf
 *
 * Return: 1 (success)else 0
 *
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t w = *p;

	if (buf[w] == '|' && buf[w + 1] == '|')
	{
		buf[w] = 0;
		w++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[w] == '&' && buf[w + 1] == '&')
	{
		buf[w] = 0;
		w++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[w] == ';') /* found end of this command */
	{
		buf[w] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = w;
	return (1);
}

/**
 * check_chain - This function checks if to continue chaining
 * @info: the available parameter struct
 * @buf: the given char buffer
 * @p: The available address of current position in buf
 * @i: buf atarter position
 * @len: buf length
 *
 * Return: Void (success)
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t q = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			q = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			q = len;
		}
	}

	*p = q;
}

/**
 * nick - This function replaces the  aliases in the token string
 * @info: the parameter struct
 *
 * Return: 1 if replaced else 0
 */
int nick(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * nickies - This function replaces vars in the token string
 * @info: the parameter struct given
 *
 * Return: 1 else 0
 *
 */
int nickies(info_t *info)
{
	int g = 0;
	list_t *node;

	for (g = 0; info->argv[g]; g++)
	{
		if (info->argv[g][0] != '$' || !info->argv[g][1])
			continue;

		if (!_strcmp(info->argv[g], "$?"))
		{
			val_strings(&(info->argv[g]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[g], "$$"))
		{
			val_strings(&(info->argv[g]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[g][1], '=');
		if (node)
		{
			val_strings(&(info->argv[g]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		val_strings(&info->argv[g], _strdup(""));

	}
	return (0);
}

/**
 * val_string - This function replaces string
 *
 * @old: The given address of old string
 * @new: new string given
 *
 * Return: 1 (success) else 0
 */
int val_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

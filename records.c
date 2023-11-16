#include "shell.h"

/**
 * get_history_file - A Function that gets the history file
 * @info: parameter struct
 *
 * Return: allocated string file content
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * crt_records -This  creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 *
 */
int crt_records(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * call_records - Function that reads history from file
 *
 * @info: the parameter struct
 *
 * Return: record count on success, 0 otherwise
 */
int call_records(info_t *info)
{
	int d, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (d = 0; d < fsize; d++)
		if (buf[d] == '\n')
		{
			buf[d] = 0;
			pull_records_list(info, buf + last, linecount++);
			last = d + 1;
		}
	if (last != d)
		pull_records_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	makeover_records(info);
	return (info->histcount);
}

/**
 * pull_records_list - A Function that adds an entry
 * to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: 0 (success)
 */
int pull_records_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * makeover_records - Gives a new numbering to
 * the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new numbering
 */
int makeover_records(info_t *info)
{
	list_t *node = info->history;
	int m = 0;

	while (node)
	{
		node->num = m++;
		node = node->next;
	}
	return (info->histcount = m);
}

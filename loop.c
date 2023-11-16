#include "shell.h"

/**
 * hsh - The main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int ret = 0;

	while (r != -1 && ret != -2)
	{
		clear_info(info);
		if (gem(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			ret = find_builtin(info);
			if (ret == -1)
				find_cmd(info);
		}
		else if (gem(info))
			_putchar('\n');
		free_info(info, 0);
	}
	crt_records(info);
	free_info(info, 1);
	if (!gem(info) && info->status)
		exit(info->status);
	if (ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (ret);
}

/**
 * find_builtin - This finds a builtin command
 * @info: the parameter or  & return info struc given
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int k, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _cloz},
		{"env", _comp},
		{"help", _recov},
		{"history", _valin},
		{"setenv", _mysetenv},
		{"unsetenv", _rmcomp},
		{"cd", _vec},
		{"alias", _altern},
		{NULL, NULL}
	};

	for (k = 0; builtintbl[k].type; k++)
		if (_strcmp(info->argv[0], builtintbl[k].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[k].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - This finds a command in PATH
 * @info: the parameter & return info struct given
 *
 * Return: void
 *
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, y = 0; info->arg[i]; i++)
		if (!is_vet(info->arg[i], " \t\n"))
			y++;
	if (!y)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((gem(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && prompt_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - This forks a an exec thread to run cmd
 * @info: the given parameter & return info struct given
 *
 * Return: void or null
 *
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

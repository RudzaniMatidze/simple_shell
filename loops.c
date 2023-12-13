#include "main.h"

/**
 * hsh - main func of shell loop
 * @inform: parameter & return struct info
 * @arv: argument vector from main func
 * Return: 0 if success, 1 if error, or error code
 */
int hsh(info_t *inform, char **arv)
{
	ssize_t rd = 0;
	int bltin_ret = 0;

	while (rd != -1 && bltin_ret != -2)
	{
		clear_infor(inform);
		if (inter_active(inform))
			_puts("$ ");
		eputchar(BUF_FLUSH);
		rd = get_inp(inform);
		if (rd != -1)
		{
			set_infor(inform, arv);
			bltin_ret = find_bltin(inform);
			if (bltin_ret == -1)
				find_cmmd(inform);
		}
		else if (inter_active(inform))
			_putchar('\n');
		free_infor(inform, 0);
	}
	write_hist(inform);
	free_infor(inform, 1);
	if (!inter_active(inform) && inform->status)
		exit(inform->status);
	if (bltin_ret == -2)
	{
		if (inform->err_no == -1)
			exit(inform->status);
		exit(inform->err_no);
	}
	return (bltin_ret);
}

/**
 * find_bltin - find builtin command
 * @inform: parameter & return struct info
 * Return: -1 if builtin is not found,
 * -2 if builtin signals exit(),
 * 0 if builtin is executed successfully,
 * 1 if builtin is found but not successful
 */
int find_bltin(info_t *inform)
{
	int a, blt_in_ret = -1;
	builtin_table bltintbl[] = {
		{"exit", my_exit},
		{"env", my_environ},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cdr},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (a = 0; bltintbl[a].type; a++)
		if (str_cmp(inform->argv[0], bltintbl[a].type) == 0)
		{
			inform->line_count++;
			blt_in_ret = bltintbl[a].func(inform);
			break;
		}
	return (blt_in_ret);
}

/**
 * find_cmmd - finds command in path
 * @inform: parameter & return struct info
 * Return: void
 */
void find_cmmd(info_t *inform)
{
	char *pth = NULL;
	int a, b;

	inform->path = inform->argv[0];
	if (inform->linecount_flag == 1)
	{
		inform->line_count++;
		inform->linecount_flag = 0;
	}
	for (a = 0, b = 0; inform->arg[a]; a++)
		if (!is_delimiter(inform->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	pth = find_pth(inform, get_env(inform, "PATH="), inform->argv[0]);
	if (pth)
	{
		inform->path = pth;
		fork_cmmd(inform);
	}
	else
	{
		if ((inter_active(inform) || get_env(inform, "PATH=")
			|| inform->argv[0][0] == '/') && is_cmmd(inform, inform->argv[0]))
			fork_cmmd(inform);
		else if (*(inform->arg) != '\n')
		{
			inform->status = 127;
			prints_error(inform, "not found\n");
		}
	}
}

/**
 * fork_cmmd - forks an execu thread to run cmd
 * @inform: parameter & return struct info
 * Return: void
 */
void fork_cmmd(info_t *inform)
{
	pid_t chld_pid;

	chld_pid = fork();
	if (chld_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (chld_pid == 0)
	{
		if (execve(inform->path, inform->argv, get_envi(inform)) == -1)
		{
			free_infor(inform, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inform->status));
		if (WIFEXITED(inform->status))
		{
			inform->status = WEXITSTATUS(inform->status);
			if (inform->status == 126)
				prints_error(inform, "Permission denied\n");
		}
	}
}

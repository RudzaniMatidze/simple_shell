#include "main.h"

/**
 * clear_infor - initializes info_t struct
 * @inform: struct address
 */
void clear_infor(info_t *inform)
{
	inform->arg = NULL;
	inform->argv = NULL;
	inform->path = NULL;
	inform->argc = 0;
}

/**
 * set_infor - initializes info_t struct
 * @inform: struct address
 * @arv: argument vector
 */
void set_infor(info_t *inform, char **arv)
{
	int a = 0;

	inform->fname = arv[0];
	if (inform->arg)
	{
		inform->argv = split(inform->arg, " \t");
		if (!inform->argv)
		{

			inform->argv = malloc(sizeof(char *) * 2);
			if (inform->argv)
			{
				inform->argv[0] = str_dup(inform->arg);
				inform->argv[1] = NULL;
			}
		}
		for (a = 0; inform->argv && inform->argv[a]; a++)
			;
		inform->argc = a;

		repl_alias(inform);
		repl_variable(inform);
	}
}

/**
 * free_infor - frees info_t struct field
 * @inform: struct address
 * @allc: true if frees all fields
 */
void free_infor(info_t *inform, int allc)
{
	free_string(inform->argv);
	inform->argv = NULL;
	inform->path = NULL;
	if (allc)
	{
		if (!inform->cmd_buf)
			free(inform->arg);
		if (inform->env)
			frees_list(&(inform->env));
		if (inform->history)
			frees_list(&(inform->history));
		if (inform->alias)
			frees_list(&(inform->alias));
		free_string(inform->environ);
			inform->environ = NULL;
		free_memory((void **)inform->cmd_buf);
		if (inform->readfd > 2)
			close(inform->readfd);
		_putchar(BUF_FLUSH);
	}
}

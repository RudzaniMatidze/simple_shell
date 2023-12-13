#include "main.h"

/**
 * is_chains - test if current char in buffer is chain delim
 * @inform: parameter struct
 * @buffr: char buffer
 * @pos: address of current position in buffer
 * Return: 1 if chain delimeter, 0 if not
 */
int is_chains(info_t *inform, char *buffr, size_t *pos)
{
	size_t a = *pos;

	if (buffr[a] == '|' && buffr[a + 1] == '|')
	{
		buffr[a] = 0;
		a++;
		inform->cmd_buf_type = CMD_OR;
	}
	else if (buffr[a] == '&' && buffr[a + 1] == '&')
	{
		buffr[a] = 0;
		a++;
		inform->cmd_buf_type = CMD_AND;
	}
	else if (buffr[a] == ';')
	{
		buffr[a] = 0;
		inform->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = a;
	return (1);
}

/**
 * check_chains - checks if to continue chaining based on last status
 * @inform: parameter struct
 * @buffr: char buffer
 * @pos: address of current position in buffer
 * @a: starting position in buffer
 * @len: length of buf
 * Return: Void
 */
void check_chains(info_t *inform, char *buffr,
		size_t *pos, size_t a, size_t len)
{
	size_t b = *pos;

	if (inform->cmd_buf_type == CMD_AND)
	{
		if (inform->status)
		{
			buffr[a] = 0;
			b = len;
		}
	}
	if (inform->cmd_buf_type == CMD_OR)
	{
		if (!inform->status)
		{
			buffr[a] = 0;
			b = len;
		}
	}

	*pos = b;
}

/**
 * repl_alias - replaces an alias in the tokenized string
 * @inform: parameter struct
 * Return: 1 if replaced, 0 if not
 */
int repl_alias(info_t *inform)
{
	int a;
	list_t *nodes;
	char *pos;

	for (a = 0; a < 10; a++)
	{
		nodes = nodes_starts_wth(inform->alias, inform->argv[0], '=');
		if (!nodes)
			return (0);
		free(inform->argv[0]);
		pos = strchr(nodes->str, '=');
		if (!pos)
			return (0);
		pos = str_dup(pos + 1);
		if (!pos)
			return (0);
		inform->argv[0] = pos;
	}
	return (1);
}

/**
 * repl_variable - replaces variable in tokenized string
 * @inform: parameter struct
 * Return: 1 if replaced, 0 if not
 */
int repl_variable(info_t *inform)
{
	int a = 0;
	list_t *nodes;

	for (a = 0; inform->argv[a]; a++)
	{
		if (inform->argv[a][0] != '$' || !inform->argv[a][1])
			continue;

		if (!str_cmp(inform->argv[a], "$?"))
		{
			repl_string(&(inform->argv[a]),
				str_dup(convert_num(inform->status, 10, 0)));
			continue;
		}
		if (!str_cmp(inform->argv[a], "$$"))
		{
			repl_string(&(inform->argv[a]),
				str_dup(convert_num(getpid(), 10, 0)));
			continue;
		}
		nodes = nodes_starts_wth(inform->env, &inform->argv[a][1], '=');
		if (nodes)
		{
			repl_string(&(inform->argv[a]),
				str_dup(strchr(nodes->str, '=') + 1));
			continue;
		}
		repl_string(&inform->argv[a], str_dup(""));

	}
	return (0);
}

/**
 * repl_string - replaces string
 * @older: address of old string
 * @newer: new string
 * Return: 1 if replaced, 0 if not
 */
int repl_string(char **older, char *newer)
{
	free(*older);
	*older = newer;
	return (1);
}

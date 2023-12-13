#include "main.h"

/**
 * my_history - displays the history list, one cmd by line, preceded
 * with line num, starting at 0.
 * @inform: contains potential argument.
 * Return: Always 0 (success)
 */
int my_history(info_t *inform)
{
	prints_lists(inform->history);
	return (0);
}

/**
 * _unset_alias - sets alias to string
 * @inform: parameter struct
 * @st: string alias
 * Return: Always 0 on success, 1 if not
 */
int _unset_alias(info_t *inform, char *st)
{
	char *pos, ch;
	int rets;

	pos = string_chr(st, '=');
	if (!pos)
		return (1);
	ch = *pos;
	*pos = 0;
	rets = deletes_node_index(&(inform->alias),
		get_node_indexes(inform->alias, nodes_starts_wth(inform->alias, st, -1)));
	*pos = ch;
	return (rets);
}

/**
 * _set_alias - sets alias to a string
 * @inform: parameter struct
 * @st: string alias
 * Return: Always 0 on success, 1 if not
 */
int _set_alias(info_t *inform, char *st)
{
	char *pos;

	pos = string_chr(st, '=');
	if (!pos)
		return (1);
	if (!*++pos)
		return (_unset_alias(inform, st));

	_unset_alias(inform, st);
	return (adds_node_end(&(inform->alias), st, 0) == NULL);
}

/**
 * _print_alias - prints alias string
 * @nodes: alias node
 * Return: Always 0 on success, 1 if not
 */
int _print_alias(list_t *nodes)
{
	char *pos = NULL, *n = NULL;

	if (nodes)
	{
		pos = string_chr(nodes->str, '=');
		for (n = nodes->str; n <= pos; n++)
			_putchar(*n);
		_putchar('\'');
		_puts(pos + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics builtin alias (man alias)
 * @inform: contains potential arguments.
 *  Return: Always 0 (success)
 */
int my_alias(info_t *inform)
{
	int a = 0;
	char *pos = NULL;
	list_t *nodes = NULL;

	if (inform->argc == 1)
	{
		nodes = inform->alias;
		while (nodes)
		{
			_print_alias(nodes);
			nodes = nodes->next;
		}
		return (0);
	}
	for (a = 1; inform->argv[a]; a++)
	{
		pos = string_chr(inform->argv[a], '=');
		if (pos)
			_set_alias(inform, inform->argv[a]);
		else
			_print_alias(nodes_starts_wth(inform->alias, inform->argv[a], '='));
	}

	return (0);
}

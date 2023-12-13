#include "main.h"

/**
 * list_length - determines len of linked list
 * @hptr: pointer head
 * Return: size of lists
 */
size_t list_length(const list_t *hptr)
{
	size_t a = 0;

	while (hptr)
	{
		hptr = hptr->next;
		a++;
	}
	return (a);
}

/**
 * list_arr_strings - an array of strings of the list->str
 * @hptr: ptr to first node
 * Return: array of string
 */
char **list_arr_strings(list_t *hptr)
{
	list_t *nodes = hptr;
	size_t a = list_length(hptr), b;
	char **string;
	char *st;

	if (!hptr || !a)
		return (NULL);
	string = malloc(sizeof(char *) * (a + 1));
	if (!string)
		return (NULL);
	for (a = 0; nodes; nodes = nodes->next, a++)
	{
		st = malloc(str_len(nodes->str) + 1);
		if (!st)
		{
			for (b = 0; b < a; b++)
				free(string[b]);
			free(string);
			return (NULL);
		}

		st = str_cpy(st, nodes->str);
		string[a] = st;
	}
	string[a] = NULL;
	return (string);
}

/**
 * prints_lists - prints elements of list_t linked list
 * @hptr: ptr to first node
 * Return: size of lists
 */
size_t prints_lists(const list_t *hptr)
{
	size_t a = 0;

	while (hptr)
	{
		_puts(convert_num(hptr->no, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hptr->str ? hptr->str : "(nil)");
		_puts("\n");
		hptr = hptr->next;
		a++;
	}
	return (a);
}

/**
 * nodes_starts_wth - node with a string starts with prefix
 * @nodes: ptr to list head
 * @prfx: string that match
 * @ch: next char after prefix to match
 * Return: match node, or null
 */
list_t *nodes_starts_wth(list_t *nodes, char *prfx, char ch)
{
	char *pt = NULL;

	while (nodes)
	{
		pt = starts_wth(nodes->str, prfx);
		if (pt && ((ch == -1) || (*pt == ch)))
			return (nodes);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * get_node_indexes - gets node index
 * @hptr: pntr to list head
 * @nodes: ptr to the node
 * Return: index of node, -1 if not
 */
ssize_t get_node_indexes(list_t *hptr, list_t *nodes)
{
	size_t a = 0;

	while (hptr)
	{
		if (hptr == nodes)
			return (a);
		hptr = hptr->next;
		a++;
	}
	return (-1);
}

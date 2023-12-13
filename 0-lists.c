#include "main.h"

/**
 * adds_node - adds node to the beginning of list
 * @hd: address of ptr to head node
 * @st: string field of node
 * @numb: index node used by history
 * Return: size of lists
 */
list_t *adds_node(list_t **hd, const char *st, int numb)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->no = numb;
	if (st)
	{
		new_hd->str = str_dup(st);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *hd;
	*hd = new_hd;
	return (new_hd);
}

/**
 * adds_node_end - adds node to end of list
 * @hd: address of ptr to head node
 * @st: string field of node
 * @numb: index node used by history
 * Return: size of lists
 */
list_t *adds_node_end(list_t **hd, const char *st, int numb)
{
	list_t *new_nodes, *nodes;

	if (!hd)
		return (NULL);

	nodes = *hd;
	new_nodes = malloc(sizeof(list_t));
	if (!new_nodes)
		return (NULL);
	_memset((void *)new_nodes, 0, sizeof(list_t));
	new_nodes->no = numb;
	if (st)
	{
		new_nodes->str = str_dup(st);
		if (!new_nodes->str)
		{
			free(new_nodes);
			return (NULL);
		}
	}
	if (nodes)
	{
		while (nodes->next)
			nodes = nodes->next;
		nodes->next = new_nodes;
	}
	else
		*hd = new_nodes;
	return (new_nodes);
}

/**
 * prints_list_str - prints str element of a list_t linked list
 * @hp: ptr to first node
 * Return: size of lists
 */
size_t prints_list_str(const list_t *hp)
{
	size_t a = 0;

	while (hp)
	{
		_puts(hp->str ? hp->str : "(nil)");
		_puts("\n");
		hp = hp->next;
		a++;
	}
	return (a);
}

/**
 * deletes_node_index - deletes node at index
 * @hd: address of ptr to first node
 * @start: index node to delete
 * Return: 1 if success, 0 if not
 */
int deletes_node_index(list_t **hd, unsigned int start)
{
	list_t *nodes, *prev_nodes;
	unsigned int a = 0;

	if (!hd || !*hd)
		return (0);

	if (!start)
	{
		nodes = *hd;
		*hd = (*hd)->next;
		free(nodes->str);
		free(nodes);
		return (1);
	}
	nodes = *hd;
	while (nodes)
	{
		if (a == start)
		{
			prev_nodes->next = nodes->next;
			free(nodes->str);
			free(nodes);
			return (1);
		}
		a++;
		prev_nodes = nodes;
		nodes = nodes->next;
	}
	return (0);
}

/**
 * frees_list - frees all list nodes
 * @hd_ptr: address of ptr to head node
 * Return: void
 */
void frees_list(list_t **hd_ptr)
{
	list_t *nodes, *next_nodes, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	nodes = hd;
	while (nodes)
	{
		next_nodes = nodes->next;
		free(nodes->str);
		free(nodes);
		nodes = next_nodes;
	}
	*hd_ptr = NULL;
}

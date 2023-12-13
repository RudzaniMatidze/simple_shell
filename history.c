#include "main.h"

/**
 * get_hist_file - gets history file
 * @inform: parameter struct
 * Return: allocated string containg history file
 */

char *get_hist_file(info_t *inform)
{
	char *buffr, *direct;

	direct = get_env(inform, "HOME=");
	if (!direct)
		return (NULL);
	buffr = malloc(sizeof(char) * (str_len(direct) + str_len(HIST_FILE) + 2));
	if (!buffr)
		return (NULL);
	buffr[0] = 0;
	str_cpy(buffr, direct);
	str_cat(buffr, "/");
	str_cat(buffr, HIST_FILE);
	return (buffr);
}

/**
 * write_hist - creates file, or appends existing file
 * @inform: parameter struct
 * Return: 1 on success, -1 if not
 */
int write_hist(info_t *inform)
{
	ssize_t fd;
	char *filename = get_hist_file(inform);
	list_t *nodes = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nodes = inform->history; nodes; nodes = nodes->next)
	{
		putsfld(nodes->str, fd);
		putfd('\n', fd);
	}
	putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - reads history from file
 * @inform: parameter struct
 * Return: histcount on success, 0 if not
 */
int read_hist(info_t *inform)
{
	int a, lastt = 0, linecnt = 0;
	ssize_t fd, readlen, filesize = 0;
	struct stat st;
	char *buffr = NULL, *filename = get_hist_file(inform);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buffr = malloc(sizeof(char) * (filesize + 1));
	if (!buffr)
		return (0);
	readlen = read(fd, buffr, filesize);
	buffr[filesize] = 0;
	if (readlen <= 0)
		return (free(buffr), 0);
	close(fd);
	for (a = 0; a < filesize; a++)
		if (buffr[a] == '\n')
		{
			buffr[a] = 0;
			build_hist_list(inform, buffr + lastt, linecnt++);
			lastt = a + 1;
		}
	if (lastt != a)
		build_hist_list(inform, buffr + lastt, linecnt++);
	free(buffr);
	inform->histcount = linecnt;
	while (inform->histcount-- >= HIST_MAX)
		deletes_node_index(&(inform->history), 0);
	re_number_hist(inform);
	return (inform->histcount);
}

/**
 * build_hist_list - adds entry to a history linked list
 * @inform: Structure containing potential arguments.
 * @buffr: buffer
 * @linecnt: history linecount,
 * Return: Always 0 (success)
 */
int build_hist_list(info_t *inform, char *buffr, int linecnt)
{
	list_t *nodes = NULL;

	if (inform->history)
		nodes = inform->history;
	adds_node_end(&nodes, buffr, linecnt);

	if (!inform->history)
		inform->history = nodes;
	return (0);
}

/**
 * re_number_hist - renumbers history linked list after changes
 * @inform: structure containing potential arguments
 * Return: new histcnt
 */
int re_number_hist(info_t *inform)
{
	list_t *nodes = inform->history;
	int a = 0;

	while (nodes)
	{
		nodes->no = a++;
		nodes = nodes->next;
	}
	return (inform->histcount = a);
}

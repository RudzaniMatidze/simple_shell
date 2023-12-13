#include "main.h"

/**
 * is_cmmd -checks if a file is an executable command
 * @inform: information struct
 * @pth: path to file
 * Return: 1 if true, 0 if not
 */
int is_cmmd(info_t *inform, char *pth)
{
	struct stat sst;

	(void)inform;
	if (!pth || stat(pth, &sst))
		return (0);

	if (sst.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupl_chars - duplicates char
 * @pthstr: path string
 * @strt: start index
 * @stp: stop index
 * Return: pointer to new buffer
 */
char *dupl_chars(char *pthstr, int strt, int stp)
{
	static char buffr[1024];
	int a = 0, b = 0;

	for (b = 0, a = strt; a < stp; a++)
		if (pthstr[a] != ':')
			buffr[b++] = pthstr[a];
	buffr[b] = 0;
	return (buffr);
}

/**
 * find_pth - finds command in the PATH string
 * @inform: information struct
 * @pthstr: PATH string
 * @cmmd: command to find
 * Return: full path of cmd or NULL if not found
 */
char *find_pth(info_t *inform, char *pthstr, char *cmmd)
{
	int a = 0, cu_pos = 0;
	char *pth;

	if (!pthstr)
		return (NULL);
	if ((str_len(cmmd) > 2) && starts_wth(cmmd, "./"))
	{
		if (is_cmmd(inform, cmmd))
			return (cmmd);
	}
	while (1)
	{
		if (!pthstr[a] || pthstr[a] == ':')
		{
			pth = dupl_chars(pthstr, cu_pos, a);
			if (!*pth)
				str_cat(pth, cmmd);
			else
			{
				str_cat(pth, "/");
				str_cat(pth, cmmd);
			}
			if (is_cmmd(inform, pth))
				return (pth);
			if (!pthstr[a])
				break;
			cu_pos = a;
		}
		a++;
	}
	return (NULL);
}

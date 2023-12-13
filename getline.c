#include "main.h"

/**
 * input_buffr - buffer chain commands
 * @inform: parameter struct
 * @buffr: address of buffer
 * @len: address of lenght var
 * Return: byte read
 */
ssize_t input_buffr(info_t *inform, char **buffr, size_t *len)
{
	ssize_t rd = 0;
	size_t len_pt = 0;

	if (!*len)
	{
		free(*buffr);
		*buffr = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		rd = getline(buffr, &len_pt, stdin);
#else
		rd = get_line(inform, buffr, &len_pt);
#endif
		if (rd > 0)
		{
			if ((*buffr)[rd - 1] == '\n')
			{
				(*buffr)[rd - 1] = '\0';
				rd--;
			}
			inform->linecount_flag = 1;
			rem_comments(*buffr);
			build_hist_list(inform, *buffr, inform->histcount++);
			{
				*len = rd;
				inform->cmd_buf = buffr;
			}
		}
	}
	return (rd);
}

/**
 * get_inp - gets line minus newline
 * @inform: parameter struct
 * Return: bytes read
 */
ssize_t get_inp(info_t *inform)
{
	static char *buffr;
	static size_t a, b, len;
	ssize_t rd = 0;
	char **buffr_p = &(inform->arg), *pt;

	_putchar(BUF_FLUSH);
	rd = input_buffr(inform, &buffr, &len);
	if (rd == -1)
		return (-1);
	if (len)
	{
		b = a;
		pt = buffr + a;

		check_chains(inform, buffr, &b, a, len);
		while (b < len)
		{
			if (is_chains(inform, buffr, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			inform->cmd_buf_type = CMD_NORM;
		}

		*buffr_p = pt;
		return (str_len(pt));
	}

	*buffr_p = buffr;
	return (rd);
}

/**
 * read_buffr - reads a buffer
 * @inform: parameter struct
 * @buffr: buffer
 * @a: size of buffer
 * Return: rd
 */
ssize_t read_buffr(info_t *inform, char *buffr, size_t *a)
{
	ssize_t rd = 0;

	if (*a)
		return (0);
	rd = read(inform->readfd, buffr, READ_BUF_SIZE);
	if (rd >= 0)
		*a = rd;
	return (rd);
}

/**
 * get_line - gets next line of input from STDIN
 * @inform: parameter struct
 * @pts: address of ptr to buffer, pre-allocated or NULL
 * @lngth: size of pre-allocated ptr buffer if not NULL
 * Return: st
 */
int get_line(info_t *inform, char **pts, size_t *lngth)
{
	static char buffr[READ_BUF_SIZE];
	static size_t a, ln;
	size_t b;
	ssize_t rd = 0, st = 0;
	char *pt = NULL, *new_pt = NULL, *ch;

	pt = *pts;
	if (pt && lngth)
		st = *lngth;
	if (a == ln)
		a = ln = 0;

	rd = read_buffr(inform, buffr, &ln);
	if (rd == -1 || (rd == 0 && ln == 0))
		return (-1);

	ch = string_chr(buffr + a, '\n');
	b = ch ? 1 + (unsigned int)(ch - buffr) : ln;
	new_pt = real_loc(pt, st, st ? st + b : b + 1);
	if (!new_pt)
		return (pt ? free(pt), -1 : -1);

	if (st)
		string_cat(new_pt, buffr + a, b - a);
	else
		string_cpy(new_pt, buffr + a, b - a + 1);

	st += b - a;
	a = b;
	pt = new_pt;

	if (lngth)
		*lngth = st;
	*pts = pt;
	return (st);
}

/**
 * sigint_handler - blocks ctrl-C
 * @sig_no: signal number
 * Return: void
 */
void sigint_handler(__attribute__((unused))int sig_no)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

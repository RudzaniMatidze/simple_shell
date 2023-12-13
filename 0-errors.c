#include "main.h"

/**
 *eputs - prints input string
 * @st: string to be printed
 * Return: Nothing
 */
void eputs(char *st)
{
	int a = 0;

	if (!st)
		return;
	while (st[a] != '\0')
	{
		eputchar(st[a]);
		a++;
	}
}

/**
 * eputchar - writes the char ch to stderr
 * @ch: character to print
 * Return: On success 1.
 * if error, -1 is returned, and errno is set appropriately.
 */
int eputchar(char ch)
{
	static int a;
	static char buffr[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buffr, a);
		a = 0;
	}
	if (ch != BUF_FLUSH)
		buffr[a++] = ch;
	return (1);
}

/**
 * putfd - writes the char ch to given fd
 * @ch: character to print
 * @fld: filedescriptor to write to
 * Return: On success 1.
 * if error, -1 is returned, and errno is set appropriately.
 */
int putfd(char ch, int fld)
{
	static int a;
	static char buffr[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fld, buffr, a);
		a = 0;
	}
	if (ch != BUF_FLUSH)
		buffr[a++] = ch;
	return (1);
}

/**
 * putsfld - prints input string
 * @st: string to be printed
 * @fld: filedescriptor to write to
 * Return: number of chars put
 */
int putsfld(char *st, int fld)
{
	int a = 0;

	if (!st)
		return (0);
	while (*st)
	{
		a += putfd(*st++, fld);
	}
	return (a);
}

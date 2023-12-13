#include "main.h"

/**
 * str_cpy - copies string
 * @des: string destination
 * @srd: source destination
 * Return: ptr to destination
 */
char *str_cpy(char *des, char *srd)
{
	int a = 0;

	if (des == srd || srd == 0)
		return (des);
	while (srd[a])
	{
		des[a] = srd[a];
		a++;
	}
	des[a] = 0;
	return (des);
}

/**
 * str_dup - duplicates string
 * @st: string to be duplicated
 * Return: ptr to the duplicated string
 */
char *str_dup(const char *st)
{
	int lngth = 0;
	char *rets;

	if (st == NULL)
		return (NULL);
	while (*st++)
		lngth++;
	rets = malloc(sizeof(char) * (lngth + 1));
	if (!rets)
		return (NULL);
	for (lngth++; lngth--;)
		rets[lngth] = *--st;
	return (rets);
}

/**
 *_puts - prints string input
 *@st: string to print
 * Return: void
 */
void _puts(char *st)
{
	int a = 0;

	if (!st)
		return;
	while (st[a] != '\0')
	{
		_putchar(st[a]);
		a++;
	}
}

/**
 * _putchar - writes the char ch to stdout
 * @ch: char to be printed
 * Return: if success 1. if error, return -1,
 * and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int a;
	static char buffr[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buffr, a);
		a = 0;
	}
	if (ch != BUF_FLUSH)
		buffr[a++] = ch;
	return (1);
}

#include "main.h"

/**
 * _memset - adds memory with a constant byte
 * @st: pointer to the memory area
 * @byte: byte to fill *st
 * @am: amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *st, char byte, unsigned int am)
{
	unsigned int a;

	for (a = 0; a < am; a++)
		st[a] = byte;
	return (st);
}

/**
 * free_string - frees string of strings
 * @pstr: string of strings
 */
void free_string(char **pstr)
{
	char **k = pstr;

	if (!pstr)
		return;
	while (*pstr)
		free(*pstr++);
	free(k);
}

/**
 * real_loc - locates a real block of memory
 * @pntr: pointer to prev malloc'ated block
 * @old_sz: byte size of prev block
 * @new_sz: byte size of new block
 * Return: pointer to prev block name.
 */
void *real_loc(void *pntr, unsigned int old_sz, unsigned int new_sz)
{
	char *st;

	if (!pntr)
		return (malloc(new_sz));
	if (!new_sz)
		return (free(pntr), NULL);
	if (new_sz == old_sz)
		return (pntr);

	st = malloc(new_sz);
	if (!st)
		return (NULL);

	old_sz = old_sz < new_sz ? old_sz : new_sz;
	while (old_sz--)
		st[old_sz] = ((char *)pntr)[old_sz];
	free(pntr);
	return (st);
}

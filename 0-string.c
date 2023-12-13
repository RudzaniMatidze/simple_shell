#include "main.h"

/**
 * str_len - returns length of a string
 * @st: string length to check
 * Return: integer len of string
 */
int str_len(char *st)
{
	int a = 0;

	if (!st)
		return (0);

	while (*st++)
		a++;
	return (a);
}

/**
 * str_cmp - lexicogarphic comparison of two strangs.
 * @st1: first string
 * @st2: second string
 * Return: negative if st1 < st2,
 * positive if st1 > st2, 0 if st1 == st2
 */
int str_cmp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * starts_wth - checks needle begins with haystack
 * @haystacks: string to be searched
 * @ndle: substring to be found
 * Return: address of next haystack char or NULL
 */
char *starts_wth(const char *haystacks, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *haystacks++)
			return (NULL);
	return ((char *)haystacks);
}

/**
 * str_cat - concatenates two strings
 * @des: the destination buffer
 * @srb: source buffer
 * Return: ptr to destination buffer
 */
char *str_cat(char *des, char *srb)
{
	char *rets = des;

	while (*des)
		des++;
	while (*srb)
		*des++ = *srb++;
	*des = *srb;
	return (rets);
}

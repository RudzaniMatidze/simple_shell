#include "main.h"

/**
 **string_cpy - copies string
 *@des: destination string to copied
 *@src: source string
 *@mnt: amount of characters to be copied
 *Return: concatenated string
 */
char *string_cpy(char *des, char *src, int mnt)
{
	int a, b;
	char *string = des;

	a = 0;
	while (src[a] != '\0' && a < mnt - 1)
	{
		des[a] = src[a];
		a++;
	}
	if (a < mnt)
	{
		b = a;
		while (b < mnt)
		{
			des[b] = '\0';
			b++;
		}
	}
	return (string);
}

/**
 **string_cat - concatenates two strings
 *@des: first string
 *@src: the second string
 *@mnt: amount of bytes to be maximally used
 *Return: concatenated string
 */
char *string_cat(char *des, char *src, int mnt)
{
	int a, b;
	char *string = des;

	a = 0;
	b = 0;
	while (des[a] != '\0')
		a++;
	while (src[b] != '\0' && b < mnt)
	{
		des[a] = src[b];
		a++;
		b++;
	}
	if (b < mnt)
		des[a] = '\0';
	return (string);
}

/**
 **string_chr - locates a character in a string
 *@string: string to be parsed
 *@ch: character to look for
 *Return: pointer to the memory area string
 */
char *string_chr(char *string, char ch)
{
	do {
		if (*string == ch)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

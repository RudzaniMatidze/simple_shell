#include "main.h"

/**
 * **split - splits a string into words. Repeat delim are ignored
 * @str: input string
 * @del: delimeter string
 * Return: array pointer of strings, or NULL if not
 */

char **split(char *str, char *del)
{
	int a, e, f, g, no_words = 0;
	char **string;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delimiter(str[a], del) && (is_delimiter(str[a + 1],
						del) || !str[a + 1]))
			no_words++;

	if (no_words == 0)
		return (NULL);
	string = malloc((1 + no_words) * sizeof(char *));
	if (!string)
		return (NULL);
	for (a = 0, e = 0; e < no_words; e++)
	{
		while (is_delimiter(str[a], del))
			a++;
		f = 0;
		while (!is_delimiter(str[a + f], del) && str[a + f])
			f++;
		string[e] = malloc((f + 1) * sizeof(char));
		if (!string[e])
		{
			for (f = 0; f < e; f++)
				free(string[f]);
			free(string);
			return (NULL);
		}
		for (g = 0; g < f; g++)
			string[e][g] = str[a++];
		string[e][g] = 0;
	}
	string[e] = NULL;
	return (string);
}

/**
 * **split2 - splits a string into words
 * @str: input string
 * @del: delimeter
 * Return: a pointer to an array of strings, or NULL if not
 */
char **split2(char *str, char del)
{
	int a, e, f, g, no_words = 0;
	char **string;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != del && str[a + 1] == del) ||
		    (str[a] != del && !str[a + 1]) || str[a + 1] == del)
			no_words++;
	if (no_words == 0)
		return (NULL);
	string = malloc((1 + no_words) * sizeof(char *));
	if (!string)
		return (NULL);
	for (a = 0, e = 0; e < no_words; e++)
	{
		while (str[a] == del && str[a] != del)
			a++;
		f = 0;
		while (str[a + f] != del && str[a + f] && str[a + f] != del)
			f++;
		string[e] = malloc((f + 1) * sizeof(char));
		if (!string[e])
		{
			for (f = 0; f < e; f++)
				free(string[f]);
			free(string);
			return (NULL);
		}
		for (g = 0; g < f; g++)
			string[e][g] = str[a++];
		string[e][g] = 0;
	}
	string[e] = NULL;
	return (string);
}

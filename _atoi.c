#include "main.h"

/**
 * inter_active - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 if not
 */
int inter_active(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if char is delimeter
 * @ch: char to check
 * @delim: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic char
 * @ch: character to input
 * Return: 1 if ch is alphabetic, 0 if not
 */

int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to integer
 * @st: string to convert
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *st)
{
	int a, signs = 1, flags = 0, outputs;
	unsigned int results = 0;

	for (a = 0;  st[a] != '\0' && flags != 2; a++)
	{
		if (st[a] == '-')
			signs *= -1;

		if (st[a] >= '0' && st[a] <= '9')
		{
			flags = 1;
			results *= 10;
			results += (st[a] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (signs == -1)
		outputs = -results;
	else
		outputs = results;

	return (outputs);
}

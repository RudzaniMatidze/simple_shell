#include "main.h"

/**
 * err_atoi - converts string to integer
 * @st: string to be converted
 * Return: 0 if no numbers in string, -1 if error
 */
int err_atoi(char *st)
{
	int a = 0;
	unsigned long int outcome = 0;

	if (*st == '+')
		st++;  /* TODO: why does it make main return 255? */
	for (a = 0;  st[a] != '\0'; a++)
	{
		if (st[a] >= '0' && st[a] <= '9')
		{
			outcome *= 10;
			outcome += (st[a] - '0');
			if (outcome > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (outcome);
}

/**
 * prints_error - prints error message
 * @inform: parameter and return info struct
 * @est: contains specified error type
 * Return: 0 if no num in string, -1 if error
 */
void prints_error(info_t *inform, char *est)
{
	eputs(inform->fname);
	eputs(": ");
	prints_d(inform->line_count, STDERR_FILENO);
	eputs(": ");
	eputs(inform->argv[0]);
	eputs(": ");
	eputs(est);
}

/**
 * prints_d - prints a decimal (int) num (base 10)
 * @inp: input value
 * @fld: filedescriptor to write to
 * Return: num of char printed
 */
int prints_d(int inp, int fld)
{
	int (*__putchar)(char) = _putchar;
	int a, cnt = 0;
	unsigned int _abs, curr;

	if (fld == STDERR_FILENO)
		__putchar = eputchar;
	if (inp < 0)
	{
		_abs = -inp;
		__putchar('-');
		cnt++;
	}
	else
		_abs = inp;
	curr = _abs;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs / a)
		{
			__putchar('0' + curr / a);
			cnt++;
		}
		curr %= a;
	}
	__putchar('0' + curr);
	cnt++;

	return (cnt);
}

/**
 * convert_num - converter func, a clone of itoa
 * @no: number
 * @bs: base value
 * @flgs: argument flags
 * Return: string
 */
char *convert_num(long int no, int bs, int flgs)
{
	static char *arr;
	static char buffr[50];
	char signs = 0;
	char *pt;
	unsigned long a = no;

	if (!(flgs & CONVERT_UNSIGNED) && no < 0)
	{
		a = -no;
		signs = '-';

	}
	arr = flgs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffr[49];
	*pt = '\0';

	do	{
		*--pt = arr[a % bs];
		a /= bs;
	} while (a != 0);

	if (signs)
		*--pt = signs;
	return (pt);
}

/**
 * rem_comments - replaces instance of '#' with '\0'
 * @buffr: address of modified string
 * Return: Always 0 (success)
 */
void rem_comments(char *buffr)
{
	int a;

	for (a = 0; buffr[a] != '\0'; a++)
		if (buffr[a] == '#' && (!a || buffr[a - 1] == ' '))
		{
			buffr[a] = '\0';
			break;
		}
}

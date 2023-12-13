#include "main.h"

/**
 * main - entry point of main func
 * @arc: argument count
 * @arv: argument vector
 * Return: 0 on success, 1 if not
 */
int main(int arc, char **arv)
{
	info_t inform[] = { INFO_INIT };
	int fld = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fld)
		: "r" (fld));

	if (arc == 2)
	{
		fld = open(arv[1], O_RDONLY);
		if (fld == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputs(arv[0]);
				eputs(": 0: Can't open ");
				eputs(arv[1]);
				eputchar('\n');
				eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inform->readfd = fld;
	}
	popul_environ_list(inform);
	read_hist(inform);
	hsh(inform, arv);
	return (EXIT_SUCCESS);
}

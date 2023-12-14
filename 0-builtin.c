#include "main.h"

/**
 * my_exit - exits the shell
 * @inform: contains potential arguments.
 * Return: exits with a given exit status
 */
int my_exit(info_t *inform)
{
	int exit_check;

	if (inform->argv[1])
	{
		exit_check = err_atoi(inform->argv[1]);
		if (exit_check == -1)
		{
			inform->status = 2;
			prints_error(inform, "Illegal number: ");
			eputs(inform->argv[1]);
			eputchar('\n');
			return (1);
		}
		inform->err_no = err_atoi(inform->argv[1]);
		return (-2);
	}
	inform->err_no = -1;
	return (-2);
}

/**
 * my_cdr - changes current dir of the process
 * @inform: contains potential arguments.
 *  Return: Always 0 (success)
 */
int my_cdr(info_t *inform)
{
	char *st, *dirct, buffr[1024];
	int chkdir_ret;

	st = getcwd(buffr, 1024);
	if (!st)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inform->argv[1])
	{
		dirct = get_env(inform, "HOME=");
		if (!dirct)
			chkdir_ret =
				chdir((dirct = get_env(inform, "PWD=")) ? dirct : "/");
		else
			chkdir_ret = chdir(dirct);
	}
	else if (str_cmp(inform->argv[1], "-") == 0)
	{
		if (!get_env(inform, "OLDPWD="))
		{
			_puts(st);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(inform, "OLDPWD=")), _putchar('\n');
		chkdir_ret =
			chdir((dirct = get_env(inform, "OLDPWD=")) ? dirct : "/");
	}
	else
		chkdir_ret = chdir(inform->argv[1]);
	if (chkdir_ret == -1)
	{
		prints_error(inform, "can't cd to ");
		eputs(inform->argv[1]), eputchar('\n');
	}
	else
	{
		set_env(inform, "OLDPWD", get_env(inform, "PWD="));
		set_env(inform, "PWD", getcwd(buffr, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current dir of the process
 * @inform: contains potential arguments.
 * Return: Always 0 (success)
 */
int my_help(info_t *inform)
{
	char **arg_arr;

	arg_arr = inform->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}

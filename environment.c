#include "main.h"

/**
 * my_environ - prints current environment
 * @inform: contains potential arguments.
 * maintains prototypes.
 * Return: Always 0 (success)
 */
int my_environ(info_t *inform)
{
	prints_list_str(inform->env);
	return (0);
}

/**
 * get_env - value of an environ variable
 * @inform: containing potential arguments.
 * @envname: env variable name
 * Return: value of env
 */
char *get_env(info_t *inform, const char *envname)
{
	list_t *nodes = inform->env;
	char *pos;

	while (nodes)
	{
		pos = starts_wth(nodes->str, envname);
		if (pos && *pos)
			return (pos);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * my_setenv - initialize new environment variable,
 * or modify an existing one
 * @inform: contains potential arguments.
 * Return: Always 0 (success)
 */
int my_setenv(info_t *inform)
{
	if (inform->argc != 3)
	{
		eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(inform, inform->argv[1], inform->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - removes an environ variable
 * @inform: contains potential arguments.
 * Return: Always 0 (success)
 */
int my_unsetenv(info_t *inform)
{
	int a;

	if (inform->argc == 1)
	{
		eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= inform->argc; a++)
		unset_env(inform, inform->argv[a]);

	return (0);
}

/**
 * popul_enviro_list - populates envron linked list
 * @inform: contains potential arguments.
 * Return: Always 0
 */
int popul_environ_list(info_t *inform)
{
	list_t *nodes = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		adds_node_end(&nodes, environ[a], 0);
	inform->env = nodes;
	return (0);
}

#include "main.h"

/**
 * get_envi - returns copy string array of our environ
 * @inform: contains potential arguments.
 * Return: Always 0 (success)
 */
char **get_envi(info_t *inform)
{
	if (!inform->environ || inform->env_changed)
	{
		inform->environ = list_arr_strings(inform->env);
		inform->env_changed = 0;
	}

	return (inform->environ);
}

/**
 * unset_env - Remove an environment var
 * @inform: contains potential arguments.
 * @vrbl: variable of env string
 * Return: 1 on delete, 0 if not
 */
int unset_env(info_t *inform, char *vrbl)
{
	list_t *nodes = inform->env;
	size_t a = 0;
	char *pt;

	if (!nodes || !vrbl)
		return (0);

	while (nodes)
	{
		pt = starts_wth(nodes->str, vrbl);
		if (pt && *pt == '=')
		{
			inform->env_changed = deletes_node_index(&(inform->env), a);
			a = 0;
			nodes = inform->env;
			continue;
		}
		nodes = nodes->next;
		a++;
	}
	return (inform->env_changed);
}

/**
 * set_env - initialize a new environ var,
 * or modify an existing one
 * @inform: contains potential arguments.
 * @vrbl: variable of string env
 * @vlu: var value of string env
 * Return: Always 0 (success)
 */
int set_env(info_t *inform, char *vrbl, char *vlu)
{
	char *buffr = NULL;
	list_t *nodes;
	char *pt;

	if (!vrbl || !vlu)
		return (0);

	buffr = malloc(str_len(vrbl) + str_len(vlu) + 2);
	if (!buffr)
		return (1);
	str_cpy(buffr, vrbl);
	str_cat(buffr, "=");
	str_cat(buffr, vlu);
	nodes = inform->env;
	while (nodes)
	{
		pt = starts_wth(nodes->str, vrbl);
		if (pt && *pt == '=')
		{
			free(nodes->str);
			nodes->str = buffr;
			inform->env_changed = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	adds_node_end(&(inform->env), buffr, 0);
	free(buffr);
	inform->env_changed = 1;
	return (0);
}

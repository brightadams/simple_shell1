#include "shell.h"

/**
 * _myenv - Prints the current environment.
 * @info: Pointer to struct containing potential arguments.
 *
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @info: Pointer to struct containing potential arguments.
 * @name: Name of environment variable.
 *
 * Return: Pointer to value of environment variable, or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *env_node = info->env;
	char *p;

	while (env_node)
	{
		p = starts_with(env_node->str, name);
		if (p && *p)
			return (p);
		env_node = env_node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initializes a new environment variable,
 *             or modifies an existing one.
 * @info: Pointer to struct containing potential arguments.
 *
 * Return: Always 0.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable.
 * @info: Pointer to struct containing potential arguments.
 *
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: Pointer to struct containing potential arguments.
 *
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
	list_t *env_node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&env_node, environ[i], 0);
	info->env = env_node;
	return (0);
}


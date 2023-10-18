#include "main.h"

/**
 * copy_info - copies info to create a new environment or alias
 * @name: name of env or alias
 * @value: value of env or alias
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new_new;
	int len_name, len_value, len;

	len_name = str_len(name);
	len_value = str_len(value);
	len = len_name + len_value + 2;
	new_new = malloc(sizeof(char) * (len));
	str_cpy(new_new, name);
	str_cat(new_new, "=");
	str_cat(new_new, value);
	str_cat(new_new, "\0");

	return (new_new);
}

/**
 * set_env - the function sets an environment variable
 *
 * @name: environment variable name
 * @value: environment variable value
 * @datash: the data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int a;
	char *var_env, *name_env;

	for (a = 0; datash->_environ[a]; a++)
	{
		var_env = str_dup(datash->_environ[a]);
		name_env = str_tok(var_env, "=");
		if (str_cmp(name_env, name) == 0)
		{
			free(datash->_environ[a]);
			datash->_environ[a] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _realloc_dp(datash->_environ, a, sizeof(char *) * (a + 2));
	datash->_environ[a] = copy_info(name, value);
	datash->_environ[a + 1] = NULL;
}

/**
 * _setenv - the function compares environment variables names
 * with name passed.
 * @datash: (env name and env value) data relevant
 *
 * Return: on success 1.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - the function deletes a environment variable
 *
 * @datash: (env name) data relevant
 *
 * Return: on success 1.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int a, b, c;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	c = -1;
	for (a = 0; datash->_environ[a]; a++)
	{
		var_env = str_dup(datash->_environ[a]);
		name_env = str_tok(var_env, "=");
		if (str_cmp(name_env, datash->args[1]) == 0)
		{
			c = a;
		}
		free(var_env);
	}
	if (c == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (a));
	for (a = b = 0; datash->_environ[a]; a++)
	{
		if (a != c)
		{
			realloc_environ[b] = datash->_environ[a];
			b++;
		}
	}
	realloc_environ[b] = NULL;
	free(datash->_environ[c]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}

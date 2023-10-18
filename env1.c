#include "main.h"

/**
 * cmp_env_name - compares environ variables names
 * with the name passed into it.
 * @nenv: name of the environment variable to be compared
 * @name: the name passed to be compared
 *
 * Return: if are not equal 0. if they are Another value.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int a;

	for (a = 0; nenv[a] != '='; a++)
	{
		if (nenv[a] != name[a])
		{
			return (0);
		}
	}

	return (a + 1);
}

/**
 * _getenv - the function gets a environment variable
 * @name: name of the environment variable to be got
 * @_environ: environment variable
 *
 * Return: value of environment variable if found.
 * Or NULL, otherwise.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int a, mo;

	ptr_env = NULL;
	mo = 0;

	for (a = 0; _environ[a]; a++)
	{
		mo = cmp_env_name(_environ[a], name);
		if (mo)
		{
			ptr_env = _environ[a];
			break;
		}
	}

	return (ptr_env + mo);
}

/**
 * _env - the function prints the evironment variables
 *
 * @datash: the data relevant.
 * Return: on success 1
 */
int _env(data_shell *datash)
{
	int a, b;

	for (a = 0; datash->_environ[a]; a++)
	{

		for (b = 0; datash->_environ[a][b]; b++)
			;

		write(STDOUT_FILENO, datash->_environ[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}

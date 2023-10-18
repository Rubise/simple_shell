#include "main.h"

/**
 * cd_shell - function changes current directory.
 *
 * @datash: data relevant.
 * Return: 1. on success.
 */
int cd_shell(data_shell *datash)
{
	char *dir;
	int is_home, is_home2, is_ddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		is_home = str_cmp("$HOME", dir);
		is_home2 = str_cmp("~", dir);
		is_ddash = str_cmp("--", dir);
	}

	if (dir == NULL || !is_home || !is_home2 || !is_ddash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (str_cmp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (str_cmp(".", dir) == 0 || str_cmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}

#include "main.h"

/**
 * _errorenv - error message created for env in get_env.
 * @datash: the data relevant (counter, arguments)
 * Return: error message.
 */
char *_errorenv(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_intoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	length = str_len(datash->av[0]) + str_len(ver_str);
	length += str_len(datash->args[0]) + str_len(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	str_cpy(error, datash->av[0]);
	str_cat(error, ": ");
	str_cat(error, ver_str);
	str_cat(error, ": ");
	str_cat(error, datash->args[0]);
	str_cat(error, msg);
	str_cat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path - error message created for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path(data_shell *datash)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_intoa(datash->counter);
	length = str_len(datash->av[0]) + str_len(ver_str);
	length += str_len(datash->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	str_cpy(error, datash->av[0]);
	str_cat(error, ": ");
	str_cat(error, ver_str);
	str_cat(error, ": ");
	str_cat(error, datash->args[0]);
	str_cat(error, ": Permission denied\n");
	str_cat(error, "\0");
	free(ver_str);
	return (error);
}

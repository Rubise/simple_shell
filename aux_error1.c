#include "main.h"

/**
 * str_cat_cd - the function that concatenates the message for cd error
 *
 * @datash: data relevant (directory)
 * @msg: message to be printed
 * @error: the output message
 * @ver_str: counter lines
 * Return: error message
 */
char *str_cat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	str_cpy(error, datash->av[0]);
	str_cat(error, ": ");
	str_cat(error, ver_str);
	str_cat(error, ": ");
	str_cat(error, datash->args[0]);
	str_cat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		str_cat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		str_cat(error, datash->args[1]);
	}

	str_cat(error, "\n");
	str_cat(error, "\0");
	return (error);
}

/**
 * _errorgetcd - the error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *_errorgetcd(data_shell *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_intoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = str_len(datash->args[1]);
	}

	length = str_len(datash->av[0]) + str_len(datash->args[0]);
	length += str_len(ver_str) + str_len(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = str_cat_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * _errornotfound - the generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *_errornotfound(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_intoa(datash->counter);
	length = str_len(datash->av[0]) + str_len(ver_str);
	length += str_len(datash->args[0]) + 16;
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
	str_cat(error, ": not found\n");
	str_cat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit - generic error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_intoa(datash->counter);
	length = str_len(datash->av[0]) + str_len(ver_str);
	length += str_len(datash->args[0]) + str_len(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	str_cpy(error, datash->av[0]);
	str_cat(error, ": ");
	str_cat(error, ver_str);
	str_cat(error, ": ");
	str_cat(error, datash->args[0]);
	str_cat(error, ": Illegal number: ");
	str_cat(error, datash->args[1]);
	str_cat(error, "\n\0");
	free(ver_str);

	return (error);
}

#include "main.h"

/**
 * exit_shell - the function to exit the shell
 *
 * @datash: (status and args) data relevant.
 * Return: on success, 0.
 */
int exit_shell(data_shell *datash)
{
	unsigned int ustatus;
	int _isdigit;
	int _strlen;
	int big_number;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoint(datash->args[1]);
		_isdigit = is_digit(datash->args[1]);
		_strlen = str_len(datash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!_isdigit || _strlen > 10 || big_number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}

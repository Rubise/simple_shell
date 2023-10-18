#include "main.h"

/**
 * get_error - the function calls the error according the builtin
 * syntax or permission
 * @datash: arguments from the data structure
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *datash, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = _errorenv(datash);
		break;
	case 126:
		err = error_path(datash);
		break;
	case 127:
		err = _errornotfound(datash);
		break;
	case 2:
		if (str_cmp("exit", datash->args[0]) == 0)
			err = error_exit(datash);
		else if (str_cmp("cd", datash->args[0]) == 0)
			err = _errorgetcd(datash);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, str_len(err));
		free(err);
	}

	datash->status = eval;
	return (eval);
}

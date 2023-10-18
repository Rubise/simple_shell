#include "main.h"

/**
 * get_help - retrieves help messages according to builtin
 * @datash: (args and input) data structure
 * Return: Always 0.
*/
int get_help(data_shell *datash)
{

	if (datash->args[1] == 0)
		_aux_help_gen();
	else if (str_cmp(datash->args[1], "setenv") == 0)
		_aux_help_setenv();
	else if (str_cmp(datash->args[1], "env") == 0)
		_aux_help_env();
	else if (str_cmp(datash->args[1], "unsetenv") == 0)
		_aux_help_unsetenv();
	else if (str_cmp(datash->args[1], "help") == 0)
		aux_help_info();
	else if (str_cmp(datash->args[1], "exit") == 0)
		_aux_help_exit();
	else if (str_cmp(datash->args[1], "cd") == 0)
		aux_help_cd_info();
	else if (str_cmp(datash->args[1], "alias") == 0)
		aux_help_alias_info();
	else
		write(STDERR_FILENO, datash->args[0],
		      str_len(datash->args[0]));

	datash->status = 0;
	return (1);
}

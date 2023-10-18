#include "main.h"

/**
 * aux_help_info - Help info for the builtin help.
 * Return: no return
 */
void aux_help_info(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, str_len(help));
}
/**
 * aux_help_alias_info - Help info for the builtin alias.
 * Return: no return
 */
void aux_help_alias_info(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, str_len(help));
}
/**
 * aux_help_cd_info - Help info for the builtin alias.
 * Return: no return
 */
void aux_help_cd_info(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, str_len(help));
}

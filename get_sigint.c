#include "main.h"

/**
 * get_sigint - Handle the command + c call in prompt
 * @sig: the Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

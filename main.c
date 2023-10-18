#include "main.h"

/**
 * free_data - the function frees data structure
 *
 * @datash: the data structure
 * Return: no return
 */
void free_data(data_shell *datash)
{
	unsigned int a;

	for (a = 0; datash->_environ[a]; a++)
	{
		free(datash->_environ[a]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - The function Initializes data structure
 *
 * @datash: The Data Structure
 * @av: The Argument Vector
 * Return: No Return
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int a;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (a = 0; environ[a]; a++)
		;

	datash->_environ = malloc(sizeof(char *) * (a + 1));

	for (a = 0; environ[a]; a++)
	{
		datash->_environ[a] = str_dup(environ[a]);
	}

	datash->_environ[a] = NULL;
	datash->pid = aux_intoa(getpid());
}

/**
 * main - Entry point.
 *
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: on success, 0.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}

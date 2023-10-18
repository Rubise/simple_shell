#include "main.h"

/**
 * without_comment - The function Deletes comments from the input.
 *
 * @in: The Input String.
 * Return: Input Without Comments.
 */
char *without_comment(char *in)
{
	int a, up_to;

	up_to = 0;
	for (a = 0; in[a]; a++)
	{
		if (in[a] == '#')
		{
			if (a == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[a - 1] == ' ' || in[a - 1] == '\t' || in[a - 1] == ';')
				up_to = a;
		}
	}

	if (up_to != 0)
	{
		in = re_alloc(in, a, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - The function controls the Loop of shell.
 * @datash: (av, input, args) data relevant.
 *
 * Return: No Return.
 */
void shell_loop(data_shell *datash)
{
	int lp, i_eof;
	char *inp;

	lp = 1;
	while (lp == 1)
	{
		char prompt[] = "$ ";

		write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
		inp = read_line(&i_eof);
		if (i_eof != -1)
		{
			inp = without_comment(inp);
			if (inp == NULL)
				continue;

			if (check_syntax_error(datash, inp) == 1)
			{
				datash->status = 2;
				free(inp);
				continue;
			}
			inp = rep_var(inp, datash);
			lp = split_commands(datash, inp);
			datash->counter += 1;
			free(inp);
		}
		else
		{
			lp = 0;
			free(inp);
		}
	}
}

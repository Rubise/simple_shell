#include "main.h"

/**
 * check_env - The Function checks if the typed variable is an env variable
 * @h: Linked list head
 * @in: Input String
 * @data: Data Structure
 * Return: No Return
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, a, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (a = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = str_len(_envr[row] + chr + 1);
				add_rvar(h, a, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[a] == _envr[row][chr])
				a++;
			else
				break;
		}
	}

	for (a = 0; in[a]; a++)
	{
		if (in[a] == ' ' || in[a] == '\t' || in[a] == ';' || in[a] == '\n')
			break;
	}

	add_rvar(h, a, NULL, 0);
}

/**
 * check_vars - the function checks if the typed variable is $$ or $?
 *
 * @h: Linked List head.
 * @in: The Input string.
 * @st: Last status of the Shell.
 * @data: The Data structure.
 * Return: No Return.
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int a, lst, lpd;

	lst = str_len(st);
	lpd = str_len(data->pid);
	for (a = 0; in[a]; a++)
	{
		if (in[a] == '$')
		{
			if (in[a + 1] == '?')
			{
				add_rvar(h, 2, st, lst), a++;
			}
			else if (in[a + 1] == '$')
			{ add_rvar(h, 2, data->pid, lpd), a++;
			}
			else if (in[a + 1] == '\n')
			{ add_rvar(h, 0, NULL, 0);
			}
			else if (in[a + 1] == '\0')
			{ add_rvar(h, 0, NULL, 0);
			}
			else if (in[a + 1] == ' ')
			{
				add_rvar(h, 0, NULL, 0);
			}
			else if (in[a + 1] == '\t')
			{
				add_rvar(h, 0, NULL, 0);
			}
			else if (in[a + 1] == ';')
			{
				add_rvar(h, 0, NULL, 0);
			}
			else
			{
				check_env(h, in + a, data);
			}
		}
	}
	return (a);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int a, b, c;

	indx = *head;
	for (b = a = 0; a < nlen; a++)
	{
		if (input[b] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[a] = input[b];
				b++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (c = 0; c < indx->len_var; c++)
					b++;
				a--;
			}
			else
			{
				for (c = 0; c < indx->len_val; c++)
				{
					new_input[a] = indx->val[c];
					a++;
				}
				b += (indx->len_var);
				a--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[a] = input[b];
			b++;
		}
	}

	return (new_input);
}

/**
 * rep_var - the function Calls Functions to replace string into vars.
 *
 * @input: The Input String.
 * @datash: The Data Structure.
 * Return: The Replaced String.
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *start, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_intoa(datash->status);
	start = NULL;

	olen = check_vars(&start, input, status, datash);

	if (start == NULL)
	{
		free(status);
		return (input);
	}

	indx = start;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&start, input, new_input, nlen);

	free(input);
	free(status);
	free_list(&start);

	return (new_input);
}

#include "main.h"

/**
 * swap_char - The Function swaps | and & for non-printed chars
 *
 * @input: The Input String
 * @bool: The Type of Swap
 * Return: The Swapped String
 */
char *swap_char(char *input, int bool)
{
	int a;

	if (bool == 0)
	{
		for (a = 0; input[a]; a++)
		{
			if (input[a] == '|')
			{
				if (input[a + 1] != '|')
					input[a] = 16;
				else
					a++;
			}

			if (input[a] == '&')
			{
				if (input[a + 1] != '&')
					input[a] = 12;
				else
					a++;
			}
		}
	}
	else
	{
		for (a = 0; input[a]; a++)
		{
			input[a] = (input[a] == 16 ? '|' : input[a]);
			input[a] = (input[a] == 12 ? '&' : input[a]);
		}
	}
	return (input);
}

/**
 * add_nodes - The Function adds separators and command lines in the lists.
 *
 * @head_s: The Head of separator list.
 * @head_l: The Head of command lines list.
 * @input: Input String.
 * Return: No Return.
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int a;
	char *line;

	input = swap_char(input, 0);

	for (a = 0; input[a]; a++)
	{
		if (input[a] == ';')
			add_sep_end(head_s, input[a]);

		if (input[a] == '|' || input[a] == '&')
		{
			add_sep_end(head_s, input[a]);
			a++;
		}
	}

	line = str_tok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_end(head_l, line);
		line = str_tok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - The function goes to the next command line stored.
 *
 * @list_s: The Separator List.
 * @list_l: The Command Line List.
 * @datash: The Data Structure.
 * Return: No Return.
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int lp_sep;
	sep_list *ls_s;
	line_list *ls_l;

	lp_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && lp_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
			{
				lp_sep = 0;
			}
			if (ls_s->separator == '|')
			{
				ls_l = ls_l->next, ls_s = ls_s->next;
			}
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
			{
				lp_sep = 0;
			}
			if (ls_s->separator == '&')
			{
				ls_l = ls_l->next, ls_s = ls_s->next;
			}
		}
		if (ls_s != NULL && !lp_sep)
		{
			ls_s = ls_s->next;
		}
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - The function Splits command lines according to
 * separators ;, | and &, and executes them.
 *
 * @datash: The Data Structure.
 * @input: Input String.
 * Return: To exit 0, To continue 1.
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int lp;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		lp = exec_line(datash);
		free(datash->args);

		if (lp == 0)
		{
			break;
		}

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
		{
			list_l = list_l->next;
		}
	}
	free_sep_lists(&head_s);
	_free_line_list(&head_l);

	if (lp == 0)
	{
		return (0);
	}
	return (1);
}

/**
 * split_line - The Function tokenizes the input string
 *
 * @input: The Input String.
 * Return: String Splitted.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t a;
	char **tkns;
	char *tkn;

	bsize = TOK_BUFSIZE;
	tkns = malloc(sizeof(char *) * (bsize));
	if (tkns == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	tkn = str_tok(input, TOK_DELIM);
	tkns[0] = tkn;

	for (a = 1; tkn != NULL; a++)
	{
		if (a == bsize)
		{
			bsize += TOK_BUFSIZE;
			tkns = _realloc_dp(tkns, a, sizeof(char *) * bsize);
			if (tkns == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tkn = str_tok(NULL, TOK_DELIM);
		tkns[a] = tkn;
	}

	return (tkns);
}

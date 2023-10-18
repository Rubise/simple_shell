#include "main.h"

/**
 * read_line - The function reads the input string.
 *
 * @i_eof: Return value of the getline function
 * Return: Input String
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t buffsize = 0;

	*i_eof = getline(&input, &buffsize, stdin);

	return (input);
}

#include "main.h"

/**
 * bring_line - the function assigns the line var for get_line
 * @lineptr: Buffer that store the input string
 * @buffer: string that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		str_cpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Reads an inpt from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int a;
	static ssize_t input;
	ssize_t retval;
	char *buff;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buff = malloc(sizeof(char) * BUFSIZE);
	if (buff == 0)
		return (-1);
	while (t != '\n')
	{
		a = read(STDIN_FILENO, &t, 1);
		if (a == -1 || (a == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (a == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buff = re_alloc(buff, input, input + 1);
		buff[input] = t;
		input++;
	}
	buff[input] = '\0';
	bring_line(lineptr, n, buff, input);
	retval = input;
	if (a != 0)
		input = 0;
	return (retval);
}

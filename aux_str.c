#include "main.h"

/**
 * str_cat - concatenates two strings
 * @dest: char pointer to the destination of the copied str
 * @src: const char pointer to the source of str
 * Return: the destination
 */
char *str_cat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * *str_cpy - Copies the string pointed to by source.
 * @dest: Type char pointer of the destination of the copied string
 * @src: Type char pointer the source of string
 * Return: the destination.
 */
char *str_cpy(char *dest, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}
/**
 * str_cmp - Function that compares two strings.
 * @s1: type string compared
 * @s2: type string compared
 * Return: 0. Always.
 */
int str_cmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * str_chr - locates a character in a string,
 * @s: the string.
 * @c: the character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *str_chr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * str_spn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: number of accepted bytes.
 */
int str_spn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}

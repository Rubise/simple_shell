#include "main.h"

/**
 * mem_cpy - copies info between void pointers.
 * @newptr: the destination pointer.
 * @ptr: the source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void mem_cpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * re_alloc - this reallocates a memory block.
 * @ptr: the pointer to the previously allocated memory.
 * @old_size: size of the allocated space of ptr, in bytes.
 * @new_size: new size of the new memory block, in bytes.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		mem_cpy(newptr, ptr, new_size);
	else
		mem_cpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _realloc_dp - reallocates a] double pointer of memory block.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size of the allocated space of ptr, in bytes.
 * @new_size: new size of the new memory block, in bytes.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_realloc_dp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}

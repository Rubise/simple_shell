#include "main.h"

/**
 * add_rvar - adds a variable at the end
 * of a r_var list.
 * @head: the head of the linked list.
 * @lvar: the length of the variable.
 * @val: the value of the variable.
 * @lval: the length of the value.
 * Return: address of the head.
 */
r_var *add_rvar(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_list - frees from r_var list
 * @head: the head of the linked list.
 * Return: no return.
 */
void free_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

#include "monty.h"
/**
* push_func - pushes a new node to the top of the stack
*
* @tokens: line of command tokenized
* @stack: double pointer to the first node of the stack
* @line_number: number of the line of command
*
* Return: void
*/
void push_func(char **tokens, stack_t **stack, unsigned int line_number)
{
	stack_t *newnode = NULL;
	int i;

	newnode = malloc(sizeof(stack_t));
	if (newnode == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	if (tokens[1] != NULL)
	{
		for (i = 0; tokens[1][i] != '\0'; i++)
		{
			if (!isdigit(tokens[1][i]) && tokens[1][i] != '-')
			{
				free(newnode);
				free_dp(tokens);
				fprintf(stderr, "L%u: usage: push integer\n", line_number);
				exit(EXIT_FAILURE);
			}
		}
		newnode->n = atoi(tokens[1]);
		newnode->prev = NULL;
		if (!(*stack))
		{
			newnode->next = NULL;
		}
		else
		{
			newnode->next = (*stack);
		}
		*stack = newnode;
	}
	else
	{
		free(newnode);
		free_dp(tokens);
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
}

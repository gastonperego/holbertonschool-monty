#include "monty.h"

/**
* pall_func - prints the value of each node, starting for the top of the stack
*
* @stack: double pointer to the first node of the stack
* @line: number of the line of command
*
* Return: void
*/
void pall_func(stack_t **stack, unsigned int line __attribute__((unused)))
{
	stack_t *tmp = *stack;

	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}
/**
* pint_func - prints the value of the node at the top of the stack
*
* @stack: double pointer to the first node of the stack
* @line_number: number of the line of command
*
* Return: void
*/
void pint_func(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		dprintf(STDERR_FILENO, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%d\n", (*stack)->n);
	}
}
/**
* pop_func - removes the node at the top of the stack
*
* @stack: double pointer to the first node of the stack
* @line_number: number of the line of command
*
* Return: void
*/
void pop_func(stack_t **stack, unsigned int line_number)
{
	stack_t *aux = NULL;

	if (!(*stack))
	{
		dprintf(STDERR_FILENO, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
	{
		aux = (*stack)->next;
		free((*stack));
		(*stack) = aux;
	}
}
/**
* swap_func - swaps the first 2 nodes of the stack
*
* @stack: double pointer to the first node of the stack
* @line_number: number of the line of command
*
* Return: void
*/
void swap_func(stack_t **stack, unsigned int line_number)
{
	stack_t *aux = malloc(sizeof(stack_t));

	if (!(*stack) || !(*stack)->next)
	{
		dprintf(STDERR_FILENO, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
	{
		aux->n = (*stack)->n;
		(*stack)->n = (*stack)->next->n;
		(*stack)->next->n = aux->n;
		free(aux);
	}
}
/**
* add_func - adds the values (n) of the 2 nodes at the top of the stack
*
* @stack: double pointer to the first node of the stack
* @line_number: number of the line of command
*
* Return: void
*/
void add_func(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp =  NULL;

	if (!(*stack) || !(*stack)->next)
	{
		dprintf(STDERR_FILENO, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
	{
		tmp = (*stack)->next;
		tmp->n = (((*stack)->n + (*stack)->next->n));
		free(*stack);
		*stack = tmp;
	}
}

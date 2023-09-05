#include "monty.h"
/**
*
*/
void push_func(char **tokens, stack_t **stack, unsigned int line_number __attribute__((unused)))
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

/**
*
*/
void pall_func(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
    stack_t *tmp = *stack;

    while (tmp)
    {
        printf("%d\n", tmp->n);
        tmp = tmp->next;    
    }
}

/*
*
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
*
*/
void pop_func(stack_t **stack, unsigned int line_number)
{
    stack_t *aux = NULL;

    if (!(*stack))
    {
        dprintf(STDERR_FILENO ,"L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }
    else
    {
        aux = (*stack)->next;
        (*stack) = aux;
        free(aux);
    }
}
/**
*
*/
void swap_func(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
    stack_t *aux = malloc(sizeof(stack_t));

    if (!(*stack) || !(*stack)->next)
    {
        dprintf(STDERR_FILENO, "too short\n");
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
*
*/
void add_func(stack_t **stack, unsigned int line_number)
{
    stack_t *aux = malloc(sizeof(stack_t));
    
    if ((*stack) == NULL || (*stack)->next == NULL)
    {
        free(aux);
        dprintf(STDERR_FILENO, "L%u: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    else
    {
        aux->prev = NULL;
        aux->n = ((*stack)->n + (*stack)->next->n);
        aux->next = (*stack)->next->next;
        free((*stack));
        free((*stack)->next);
        *stack = aux;
    }
}

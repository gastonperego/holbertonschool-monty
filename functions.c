#include "monty.h"
/**
*
*/
void push_func(char **tokens, stack_t **stack, unsigned int line_number __attribute__((unused)))
{
    stack_t *newnode;
    stack_t *same = *stack;
    int i;

    /*printf("Entra al if\n");*/
    newnode = malloc(sizeof(stack_t));
    if (newnode == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
    }
    for (i = 0; tokens[1][i] != '\0'; i++)
	{
		if (!isdigit(tokens[1][i]) && tokens[1][i] != '-')
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}
    newnode->n = atoi(tokens[1]);
    newnode->prev = NULL;
    if (!same)
    {
        newnode->next = NULL;
    }
    else
    {
        newnode->next = same;    
    }
    *stack = newnode;
    /*free(newnode);*/
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
    stack_t *same = *stack;

    if (!*stack)
    {
        dprintf(STDERR_FILENO, "L%u: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);    
    }
    else
    {
        printf("%d\n", same->n);
    }
}
/**
*
*/
void pop_func(stack_t **stack, unsigned int line_number)
{
    stack_t *aux = NULL;
    stack_t *same = *stack;

    if (!same)
    {
        dprintf(STDERR_FILENO ,"L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }
    else
    {
        aux = same->next;
        free(same->prev);
        free(same->next);
        same = aux;
        free(aux);
    }
}
/**
*
*/
void swap_func(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
    stack_t *aux = malloc(sizeof(stack_t));
    stack_t *same = *stack;

    if (!same || !same->next)
    {
        dprintf(STDERR_FILENO, "too short\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        aux->n = same->n;
        same->n = same->next->n;
        same->next->n = aux->n;
        free(aux);
    }
}
/**
*
*/
void add_func(stack_t **stack, unsigned int line_number)
{
    stack_t *same = *stack;
    stack_t *aux = malloc(sizeof(stack_t));
    
    
    if (same == NULL || same->next == NULL)
    {
        dprintf(STDERR_FILENO, "L%u: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    else
    {
        aux->prev = NULL;
        aux->n = (same->n + same->next->n);
        aux->next = same->next->next;
        *stack = aux;
        free(aux);
    }
}

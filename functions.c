#include "monty.h"

/**
*
*/
void pall_func(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
    stack_t *tmp = *stack;
    if (!*stack)
        exit(EXIT_FAILURE);
    else
    {
        while (tmp)
        {
            printf("%d\n", tmp->n);
            tmp = tmp->next;
        }
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

/**
*
*/
void nop_func(stack_t **stack __attribute__((unused)), unsigned int line_number __attribute__((unused)))
{
    
}
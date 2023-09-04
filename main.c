#include "monty.h"
/**
*
*/
int main(int argc, char *argv[])
{
    unsigned int line_number = 0;
    int exit_sta = EXIT_SUCCESS;
    FILE *fp = NULL;
    size_t n = 0;
    char *buf = NULL, **tokens;
    stack_t *stack;

    if (argc != 2)
    {
        dprintf(STDERR_FILENO,"USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    while (getline(&buf, &n, fp) != -1)
    {
        line_number++;
        if (del_only(buf) == '\0')
            continue;
        tokens = tokenizer(buf, " \n\t$");
        if (strcmp(tokens[0], "push") == 0)
        {
                push_func(tokens, &stack, line_number);
                free_dp(tokens);
        }
        else if (strcmp(tokens[0], "nop") == 0)
        {
            free_dp(tokens);
            continue;
        }
        else
        {
            exit_sta = choose_func(tokens, &stack, line_number);
            free_dp(tokens);
        }
    }
    free(buf);
    fclose(fp);
    return(exit_sta);
}
/**
*
*/
int choose_func(char **tokens, stack_t **stack, unsigned int line_number)
{
    int i = 0;
    instruction_t func_selector[] = {
        {"pall", pall_func},
        {"pint", pint_func},
        {"pop", pop_func},
        {"swap", swap_func},
        {"add", add_func},
        {NULL, NULL},
    };

    for (;i < 6 && strcmp(tokens[0],func_selector[i].opcode) == 0; i++)
    {
            func_selector[i].f(stack, line_number);
            return(EXIT_SUCCESS);
    }
    free_stack(stack);
	fprintf(stderr, "L%i: unknown instruction %s\n", line_number, tokens[0]);
	return (EXIT_FAILURE);
}

/*
* tokenizer - makes tokens from the input string
*
* @input: input string from getline
* @delim: delimiter to separate the tokens
*
* Return: array of tokens
*/

char **tokenizer(char *input, char *delim)
{
    char *input_copy, *token, **av;
    int count = 0, i = 0;

    input_copy = strdup(input);
	if (input_copy == NULL)
    {
		free(input_copy);
        exit(-1);
    }

    token = strtok(input_copy, delim);
    while (token != NULL)
    {
        count++;
        token = strtok(NULL, delim);
    }
    free(input_copy);
    count++;
    if (count == 1)
        return (NULL);

    av = malloc(sizeof(char *) * count); /*FREE AV*/
	if (av == NULL)
    {
		free_dp(av);
        exit(-1);
    }
 
    token = strtok(input, delim);
    while (token != NULL)
    {
        av[i] = strdup(token);
        if (av[i] == NULL)
        {
            for (; i >= 0; i--)
                free(av[i]);
            free(av);
            exit(-1);
        }
        token = strtok(NULL, delim);
        i++;
    }
    av[i] = NULL;
    return (av);    
}

void free_dp(char **command)
{
	size_t i = 0;
	if (command == NULL)
		return;
        
    while (command[i])
	{
	free(command[i]);
	i++;
	}

	if (command[i] == NULL)
		free(command[i]);
	free(command);
}
void free_stack(stack_t **stack)
{
	stack_t *aux = *stack;

	if (*stack == NULL)
		return;
	while (*stack)
	{
		aux = (*stack)->next;
		free(*stack);
		*stack = aux;
	}
}
/**
 * del_only - checks if the line only contains delimiters.
 * 
 * @line: the pointer to the line.
 * @delims: string with delimiter characters.
 * 
 * Return: 1 if the line only contains delimiters, otherwise 0.
 */
int del_only(char *line)
{
	int i = 0, j = 0, k = 0, l = 0, m = 0;
    while (line[i])
    {
        if (line[i] == ' ')
            j++;
        else if (line[i] == '\n')
            k++;
        else if (line[i] == '\t')
            l++;
        else if (line[i] == '$')
            m++;
        i++;
    }
    if ((strlen(line) - (j + k + l + m)) == 0)
    {
        return('\0');
    }
	return (1);
}
#include "monty.h"
/**
*
*/
int main(int argc, char *argv[])
{
    unsigned int line_number = 0;
    FILE *fp = NULL;
    size_t n = 0;
    ssize_t got;
    char *buf = NULL, **tokens = NULL;
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
    while (1)
    {
        got = getline(&buf, &n, fp);
        if (got == -1)
            exit(EXIT_FAILURE);
        line_number++;

        tokens = tokenizer(buf, " \n\t$");
        if (strcmp(tokens[0], "push") == 0)
        {
            push_func(tokens, &stack, line_number);
            printf("%s\n", tokens[1]);
        }
        else
        {
            choose_func(tokens, line_number)(&stack, line_number);
            break;
        }
    }
    fclose(fp);
    return(0);
}
/**
*
*/
void (*choose_func(char **tokens, unsigned int line_number))(stack_t **stack, unsigned int line_number)
{
    int i = 0;
    instruction_t func_selector[] = {
        {"pall", pall_func},
        {"pint", pint_func},
        {"pop", pop_func},
        {"swap", swap_func},
        {"add", add_func},
        {"nop", nop_func},
        {NULL, NULL},
    };

    while (i < 7 && strcmp(tokens[0],func_selector[i].opcode) != 0)
    {
            i++;
    }
    if (func_selector[i].opcode == NULL)
    {
        dprintf(STDERR_FILENO,"L%d: unknown instruction %s\n", line_number, tokens[0]);
        exit(EXIT_FAILURE);
    }
    else
        return(func_selector[i].f);
    return(0);
}

/*
* tokening - makes tokens from the input string
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

    input_copy = strdup(input); /*FREE INPUT COPY MANEJADO*/
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
#include "monty.h"
/**
* choose_func - chooses the function based on the opcode given
*
* @tokens: line of command tokenized
* @stack: double pointer to th first node of the stack
* @line_number: number of the line of command
*
* Return: pointer to the function called by the opcode
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

	for (; i < 5; i++)
	{

			if (strcmp(func_selector[i].opcode, tokens[0]) == 0)
			{
				func_selector[i].f(stack, line_number);
				return (EXIT_SUCCESS);
			}
	}
	free_stack(stack);
	fprintf(stderr, "L%i: unknown instruction %s\n", line_number, tokens[0]);
	return (EXIT_FAILURE);
}

/**
* tokenizer - makes tokens from the input string
*
* @input: input string from getline
* @delim: delimiter to separate the tokens
*
* Return: array of tokens
*/

char **tokenizer(char *input, char *delim)
{
	char *input_copy = NULL, *token = NULL, **av = NULL;
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

	av = malloc(sizeof(char *) * count);
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
		i++; }
	av[i] = NULL;
	return (av); }
/**
 * free_dp - frees a double pointer
 *
 * @command: double pointer to be freed
 *
 * Return: void
 */
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
/**
 * free_stack - frees a stack
 *
 * @stack: stack to be freed
 *
 * Return: void
 */
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
		return ('\0');
	}
	return (1);
}

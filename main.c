#include "monty.h"
/**
* main - executes a monty file
*
* @argc: argc
* @argv: argv
*
* Return: 0 on succes, 1 otherwise
*/
int main(int argc, char *argv[])
{
	unsigned int line_number = 0, exit_sta = EXIT_SUCCESS;
	FILE *fp = NULL;
	size_t n = 0;
	char *buf = NULL, **tokens = NULL;
	stack_t *stack = NULL, *tmp = NULL;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE); }
	fp = fopen(argv[1], "r");
	if (fp == NULL)
		{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE); }
	while (getline(&buf, &n, fp) != -1)
	{
		line_number++;
		if (del_only(buf) == '\0')
			continue;
		tokens = tokenizer(buf, " \n\t$");
		if (strcmp(tokens[0], "push") == 0)
		{
			push_func(tokens, &stack, line_number);
			free_dp(tokens); }
		else if (strcmp(tokens[0], "nop") == 0)
		{
			free_dp(tokens);
			continue; }
		else
		{
			exit_sta = choose_func(tokens, &stack, line_number);
			free_dp(tokens); } }
	while (stack)
	{
		tmp = stack->next;
		free(stack), stack = tmp; }
	free(buf), fclose(fp);
	return (exit_sta); }
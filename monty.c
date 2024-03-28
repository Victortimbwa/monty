#include "monty.h"
/**
 * execute_opcode - function that executes an opcode
 * @opcode: The opcode to execute.
 * @line_number: The line number where the opcode is found.
 * @stack: The stack to perform operations on.
 * @arg: argument for the opcode
 *
 * Description: function takes an opcode and executes the corresponding
 * function. It handles different opcodes, like 'push' and 'pall'.
 */
void execute_opcode(char *opcode, unsigned int line_number,
		stack_t **stack, char *arg);

/**
 * main - Entry point of the Monty interpreter
 * @argc: The number of command line arguments
 * @argv: Array of command line arguments
 *
 * Return: Exit status
 * Description: The main function opens and reads a Monty bytecodes file,
 * processes each line, and executes the corresponding opcodes.
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	/*size_t read;*/
	unsigned int line_number = 0;
	stack_t *stack = NULL;
	char *opcode, *arg;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, file) != -1)
	{
		line_number++;
		opcode = strtok(line, " \n");
		arg = strtok(NULL, " \n");

		if (opcode && opcode[0] != '#')
		{
			execute_opcode(opcode, line_number, &stack, arg);
		}
	}

	free(line);
	fclose(file);
	free_stack(&stack);

	return (0);
}
/**
 * execute_opcode - function that executes an opcode
 * @opcode: The opcode to execute.
 * @line_number: The line number where the opcode is found.
 * @stack: The stack to perform operations on.
 * @arg: argument
 */
void execute_opcode(char *opcode, unsigned int line_number,
		stack_t **stack, char *arg)
{
	int i;
	instruction_t instructions[] = {
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"sub", sub},
		{"div", div_stack},
		{"mod", mod},
		{"mul", mul},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{NULL, NULL}
	};

	if (strcmp(opcode, "push") == 0)
	{
		push(stack, line_number, arg);
		return;
	}

	for (i = 0; instructions[i].opcode; i++)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, line_number);
			return;
		}
	}

	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}

#include "monty.h"
/**
 * swap - Swaps the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number in the script file.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	(*stack)->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = *stack;
	temp->next = *stack;
	temp->prev = (*stack)->prev;
	(*stack)->prev = temp;
	*stack = temp;
}

/**
 * add - Adds the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number in the script file.
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	(*stack)->next->n += temp->n;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * nop - Does nothing.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number in the script file.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * sub - subtracts top element of stack from second top element of stack
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number in the script file.
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	(*stack)->next->n -= temp->n;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * rotl - Rotates the stack to the top.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number in the script file.
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *top, *bottom;

	(void)line_number;

	if (*stack && (*stack)->next)
	{
		top = *stack;
		bottom = *stack;

		while (bottom->next)
			bottom = bottom->next;

		*stack = top->next;
		top->next->prev = NULL;
		top->next = NULL;
		bottom->next = top;
		top->prev = bottom;
	}
}

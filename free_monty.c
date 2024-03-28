#include "monty.h"

/**
 * free_stack - Frees a stack.
 * @stack: Double pointer to the top of the stack.
 */
void free_stack(stack_t **stack)
{
	stack_t *temp;

	while (*stack != NULL)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
}

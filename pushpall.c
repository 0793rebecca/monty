#include "monty.h"

/**
  * push - pushes element onto stack
  * @ sk: pointer to the structure of stack
  * intval: integer value to be pushed on stack
  */

void push(stack_t **stack, int intval)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = intval;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	*stack = new_node;
}

/**
  * pall - prints all values in stack
  * @stack: ponter that points to the structure of Stack
  */

void pall(stack_t *stack)
{
	stack_t *current = stack;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
  * file_procc - builds stack from bytecode instructions
  * @namefile: file name that hold bytecode instructions
  * @stack: pointer that points to the structure of stack
  * Return: EXIT_FAILURE on Failure, else EXIT_SUCCESS On Success
  */
int file_procc(const char *namefile,
		stack_t **stack)
{
	char row[100];
	int row_num = 0;
	char *token = strtok(row, "\t\n");
	int intval = atoi (token);

	FILE *pushpallfile = fopen(namefile, "r");

	if (pushpallfile == NULL)
	{
		fprintf(stderr, "Error: Cannot open file\n");
		return (0);
	}

	while (fgets(row, sizeof(row), pushpallfile))
	{
		row_num++;

		if (token == NULL || *token == '#')
		{
			continue;
		}
		else if (strcmp(token, "push") == 0)
		{
			token = strtok(NULL, "\t\n");

			if (token == NULL)
			{
				fprintf(stderr, "Error at row %d: usage: push integer\n", row_num);
				fclose(pushpallfile);
				return (EXIT_FAILURE);
			}

			push(stack, intval);
		}
		else if (strcmp(token, "pall") == 0)
		{
			pall(*stack);
		}
		else
		{
			fprintf(stderr, "Error at row %d: opcode unknown: %s\n", row_num, token);
			fclose(pushpallfile);
			return (EXIT_FAILURE);
		}
	}

	fclose(pushpallfile);
	return (EXIT_SUCCESS);
}

/**
  * byte_exec - function to execute bytecode on stack
  * @namefile: file name that has bytecode instructions
  * Return: On Success, EXIT_SUCCESS
  * else On Failure, EXIT_FAILURE
  */
int byte_exec(const char *namefile)
{
	stack_t *stack = NULL;

	if (!file_procc(namefile, &stack))
	{
		fprintf(stderr, "Error: Failed to execute bytecode\n");
		return (EXIT_FAILURE);
	}

	while (stack != NULL)
	{
		stack_t *temp = stack;

		stack = stack->next;
		free(temp);
	}

	return (EXIT_SUCCESS);
}

/**
  * main -Entry point of the program
  * Return: EXIT_SUCCESS On Success, else On Failure, EXIT_FAILURE
  */
int main(void)
{
	const char *namefile = "bytecodes/00.m";
	int readiness = byte_exec(namefile);

	return (readiness);
}

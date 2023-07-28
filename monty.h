#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: interger
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doublylinked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to the handle opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/*task 0*/
void push(stack_t **stack, int intval);
void pall(stack_t *stack);
int file_procc(const char *namefile,
		stack_t **stack);
int byte_exec(const char *namefile);
int main(void);

#endif

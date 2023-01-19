#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct stack
{
	size_t type;
	size_t size;
	void *data;
	int top_index;
};

typedef struct stack stack_t;

/* 
 * Stack create will create a empty stack of the
 * specified data type and size.
 */
stack_t stack_create(size_t size, size_t type);

/* 
 * Free the data field of the stack.
 */
void stack_destroy(stack_t *stack);

/* 
 * Push a element to the stack.
 * As in the nature of a stack, this will put the element
 * on the top of the stack, following LIFO directive.
 */
bool stack_push(stack_t *stack, void *elem);

/* 
 * Pops an element from the stack.
 * Will be the last inserted element (LIFO).
 */
void *stack_pop(stack_t *stack);

/* 
 * Generic typedef for functions that will print
 * different data types.
 */
typedef void (*print_fn)(void*);

/* 
 * Print integers.
 */
void print_int(void* val);

/* 
 * Print floats.
 */
void print_float(void* val);

/* 
 * Print characters.
 */
void print_char(void* val);

/* 
 * Naive way of printing stack, will sort of
 * mess up the placement of the elements.
 */
void stack_reverse_print(stack_t* stack, print_fn print);

/* 
 * Print the stack
 */
void stack_print(stack_t *stack, print_fn print);


#endif
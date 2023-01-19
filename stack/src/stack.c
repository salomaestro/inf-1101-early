#include "stack.h"


stack_t stack_create(size_t size, size_t type)
{
	size_t effective_size = type * size;

	stack_t stack = {
		.type = type,
		.size = size,
		.data = malloc(effective_size),
		.top_index = 0
	};

	return stack;
}

void stack_destroy(stack_t *stack)
{
	free(stack->data);
	stack->data = NULL;
}

/* 
 * Push a element to the stack.
 * As in the nature of a stack, this will put the element
 * on the top of the stack, following LIFO directive.
 */
bool stack_push(stack_t *stack, void *elem)
{
	/*
	 * If the top index in the stack is equal to the predefined
	 * size of the stack we cannot add any more elements. Return
	 * false to indicate that it was not possible to push another
	 * element to the stack.
	 */
	if (stack->top_index == stack->size) {
		return false;
	}

	/* 
	 * As data simply is the address of the first element of our array
	 * but stored as a void pointer we must type cast it to a char pointer
	 * as pointer arithmetic is done based on the size of the type being
	 * pointed to. By casting to a char we are telling the compiler we want 
	 * pointer arithmetic to be done in increments of 1 byte, which is what
	 * we need since we're using the top_index * type offset to move the 
	 * pointer by the number of bytes required to get to the correct location
	 * in the array.
	 */
	void *destination = (char *)stack->data + stack->top_index * stack->type;

	/* 
	 * We are now using the calculated position in the array to place elem at
	 * the correct position in the array, with its predefined size.
	 */
	memcpy(destination, elem, stack->type);

	/* 
	 * Increment the top index.
	 */
	stack->top_index++;

	return true;
}

/* 
 * Pops an element from the stack.
 * Will be the last inserted element (LIFO).
 */
void *stack_pop(stack_t *stack)
{
	/* 
	 * Check if stack is empty.
	 */
	if (stack->top_index == 0) {
		return NULL;
	}

	/* 
	 * Allocate the space for our soon to be popped element.
	 * This is just a temporary variable.
	 */
	void *elem = malloc(stack->type);

	/* 
	 * Decrement the top_index variable
	 */
	stack->top_index--;
	
	/* 
	 * Pointer arithmetic to calculate the location of the top element:
	 *              |data|       |loc_top |
	 *                v              v
	 * Memory:	xxxxxx|xxxx|xxxx|xxxx|xxxx|xxxxxxx
	 *                0    1    2    3
	 *                |------ Array ------|
	 * top_index = 3  |  type = 4
	 */
	void *loc_top = (char *)stack->data + stack->top_index * stack->type;

	/* 
	 * Copy [stack->type] amount of bytes from [loc_top]
	 * to [elem].
	 */
	memcpy(elem, loc_top, stack->type);

	/* 
	 * Set memory starting at [loc_top] till [loc_top + stack->type] to 0 
	 */
	memset(loc_top, 0, stack->type);

	return elem;
}

void print_int(void* val) 
{
    printf("%d", *(int*)val);
}

void print_float(void* val)
{
    printf("%f", *(float*)val);
}

void print_char(void* val)
{
    printf("%c", *(char*)val);
}


void stack_reverse_print(stack_t* stack, print_fn print) 
{

	printf("Stack:\n");

    for(int i=0; i<stack->top_index; i++) {
	
		printf("    %d:", i);
		printf("\t");
    
	    print((char*)stack->data + i*stack->type);
	
		printf("\n");
    }
}

void stack_print(stack_t *stack, print_fn print)
{
	printf("Stack:\n");

	for (int i=stack->top_index - 1; i >= 0; i--) {

		printf("    %d:", stack->top_index - 1 - i);
		printf("\t");

		print((char *)stack->data + i * stack->type);

		printf("\n");
	}
}

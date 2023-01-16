#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// typedef enum stack_data_type {
// 	TYPE_INT = sizeof(int),
// 	TYPE_FLOAT = sizeof(float),
// 	TYPE_CHAR = sizeof(char)
// } size_t;

typedef struct stack
{
	size_t type;
	size_t size;
	void *data;
	void *top;
	int top_index;
} stack_t;

stack_t stack_create(size_t size, size_t type)
{
	size_t effective_size = type * size;

	stack_t stack = {
		.type = type,
		.size = size,
		.data = malloc(effective_size),
		.top = NULL,
		.top_index = 0
	};

	return stack;
}

void stack_destroy(stack_t *stack)
{
	free(stack->data);
	stack->data = NULL;
}

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

void *stack_pop(stack_t *stack)
{
	if (stack->top_index == 0) {
		return NULL;
	}

	void *elem = malloc(stack->type);

	stack->top_index--;
	
	void *location_of_top = (char *)stack->data + stack->top_index * stack->type;

	memcpy(elem, location_of_top, stack->type);

	memset(location_of_top, 0, stack->type);

	return elem;
}

typedef void (*print_fn)(void*);

void print_int(void* val) {
    printf("%d", *(int*)val);
}

void print_float(void* val) {
    printf("%f", *(float*)val);
}

void print_char(void* val) {
    printf("%c", *(char*)val);
}

void stack_print(stack_t* stack, print_fn print) {
    for(int i=0; i<stack->top_index; i++) {
        print((char*)stack->data + i*stack->type);
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Error: No arguments passed\n");
        return 1;
    }

    int n = atoi(argv[1]);

    stack_t stack = stack_create(10, sizeof(int));

    int* arr = (int *)malloc(sizeof(int) * n);

    for (int i = 2; i < argc; i++) {
        arr[i-2] = atoi(argv[i]);
    }
    for (int i = 0; i < n; i++) {
        stack_push(&stack, &arr[i]);
    }

	stack_print(&stack, print_int);
    free(arr);
    return 0;
}

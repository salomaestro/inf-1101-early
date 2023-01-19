#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Error: No arguments passed\n");
        return 1;
    }

    int n = atoi(argv[1]);

    stack_t stack = stack_create(10, sizeof(float));

    float* arr = (float *)malloc(sizeof(float) * n);

    for (int i = 2; i < argc; i++) {
        arr[i-2] = atof(argv[i]);
    }
    for (int i = 0; i < n; i++) {
        stack_push(&stack, &arr[i]);
    }

	stack_print(&stack, print_float);
	
	printf("Popped: %f from the stack!\n", *(float *)stack_pop(&stack));

	stack_print(&stack, print_float);

	float *new_elem = (float *)malloc(sizeof(float));
	*new_elem = 69.1;

	printf("push: %d\n", stack_push(&stack, new_elem));

	printf("Pushed: %f to the stack!\n", *new_elem);

	stack_print(&stack, print_float);

	printf("Popped: %f from the stack!\n", *(float *)stack_pop(&stack));

    stack_print(&stack, print_float);

    free(arr);
	stack_destroy(&stack);

    return 0;
}

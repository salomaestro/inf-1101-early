#include <stdlib.h>
#include <stdio.h>

/* 
 * Given an array of integers, write a function that takes a pointer to the array, 
 * an array size and an index, and returns the value at that index.
 */
int get_array_value(int* arr, int size, int index) {
    return *(arr + index);
}

/* 
 * Given an array of integers, write a function that takes a pointer to the array, 
 * an array size and an index, and sets the value at that index to a given value.
 */
void set_array_value(int* arr, int size, int index, int value) {
    *(arr + index) = value;
}

/* 
 * Given a pointer to an array of integers, 
 * write a function that takes a pointer to the array, 
 * an array size and prints all the elements of the array.
 */
void print_array(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d, ", *(arr + i));
    }
    printf("]\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index = 2;
    int value = 10;
    print_array(arr, size);
    printf("Value at index %d before modification: %d\n", index, get_array_value(arr, size, index));
    print_array(arr, size);
    set_array_value(arr, size, index, value);
    printf("Value at index %d after modification: %d\n", index, get_array_value(arr, size, index));
    print_array(arr, size);
    printf("Elements of the array are: ");
    print_array(arr, size);
    return 0;
}

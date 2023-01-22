#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binarysearch.h"
#include "compare.h"

void test_int() {
    cmpfunc_t cmp = cmp_int;
    print_func print_int = print_integer;

    int my_data[] = {2, 3, 5, 1, 8, 9, 7, 0, 4, 6, 5};
    int data_len = 11;

    tree_t *t = tree_create(cmp, my_data, data_len, sizeof(int), 2);

    tree_print(t, print_int);

    tree_destroy(t);
}

void test_char() {
    cmpfunc_t cmp = cmp_char;
    print_func print = print_character;

    char my_data[] = "Helloworld!=?";
    int data_len = 13;

    tree_t *t = tree_create(cmp, my_data, data_len, sizeof(char), 2);

    tree_print(t, print);

    tree_destroy(t);
}

void test_str() {
    cmpfunc_t cmp = cmp_str;
    print_func print = print_string;

    char my_data[7][10] = {"Hello", "world", "I", "am", "finally",
                           "achieving", "something!"};
    // int data_len = 10;
    tree_t *t = tree_create(cmp, my_data, 7, sizeof(char) * 10, 4);

    tree_print(t, print);

    tree_destroy(t);
}

int main()
{
    // test_int();
    // test_char();
    // test_str();
    return 0;
}
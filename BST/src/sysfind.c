#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binarysearch.h"
#include "compare.h"

int main(int argc, void *argv[64]) {

    char my_data[argc-1][64];

    for (int i = 1; i < argc; i++) {
        strcpy(my_data[i-1], argv[i]);
    }

    cmpfunc_t cmp = cmp_str;
    print_func print = print_string;

    tree_t *t = tree_create(cmp, my_data, argc-1, sizeof(char) * 64, 0);

    tree_print(t, print);

    tree_destroy(t);
    return 0;
}
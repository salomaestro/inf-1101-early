#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binarysearch.h"
#include "compare.h"

int main()
{
    cmpfunc_t cmp = cmp_int;
    tree_t *tree = tree_create(cmp);

    time_t t;
    srand((unsigned) time(&t));

    for (int i = 0; i < 25; i++) {

        int *inp = malloc(sizeof(int));
        *inp = rand() % 25;
    
        tree_node_t *node;
        node = tree_createnode(inp);

        tree_insert(tree, node);
    }

    print_func print_int = print_integer;
    print_func print_char = print_character;

    tree_print(tree, print_int);

    tree_destroy(tree);
    
    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binarysearch.h"

int cmp_int(void *arg1, void *arg2)
{
    int a1, a2;
    a1 = (int)arg1; a2 = (int)arg2;

    if (a1 == a2) {
        return 0;
    } else if (a1 < a2) {
        return -1;
    } else {
        return 1;
    }
}

int main()
{
    cmpfunc_t cmp = cmp_int;

    tree_t t = create_tree(cmp);

    size_t isize = sizeof(int);

    int *i1, *i2;
    i1 = (int *)malloc(sizeof(int));
    i2 = (int *)malloc(isize);
    *i1 = 5;
    *i2 = 1;

    tree_node_t *n1, *n2;

    n1 = tree_createnode(isize, i1);
    n2 = tree_createnode(isize, i2);

    tree_insert(&t, n1);
    tree_insert(&t, n2);

    destroy_tree(&t);
    
    free(i1);
    free(i2);

    return 0;
}
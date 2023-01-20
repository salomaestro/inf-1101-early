#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

#include <stdlib.h>

struct tree_node;
struct tree;

typedef int (*cmpfunc_t) (void *, void*);

typedef struct tree_node
{
    size_t type;
    void *data;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct tree
{
    struct tree_node *root;
    cmpfunc_t cmp;
} tree_t;

tree_node_t tree_createnode(size_t type, void *data);

void tree_destroynode(tree_node_t *node);

tree_t tree_create(cmpfunc_t cmp);

void tree_destroy(tree_t *tree);

int tree_insert(tree_t *tree, tree_node_t *node);

#endif
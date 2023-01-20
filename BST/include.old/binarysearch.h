#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "list.h"

typedef struct tree_node tree_node_t;

typedef struct tree tree_t;

tree_node_t *tree_createnode(void *elem);

void tree_printnode(tree_node_t *node);

tree_t *tree_create(cmpfunc_t cmpfunc, tree_node_t *root);

int tree_insert(tree_t *tree, void *elem);

int tree_deletenode(tree_t *tree, void *elem);

int tree_find(tree_t *tree, void *elem);

void tree_print_util(tree_node_t *root, int space);

void tree_print(tree_t *tree);

#endif
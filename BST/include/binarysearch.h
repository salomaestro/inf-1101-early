#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include "compare.h"

struct tree_node;
struct tree;

typedef struct tree_node
{
    void *data;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct tree
{
    struct tree_node *root;
    cmpfunc_t cmp;
} tree_t;

tree_node_t *tree_createnode(void *data);

void tree_destroynode(tree_node_t *node);

tree_t *tree_create(cmpfunc_t cmp);

void tree_destroy(tree_t *tree);

int tree_insert(tree_t *tree, tree_node_t *node);

typedef void (*print_func) (void *);

void print_integer(void *elem);
void print_character(void *elem);
void print_floating(void *elem);
// void print_string(void *elem);

void tree_print(tree_t *tree, print_func print);

void print_util(tree_node_t *root, int space, print_func print);


#endif
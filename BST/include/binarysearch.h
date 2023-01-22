#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compare.h"

struct tree_node;
struct tree;

typedef struct tree_node
{
    int key;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct tree
{
    struct tree_node *root;
    cmpfunc_t cmp;
    void *data_arr;
    size_t arr_size;
    size_t dtype;
} tree_t;

tree_node_t *tree_createnode(int key);

void tree_destroynode(tree_node_t *node);

void *tree_node_get_data(tree_t *tree, tree_node_t *node);

void *tree_getloc(char *start, size_t step, size_t step_size);

tree_t *tree_create(cmpfunc_t cmp, void *data_arr, size_t arr_size, size_t dtype, int root_key);

void tree_destroy(tree_t *tree);

int tree_insert(tree_t *tree, tree_node_t *node);

typedef void (*print_func) (void *);

void print_integer(void *elem);
void print_character(void *elem);
void print_floating(void *elem);
void print_string(void *elem);

void tree_print(tree_t *tree, print_func print);

void print_util(tree_t *tree, tree_node_t *root, int space, print_func print);

#endif
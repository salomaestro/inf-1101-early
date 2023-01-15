#include <string.h>
#include "common.h"
#include "binarysearch.h"

typedef struct tree_node
{
	void *elem;
	tree_node_t *left;
	tree_node_t *right;
} tree_node_t;

typedef struct tree
{
	tree_node_t *root;
	cmpfunc_t cmpfunc;
} tree_t;

tree_node_t *tree_createnode(void *elem)
{
	tree_node_t *node = (tree_node_t *)malloc(sizeof(tree_node_t));

	if (!node) {
		puts("Out of memory...");
	}

	node->elem = elem;
	node->right = NULL;
	node->left = NULL;

	return node;
}

void tree_printnode(tree_node_t *node)
{
	printf("%s", (char *)node->elem);
}

tree_t *tree_create(cmpfunc_t cmpfunc, tree_node_t *root)
{
	tree_t *tree = (tree_t *)malloc(sizeof(tree_t));

	if (!tree) {
		puts("Out of memory...");
	}

	tree->root = root;
	tree->cmpfunc = cmpfunc;

	return tree;
}

int tree_find(tree_t *tree, void *elem)
{
	tree_node_t *current = tree->root;

	cmpfunc_t cmp = tree->cmpfunc;
	
	/*
	 * Check if either current element is equal to current's element,
	 * then return a 1 for true or if elem is greater and current has
	 * a right node do the comparison again but for it's right node.
	 * or likewise for the less than case.
	 */ 
	if (cmp(elem, current->elem) == 0) {
		return 1;
	} else if (cmp(elem, current->elem) < 0 && current->right) {
		tree_t *subtree = tree_create(cmp, current->right);
		
		return tree_find(subtree, elem);
	} else if (cmp(elem, current->elem) > 0 && current->left) {
		tree_t *subtree = tree_create(cmp, current->left);

		return tree_find(subtree, elem);
	} else {
		return 0;
	}
}

int tree_insert(tree_t *tree, void *elem)
{
	tree_node_t *current = tree->root;
	cmpfunc_t cmp = tree->cmpfunc;

	if (cmp(elem, current->elem) == 0) {
		return 0;
	}

	if (cmp(elem, current->elem) < 0) {
		if (current->right) {
			tree_t *subtree = tree_create(cmp, current->right);
			return tree_insert(subtree, elem);
		} else {
			current->right = tree_createnode(elem);
		}
	} else if (cmp(elem, current->elem) > 0) {
		if (current->left) {
			tree_t *subtree = tree_create(cmp, current->left);
			return tree_insert(subtree, elem);
		} else {
			current->left = tree_createnode(elem);
		}
	}
	return 1;
}

// int tree_deletenode(tree_t *tree, void *elem)
// {
// 	tree_node_t *current = tree->root;
	
// 	if (elem == current->elem) {
// 		if (!current->right) {
// 			// do something
// 		} else if (!current->left) {
// 			// do something else
// 		} else {
// 			// leaf node case

// 		}
// 	}
// }

#define COUNT 10

void tree_print_util(tree_node_t *root, int space)
{
	if (!root) {
		return;
	}

	space += COUNT;

	tree_print_util(root->right, space);

	printf("\n");
	for (int i=COUNT; i<space; i++) {
		printf(" ");
	}
	printf("%s", (char *)root->elem);

	tree_print_util(root->left, space);
}

void tree_print(tree_t *tree)
{
	tree_print_util(tree->root, 0);
}
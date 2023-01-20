#include "binarysearch.h"

/* 
 * Create a tree node.
 */
tree_node_t *tree_createnode(size_t type, void *data)
{
    // tree_node_t node = {
    //     .type = type,
    //     .data = malloc(type),
    //     .left = NULL,
    //     .right = NULL
    // };

    tree_node_t *new_node = malloc(sizeof(tree_node_t));
    if (new_node == NULL) {
        printf("error:");
        exit(1);
    }

    // new_node->data = malloc(sizeof(type));
    // if (new_node->data == NULL) {

    // }

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->type = type;


    return new_node;
}

/* 
 * Destroy tree node.
 */
void tree_destroynode(tree_node_t *node)
{
    free(node->data);
    free(node);
}

/* 
 * Create a binary tree object and allocate space for the data.
 * Will allocate space for a fixed size tree.
 */
tree_t *tree_create(cmpfunc_t cmp)
{
    // tree_t tree = {
    //     .root = NULL,
    //     .cmp = cmp
    // };

    tree_t *tree = malloc(sizeof(tree_t));
    tree->cmp = cmp;
    tree->root = NULL;

    return tree;
}

/* 
 * Destroy the tree and free memory allocated.
 */
void tree_destroy(tree_t *tree)
{
    if (!tree->root) {
        free(tree);
    }

    /* Set the current node to be the root of the tree */
    tree_node_t *curr = tree->root;

    /* 
     * Destroy only free's its data, 
     * so won't loose reference to node.
     */
    // tree_destroynode(curr);

    /* 
     * For bot left and right nodes free their data.
     */
    while (curr) {
        
    }
}

/* 
 * Insert an element to the tree.
 */
int tree_insert(tree_t *tree, tree_node_t *node)
{
    if (!node->data) {
        return 1;
    }

    if (!tree->root) {
        tree->root = node;
        return 0;
    }

    if (node->type != tree->root->type) {
        return 1;
    }

    tree_node_t *curr = tree->root;

    int cmpval;
    while (curr) {
        cmpval = cmp(node, curr);

        /* The case where to node already exists. */        
        if (!cmpval) {
            return 2;
        }

        if (cmpval < 0) {
            
            /* Assign value to current's left */
            if (!curr->left) {
                curr->left = node;
                return 0;
            }

            /* Iterate again but current is now its left node. */
            curr = curr->left;
        } else if (cmpval > 0) {
            if (!curr->right) {
                curr->right = node;
                return 0;
            }

            curr = curr->right;
        }
    }
}
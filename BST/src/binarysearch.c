#include "binarysearch.h"

/* 
 * Create a tree node.
 * Takes a void * to some data.
 */
tree_node_t *tree_createnode(void *data)
{
    tree_node_t *new_node = malloc(sizeof(tree_node_t));
    
    if (!new_node) {
        printf("Error: malloc failed.");
        exit(1);
    }

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/* 
 * Destroy tree node.
 */
void tree_destroynode(tree_node_t *node)
{
    /* Trivial case */
    if (!node) {
        return;
    }

    /* Destroy left child nodes */
    if (node->left) {
        tree_destroynode(node->left);
    }

    /* Destroy right child nodes */
    if (node->right) {
        tree_destroynode(node->right);
    }

    /* Free the data stored, then free the node. */
    free(node->data);
    free(node);
}

/* 
 * Create a binary tree object and allocate space for the data.
 * Will allocate space for a fixed size tree.
 */
tree_t *tree_create(cmpfunc_t cmp)
{
    tree_t *tree = malloc(sizeof(tree_t));

    if (!tree) {
        printf("Error: malloc failed.");
        exit(1);
    }

    tree->cmp = cmp;
    tree->root = NULL;

    return tree;
}

/* 
 * Destroy the tree and free memory allocated.
 */
void tree_destroy(tree_t *tree)
{
    /* If the root doesn't exist, tree can be destroyed. */
    if (!tree->root) {
        free(tree);
    }
    
    /* Recursively destroy each node of the tree. */
    tree_destroynode(tree->root);
}

/* 
 * Insert an element to the tree.
 */
int tree_insert(tree_t *tree, tree_node_t *node)
{
    /* Check that node is properly initialized */
    if (!node->data) {
        return 1;
    }

    /* Trivial case, node assigned to root of tree. */
    if (!tree->root) {
        tree->root = node;
        return 0;
    }

    tree_node_t *curr = tree->root;

    int cmpval;

    while (curr) {
        cmpval = tree->cmp(node->data, curr->data);

        /* Handle case where the node already exists. */        
        if (!cmpval) {
            return 2;
        }

        /* new node less than root */
        if (cmpval < 0) {
            
            /* Assign new node to current's left */
            if (!curr->left) {
                curr->left = node;
                return 0;
            }

            /* Iterate again but current is now its left node. */
            curr = curr->left;
        
        /* New node larger than root */
        } else if (cmpval > 0) {

            /* Assign new node to current's right */
            if (!curr->right) {
                curr->right = node;
                return 0;
            }

            curr = curr->right;
        }
    }
}

void print_integer(void *elem)
{
    printf("%d", *(int *)elem);
}

void print_character(void *elem)
{
    printf("%c", *(char *) elem);
}

void print_floating(void *elem)
{
    printf("%f", *(float *)elem);
}

// void print_string(void *elem)
// {
//     printf("%s", *(char *))
// }

void tree_print(tree_t *tree, print_func print)
{
    print_util(tree->root, 0, print);
}

void print_util(tree_node_t *root, int space, print_func print)
{
    if (root == NULL) 
        return;
    
    space += 10;

    if (root->right)
        print_util(root->right, space, print);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");

    print(root->data);
    printf("\n");

    if (root->left)
        print_util(root->left, space, print);
}
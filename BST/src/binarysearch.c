#include "binarysearch.h"

/**
 * @brief Create a tree node.
 * 
 * @param key 
 * @return tree_node_t* 
 */
tree_node_t *tree_createnode(int key)
{
    tree_node_t *new_node = malloc(sizeof(tree_node_t));
    
    if (!new_node) {
        printf("Error: malloc failed!\n");
        exit(1);
    }

    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/**
 * @brief Destory a node of the tree and recursively it's sub-nodes.
 * 
 * @param node
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
    // free(node->key);
    free(node);
}

/**
 * @brief Create a binary tree and allocate space for the data.
 * 
 * @param cmp       Comparison function. 
 * @param data_arr  The array with data that will be used in the tree.
 * @param arr_size  Number of elements in data array.
 * @param dtype     sizeof(data type) used in array (size of one element).
 * @param root_key  The index of the first element inserted to the tree.
 * @return tree_t* 
 */
tree_t *tree_create(cmpfunc_t cmp, void *data_arr, size_t arr_size, size_t dtype, int root_key)
{
    tree_t *tree = malloc(sizeof(tree_t));

    if (!tree) {
        printf("Error: malloc failed!\n");
        exit(1);
    }

    tree->cmp = cmp;
    tree->data_arr = data_arr;
    tree->arr_size = arr_size;
    tree->dtype = dtype;
    tree->root = NULL;

    tree_node_t *root = tree_createnode(root_key);

    int status = tree_insert(tree, root);

    /* 
     * Insert the rest of the data_arr in the tree,
     * comparing with the root node.
     */
    for (int i = 0; i < arr_size; i++) {
        
        if (status == 2)
            printf("Warning: Duplicate values, previous state preserved.\n");
        if (status == -1)
            exit(1);
        
        if (i == root_key) {
            continue;
        }
        tree_node_t *new_node = tree_createnode(i);

        status = tree_insert(tree, new_node);
    }

    return tree;
}

/**
 * @brief Destroy the tree and free memory allocated.
 * 
 * @param tree 
 */
void tree_destroy(tree_t *tree)
{
    /* If the root doesn't exist, tree can be destroyed. */
    if (tree->root == NULL) {
        free(tree);
        return;
    }
    
    /* Recursively destroy each node of the tree. */
    tree_destroynode(tree->root);
    free(tree);
}

/**
 * @brief Get the pointer (loc) to a index (step) in a array (start).
 * 
 * @param start     (char *)some_array
 * @param step      index
 * @param step_size size of elements in some_array.
 * @return void* 
 */
void *tree_getloc(char *start, size_t step, size_t step_size)
{
    void *loc = start + step * step_size;

    return loc;
}

/**
 * @brief Get the pointer to the data of a node.
 * Remember to free the return value!
 * 
 * @param tree 
 * @param node 
 * @return void* 
 */
void *tree_node_get_data(tree_t *tree, tree_node_t *node) 
{
    void *data = malloc(tree->dtype);

    void *loc = tree_getloc(
        (char *)tree->data_arr,
        (size_t)node->key,
        tree->dtype
    );

    memcpy(data, loc, tree->dtype);

    return data;
}

int tree_insert_multiple(tree_t *tree, void *elem, int num){
    tree->arr_size++;

    tree_node_t *nodes[num];

    for (int i = 0; i < num; i++) {
        nodes[i] = tree_createnode((int)tree->arr_size + i);
    }

    void *arr_dest = tree_getloc(
        (char *)tree->data_arr,
        tree->arr_size,
        tree->dtype
    );

    memcpy(arr_dest, elem, num * tree->dtype);

    int retval = 0;
    int temp_retval;
    for (int i = 0; i < num; i++) {

        temp_retval = tree_insert(tree, nodes[i]);

        if (temp_retval == -1)
            retval = temp_retval;
    }
    return retval;
}

int tree_insert_new(tree_t *tree, void *elem) {

    /* Increment size of array. */
    tree->arr_size++;

    tree_node_t *new_node = tree_createnode((int)tree->arr_size);

    void *arr_dest = tree_getloc(
        (char *)tree->data_arr,
        tree->arr_size,
        tree->dtype
    );

    /* 
     * I use memcpy here instead of memset, as memcpy works
     * with void pointers wheras memset I woul insert
     * for a specific type.
     */
    memcpy(arr_dest, elem, tree->dtype);

    return tree_insert(tree, new_node);
}

/* 
 * Insert an element to the tree.
 */
int tree_insert(tree_t *tree, tree_node_t *node)
{
    /* Trivial case, node will be assigned to root of tree. */
    if (!tree->root) {
        tree->root = node;
        return 0;
    }

    void *new_node_data = tree_node_get_data(tree, node);
    
    tree_node_t *curr = tree->root;
    int cmpval;

    while (curr) {

        void *curr_node_data = tree_node_get_data(tree, curr);

        cmpval = tree->cmp(new_node_data, curr_node_data);

        free(curr_node_data);

        /* Handle case where the node already exists. */
        if (!cmpval) {
            free(new_node_data);
            return 2;
        }

        /* new node less than root */
        if (cmpval < 0) {
            
            /* Assign new node to current's left */
            if (!curr->left) {
                curr->left = node;
                free(new_node_data);
                return 0;
            }

            /* Iterate again but current is now its left node. */
            curr = curr->left;
        
        /* New node larger than root */
        } else if (cmpval > 0) {

            /* Assign new node to current's right */
            if (!curr->right) {
                curr->right = node;
                free(new_node_data);
                return 0;
            }

            curr = curr->right;
        } else {
            printf("Unexpected error!\n");
            return -1;
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

void print_string(void *elem)
{
    printf("%s", (char *)elem);
}

void tree_print(tree_t *tree, print_func print)
{
    print_util(tree, tree->root, 0, print);
}

void print_util(tree_t *tree, tree_node_t *root, int space, print_func print)
{
    if (root == NULL) 
        return;
    
    space += 10;

    if (root->right)
        print_util(tree, root->right, space, print);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");

    void *data = tree_node_get_data(tree, root);

    print(data);

    free(data);

    printf("\n");

    if (root->left)
        print_util(tree, root->left, space, print);
}
/* Author: Christian Salomonsen */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "common.h"
#include "list.h"

typedef struct list_node
{
    void *elem;
    list_node_t *next;
    list_node_t *prev;
} list_node_t;

typedef struct list
{
    list_node_t *head;
    cmpfunc_t cmpfunc;
    size_t size;
} list_t;

/* Creates a node which preferably lives inside a list. */
list_node_t *list_node_create(void *elem)
{
    list_node_t *node = (list_node_t *)malloc(sizeof(list_node_t));

    if (node == NULL)
    {
        printf("OUT OF MEMORY");
        return node;
    }

    node->elem = elem;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

list_t *list_create(cmpfunc_t cmpfunc) {
    list_t *list = (list_t *)malloc(sizeof(list_t));
    list_node_t *head = list_node_create(NULL);

    if (list == NULL)
    {
        printf("OUT OF MEMORY");
        return list;
    }

    list->cmpfunc = cmpfunc;
    list->size = 1;
    list->head = head;

    return list;
}

void list_destroy(list_t *list)
{
    /* 
     * NB! greatly inspired by: https://stackoverflow.com/a/18412733
     * I tried to find my own way of doing it, but I once you
     * see a good implementation it is hard to forget about it ;).
     */
    list_node_t *current = list->head;

    /* 
     * Define a temporary list node to store next pointer in while destroying
     * the 'current' node.
     */
    list_node_t *temp;

    /* Iterate till current node is NULL */
    while (current != NULL)
    {

        /* 
         * Store next pointer of current node in temp node
         * such that we can free the memory position of the
         * current node without losing the pointer to the
         * next node.
         */
        temp = current->next;
        free(current);

        /* 
         * Assign current as the previously temporarily assigned
         * next node.
         */
        current = temp;
    }
    free(list);
}

int list_size(list_t *list)
{
    int retval = list->size;
    return retval;
}

int list_addfirst(list_t *list, void *elem)
{
    if (list == NULL)
    {
        return 0;
    }

    /*
     * When initializing a list with 'list_create(cmpfunc)' a head
     * node is created with head->elem = NULL. Therefore this
     * function will catch this case and modify its 'elem' to
     * the elem argument. Note, this only triggers when there
     * is only one node in the list.
     */
    if (list->head->elem == NULL && list->head->next == NULL)
    {
        list->head->elem = elem;
        return 1;
    }

    /* Generate a new node and put 'elem' inside its 'elem' slot. */
    list_node_t *new_node = list_node_create(elem);

    /* Set the next of the node as the list's head. */
    new_node->next = list->head;

    /* Set lists head as the new node. */
    list->head = new_node;

    /* Set head's prev as the new node. */
    new_node->next->prev = new_node;

    /* Update size of list */
    ++list->size;

    return 1;
}

int list_addlast(list_t *list, void *elem)
{
    /* Check that list exist. */
    if (list == NULL)
    {
        return 0;
    }

    /*
     * When initializing a list with 'list_create(cmpfunc)' a head
     * node is created with head->elem = NULL. Therefore this
     * function will catch this case and modify its 'elem' to
     * the elem argument. Note, this only triggers when there
     * is only one node in the list.
     */
    if (list->head->elem == NULL && list->head->next == NULL)
    {
        list->head->elem = elem;
        return 1;
    }

    /* Construct new node with new data. */
    list_node_t *new_node = list_node_create(elem);

    /* Set current node as head, then iterate till last node. */
    list_node_t *current = list->head;
    
    while (current->next != NULL)
    {
        current = current->next;
    }
    
    /* Set next of last node to the new node. */
    current->next = new_node;

    /* Set the prev of the new node as the formerly last node. */
    new_node->prev = current;
    
    /* Increase list size by one. */
    ++list->size;

    return 1;
}

void *list_popfirst(list_t *list)
{
    /* Get the head node and exctract its value. */
    list_node_t *head = list->head;
    void *elem = head->elem;

    /* Set list's new head to head's next pointer. */
    list->head = head->next;

    /* Subtract one from the list size. */
    --list->size;

    /* Free up memory of head. */
    free(head);

    if (list->size == 1)
    {
        list_destroy(list);
    }

    return elem;
}

void *list_poplast(list_t *list)
{
    list_node_t *current = list->head;
    list_node_t *last;
    void *elem;

    if (list->size == 1)
    {
        elem = current->elem;
        list_destroy(list);        
        return elem;
    }

    /* Iterate till next to last node. */
    while (current->next->next != NULL)
    {
        current = current->next;
    }

    /* Set last to be the last node of the list */
    last = current->next;

    /* Set return value */
    elem = last->elem;

    /* 
     * Set next of current to be NULL, meaning the last node will not 
     * have any nodes pointing to it anymore. 
     */
    current->next = NULL;

    /* Reduce list size. */
    --list->size;

    /* Free its memory. */
    free(last);

    return elem;
}

int list_contains(list_t *list, void *elem)
{
    list_node_t *current = list->head;
    int retval = 0;
    
    while (current != NULL)
    {
        /* If elem is in list, set the return value to 1. */
        if (current->elem == elem)
        {
            retval = 1;

            /* 
             * As the implementation only asks too find at least
             * one occurence of the input element in the list
             * we may break the loop to save time if a single
             * occurence is found.
             */
            break;
        }
        current = current->next;
    }
    return retval;
}

void list_nodeswap(list_node_t *node) 
{
    /* Store adjacent nodes to the argument node. */
    list_node_t *next = node->next;

    void *elem = node->elem;
    node->elem = next->elem;
    next->elem = elem;
}

void list_sort(list_t *list)
{
    /* 
     * This implementation is pretty basic and use what I think is
     * a pretty common approach of assuming each entry of the list
     * needs to move and is given one try traversing the list. This
     * is the outer loop. Then an inner loop handles the traversing.
     * Although each entry is given one try each element is compared
     * in every inner loop. 
     * To save some computations if the inner loop does not change
     * the position of any entries, we terminate the function as this
     * would indicate there is nothing left to sort.
     */

    const int size = list->size;

    /* Outer loop. */
    for (int try = 0; try < size - 1 ; ++try)
    {
        /* Each iteration of outer loop start at the head node. */
        list_node_t *current = list->head;

        /* 
         * Variable that will terminate function if no nodes are
         * swapped. 
         */
        int sorted = 0;

        /* 
         * Inner loop.
         * Each time a outer loop is completed we know that the
         * number of tries correspond to how many (from the tail)
         * is already sorted correctly, therefore there is no need
         * to sort the last element sorted in the previous try.
         */
        for (int i = 0; i < size - try - 1; ++i)
        {
            /* Initialize next node */
            list_node_t *next = current->next;

            /* Get the compared value produced by the list' compare func. */
            const int cmpval = list->cmpfunc(current->elem, next->elem);

            /* 
             * Here we could implement an alternative to the reverse 
             * sorting algorithm in 'reverseword.c' by instead using
             * cmpval == -1. 
             */
            if (cmpval == 1)
            {
                /* Perform a node swap if criteria met. */
                list_nodeswap(current);

                /* Prevent early termination. */
                sorted = 1;
            }

            /* Increment to next node. */
            current = current->next;
        }
        
        /* 
         * Break early if there is no changes between each list 
         * traverse.
         */
        if (!sorted){
            break;
        }
    }
}

void list_print(list_t *list, int brackets, char *sep)
{
    list_node_t *current = list->head;
    char *default_sep = ", ";

    if (current == NULL)
    {
        printf("ERROR: Head node not initialized! Trying to print list without head node.\n");
        exit(0);
    }

    /* If brackets = 1 use brackets */
    printf(brackets ? "[" : "");

    /* Iterate till last node */
    while (current->next != NULL)
    {
        /* Because elem is a void pointer type-cast it to a string. */
        printf("%s", (char*)current->elem);
        current = current->next;

        !strcmp(default_sep, sep) ? printf("%s", default_sep) : printf("%s", sep);
    }

    /* Print last element */
    printf("%s", (char*)current->elem);

    /* If brackets = 1 use brackets */
    printf(brackets ? "]\n" : "\n");
}

void list_reverse(list_t *list)
{
    /* Initialize nodes */
    list_node_t *current, *prev, *next;
    prev = NULL;

    /* 
     * Set current to list' head, test expr in for loop is eqivalent
     * to while (current !=NULL) and increment by current = next
     */
    for (current=list->head; current; current = next) {

        /* Store current nodes original next pointer. */
        next = current->next;

        /* 
         * Modify current nodes next pointer to point 
         * in opposite direction.
         */
        current->next = prev;

        /* Set the previous node to be current before incrementing. */
        prev = current;
    }

    /* Before terminating set head of list to be the last node in
     * input list.
     */
    list->head = prev;
}

typedef struct list_iter
{
    list_t *list;
    list_node_t *current;
} list_iter_t;

list_iter_t *list_createiter(list_t *list)
{
    list_iter_t *iter = (list_iter_t *)malloc(sizeof(list_iter_t));

    if (iter == NULL)
    {
        printf("OUT OF MEMORY");
        exit(-1);
    }

    iter->list = list;
    iter->current = list->head;

    return iter;
}

void list_destroyiter(list_iter_t *iter)
{
    free(iter);
}

int list_hasnext(list_iter_t *iter)
{
    return iter->current != NULL;
}

void *list_next(list_iter_t *iter)
{
    void *elem = NULL;

    if (iter->current)
    {
        elem = iter->current->elem;
        iter->current = iter->current->next;
    }

    return elem;
}

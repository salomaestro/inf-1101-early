#include "compare.h"

/**
 * @brief Compare two integers stored as void pointers.
 * Returns 0 if equal, -1 if first < second and
 * 1 if first > second.
 * 
 * @param arg1 
 * @param arg2 
 * @return int 
 */
int cmp_int(void *arg1, void *arg2)
{
    int a1, a2;
    a1 = *(int *)arg1; a2 = *(int *)arg2;

    if (a1 == a2) {
        return 0;
    } else if (a1 < a2) {
        return -1;
    } else {
        return 1;
    }
}

/**
 * @brief Compare two characters stored as void pointers.
 * Return 0 if equal, -1 if first < second and
 * 1 if first > second.
 * 
 * @param arg1 
 * @param arg2 
 * @return int 
 */
int cmp_char(void *arg1, void *arg2)
{
    char *a1, *a2;
    a1 = (char *)arg1; a2 = (char *)arg2;

    int cmpval = strcmp(a1, a2);
    if (cmpval == 0) {
        return 0;
    } else if (cmpval > 0) {
        return -1;
    } else {
        return 1;
    }
}

int cmp_str(void *arg1, void *arg2)
{
    char *a1, *a2;
    a1 = (char *)arg1; a2 = (char *)arg2;

    int cmpval = strcmp(a1, a2);
    if (cmpval == 0) {
        return 0;
    } else if (cmpval > 0) {
        return -1;
    } else {
        return 1;
    }
}
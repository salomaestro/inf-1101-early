#include "compare.h"

/* 
 * Compare two integers stored as void pointers.
 * Returns 0 if equal, -1 if first < second and
 * 1 if first > second.
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
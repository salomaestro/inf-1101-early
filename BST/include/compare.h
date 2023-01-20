#ifndef COMPARE_H
#define COMPARE_H

typedef int (*cmpfunc_t) (void *, void*);

int cmp_int(void *arg1, void *arg2);

#endif
#ifndef COMPARE_H
#define COMPARE_H

#include <string.h>

typedef int (*cmpfunc_t) (void *, void*);

int cmp_int(void *arg1, void *arg2);
int cmp_char(void *arg1, void *arg2);
int cmp_str(void *arg1, void *arg2);

#endif
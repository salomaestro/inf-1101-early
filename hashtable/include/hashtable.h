#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRLEN 256
#define TABLE_SIZE 10

typedef struct{
    char name[MAX_STRLEN];
    int age;
} person;

typedef unsigned int (*hash_t) (char *);

typedef struct {
    hash_t hash;

}

void create_hashtable(size_t table_size) {

}

void init_hash_table();

void print_table();

unsigned int hash(char *name);

#endif
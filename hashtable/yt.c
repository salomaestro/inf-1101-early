#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRLEN 256
#define TABLE_SIZE 10

typedef struct{
    char name[MAX_STRLEN];
    int age;
} person;

person * hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_STRLEN);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = hash_value * name[i];
    }
    return hash_value % TABLE_SIZE;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void print_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
}

int main() {
    init_hash_table();

    print_table();

    printf("Jostein => %u\n", hash("Jostein"));
    printf("Mauritz => %u\n", hash("Mauritz"));
    printf("Jonny => %u\n", hash("Jonny"));
    printf("Jæren => %u\n", hash("Jæren"));
    printf("Pølsa => %u\n", hash("Pølsa"));
    printf("Prikken => %u\n", hash("Prikken"));
    printf("Kråka => %u\n", hash("Kråka"));
    printf("Kenneth => %u\n", hash("Kenneth"));
    printf("Tove => %u\n", hash("Tove"));

    return 0;
}
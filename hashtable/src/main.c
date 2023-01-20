#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <hashtable.h>

int main()
{
    init_hash_table();

    print_table();

    printf("Jacob => %u\n", hash("Jacob"));
    printf("Ogrel => %u\n", hash("Ogrel"));
    printf("Jonny => %u\n", hash("Jonny"));
    printf("Jæren => %u\n", hash("Jæren"));
    printf("Pølsa => %u\n", hash("Pølsa"));
    printf("Prikken => %u\n", hash("Prikken"));
    printf("Kråka => %u\n", hash("Kråka"));
    printf("Kenth => %u\n", hash("Kenth"));
    printf("Tove => %u\n", hash("Tove"));

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char binary[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
const char *digits = "0123456789abcdef";
const char *abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* hex2bin(char *input) {
    int len = strlen(input);
    char *res[1024];
    int p = 0;

    while (input[p]) {
        const char *v = strchr(digits, input[p++]);
        if (v)
            strcat(res, binary[v - digits]);
    }

    return res;
}


int main()
{
    const char *hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    const char *wanted = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

    const int len = strlen(hex);

    char inp[len];
    strcpy(inp, hex);

    /* 
     * Function call here to return wanted.
     */

    char *res = hex2bin(inp);

    puts(res);

    free(res);

    return 0;


    // if (strcmp(hex, wanted)) {
    //     printf("Error: Strings do not match!");
    // }

    // printf("Strings match, success!");
}
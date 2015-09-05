#include <stdio.h>

// Source: http://www.cse.yorku.ca/~oz/hash.html

unsigned long hash(unsigned char* str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./djb2 string\n")
        return 1;
    }
    printf("Hash value is: %lu", hash(argv[1]));
    return 0;
}

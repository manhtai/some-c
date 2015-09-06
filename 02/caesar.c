#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    // Check agrc
    if (argc != 2)
    {
        printf("Usage: ./caesar k");
        return 1;
    }

    // Get k from argv, converted to int
    int k = atoi(argv[1]);

    // Change k to k mod 26
    k %= 26;

    // Get plain text
    string s = GetString();

    // Check s
    if (s == NULL)
        return 1; // Error

    // Encrypt it
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i])) // Convert just letter
        {
            if (islower(s[i]))
                printf("%c", (s[i] - 'a' + k) % 26 + 'a');
            else
                printf("%c", (s[i] - 'A' + k) % 26 + 'A');
        }
        else
            printf("%c", s[i]); // Keep the not letter unchanged
    }

    printf("\n");

    return 0; // Success
}

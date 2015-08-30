#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char* argv[])
{
    // Check agrc
    if (argc != 2)
        return 1;

    // Get k from argv
    string k = argv[1];

    // Check k
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!isalpha(k[i]))
            return 1;
    }

    // Get plain text
    string s = GetString();

    // Check s
    if (s == NULL)
        return 1; // Error

    // Init len and count for get letters from key
    int len = strlen(k);
    int count = 0;
    // Encrypt it
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i])) // Convert just alphabet letters
        {
            count %= len;
            if (islower(s[i]))
                printf("%c", (s[i] - 2*'a' + k[count++]) % 26 + 'a');
            else
                printf("%c", (s[i] - 2*'A' + k[count++]) % 26 + 'A');
        }
        else
            printf("%c", s[i]); // Keep the not alphabet letters unchanged
    }

    return 0; // Success
}

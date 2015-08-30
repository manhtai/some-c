#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(void)
{
    // Get name
    string s = GetString();

    // Check s
    if (s == NULL)
        return 1; // Error

    // Get first letter capitalized
    if (islower(s[0]))
        printf("%c", toupper(s[0]));
    else
        printf("%c", s[0]);

    // Get other letters capitalized
    for (int i = 1, n = strlen(s); i < n-1; i++)
    {
        if (s[i] == ' ')
        {
            if islower(s[i+1])
                printf("%c", toupper(s[i+1]));
            else
                printf("%c", s[i+1]);
        }
    }

    return 0; // Success
}

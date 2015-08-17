#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = 0;
    
    // Get height from keyboard
    do
    {
        printf("Height: ");
        n = GetInt();
    }
    while (n < 0 || n > 23);
    
    // Print tower
    for (int i = 0; i < n; i++)
    {
        // Print space
        for (int j = n-i-1; j > 0; j--)
            printf(" ");
            
        // Print #
        for (int j = 0; j < i+2; j++)
            printf("#");
        printf("\n");
    }
}

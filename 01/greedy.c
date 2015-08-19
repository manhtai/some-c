#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get change from keyboard
    float dollar = 0;
    do
    {
        printf("How much change is owned?\n");
        dollar = GetFloat();
    }
    while (dollar < 0);

    // Convert to cents
    int cents = dollar * 100;
    
    // Greedy algorithm to change
    float coins[] = {25, 10, 5, 1};
    int i = 0;
    int count = 0;
    while (i < 4)
    {
        while (cents >= coins[i])
        {
            cents -= coins[i];
            count++;
        };
        i++;
    };
    printf("%d\n", count);
}

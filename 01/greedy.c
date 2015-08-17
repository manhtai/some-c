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
    // Must use array here
    float coins[4];
    coins[0] = 25;
    coins[1] = 10;
    coins[2] = 5;
    coins[3] = 1;
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

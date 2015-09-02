/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Binary search
    int low = 0, hig = n-1;
    while (low <= hig)
    {
        int mid = (low + hig) / 2;
        if (value == values[mid])
            return true;
        else if (value < values[mid])
            hig = mid - 1;
        else
            low = mid + 1;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Insertion sort
    for (int i = 1; i < n; i++)
    {
        int key = values[i];
        int k = i - 1;
        while (k >= 0 && key < values[k])
        {
            values[k+1] = values[k];
            k--;
        }
        values[k+1] = key;
    }
}

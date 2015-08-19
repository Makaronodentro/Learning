/**
 * greedy.c
 *
 * Georgios Kontogiannis
 *
 * Computer Science 50
 * Problem Set 1
 *
 * Calculates minimum number of coins for change.
 */
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Ensure non-negative input
    float f;
    do
    {
        printf("O hai! How much change is owed?");
        f = GetFloat();
    }
    while(f <= 0);
    
    // Calculate number of coins needed
    f = f*100;
    int d = roundf(f);        // Round the amount
    int c;                    // Initialize counter
    

        // Quarters
            c = d/25;
            d %= 25;
        
        // Dimes
            c += d/10;
            d %= 10;
        
        // Nickles
            c += d/5;
            d %= 5;
        
        // Pennies
            c += d/1;
            d %= 1;

    
    printf("%d\n", c);
    
    return 0;
}

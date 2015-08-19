/**
 * mario.c
 *
 * Georgios Kontogiannis
 *
 * Computer Science 50
 * Problem Set 1
 *
 * Prompts for pyramid height and returns a half pyramind with the respective height.
 */
#include <cs50.h>
#include <stdio.h>

int main (void)
{
    // Prompt for height and ensure that 0<=h<=23
    int h;
    do
    {
        printf("Height:");
        h = GetInt();
    }
    while(h < 0 || h > 23);   
    
    // Pyramid
    for(int i = 0; i < h; i++)
    {
        //Print Spaces 
        for(int j = 0; j < h-i-1; j++)
        {
            printf(" ");
        }
               
        //Print #
        for(int j = 0; j < i + 2; j++)
        {
            printf("#");
        }        
       
        //Print new lines
        printf("\n");
    }
}

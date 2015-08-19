/**
 * caesar.c
 *
 * Georgios Kontogiannis
 *
 * Computer Science 50
 * Problem Set 2
 *
 * Encrypts text using a caesar cypher.
 */
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    int k;
    // Check user input
    if (argc != 2) // Checks for 1 argument
    {
        printf("Please make sure you provide one integer as a key\n");
        
        return 1;
    }
    else 
    {
            // Checks if key is positive and numerical
            k = atoi(argv[1]);
            if (!k || k < 0)
            {
                printf("Please make sure you provide a non-negative numerical key\n");
                return 1;
            }
    
    }
    
    // Prompt user to input simple text
    string t = GetString();
    
    // Convert to ciphertext
    for(int i = 0 , n = strlen(t); i < n; i++)
    {
        if(isalpha(t[i])) // Ignore all non-alphabetic input
        {
            if(islower(t[i]))
            {
                t[i] = 'a' + (t[i]- 'a' + k % 26)%26;
            }
            else 
            {
                t[i] = 'A' + (t[i] - 'A' + k % 26)%26;
            }
        }
    }
    
    // Return ciphertext
    printf("%s\n", t);
    
    return 0;

}

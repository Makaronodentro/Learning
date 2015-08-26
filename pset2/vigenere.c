/**
 * vigenere.c
 *
 * Georgios Kontogiannis
 *
 * Computer Science 50
 * Problem Set 2
 *
 * Encrypts text using a vigenere cypher.
 */
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    // Check if appropriate user input has been obtained
    if (argc != 2) // Checks for correct number of arguments
    {
        printf("Please make sure you provide a key\n");
        
        return 1;
    }
    
    for (int i = 0 , n = strlen(argv[1]);  i < n; i++) // Checks for the validity of the key
    {
            if (isalpha(argv[1][i]) == false)
            {
                printf("Please make sure you provide an alphabetic key\n");
                return 1;
            }
            
    }
    
    
    // Convert the key to numerical
    
    int lk = strlen(argv[1]); // Length of key to avoid recalculating it.
    
    int k [lk]; // Array to store the numerical key
    
    for(int i = 0, n = lk; i < n; i++)
    {
        if(isupper(argv[1][i]))
        {
            k[i] = argv[1][i] - 'A';
        }
        else
        {
            k[i] = argv[1][i] - 'a';
        }
    }
    
    // Ask for plaintext and convert to ciphertext
    
    string t = GetString();
    
    int lt = strlen(t); // Length of text to avoid recalculating it
    
    int c = 0; // Count of repetitions
    
    for(int i = 0; i < lt; i++)
    {
            if(isalpha(t[i]))
            {
                if(islower(t[i]))
                {
                    t[i] = 'a' + (t[i]- 'a' + k[c%lk] % 26)%26;
                }
                else 
                {
                    t[i] = 'A' + (t[i] - 'A' + k[c%lk] % 26)%26;
                }
                
                c++;
           }
        
    }
    
    // Print ciphertext
    printf("%s\n", t);
    
    return 0;

}

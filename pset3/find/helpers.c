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
    // TODO: implement a searching algorithm  || CHECK ! 
    for(int i = 0; i < n; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
 
 /*
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm 
    
    //Selection Sort
    for(int i = 0; i < n - 1; i++)
    {
        int min = i;
        
        for(int j = i + 1; j < n; j++)
        {
            if(values[j] < values[min])
            {
                min = j;
            }
            
        }
        
        if(values[min] != values[i])
        {
            swap(&values[min] , &values[i]);
        }
    }
    
    return;
}

*/

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b; //swaps location a with location b
    *b = tmp;
}


void sort(int values[], int n)
{   
    //Bubble Sort
    int max = 0;
    int check = 0;
    do
    {
        check = 1;
        for(int i = 0; i < n - 1 - max; i++)
        {
            if(values[i] > values[i + 1])
            {
                swap(&values[i] , &values[i+1]);
                check = 0;
            }
        }
        max = max + 1;
    }
    while(check != 1);
    
    return;
}















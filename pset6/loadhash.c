/*
* load.c
*
*
*
*
* loads a dictionary file to memory.
*/

#include <stdio.h>
#include <cs50.h>
#include <stdint.h>
#include <stdlib.h>


#define DICTIONARY "/home/cs50/pset6/dictionaries/small"

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

int main (void)
{   
    //file i/o for dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", DICTIONARY);
        return false;
    }
    
    //initiate hashtable
    node* hashtable[27];
    for(int i; i < 27; i++)
    {
        hashtable[i] = (node*)malloc(sizeof(node*));
    }

    //populate hastable 

    //int* dsize; //count dictionary size
    //dsize = malloc(sizeof(int));
    
    node* current;
    current = (node*)malloc(sizeof(node*));
    current = hashtable[0];
    node* previous;
    
    while(fscanf(fp, "%s", current->word) != EOF)
    {
        printf("%s\n", current->word); //debugging
        current->next = (node*)malloc(sizeof(node*));
        //hash function
        if(current->word[0] != previous->word[0])
        {
            hashtable[current->word[0] - 97] = current;
            previous->next = NULL;
            previous = hashtable[current->word[0] - 97];
            current = current->next;
        }
        else
        {
            previous = current;
            current = current -> next;
        }
        
    }

    printf("Locked and loaded!");

    //free before exiting
    
    return 0;
}

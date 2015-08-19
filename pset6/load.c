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
    bool is_word;
    struct node* children[27];
}
node;

int main (void)
{   
    //file i/o for dictionary
    FILE* fp = fopen(DICTIONARY, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", DICTIONARY);
        return 1;
    }
        

    node* root;
    root = (node*)malloc(sizeof(node*));
    if(root == NULL)
    {
        return 1;
    }

    for(int i = 0; i < 27; i++)
    {
        root->children[i] = NULL;
    }
    
    node* current; //pointer to preserve the address of the current child
    current = root;
    
    char fc;
    fc = (char)malloc(sizeof(char));
    
    while(fread(&fc, sizeof(char), 1, fp) == 1)
    {
        printf("%c", fc); //Debugging
        
        if(fc > 96 && fc < 123) //if character is a letter
        {
            if(current == root) //if at start of a word
            {
                //check if letter exists already
                    //no? 1_malloc 2_set the pointer 3_initialize
                if(root -> children[fc - 97] == NULL)
                {
                    root -> children[fc - 97] = (node*)malloc(sizeof((node*)+1)); //1
                    if(root->children[fc - 97] == NULL)
                    {
                        return 1;
                    }
                    
                    current = root -> children[fc - 97]; //2
                    
                    for(int i = 0; i < 27; i++) //3
                    {
                        current->children[i] = NULL;
                    }                     
                }
                else //yes? 2_set the pointer
                {
                    current = root -> children[fc - 97]; //2
                }
            }
            else //if at middle of word
            {
                //does the current letter exist?
                    //no? 1_malloc 2_set the pointer 3_initialize
                if(current -> children[fc - 97] == NULL)
                {
                    current -> children[fc - 97] = (node*)malloc(sizeof((node*)+1));//1
                    if(current -> children[fc - 97] == NULL)
                    {
                        return 1;
                    }
                    
                    current = current -> children[fc - 97]; //2 
                                       
                    for(int i = 0; i < 27; i++)//3
                    {
                        current->children[i] = NULL;
                    }
                }
                else //yes? 2_set the pointer
                {
                    current = current -> children[fc - 97]; //2
                }
            }
        }
        else if(fc == 39) //if character is an apostrophe
        {
                //does the current apostrophe exist?
                    //no? 1_malloc 2_set the pointer 3_initialize 
                if(current -> children[fc - 13] == NULL)
                {
                    current -> children[fc - 13] = (node*)malloc(sizeof((node*)+1)); //1
                    if(current -> children[fc - 13] == NULL)
                    {
                        return 1;
                    }
                    
                    current = current -> children[fc - 13]; //2                    
                    
                    for(int i = 0; i < 27; i++) //3
                    {
                        current->children[i] = NULL;
                    }
                }
                else //yes? 2_set the pointer
                {
                    current = current -> children[fc - 13]; //2
                }
        }
        else if(fc == 10) //if character is a new line feed
        {
                current -> is_word = true;
                current = root;
        }
    }

    printf("Locked and loaded!");

    //free before exiting
    //trie freeing
    

    
    return 0;
}

/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

node* hashtable[HASHSIZE];

unsigned int dsize = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    if(strlen(word) > 45)
        return false;
        
    char* currentword = (char*)calloc(1, strlen(word)+1);
    if(currentword == NULL)
    {
        //printf("Could not malloc.\n");
        return false;
    }
    
    for(int i = 0, n = strlen(word); i < n; i++)
    {
        currentword[i] = tolower(word[i]);
    }
    
    int hashindex = hashfunction(currentword);
    
    if(hashtable[hashindex]->next == NULL)
    {
        free(currentword);
        return false;
    }
    else
    {
        node* ptr;
        ptr = hashtable[hashindex]->next;
        while(ptr != NULL)
        {
            if(strcmp(ptr->word, currentword) == 0)
            {
                free(currentword);
                return true;
            }
            ptr = ptr->next;
        }
    }
    
    free(currentword);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    // Initialize Hash Table
    for(int i = 0; i < HASHSIZE; i++)
    {
        hashtable[i] = (node*)calloc(1, HASHSIZE*sizeof(node));
    }
    
    if(hashtable == NULL)
    {
        //printf("Could not malloc hashtable.\n");
        return false;
    }
    
    //open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        //printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    char word[LENGTH + 1];
    
    while(fscanf(fp, "%s",word) != EOF)
    {
        // Count Size
        dsize++;
        
        // Get Hash Index for Word
        int hashindex = hashfunction(word);
        
        // Check Hash Index Size
        if(hashindex > HASHSIZE)
        {
            //printf(" Hash index %d is greater than the allowed size of %d\n", hashindex, HASHSIZE);
            return false;
        }
        
        // Create a new Node
        node* new;
        new = (node*)calloc(1, sizeof(node));
        if(new == NULL)
        {
            //printf("Could not create a new node.\n");
            return false;
        }
        new->word = (char*)malloc(sizeof(char[strlen(word)+1]));
        if(new->word == NULL)
            return false;
        strcpy(new->word, word);
        
        // Place the node in the correct space in the hashtable
            // If the index empty
            if(hashtable[hashindex]->next == NULL)
            {
                hashtable[hashindex]->next = new;    
            }
            else
            {
                new->next = hashtable[hashindex]->next;
                hashtable[hashindex]->next = new;
            }
        
        //printf("HASH: %s: %d\n", word, hashindex);
    }
    
    fclose(fp);
         
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return dsize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    for(int i = 0; i < HASHSIZE; i++)
    {
        while(hashtable[i]->next != NULL)
        {
            node* ptr;
            if(hashtable[i]->next != NULL)
            {
                ptr = hashtable[i]->next;
                hashtable[i]->next = hashtable[i]->next->next;
                free(ptr->word);
                free(ptr);
            }
        }
        
    }
    
    for(int i = 0; i < HASHSIZE; i++)
    {
        free(hashtable[i]);
    }    
    return true;
}

/**
 * Returns a hash index for a given word
 */
int hashfunction(char* word)
{
    // initialize index
    int hashindex = 0;
    
    // for each char in the word
    for(int i = 0, n = strlen(word); i < n; i++)
    {
        // for the first char
        if(i == 0)
            hashindex += (word[i] << 1);
        else
            hashindex += (word[i] >> 1);
    }
    
    return (hashindex % HASHSIZE);
}

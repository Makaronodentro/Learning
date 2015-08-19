bool check(const char* word)
{
    // TODO
    if(strlen(word) > 45)
        return false;
        
    char* currentword = (char*)malloc(sizeof(word));
    if(currentword == NULL)
    {
        printf("Could not malloc.\n");
        return false;
    }
    
    for(int i = 0, n = strlen(word); i < n; i++)
    {
        currentword[i] = tolower(word[i]);
    }
    
    int hashindex = hashfunction(currentword);
    
    if(hashtable[hashindex].next == NULL)
    {
        free(currentword);
        return false;
    }
    else
    {
        node* ptr;
        ptr = hashtable[hashindex].next;
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

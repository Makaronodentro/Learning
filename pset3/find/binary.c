#include <stdbool.h>


bool binary_search(int value, int values[], int n)
{
    int beginning = 0;
    int ending = n-1;
    
    while (ending >= beginning)
    {
        int middle = (beginning + ending) / 2;
        
        //look at middle of list
        if (value == values[middle])
        {
            //if number found return true
            return true;
        }
        // else if middle higher, search left
        else if (values[middle] > value)
        {
            end = middle - 1;
        }
        else
        {
            beginning = middle + 1;
        }
    }
    
    return false;

}

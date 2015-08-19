/**
* selection.c
*
* week 3 section
* 
*
* selection sort implementation
*/

void selection_sort(int values[], int n)
{
    //while the list is out of order
    for(int i = 0; i < n; i++)
    {
        int smallest = values[i]; // redundant
        int smallest_location = i;
  
        // go through the entire list
        for(int j = 0; j < n; j++)
        {
            // find the smallest number
            if(smallest > values[j])
            {
                smallest = values[j];
                smallest_location = j;
            }
            // place it in the beginning of the list
            values[smallest_location] = values[i];
            
            // put the beginning of the list where the smallest number was
            values[i] = smallest;
        }
    }
}

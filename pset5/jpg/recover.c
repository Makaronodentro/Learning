/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;


int main(int argc, char* argv[])
{
    if (argc != 1)
    {
        printf("Usage: ./recover\n");
        return 1;
    }

    // remember filenames
    char* infile = "card.raw";

    // open input file 
    FILE* src = fopen(infile, "r");
    if (src == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
    
    FILE* dst = NULL;
    
    BYTE buffer[512];
    
    int name = 0; //counter for names
    char* title = malloc(8); //stores new files name, to enable writing.
    int found = 0; //becomes 1 after the first file is found.
    
    //repeat until end of card
    while(fread(&buffer, sizeof(BYTE), 512, src) == 512)
    {
        
        //start of a new jpg?
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1)) 
        {
            
            //yes -> create a new jpg
            sprintf(title, "%.3d.jpg", name);
            name++;
            
            if (found == 1)
            {
                fclose(dst);
            }
            
            dst = fopen(title, "w"); 
            if (dst == NULL)
            {
                fclose(dst);
                printf("Could not create %s.\n", title);
                return 2;
            }
            
            found = 1;
            
        }
            //no -> do nothing
        
        //Have you found a jpeg?
        if(found == 1)
        {   
            //Write the buffer into the new file
                fwrite(&buffer, sizeof(BYTE), 512, dst); 
        }

    }
    
    //close any remaining files & free memory
    free(title);
    
    // close infile
    fclose(src);

    // close outfile
    fclose(dst);

    // that's all folks
    return 0;

} //check50 2014/x/pset5/recover recover.c

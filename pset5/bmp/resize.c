/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP by a specific factor piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    //ensure a numerical value for n has been given
    
    for (int i = 0 , n = strlen(argv[1]);  i < n; i++)
        {
            if (isdigit(argv[1][i]) == 0 && argv[1] < 0)
            {
                printf("Please provide a numerical resize scale\n");
                return 4;
            }
            
        }
    

    //convert arg[1] to int
    
    int n = atoi(argv[1]);
    
    if(n < 1 || n > 100)
    {
        return 5;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding for scanlines


    int padding1 =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding2 =  (4 - (n * bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // change temporary BITMAPFILEHEADER
    bf.bfSize = (n * bi.biWidth * sizeof(RGBTRIPLE) + padding2) * abs(bi.biHeight) * n + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
        
    // change temporary BITMAPINFOHEADER
    bi.biWidth = n * bi.biWidth;
    bi.biHeight = n * bi.biHeight;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding2) * abs(bi.biHeight);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int scanline[bi.biWidth/n];

    // iterate over infile's scanlines
    for (int i = 0, h = abs(bi.biHeight)/n; i < h; i++)
    {
        
         // iterate over pixels in scanline
         for (int j = 0; j < bi.biWidth/n; j++)
         {
             // read RGB triple from infile
             fread(&scanline[j], sizeof(RGBTRIPLE), 1, inptr);
         }
         
         for (int l = 0; l < n; l++)
         {
         for(int j = 0; j < bi.biWidth/n; j++)
         {
            for(int k = 0; k < n; k++)
            {
               // write RGB triple to outfile
               fwrite(&scanline[j], sizeof(RGBTRIPLE), 1, outptr);
            }       
         }
         
         //add new padding
         for (int k = 0; k < padding2; k++)
         {
            fputc(0x00, outptr);
         }
         }
         
         // skip over padding, if any
         fseek(inptr, padding1, SEEK_CUR);
         
    }
    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

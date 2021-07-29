#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* TODO:
    [x] open memory card file
    [] find begining of jpeg file
        - first 3 bytes are always the same
            0xff 0xd8 0xff
        - forth byte is always 0xE? where "? is 0 - F
        - images are stored contigiously in memory
    [] open a new jpeg
        - there should be 50 jpeg images
    [] write 512 bytes until new JPEG is found
    [] detect EOF
*/

/* PSEUDOCODE:

    open card file
    repeate until end of card
        read 512 bytes into a buffer
        Start of a new JPEG?
            - yes -> ...
            - no -> ...
        already found a JPEG?
            - no -> ...
            - yes -> ...
    close any remaining files
*/



int main(int argc, char *argv[])
{
    // ensure proper command line usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember file name
    char *rawFile = argv[1];

    // open memory card file
    FILE *inptr = fopen(rawFile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", rawFile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen("outfile.jpeg", "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create outfile.jpeg.\n");
        return 3;
    }

    // buffer
    uint8_t dataBuffer[512]; // look for --> [0xFF][0xD8][0xFF][0xE?]

    int dataByte;
    int jpegFound = 0;
    int block = 0; // DEBUG: printout variable
    int jpegCount = 0; // DEBUG: printout variable
    while( (dataByte = fgetc(inptr)) != EOF )
    {

        //printf("\n**** BLOCK %i ****\n", block); // DEBUG
        printf("\n\n"); // DEBUG <-- gap for showing every 512 block of memory
        fread(dataBuffer, sizeof(uint8_t), 512, inptr);
        for(int i = 0; i < 512; i++)
        {
            if( ((dataBuffer[i] == 0xFF) && (dataBuffer[i+1] == 0xD8) && (dataBuffer[i+2] == 0xFF)) )
            {

                if(jpegFound == 1)
                {
                    return 0;
                }

                printf("\n\n\n\n");
                printf("-------------------------> NEW JPEG FOUND\n");  // DEBUG
                jpegFound = 1;
                jpegCount++; // DEBUG
            }

            if(jpegFound == 1)
            {
                printf("%X ", dataBuffer[i]);
                fwrite(&dataBuffer[i], sizeof(uint8_t), 1, outptr);
            }

        }


        block++;
        //jpegFound = 0;
    }


    printf("JPEG COUNT: %i \n", jpegCount); // DEBUG


    fclose(inptr);
    fclose(outptr);

    return 0;
}
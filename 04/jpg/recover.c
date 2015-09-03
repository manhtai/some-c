/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    // Open file
    FILE* raw = fopen("card.raw", "r");
    if (raw == NULL)
    {
        fprintf(stderr, "Can't not open the raw file.\n");
        exit(EXIT_FAILURE);
    }

    // Alloc data with 512 bytes
    BYTE data[512];
    char image_name[9];
    int count = 0;
    // Read raw into data, 512 bytes each
    fread(&data, 512, 1, raw);

    while (!feof(raw))
    {
        // If it smells jpeg
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff
                && (data[3] == 0xe0 || data[3] == 0xe1))
        {
            sprintf(image_name, "%03i.jpg", count++);
            // Create new image files
            FILE* new = fopen(image_name, "w");
            if (new == NULL)
            {
                fprintf(stderr, "Can't not create new image file.\n");
                exit(EXIT_FAILURE);
            }

            // Write content to image file util end of file or smelling new image
            do
            {
                fwrite(&data, 512, 1, new);
                fread(&data, 512, 1, raw);
            }
            while (!(data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff
                && (data[3] == 0xe0 || data[3] == 0xe1))
                    && !feof(raw));

            // Close the file
            fclose(new);
            continue;
        }
        fread(&data, 512, 1, raw);
    }

    // Close file
    fclose(raw);
    return 0;
}

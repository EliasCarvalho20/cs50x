#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int CHUNK_SIZE = 512;

int main(int argc, char *argv[])
{
    // If the arguments less than 1, exit
    if (argc != 2)
    {
        return 1;
    }
    
    // Read the data from card
    char *data = argv[1];
    FILE *card_data = fopen(data, "rb");
    if (card_data == NULL)
    {
        return 2;
    }

    FILE *jpg_file;
    bool is_file_open = false;

    int count = 0;
    // Creates a 512 bytes chunk to read the data
    uint8_t buffer[CHUNK_SIZE];
    while (fread(buffer, sizeof(uint8_t), CHUNK_SIZE, card_data) > 0)
    {
        // Check if the header of the current data correspond to a jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If file is already open, closes it
            if (is_file_open)
            {
                fclose(jpg_file);
                is_file_open = false;
            }
            
            // Create a dynamic name string to save the file
            char *jpgs_found[8];
            sprintf(jpgs_found, "%03i.jpg", count);
            
            // Create the file on disk
            jpg_file = fopen(jpgs_found, "w");

            count += 1;
            is_file_open = true;
        }
        
        // If file is open, append the current data to it
        if (is_file_open)
        {
            fwrite(buffer, sizeof(uint8_t), CHUNK_SIZE, jpg_file);
        }
    }

    if (jpg_file)
    {
        fclose(jpg_file);
    }

    fclose(card_data);
}
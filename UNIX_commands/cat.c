/**
 * This program simulates the basic functionality of the Unix 'cat' command.
 * It reads files specified as command-line arguments and writes their content to standard output.
 * If no file is specified, it sends an error message prompting the user to provide file paths.
 *
 * Usage:
 *   ./cat file1.txt file2.txt ...
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

void filecopy(FILE* file_source, FILE* file_dest);


int main(int argc, char** argv)
{

    uint8_t u8idxL;
    FILE* currentFileL = NULL;

    if(argc == 1)
    {
        fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }


    for(u8idxL = 1; u8idxL < argc; u8idxL++)
    {
        currentFileL = fopen(argv[u8idxL], "rb");

        if (currentFileL != NULL)
        {
            filecopy(currentFileL, stdout);
            fclose(currentFileL);
        }
        else
        {
            printf("cat: can't open %s\n", argv[u8idxL]);
        }

    }

    return EXIT_SUCCESS;
}

/**
 * Copies content from the source file to the destination file.
 *
 * Parameters:
 *   source: A pointer to a FILE object that represents the input file
 *   destination: A pointer to a FILE object that represents the output file
 */
void filecopy(FILE* file_source, FILE* file_dest)
{
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file_source)) > 0) {
        fwrite(buffer, 1, bytesRead, file_dest);
    }

    if (ferror(file_source)) {
        fprintf(stderr, "Error reading file\n");
    }

    if (ferror(file_dest)) {
        fprintf(stderr, "Error writing to output\n");
    }
}
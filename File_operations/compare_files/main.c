/**
 * @file main.c
 * @brief Main file to test the file comparison functionality.
 *
 * This file contains the main function to test the compare_files function.
 * It demonstrates how to use the file comparison functions defined in file_comparator.h.
 *
 * Author: Kalin Borodzhijski
 * Date: 27.06.2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "file_comparator.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* file1 = argv[1];
    const char* file2 = argv[2];

    compare_files(file1, file2);

    return EXIT_SUCCESS;
}

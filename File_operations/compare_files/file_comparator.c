/**
 * @file file_comparator.c
 * @brief Implementation file for file comparison functions.
 *
 * This file contains the implementation of functions declared in file_comparator.h.
 * It provides functionality to compare two files line by line and print the first differing line.
 *
 * Functionality:
 * - Compare two files line by line.
 * - Identify and print the first line where the files differ.
 *
 * Author: Kalin Borodzhijski
 * Date: 27.06.2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_comparator.h"

void compare_files(const char* file1, const char* file2)
{
    char line1Buff[MAX_LINE_SIZE] = {};
    char line2Buff[MAX_LINE_SIZE] = {};

    FILE* firstFile = fopen(file1, "r");
    FILE* secondFile = fopen(file2, "r");

    if (firstFile == NULL || secondFile == NULL)
    {
        fprintf(stderr, "Error loading files !\n");
        fclose(firstFile);
        fclose(secondFile);
    }

    while (
        fgets(line1Buff, MAX_LINE_SIZE, firstFile) &&
        fgets(line2Buff, MAX_LINE_SIZE, secondFile)
        )
    {
        if (strcmp(line1Buff, line2Buff))
        {
            printf("Different row found:\nRow 1: %sRow 2: %s", line1Buff, line2Buff);
            fclose(firstFile);
            fclose(secondFile);
            return;
        }

    }


    printf("Files are identical.\n");

    fclose(firstFile);
    fclose(secondFile);
}

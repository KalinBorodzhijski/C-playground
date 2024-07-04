/**
 * @file file_comparator.h
 * @brief Header file for file comparison functions.
 *
 * This file contains the declarations of functions used to compare two files and print the first differing line.
 *
 * Functionality:
 * - Compare two files line by line.
 * - Identify and print the first line where the files differ.
 *
 * Author: Kalin Borodzhijski
 * Date: 27.06.2024
 */

#ifndef FILE_COMPARATOR_H
#define FILE_COMPARATOR_H

#define MAX_LINE_SIZE 100

void compare_files(const char* file1, const char* file2);

#endif // FILE_COMPARATOR_H

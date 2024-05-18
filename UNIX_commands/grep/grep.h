/*
 * File: grep.h
 * Description: Header file for the grep implementation.
 * Provides function prototypes and necessary includes for pattern matching operations.
 */

#ifndef GREP_H
#define GREP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_FILES 100
#define MAX_LINE_LEN 1024

#define OPTION_IGNORE_CASE  0x01 
#define OPTION_INVERT_MATCH 0x02
#define OPTION_COUNT_LINES  0x04
#define OPTION_LINE_NUMBER  0x08

typedef struct {
    unsigned int options;
    char* pattern;
    char* filename[MAX_FILES];
    unsigned int fileCount;
} GrepConfig;

void handleInput(int argc, char const* argv[], GrepConfig* config);
void handleFile(char* filename, unsigned int options, char * pattern, bool printFileName);
void toLowercase(char* str);
#endif // GREP_H
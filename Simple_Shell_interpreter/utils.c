#include "utils.h"
#include <string.h>
#include <ctype.h>

/**
 * Prints an error message to stderr.
 * @param msg The message to be printed.
 */
void error(const char *msg) 
{
    perror(msg);
}

/**
 * Trims whitespace from the beginning and end of the string.
 * @param str The string to trim.
 */
void trimWhitespace(char *str) 
{
    int i;
    int begin = 0;
    int end = strlen(str) - 1;

    while (isspace((unsigned char)str[begin])) begin++;

    while ((end >= begin) && isspace((unsigned char)str[end])) end--;

    for (i = begin; i <= end; i++) str[i - begin] = str[i];

    str[i - begin] = '\0';
}

/**
 * @file uniqueCharactersCheck.c
 * @brief Program to check if a string has all unique characters.
 *
 * This program includes a function `hasAllUniqueChars` which checks whether a given
 * string has all unique characters. The program demonstrates this functionality by
 * testing a sample string in the main function. Two variants of the function can be
 * considered: one using additional data structures and one without using any.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool hasAllUniqueChars(char *str);

int main() {
    char testStrings[][100] = {
        "abcdefghijklmnopqrstuvwxyz\0",
        "hello\0",                     
        "abcdefg12345\0",              
        "\0",                          
        "1234567890\0",                
        "aaa\0",                       
        "AaBbCc123\0",                 
        "!@#$%^&*()_+\0",              
        "abcdefghijklmnopqrstuvwxyza\0"
    };

    int numTests = sizeof(testStrings) / sizeof(testStrings[0]);
    for (int i = 0; i < numTests; i++) {
        bool isUnique = hasAllUniqueChars(testStrings[i]);
        printf("The string \"%s\" %s all unique characters.\n", testStrings[i], isUnique ? "has" : "does not have");
    }

    return 0;
}

int compare(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

bool hasAllUniqueChars(char *str)
{
    int stringLen = strlen(str);
    qsort(str, stringLen, sizeof(char), compare);

    for (size_t i = 1; i < stringLen; i++)
    {
        if (str[i] == str[i-1])
        {
            return false;
        }
        
    }
    
    return true;
}


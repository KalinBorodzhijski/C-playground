/**
 * @file string_local.h
 * @brief Local Implementations of Standard String Functions
 *
 * This header file declares a series of string manipulation functions that mimic
 * the behavior of the standard string functions provided by <string.h>. It is intended
 * as a local and educational implementation to understand the mechanics behind basic
 * string operations without relying on the standard library. The functions include
 * operations such as computing the length of a string, copying strings, concatenation,
 * and more advanced manipulations like reversing strings and converting character cases.
 *
 */

#ifndef STRING_LOCAL_H
#define STRING_LOCAL_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef int StrResult;

// Return codes for string functions
#define S_OK                ((StrResult) 0)
#define E_NOK               ((StrResult)-1)
#define E_INVALID_ARGS      ((StrResult)-2)
#define E_DEST_OUT_OF_BOUND ((StrResult)-3)

// Computes the length of the string s.
int my_strlen(const char *s, StrResult* error);

// Copies the string pointed to by src into the buffer pointed to by dest.
StrResult my_strcpy(char *dest, const char *src, const uint32_t u32dest_sizeP);

// Appends the string src to the dest string.
StrResult my_strcat(const char *src, char *dest, const uint32_t u32dest_sizeP);

// Compares two strings lexicographically.
StrResult my_strcmp(const char *pStringOneP, const char *pStringTwoP,  StrResult* errorP);

// Finds the first occurrence of the substring needle in the string haystack.
char *my_strstr(char *haystack, char *needle, StrResult* errorP);

// Concatenates at most n characters of the source string to the destination string.
StrResult my_strncat(char *dest, const char *src, size_t n);

// Finds the first occurrence of the character c in the string inputStringP.
const char *my_strchr(const char *inputStringP, int c);

// Reverses the string s in place.
StrResult my_strrev(char *s);

// Converts all uppercase letters in the string s to lowercase.
StrResult my_strtolower(char *s);

// Converts all lowercase letters in the string s to uppercase.
StrResult my_strtoupper(char *s);

// Splits the string s into tokens separated by characters in the delim.
char *my_strtok(char *s, const char *delim);

#endif //STRING_LOCAL_H
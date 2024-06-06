/*
 * File: stringCompression.c
 * Author: Kalin Borodzhijski
 *
 * Description:
 * This program contains functions to compress a string using a simple encoding
 * scheme (run-length encoding) and to decode the compressed string back to its
 * original form. The main function tests these encoding and decoding functions
 * with various test cases.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* encodeString(const char *str);
char* decodeString(const char *encodedStr);
int parseNumber(const char **encodedStr);
int calculateDecodedLength(const char *encodedStr);

int main() {
    const char *test1 = "aaaabbbcc";              // Expected encoded: "4a3b2c", decoded: "aaaabbbcc"
    const char *test2 = "abc";                    // Expected encoded: "1a1b1c", decoded: "abc"
    const char *test3 = "a";                      // Expected encoded: "1a", decoded: "a"
    const char *test4 = "";                       // Expected encoded: "", decoded: ""
    const char *test5 = "wwwwaaadexxxxxx";        // Expected encoded: "4w3a1d1e6x", decoded: "wwwwaaadexxxxxx"
    const char *test6 = "aaaaaaaaaaaaaaa";        // Expected encoded: "15a", decoded: "aaaaaaaaaaaaaaa"
    const char *test7 = "aabbaa";                 // Expected encoded: "2a2b2a", decoded: "aabbaa"
    const char *test8 = "aabbaaaabb";             // Expected encoded: "2a2b4a2b", decoded: "aabbaaaabb"
    const char *test9 = "aaaaabbbbbcccccdddddd";  // Expected encoded: "5a5b5c6d", decoded: "aaaaabbbbbcccccdddddd"
    const char *test10 = "abcdabcdabcd";          // Expected encoded: "1a1b1c1d1a1b1c1d1a1b1c1d", decoded: "abcdabcdabcd"

    char *encoded1 = encodeString(test1);
    char *encoded2 = encodeString(test2);
    char *encoded3 = encodeString(test3);
    char *encoded4 = encodeString(test4);
    char *encoded5 = encodeString(test5);
    char *encoded6 = encodeString(test6);
    char *encoded7 = encodeString(test7);
    char *encoded8 = encodeString(test8);
    char *encoded9 = encodeString(test9);
    char *encoded10 = encodeString(test10);

    char *decoded1 = decodeString(encoded1);
    char *decoded2 = decodeString(encoded2);
    char *decoded3 = decodeString(encoded3);
    char *decoded4 = decodeString(encoded4);
    char *decoded5 = decodeString(encoded5);
    char *decoded6 = decodeString(encoded6);
    char *decoded7 = decodeString(encoded7);
    char *decoded8 = decodeString(encoded8);
    char *decoded9 = decodeString(encoded9);
    char *decoded10 = decodeString(encoded10);

    printf("Original: %s, Encoded: %s, Decoded: %s\n", test1, encoded1, decoded1);
    printf("Original: %s, Encoded: %s, Decoded: %s\n", test2, encoded2, decoded2);
    printf("Original: %s, Encoded: %s, Decoded: %s\n", test3, encoded3, decoded3);
    printf("Original: %s, Encoded: %s, Decoded: %s\n", test4, encoded4, decoded4);
    printf("Original: %s, Encoded: %s, Decoded: %s\n", test5, encoded5, decoded5);
    printf("Original: %s, Encoded: %s, Decoded: %s\n", test6, encoded6, decoded6);
    printf("Original: %s, Encoded: %s, Decoded: %s\n", test7, encoded7, decoded7);
    printf("Original: %s, Encoded: %s, Decoded: %s\n", test8, encoded8, decoded8);
    printf("Original: %s, Encoded: %s, Decoded: %s\n", test9, encoded9, decoded9);
    printf("Original: %s, Encoded: %s, Decoded: %s\n", test10, encoded10, decoded10);

    free(encoded1);
    free(encoded2);
    free(encoded3);
    free(encoded4);
    free(encoded5);
    free(encoded6);
    free(encoded7);
    free(encoded8);
    free(encoded9);
    free(encoded10);

    free(decoded1);
    free(decoded2);
    free(decoded3);
    free(decoded4);
    free(decoded5);
    free(decoded6);
    free(decoded7);
    free(decoded8);
    free(decoded9);
    free(decoded10);

    return 0;
}
//---------------------------------------------------------------------------------------
char* encodeString(const char *str)
{
    
    int buffIndex = 0;

    if (str == NULL || *str == '\0') {
        char *empty = (char *)malloc(1);
        *empty = '\0';
        return empty;
    }

    int len = strlen(str);
    char *encoded = (char *)malloc(2 * len + 1); // worst-case scenario (each character is unique)
    if (!encoded) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    while (*str != '\0')
    {
        int counter = 1;
        char startChar = *str;
        str++;

        while (startChar == *str)
        {
            counter++;
            str++;
        }

        buffIndex += sprintf((encoded + buffIndex),"%d%c",counter, startChar);
    }
        encoded[buffIndex] = '\0';

    return encoded;

}
//---------------------------------------------------------------------------------------
char* decodeString(const char *encodedStr)
{

    if (encodedStr == NULL || *encodedStr == '\0') 
    {
        char *empty = (char *)malloc(1);
        *empty = '\0';
        return empty;
    }

    int decodedLength = calculateDecodedLength(encodedStr);

    char *decodedStr = (char*)malloc(decodedLength + 1);
    if (decodedStr == NULL) {
        fprintf(stderr, "Error: Decoding: Memory allocation failed !\n");
        exit(1);
    }

    char *decodedPtr = decodedStr;
    while (*encodedStr != '\0') {
        int number = parseNumber(&encodedStr);
        char currentChar = *encodedStr;
        encodedStr++;

        for (size_t i = 0; i < number; i++) {
            *decodedPtr++ = currentChar;
        }
    }
    *decodedPtr = '\0';

    return decodedStr;
    
}
//---------------------------------------------------------------------------------------
int parseNumber(const char **encodedStr) {
    const char *numberStartIndex = *encodedStr;
    while (isdigit(**encodedStr)) {
        (*encodedStr)++;
        if (**encodedStr == '\0') {
            fprintf(stderr, "Error: Decoding: Invalid encoding format !\n");
            exit(1);
        }
    }

    int numberSize = *encodedStr - numberStartIndex;
    char *strNumber = (char*)malloc((numberSize) + 1);
    for (size_t i = 0; i < numberSize; i++) {
        strNumber[i] = *numberStartIndex++;
    }
    strNumber[numberSize] = '\0';

    int number = atoi(strNumber);
    free(strNumber);

    return number;
}
//---------------------------------------------------------------------------------------
int calculateDecodedLength(const char *encodedStr) {
    int decodedLength = 0;
    while (*encodedStr != '\0') {
        int number = parseNumber(&encodedStr);
        decodedLength += number;
        encodedStr++;
    }
    return decodedLength;
}
//---------------------------------------------------------------------------------------
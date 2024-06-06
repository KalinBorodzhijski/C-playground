/*
 * File: StringReversal.c
 * Author: Kalin Borodzhijski
 *
 * Description:
 * This program contains a function that reverses a string in place without
 * using any additional buffers or the standard library functions. The main
 * function tests this string reversal function with various test cases.
 */

#include <stdio.h>

void reverseString(char *str);

int main() {
    char test1[] = "hello";
    char test2[] = "world";
    char test3[] = "a";
    char test4[] = "";
    char test5[] = "abcd1234";

    reverseString(test1);
    reverseString(test2);
    reverseString(test3);
    reverseString(test4);
    reverseString(test5);

    printf("Reversed test1: %s\n", test1);
    printf("Reversed test2: %s\n", test2);
    printf("Reversed test3: %s\n", test3);
    printf("Reversed test4: %s\n", test4);
    printf("Reversed test5: %s\n", test5);

    return 0;
}

void reverseString(char *str)
{
    int strLen = 0;
    while (str[strLen] != '\0') strLen++;
    
    for (size_t i = 0; i < strLen / 2; i++)
    {
        char temp = str[i];
        str[i] = str[strLen - i - 1];
        str[strLen - i - 1] = temp;
    }
}
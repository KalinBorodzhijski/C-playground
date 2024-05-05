#include <stdio.h>
#include "string_local.h"

int main() 
{
    char test1[100] = "Hello, World!";
    char test2[100] = {0};
    StrResult resultL = E_NOK;

    // Test strlen
    printf("Length of '%s': %d\n", test1, my_strlen(test1, &resultL));
    if(S_OK != resultL)
    {
        printf("my_strlen error code: %d\n", resultL);
    }

    // Test strcpy
    resultL = my_strcpy(test2, "Hello", 6);
    if (resultL == S_OK)
    {
        printf("Copied string: %s\n", test2);
    }
    else
    {
        printf("my_strcpy error code: %d\n", resultL);
    }

    // Test strcat
    resultL = my_strcat(" Nice to meet you.", test1, 100u);
    if (resultL == S_OK)
    {
        printf("Concatenated string: %s\n", test1);
    }
    else
    {
        printf("my_strcat error code: %d\n", resultL);
    }

    // Test strcmp
    char test_cmp1[50] = "Hello, World!";
    char test_cmp2[50] = "Hello, World!";
    int16_t result = my_strcmp(test_cmp1, test_cmp2, &resultL);
    if(S_OK != resultL)
    {
        printf("my_strcmp error code: %d\n", resultL);
    }
    else
    {
        printf("Result from my_strcmp: %d\n", result);
    }

    // Test strstr
    char haystack[20] = "ThisIsDemo";
    char needle[10] = "Demo";
    char* ret;

    ret = my_strstr(haystack, needle, &resultL);
    if(S_OK != resultL)
    {
        printf("my_strcmp error code: %d\n", resultL);
    }
    else
    {
        printf("Result from my_strstr: %s\n", ret);
    }
    

    // Test strncat
    char str1_test[20];
    char str2_test[20];
    
    my_strcpy (str1_test,"To be ", 20);
    my_strcpy (str2_test,"or not to be", 20);
    resultL = my_strncat (str1_test, str2_test, 15);
    if(S_OK == resultL)
    {
        printf("Result from my_strncat: %s\n", str1_test);
    }
    else
    {
        printf("Result from my_strncat: %s\n", ret);
    }

    // Test strchre
    char str[] = "Get the text after K This is after";
    char ch = 'K';
    const char * returnValue = my_strchr(str, ch);
    printf("String after |%c| is - |%s|\n", ch, returnValue);

    // Test strrev
    char myString[] = "Hello, world!";
    resultL = my_strrev(myString);
    if(S_OK == resultL)
    {
        printf("Result from my_strrev: %s\n", myString);
    }
    else
    {
        printf("Result from my_strrev: %d\n", resultL);
    }

    // Test strtolower
    char strToLower[] = "TURN THIS TO LOWER 123 Without the numbers";
    resultL = my_strtolower(strToLower);
    if(S_OK == resultL)
    {
        printf("Result from my_strtolower: %s\n", strToLower);
    }
    else
    {
        printf("Result from my_strtolower: %d\n", resultL);
    }

    // Test strtoupper
    char strToUpper[] = "TURN THIS TO upper 123 Without the numbers";
    resultL = my_strtoupper(strToUpper);
    if(S_OK == resultL)
    {
        printf("Result from my_strtoupper: %s\n", strToUpper);
    }
    else
    {
        printf("Result from my_strtoupper: %d\n", resultL);
    }

    // Test strtok
    char inputString[] = "hello,world;this|is:a.test";
    char *token;
    char *delim = ",;|:.";

    token = my_strtok(inputString, delim);
    while (token != NULL) {
        printf("%s\n", token);
        token = my_strtok(NULL, delim);
    }

    return 0;
}

/**
 * @file findMissingNumber.c
 * @brief Program to find the missing number in an array.
 *
 * This program contains the implementation of a function that finds the missing
 * number in an array. The array contains distinct integers from 0 to n, but one
 * of the numbers in this range is missing. The function `findMissing` is designed
 * to determine which number is missing.
 */

#include <stdio.h>

int findMissing(int arr[], int size);

int main() {
    int testArray1[] = {0, 1, 3, 4, 5};
    int size1 = sizeof(testArray1) / sizeof(testArray1[0]);
    printf("The missing number in test 1 is: %d\n", findMissing(testArray1, size1));

    int testArray2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12};
    int size2 = sizeof(testArray2) / sizeof(testArray2[0]);
    printf("The missing number in test 2 is: %d\n", findMissing(testArray2, size2));

    int testArray3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size3 = sizeof(testArray3) / sizeof(testArray3[0]);
    printf("The missing number in test 3 is: %d\n", findMissing(testArray3, size3));

    return 0;
}

int findMissing(int arr[], int size)
{
    int counter = 0;
    int sumArray = 0;
    int sumNumbers = 0;
    for (counter = 0; counter < size; counter++)
    {
        sumNumbers += counter;
        sumArray += arr[counter];
    }

    sumNumbers += counter;
    return sumNumbers - sumArray;
    
}
/*
 * File: binarySearch.c
 * Author: Kalin Borodzhijski
 * Description: This file contains the implementation of a binary search function.
 *              Binary search is an efficient algorithm for finding an item from a sorted list of items.
 *              It works by repeatedly dividing in half the portion of the list that could contain the item,
 *              until you've narrowed down the possible locations to just one.
 */


#include <stdio.h>

/*
 * - Searches for a target value within a sorted array using the binary search algorithm.
 * - Parameters:
 *     - arr: The array to search through
 *     - size: The number of elements in the array
 *     - target: The value to search for
 * - Returns the index of the target value if found, otherwise returns -1.
 */
int binarySearch(int arr[], int size, int target);
//-------------------------------------------------------------------------------------------
int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int target1 = 3;
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = binarySearch(arr1, size1, target1);
    if (result1 != -1) {
        printf("Test Case 1: Element %d found at index %d\n", target1, result1);
    } else {
        printf("Test Case 1: Element %d not found\n", target1);
    }

    int arr2[] = {1, 2, 3, 4, 5};
    int target2 = 6;
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = binarySearch(arr2, size2, target2);
    if (result2 != -1) {
        printf("Test Case 2: Element %d found at index %d\n", target2, result2);
    } else {
        printf("Test Case 2: Element %d not found\n", target2);
    }

    int arr3[] = {1};
    int target3 = 1;
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = binarySearch(arr3, size3, target3);
    if (result3 != -1) {
        printf("Test Case 3: Element %d found at index %d\n", target3, result3);
    } else {
        printf("Test Case 3: Element %d not found\n", target3);
    }

    int arr4[] = {1};
    int target4 = 2;
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    int result4 = binarySearch(arr4, size4, target4);
    if (result4 != -1) {
        printf("Test Case 4: Element %d found at index %d\n", target4, result4);
    } else {
        printf("Test Case 4: Element %d not found\n", target4);
    }
    
    return 0;
}
//-------------------------------------------------------------------------------------------
int binarySearch(int arr[], int size, int target)
{
    int start = 0;
    int end = size - 1;

    while (end >= start)
    {
        int midIndex = start + (end - start) / 2; 
        int currentNumber = arr[midIndex];

        if (target == currentNumber)
        {
            return midIndex;
        }
        else if (target > currentNumber)
        {
            start = midIndex + 1;
        }
        else
        {   

            end = midIndex - 1;
        }
    }

    return -1;    
}
//-------------------------------------------------------------------------------------------
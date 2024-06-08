/**
 * @file longestConsecutiveSequence.c
 * @brief Program to find the length of the longest consecutive elements sequence.
 *
 * This program includes the function `longestConsecutiveSequence` which determines
 * the length of the longest consecutive elements sequence in an unsorted array of
 * integers.
 */
#include <stdio.h>
#include <stdlib.h>


int longestConsecutiveSequence(int arr[], int size);

int main() {
    
    int testArray1[] = {10, 5, 12, 3, 11};
    int testArray2[] = {2, 2, 2, 2};
    int testArray3[] = {4};
    int testArray4[] = {21, 23, 22, 25, 24, 26};
    int testArray5[] = {15, 5, 1, 3, 4, 2}; 
    int testArray6[] = {1, 5};
    int testArray7[] = {-3, -1, -2, 0, 1};
    int testArray8[] = {101, 102, 104, 103, 107, 105, 100};

    // Array of test cases
    int* testArrays[] = {testArray1, testArray2, testArray3, testArray4, testArray5, testArray6, testArray7, testArray8};
    int testSizes[] = {
        sizeof(testArray1) / sizeof(testArray1[0]),
        sizeof(testArray2) / sizeof(testArray2[0]),
        sizeof(testArray3) / sizeof(testArray3[0]),
        sizeof(testArray4) / sizeof(testArray4[0]),
        sizeof(testArray5) / sizeof(testArray5[0]),
        sizeof(testArray6) / sizeof(testArray6[0]),
        sizeof(testArray7) / sizeof(testArray7[0]),
        sizeof(testArray8) / sizeof(testArray8[0])
    };

    int numberOfTests = sizeof(testArrays) / sizeof(testArrays[0]);

    for (int i = 0; i < numberOfTests; i++) {
        int result = longestConsecutiveSequence(testArrays[i], testSizes[i]);
        printf("Test Case %d - Length of the longest consecutive sequence: %d\n", i + 1, result);
    }

    return 0;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b);
}

int longestConsecutiveSequence(int arr[], int size)
{
    if ((arr == NULL) || (size < 1))
    {
        return 0;
    }
    
    int currentSeqLen = 1;
    int maxSequenceLen = 1;

    qsort(arr, size, sizeof(int), cmpfunc);

    for (size_t i = 0; i < size - 1; i++)
    {
        int currentNumber = arr[i];
        int nextNumber = arr[i+1];

        if((currentNumber + 1) == nextNumber)
        {
            currentSeqLen++;
        }
        else
        {
            currentSeqLen = 1;
        }

        if(currentSeqLen > maxSequenceLen)
        {
            maxSequenceLen = currentSeqLen;
        }
    }
    
    return maxSequenceLen;
}
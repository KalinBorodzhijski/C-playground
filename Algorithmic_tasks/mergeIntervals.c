/**
 * @file mergeIntervals.c
 * @brief Program to merge overlapping intervals.
 *
 * This program defines a function `mergeIntervals` that takes an array of intervals,
 * where each interval is represented as a pair [start, end], and merges all overlapping
 * intervals. The function returns an array of the non-overlapping intervals that cover
 * all the intervals given in the input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int **mergeIntervals(int intervals[][2], int size, int *returnSize);
void printIntervals(int **intervals, int size);

int main() {
    // Array of test cases
    int testCases[][10][2] = {
        {{1, 3}, {2, 6}, {8, 10}, {15, 18}},
        {{1, 2}, {3, 4}, {5, 6}},           
        {{1, 4}, {4, 5}},                   
        {{5, 5}, {1, 1}, {2, 3}},           
        {{0, 5}, {7, 12}, {8, 10}, {15, 18}}                                  
    };
    int sizes[] = {4, 3, 2, 3, 4};

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int returnSize;
        int **mergedIntervals = mergeIntervals(testCases[i], sizes[i], &returnSize);
        printIntervals(mergedIntervals, returnSize);

        for (int i = 0; i < sizes[i]; i++) 
        {
            free(mergedIntervals[i]);
        }

        free(mergedIntervals);
    }

    return 0;
}

int **mergeIntervals(int intervals[][2], int size, int *returnSize)
{
    if (size == 0) {
        *returnSize = 0;
        return NULL;
    }

    int **result = (int**) malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        result[i] = malloc(2 * sizeof(int));
        result[i][0] = intervals[i][0];
        result[i][1] = intervals[i][1];
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (result[i][0] > result[j][0]) {
                int tempStart = result[i][0];
                int tempEnd = result[i][1];
                result[i][0] = result[j][0];
                result[i][1] = result[j][1];
                result[j][0] = tempStart;
                result[j][1] = tempEnd;
            }
        }
    }

    *returnSize = 0;
    int currentStart = result[0][0];
    int currentEnd = result[0][1];

    for (int i = 1; i < size; i++) {
        if (currentEnd >= result[i][0]) {
            currentEnd = result[i][1] > currentEnd ? result[i][1] : currentEnd;
        } else {
            result[*returnSize][0] = currentStart;
            result[*returnSize][1] = currentEnd;
            (*returnSize)++;
            currentStart = result[i][0];
            currentEnd = result[i][1];
        }
    }
    result[*returnSize][0] = currentStart;
    result[*returnSize][1] = currentEnd;
    (*returnSize)++;

    for (int i = *returnSize; i < size; i++) {
        free(result[i]);
    }

    return result;
    
}

void printIntervals(int **intervals, int size) 
{
    for (int i = 0; i < size; i++) {
        printf("[%d, %d] ", intervals[i][0], intervals[i][1]);
    }
    printf("\n");
}
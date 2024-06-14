/**
 * @file trendDetection.c
 * @brief Program to detect trends in a dataset.
 *
 * This program contains the implementation of a function that detects trends 
 * within a dataset. The function `detectTrend` analyzes the trend in the last 
 * few samples of an input array based on a specified threshold.
 */


#include <stdio.h>
#include <stdbool.h>

typedef enum {
    TREND_NONE,
    TREND_UPWARD,
    TREND_DOWNWARD
} TrendType;

TrendType detectTrend(const double data[], int size, int threshold);

int main() 
{
    const double data1[] = {1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5}; 
    const double data2[] = {5.5, 5.0, 4.5, 4.0, 3.5, 3.0, 2.5, 2.0, 1.5, 1.0}; 
    const double data3[] = {1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0}; 
    const double data4[] = {1.0, 2.0, 3.0, 2.5, 2.0, 1.5, 1.0, 0.5, 0.0, -0.5};
    const double data5[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; 

    int threshold = 5;

    const double* datasets[] = {data1, data2, data3, data4, data5};
    const char* descriptions[] = {"Upward trend", "Downward trend", "No clear trend", "Mixed trend", "Constant"};
    int dataSize = sizeof(data1) / sizeof(data1[0]);

    for (int i = 0; i < 5; i++) 
    {
        TrendType trend = detectTrend(datasets[i], dataSize, threshold);
        printf("Dataset %d (%s): ", i + 1, descriptions[i]);
        switch (trend) 
        {
            case TREND_UPWARD:
                printf("Upward trend detected in the last %d samples.\n", threshold);
                break;
            case TREND_DOWNWARD:
                printf("Downward trend detected in the last %d samples.\n", threshold);
                break;
            case TREND_NONE:
            default:
                printf("No significant trend detected in the last %d samples.\n", threshold);
                break;
        }
    }

    return 0;
}

TrendType detectTrend(const double data[], int size, int threshold) 
{
    TrendType result;
    double currentTrend = 0;

    if (threshold > size)
    {
        fprintf(stderr, "Threshold is bigger than the array size !\n");
        return TREND_NONE;
    }

    double startTrend = data[size - threshold] - data[size - threshold + 1];
    if (startTrend > 0)
    {
        result = TREND_DOWNWARD;
    }
    else if (startTrend < 0)
    {
        result = TREND_UPWARD;
    }
    else
    {
        result = TREND_NONE;
    }
    
    for (size_t i = (size - threshold) + 1; i < size-1; i++)
    {
        currentTrend = data[i] - data[i+1];

        if((currentTrend > 0) && (result == TREND_DOWNWARD))
        {
            result = TREND_DOWNWARD;
        }
        else if ((currentTrend < 0) && (result == TREND_UPWARD))
        {
            result = TREND_UPWARD;
        }
        else
        {
            result = TREND_NONE;
        }
    }

    return result;
}

/*
This program calculates the moving average of a data array using the "Mean of available data" replacement for initial values.

The moving average is a method for smoothing out fluctuations in a time series by computing the average of a specified number of consecutive points. 
This program takes an array of data points, a window size (the number of points to include in the average), and a replacement strategy for initial values as input. 
It then calculates the moving average for the entire array and stores the results in a buffer. Finally, it prints the moving average to the console.

The "Mean of available data" replacement strategy means that for the first window size - 1 points, the average of the available data points is used.
For example, for the first point, the average of just the first point (10) is used. For the second point, the average of the first two points (10 and 12) is used. 
Once enough data points are available, the standard moving average calculation is used.
*/

#include <stdio.h>

void movingAverage(double * arr, double * buff, int size, int movingAverageWindow);

int main(int argc, char * argv[])
{
  double arr[] = {10, 12, 15, 17, 19, 20, 22};
  int size = sizeof(arr) / sizeof(arr[0]);
  int movingAverageWindow = 3;

  double buff[size];

  movingAverage(arr, buff, size, movingAverageWindow);

  for (int i = 0; i < size; i++) {
    printf("%f ", buff[i]);
  }

  return 0;

}

void movingAverage(double * arr, double * buff, int size, int movingAverageWindow)
{

    size_t counter;

    for (counter = 0; counter < (movingAverageWindow - 1); counter++)
    {
        double currentResult = 0;
        for (size_t i = 0; i < counter + 1; i++)
        {
            currentResult += arr[i];
        }
        
        buff[counter] = (currentResult / (counter + 1));
    }

    for (; counter < size; counter++)
    {
        double currentResult = 0;
        for (size_t i = 0; i < movingAverageWindow; i++)
        {
            currentResult += arr[counter - i];
        }

        buff[counter] = (currentResult / movingAverageWindow);
    }
}



/**
 * @file linearInterpolation.c
 * @brief Program to perform linear interpolation on a dataset.
 *
 * This program contains the implementation of a function that estimates intermediate
 * values within a dataset using linear interpolation. The function `linearInterpolate`
 * takes arrays of X and Y values and computes the interpolated Y value for a given X value.
 * 
 */

#include <stdio.h>

typedef struct {
    const char* description;
    const double* X;
    const double* Y;
    int size;
} ConfigTable;

double linearInterpolate(double x, const double X[], const double Y[], int size);

int main() {
    const double X1[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    const double Y1[] = {2.0, 4.0, 6.0, 8.0, 10.0};
    ConfigTable table1 = {"Linear dataset", X1, Y1, 5};

    const double X2[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    const double Y2[] = {1.0, 1.414, 1.732, 2.0, 2.236};
    ConfigTable table2 = {"Square root dataset", X2, Y2, 5};

    ConfigTable configs[] = {table1, table2};

    double testX = 3.5;
    for (int i = 0; i < 2; i++) {
        double result = linearInterpolate(testX, configs[i].X, configs[i].Y, configs[i].size);
        printf("Interpolation result for %s at x = %.2f: y = %.2f\n", configs[i].description, testX, result);
    }

    return 0;
}

double linearInterpolate(double x, const double X_Arr[], const double Y_Arr[], int size)
{
    int startIndexX = -1;
    int endIndexX = -1;
    double result = 0;

    if (size < 2)
    {
        fprintf(stderr, "Error: Not enough points to interpolate !\n");
        return -1;
    }

    if (x <= X_Arr[0]) 
    {
        return Y_Arr[0];
    } 
    else if (x >= X_Arr[size - 1]) 
    {
        return Y_Arr[size - 1];
    }

    for (int i = 0; i < size - 1; i++) 
    {
        if (x >= X_Arr[i] && x <= X_Arr[i+1]) 
        {
            double x1 = X_Arr[i];
            double y1 = Y_Arr[i];
            double x2 = X_Arr[i+1];
            double y2 = Y_Arr[i+1];
            return y1 + ((y2 - y1) / (x2 - x1)) * (x - x1);
        }
    }

    return 0.0;
}

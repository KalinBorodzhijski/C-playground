/**
 * @file calculateSumAndAverage.c
 * @brief Program to calculate the sum and average of numbers from a text file.
 *
 * This program reads a list of numbers from an input text file, calculates their sum
 * and average, and writes the results to an output text file. The input file should
 * contain one number per line. The output file will contain the sum and average
 * of the numbers.
 */

#include <stdio.h>
#include <stdlib.h>

void calculateSumAndAverage(const char *inputFileStr, const char *outputFileStr);

int main() {
    const char *inputFileName = "input.txt";
    const char *outputFileName = "output.txt";

    calculateSumAndAverage(inputFileName, outputFileName);

    return 0;
}

void calculateSumAndAverage(const char *inputFileStr, const char *outputFileStr)
{
    int numberCount = 0;
    double currentNumber = 0;
    double numberSum = 0;

    FILE * inputFile = fopen(inputFileStr, "r");
    FILE * outputFile = fopen(outputFileStr, "w");

    if((inputFile == NULL) || (outputFile == NULL))
    {
        fprintf(stderr, "Files cannot be opened !\n");
        return;
    }

    while (fscanf(inputFile, "%le", &currentNumber) != EOF)
    {
        numberSum += currentNumber;
        numberCount++;
    }

    fprintf(outputFile, "Sum: %f\n", numberSum);
    fprintf(outputFile, "Average: %f\n", (numberSum / numberCount));

    fclose(inputFile);
    fclose(outputFile);

}

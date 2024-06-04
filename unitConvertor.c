/**
 * @file unitConvertor.c
 * @brief Provides functions for converting between various units.
 *
 * This file defines a collection of functions for converting between
 * different units of measurement. Currently, it provides following functions:
 * - miles per second (mps) to miles per hour (mph)
 *
 */

#include <stdio.h>

int mpsToMph(int milesPerSecond);

int main(int argc, char* argv[])
{
    printf("%d\n", mpsToMph(5));
}

int mpsToMph(int milesPerSecond)
{
    int milesPerHour = milesPerSecond * 3600;
    return milesPerHour * 1609.34;
}
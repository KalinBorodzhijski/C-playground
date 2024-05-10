/*
 * main.c
 * This source file contains the main function and uses functions declared in main.h
 * to demonstrate and test various bitwise operations on integers.
 * The code serves as an example of how bitwise operations can be applied in practical
 * programming scenarios.
 */


#include "main.h"

int main()
{
    int number = 0x32; // Binary: 0011 0010
    printf("Original number: %d (Binary: 0011 0010)\n", number);

    // Setting bits with setBitMask
    setBitMask(&number, 0x0D); // Binary mask: 0000 1101
    printf("After setting bits with mask 0000 1101: %d (Binary: 0011 1111)\n", number);

    // Clearing bits with clearBitMask
    clearBitMask(&number, 0x09); // Binary mask: 0000 1001
    printf("After clearing bits with mask 0000 1001: %d (Binary: 0011 0110)\n", number);

    // Toggling bits with toggleBitMask
    toggleBitMask(&number, 0x0F); // Binary mask: 0000 1111
    printf("After toggling bits with mask 0000 1111: %d (Binary: 0011 1001)\n", number);


    // Test set bits
    printf("Test Result: 0x%X\n", setBits(0x00000000, 3, 4, 0x0000000F));

    // Test isEven
    printf("Test isEven: %d\n", isEven(12));

    // Swap nums
    int a = 5, b = 10;
    swap(&a, &b);
    printf("Swap numbers: a=%d, b=%d\n", a,b);

    // Count set bits
    printf("Set bits: %d\n", countSetBits(11));

    // Reverse bits
    unsigned int test_values[] =        {0x00000000, 0xFFFFFFFF, 0xAAAAAAAA, 0x55555555, 0x80000000, 0x00000001, 0x12345678};
    unsigned int expected_results[] =   {0x00000000, 0xFFFFFFFF, 0x55555555, 0xAAAAAAAA, 0x00000001, 0x80000000, 0x1E6A2C48};
    
    for (int i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        unsigned int result = reverseBits(test_values[i]);
        printf("Test %d: Input: 0x%X, Expected: 0x%X, Result: 0x%X, %s\n", 
               i + 1, test_values[i], expected_results[i], result,
               result == expected_results[i] ? "Pass" : "Fail");
    }

    // Test find missing
    int array[] = {1, 2, 4, 6, 3, 7, 8};
    int n = sizeof(array) / sizeof(array[0]);
    int missing = findMissing(array, n);
    printf("The missing number is %d\n", missing);

    // Test is power of two
    printf("Is power of two: %d\n", isPowerOfTwo(32));

    // Test find single
    int nums[] = {4, 1, 2, 1, 2};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int result = findSingle(nums, numsSize);
    printf("The single number is: %d\n", result);
    
    return 0;
}
//---------------------------------------------------------------------------------------
int setBit(int num, int position)
{
    return (num |= (1 << position));
}
//---------------------------------------------------------------------------------------
int clearBit(int num, int position)
{
    return (num &= (~(1 << position)));
}
//---------------------------------------------------------------------------------------
int toggleBit(int num, int position)
{
    return (num ^= (1 << position));
}
//---------------------------------------------------------------------------------------
int setBits(int dest, int startPosition, int numberOfBits, int source)
{
    int srcBits = 0, destinationBits = 0, bitMask = 0, result = 0;
    if((startPosition > 31) || (startPosition < 0))
    {
        fprintf(stderr, "Invalid start position\n");
        return -1;
    }

    if(startPosition < (numberOfBits-1))
    {
        fprintf(stderr, "Invalid number of bits or start position\n\n");
        return -1; 
    }

    for (int i = 0; i < numberOfBits; i++)
    {
        bitMask |= (1 << (startPosition - i));
    }   

    srcBits = source & bitMask;
    destinationBits = dest & bitMask;

    result = (dest - destinationBits) + srcBits;
    return result;
}
//---------------------------------------------------------------------------------------
bool isEven(int number)
{
    return (number & 1) ? false : true; 
}
//---------------------------------------------------------------------------------------
void swap(int * a, int * b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}
//---------------------------------------------------------------------------------------
int countSetBits(int number)
{
    int result = 0;
    while(number > 0)
    {
        result += (number & 1);
        number = number >> 1;
    }

    return result;
}
//---------------------------------------------------------------------------------------
int reverseBits(unsigned int number)
{
    unsigned int reversedNumber = 0;
    unsigned int numberOfBits = sizeof(number) * 8;

    for (unsigned int i = 0; i < numberOfBits; i++)
    {
        unsigned int numberBit = (number & (1 << i));
        if(numberBit)
        {
            reversedNumber |= (1 << (numberOfBits -1 - i));
        }
    }
    return reversedNumber;
}
//---------------------------------------------------------------------------------------
int findMissing(int * numbers, int size)
{   
    int missingVal = 1;
    for (int i = 2; i <= size+1; i++)
    {
        missingVal = missingVal ^ i;
    }
    
    int arrayVal = numbers[0];
    for (int i = 1; i < size; i++)
    {
        arrayVal = arrayVal ^ numbers[i];
    }
    
    return missingVal ^ arrayVal;
}
//---------------------------------------------------------------------------------------
bool isPowerOfTwo(int number)
{
    return (countSetBits(number) == 1);
}
//---------------------------------------------------------------------------------------
int findSingle(int * numbers, int size)
{
    int single = 0;
    for (int i = 0; i < size; i++) {
        single ^= numbers[i];
    }
    return single;
}
//---------------------------------------------------------------------------------------

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
    number = setBits(0b11001100, 2, 3, 0b10110101);
    printf("Result %d\n", number);
    number = setBits(0b11001100, 2, 0, 0b10110101);
    printf("Result %d\n", number);
    number = setBits(0b11001100, 0, 4, 0b10110101);
    printf("Result %d\n", number);
    number = setBits(0b11001100, 0, 8, 0b10110101);
    printf("Result %d\n", number);
    number = setBits(0b10000000000, 5, 3, 0b111);
    printf("Result %d\n", number);

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
    if((startPosition > 64) || (startPosition < 0))
    {
        fprintf(stderr, "Invalid start position\n");
        return -1;
    }

    if((startPosition+1) < numberOfBits)
    {
        fprintf(stderr, "Invalid arguments\n");
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
/*
 * main.h
 * This header file includes declarations for various functions performing
 * bitwise operations on integers. These operations include setting, clearing,
 * and toggling specific bits, manipulating bitfields, rotating bits, and other
 * bitwise tricks like swapping values, counting set bits, and detecting unique
 * values in arrays.
 *
 * Functions included:
 * - setBit: Sets a specific bit.
 * - clearBit: Clears a specific bit.
 * - toggleBit: Toggles a specific bit.
 * - setbits: Sets bits from one number into another at a specified position.
 * - isEven: Checks if a number is even using bitwise operations.
 * - swap: Swaps two numbers using bitwise operations.
 * - countSetBits: Counts the number of set bits in an integer.
 * - reverseBits: Reverses the bits of an unsigned integer.
 * - findMissing: Finds the missing number in a sequence using bitwise operations.
 * - isPowerOfTwo: Checks if a number is a power of two using bitwise operations.
 * - findSingle: Finds the single non-duplicate number in an array.
 */
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

#define setBitMask(number_ptr, bit_mask)         ((*number_ptr) |= bit_mask)
#define clearBitMask(number_ptr, bit_mask)       ((*number_ptr) &= ~bit_mask)
#define toggleBitMask(number_ptr, bit_mask)      ((*number_ptr) ^= bit_mask)

int setBit(int num, int position);
int clearBit(int num, int position);
int toggleBit(int num, int position);
int setBits(int dest, int startPosition, int numberOfBits, int source);
bool isEven(int number);
void swap(int * a, int * b);
int countSetBits(int number);
int reverseBits(unsigned int number);
int findMissing(int * numbers, int size);
bool isPowerOfTwo(int number);
int findSingle(int * numbers, int size);

#endif //MAIN_H

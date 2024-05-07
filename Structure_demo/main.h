/*
 * Description:
 * This program demonstrates various operations with structures in C. The following tasks are implemented:
 * 
 * 1. Define and initialize structures:
 *    - Structure definition for 'Person' which includes first name, last name, and age.
 *    - Structure definition for 'Address' which is nested in 'Person'.
 *
 * 2. Data manipulation functions:
 *    - Functions to update age, print information, and check age conditions.
 *
 * 3. File Input/Output:
 *    - Save and load an array of 'Person' structures to and from a file.
 *
 * 4. Sorting and searching:
 *    - Sort persons by age or last name using the 'qsort' function.
 *    - Implement basic search functionality for persons based on name or city.
 *
 * 5. Linked list operations:
 *    - Create, insert, delete, and print operations for a linked list of 'Person'.
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_ZIPCODE_SIZE 10
#define MAX_NAME_SIZE 20
#define MAX_CITY_SIZE 20
#define MAX_STREET_SIZE 100
#define FILE_NAME "people.txt"

typedef struct Address {
    char street[MAX_STREET_SIZE];
    char city[MAX_CITY_SIZE];
    char zipCode[MAX_ZIPCODE_SIZE];
} tAddress;

typedef struct Person {
    char firstName[MAX_NAME_SIZE];
    char lastName[MAX_NAME_SIZE];
    uint8_t age;
    tAddress address;
} tPerson;

void updateAge(tPerson * const person, const uint8_t newAge);
void printInformation(const tPerson * const person);
bool isOverAge(const tPerson * const person, const uint8_t ageToCheck);

void saveListToFile(tPerson* people, size_t peopleSize);
tPerson* readListFromFlie(size_t* peopleSize);
void appendPersonToFile(const tPerson * const  person);

#endif //MAIN_H
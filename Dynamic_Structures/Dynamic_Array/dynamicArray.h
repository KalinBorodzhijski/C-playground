/**
 * @file dynamic_array.h
 * @brief Header file for a dynamic array implementation in C.
 *
 * This header defines the interface for a dynamic array
 * that can resize itself as elements are added or removed. It provides support for
 * basic operations such as insert, delete, and access.
 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_REALLOC_SIZE_ELEMENTS 5
#define SUCCESS 0
#define ERROR -1
#define OUT_OF_MEMORY -2
#define INDEX_OUT_OF_BOUNDS -3


typedef struct {
    int *array;
    int size;
    int capacity;
} DynamicArray;

typedef struct {
    int* current;
    int* start;  
    int* end;    
} Iterator;

// List creation and destruction
DynamicArray* createDynamicArray(int initialCapacity);
void destroyDynamicArray(DynamicArray* da);

// List manipulation
void insertElement(DynamicArray* da, int index, int element);
int removeElement(DynamicArray* da, int index);
int getElement(DynamicArray* da, int index);
void resizeDynamicArray(DynamicArray* da, int newCapacity);
void pushBack(DynamicArray* da, int element);
int popBack(DynamicArray* da);

// Utils Functions
void clearDynamicArray(DynamicArray* da);
int findElement(DynamicArray* da, int element);
void sortDynamicArray(DynamicArray* da);
int replaceElement(DynamicArray* da, int index, int newElement);
void swapElements(DynamicArray* da, int index1, int index2);
void shrinkToFit(DynamicArray* da);
int isEmpty(DynamicArray* da);
int isFull(DynamicArray* da);
void reverseArray(DynamicArray* da);
void forEach(DynamicArray* da, void (*func)(int*));


// Serialization and Deserialization
int serializeDynamicArray(DynamicArray* da, const char* filename);
DynamicArray* deserializeDynamicArray(const char* filename);

// Iterator prototypes
Iterator begin(DynamicArray* da);
Iterator end(DynamicArray* da);
Iterator next(Iterator it);
Iterator prev(Iterator it);

#endif // DYNAMIC_ARRAY_H

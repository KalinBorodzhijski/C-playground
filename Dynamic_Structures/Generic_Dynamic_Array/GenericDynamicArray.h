/**
 * @file GenericDynamicArray.h
 * @brief Header file for a generic dynamic array implementation in C.
 *
 * This header defines the interface for a dynamic array
 * that can resize itself as elements are added or removed.
 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULT_REALLOC_SIZE_ELEMENTS 5
#define SUCCESS 0
#define ERROR -1
#define OUT_OF_MEMORY -2
#define INDEX_OUT_OF_BOUNDS -3

typedef void (*CopyFunction)(void* dest, const void* src);
typedef int (*CompareFunction)(const void* a, const void* b);
typedef void (*DestroyFunction)(void* data);

typedef struct {
    void *array;
    int size;
    int capacity;
    size_t elementSize;
    CopyFunction copyFunc;
    CompareFunction compareFunc;
    DestroyFunction destroyFunc;
} DynamicArray;

typedef struct {
    void* current;
    void* start;
    void* end;
    size_t elementSize;
} Iterator;

// List creation and destruction
DynamicArray* createDynamicArray(size_t elementSize, int initialCapacity, CopyFunction copyFunc, DestroyFunction destroyFunc, CompareFunction compFunc);
void destroyDynamicArray(DynamicArray* da);

// List manipulation
int insertElement(DynamicArray* da, int index, const void* element);
int removeElement(DynamicArray* da, int index, void* removedElement);
void* getElement(DynamicArray* da, int index);
int resizeDynamicArray(DynamicArray* da, int newCapacity);
int pushBack(DynamicArray* da, const void* element);
void* popBack(DynamicArray* da);

// Utils Functions
void clearDynamicArray(DynamicArray* da);
int findElement(DynamicArray* da, const void* element);
void sortDynamicArray(DynamicArray* da);
int replaceElement(DynamicArray* da, int index, const void* newElement);
int swapElements(DynamicArray* da, int index1, int index2);
void shrinkToFit(DynamicArray* da);
int isEmpty(DynamicArray* da);
int isFull(DynamicArray* da);
void reverseArray(DynamicArray* da);
void forEach(DynamicArray* da, void (*func)(void*));

// Serialization and Deserialization
int serializeDynamicArray(DynamicArray* da, const char* filename);
DynamicArray* deserializeDynamicArray(const char* filename, size_t elementSize, CopyFunction copyFunc, DestroyFunction destroyFunc, CompareFunction compFunc);

// Iterator prototypes
Iterator begin(DynamicArray* da);
Iterator end(DynamicArray* da);
Iterator next(Iterator it);
Iterator prev(Iterator it);

#endif // DYNAMIC_ARRAY_H

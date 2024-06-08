/**
 * @file GenericDynamicArray.c
 * @brief Implementation of the dynamic array operations.
 */

#include "GenericDynamicArray.h"


DynamicArray* createDynamicArray(size_t elementSize, int initialCapacity, CopyFunction copyFunc, DestroyFunction destroyFunc, CompareFunction compareFunc) 
{
    if (initialCapacity < 1) 
    {
        fprintf(stderr, "ERROR: Invalid capacity. Capacity must be at least 1.\n");
        return NULL;
    }

    DynamicArray *result = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (result == NULL) 
    {
        fprintf(stderr, "ERROR: Memory allocation for DynamicArray structure failed.\n");
        return NULL;
    }
    
    result->array = malloc(elementSize * initialCapacity);
    if (result->array == NULL) 
    {
        fprintf(stderr, "ERROR: Memory allocation for array failed.\n");
        free(result);
        return NULL;
    }

    result->capacity = initialCapacity;
    result->size = 0;
    result->elementSize = elementSize;
    result->copyFunc = copyFunc;
    result->destroyFunc = destroyFunc;
    result->compareFunc = compareFunc;

    return result;
}
//----------------------------------------------------------------------------------
void destroyDynamicArray(DynamicArray* da) 
{
    if (da == NULL) 
    {
        fprintf(stderr, "ERROR: Cannot destroy a NULL DynamicArray.\n");
        return;
    }

    if (da->destroyFunc) 
    {
        for (int i = 0; i < da->size; i++) {
            da->destroyFunc((char*)da->array + i * da->elementSize);
        }
    }

    free(da->array);
    free(da);
}

//----------------------------------------------------------------------------------
int insertElement(DynamicArray* da, int index, const void* element) 
{
    if (da == NULL || da->array == NULL || index > da->size) 
    {
        fprintf(stderr, "Cannot insert element in array!\n");
        return ERROR;
    }

    if (da->capacity <= da->size) 
    {
        if (resizeDynamicArray(da, da->capacity + DEFAULT_REALLOC_SIZE_ELEMENTS) == OUT_OF_MEMORY) {
            return OUT_OF_MEMORY;
        }
    }

    memmove((char*)da->array + (index + 1) * da->elementSize,
            (char*)da->array + index * da->elementSize,
            (da->size - index) * da->elementSize);
    da->copyFunc((char*)da->array + index * da->elementSize, element);
    da->size++;
    return SUCCESS;
}

//----------------------------------------------------------------------------------
int removeElement(DynamicArray* da, int index, void* removedElement) {
    if (da == NULL || da->array == NULL || index >= da->size || index < 0) 
    {
        fprintf(stderr, "Cannot remove element in array!\n");
        return INDEX_OUT_OF_BOUNDS;
    }

    if (removedElement != NULL) 
    {
        da->copyFunc(removedElement, (char*)da->array + index * da->elementSize);
    }

    if (da->destroyFunc) 
    {
        da->destroyFunc((char*)da->array + index * da->elementSize);
    }

    memmove((char*)da->array + index * da->elementSize,
            (char*)da->array + (index + 1) * da->elementSize,
            (da->size - index - 1) * da->elementSize);
    da->size--;
    return SUCCESS;
}
//----------------------------------------------------------------------------------
void* getElement(DynamicArray* da, int index) 
{
    if (da == NULL || da->array == NULL || index >= da->size) {
        fprintf(stderr, "Cannot get element in array!\n");
        return NULL;
    }

    return (char*)da->array + index * da->elementSize;
}

//----------------------------------------------------------------------------------
int resizeDynamicArray(DynamicArray* da, int newCapacity) 
{
    if (da == NULL || da->array == NULL) 
    {
        fprintf(stderr, "Cannot resize array!\n");
        return ERROR;
    }

    if (newCapacity < da->size) 
    {
        fprintf(stderr, "WARNING: New capacity is lower than the size and information is lost!\n");
        da->size = newCapacity;
    }

    void* newArray = realloc(da->array, newCapacity * da->elementSize);
    if (newArray == NULL) 
    {
        fprintf(stderr, "ERROR: Error during resizing of the array!\n");
        return OUT_OF_MEMORY;
    }

    da->array = newArray;
    da->capacity = newCapacity;
    return SUCCESS;
}

//----------------------------------------------------------------------------------
int pushBack(DynamicArray* da, const void* element) 
{
    if (da == NULL || da->array == NULL) 
    {
        fprintf(stderr, "Cannot push back element in array!\n");
        return ERROR;
    }

    return insertElement(da, da->size, element);
}

//----------------------------------------------------------------------------------
void* popBack(DynamicArray* da) 
{
    if (da == NULL || da->array == NULL || da->size == 0) {
        fprintf(stderr, "Cannot pop back element from array!\n");
        return NULL;
    }

    void* element = malloc(da->elementSize);
    if (element == NULL) 
    {
        fprintf(stderr, "ERROR: Memory allocation for element failed.\n");
        return NULL;
    }
    da->copyFunc(element, (char*)da->array + (da->size - 1) * da->elementSize);
    removeElement(da, da->size - 1, NULL);
    return element;
}
//----------------------------------------------------------------------------------
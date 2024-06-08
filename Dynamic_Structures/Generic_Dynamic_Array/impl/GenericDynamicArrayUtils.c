/**
 * @file GenericDynamicArrayUtils.c
 * @brief Implementation of the dynamic array utility operations.
 */

#include "GenericDynamicArray.h"

//----------------------------------------------------------------------------------
void clearDynamicArray(DynamicArray* da) 
{
    if ((da == NULL) || (da->array == NULL)) 
    {
        fprintf(stderr, "Cannot clear array!\n");
        return;
    }

    if (da->destroyFunc) 
    {
        for (int i = 0; i < da->size; i++) {
            da->destroyFunc((char*)da->array + i * da->elementSize);
        }
    }
    da->size = 0;
}
//----------------------------------------------------------------------------------
int findElement(DynamicArray* da, const void* element) 
{
    if ((da == NULL) || (da->array == NULL) || (da->compareFunc == NULL)) {
        fprintf(stderr, "Cannot find element in array!\n");
        return -1;
    }

    for (int i = 0; i < da->size; i++) 
    {
        if (da->compareFunc((char*)da->array + i * da->elementSize, element) == 0) 
        {
            return i;
        }
    }

    return -1;
}
//----------------------------------------------------------------------------------
void sortDynamicArray(DynamicArray* da) 
{
    if ((da == NULL) || (da->array == NULL) || (da->compareFunc == NULL)) 
    {
        fprintf(stderr, "Cannot sort array!\n");
        return;
    }

    if (da->size > 1) 
    {
        qsort(da->array, da->size, da->elementSize, da->compareFunc);
    }
}
//----------------------------------------------------------------------------------
int replaceElement(DynamicArray* da, int index, const void* newElement) 
{
    if ((!da) || (index < 0) || (index >= da->size)) {
        return -1;
    }

    if (da->destroyFunc) 
    {
        da->destroyFunc((char*)da->array + index * da->elementSize);
    }
    da->copyFunc((char*)da->array + index * da->elementSize, newElement);
    return 0;
}

//----------------------------------------------------------------------------------
int swapElements(DynamicArray* da, int index1, int index2) 
{
    if ((!da) || (index1 < 0) || (index1 >= da->size) || (index2 < 0) || (index2 >= da->size)) {
        return -1;
    }

    void* temp = malloc(da->elementSize);
    if (!temp) 
    {
        return OUT_OF_MEMORY;
    }

    memcpy(temp, (char*)da->array + index1 * da->elementSize, da->elementSize);
    memcpy((char*)da->array + index1 * da->elementSize, (char*)da->array + index2 * da->elementSize, da->elementSize);
    memcpy((char*)da->array + index2 * da->elementSize, temp, da->elementSize);
    free(temp);

    return 0;
}
//----------------------------------------------------------------------------------
void shrinkToFit(DynamicArray* da) 
{
    if (!da || da->size == 0) 
    {
        return;
    }

    void* newArray = realloc(da->array, da->size * da->elementSize);
    if (!newArray) 
    {
        fprintf(stderr, "ERROR: Error during shrinking of the array!\n");
        return;
    }
    da->array = newArray;
    da->capacity = da->size;
}//----------------------------------------------------------------------------------
int isEmpty(DynamicArray* da) 
{
    if (!da) 
    {
        return -1;
    }

    return da->size == 0 ? 1 : 0;
}

//----------------------------------------------------------------------------------
int isFull(DynamicArray* da) 
{
    if (!da) 
    {
        return -1;
    }

    return da->size == da->capacity;
}
//----------------------------------------------------------------------------------
void reverseArray(DynamicArray* da) 
{
    if (!da || da->size == 0) 
    {
        return;
    }

    for (int i = 0; i < da->size / 2; i++) 
    {
        swapElements(da, i, da->size - i - 1);
    }
}

//----------------------------------------------------------------------------------
void forEach(DynamicArray* da, void (*func)(void*)) 
{
    if (!da || !func) {
        return;
    }

    for (int i = 0; i < da->size; i++) 
    {
        func((char*)da->array + i * da->elementSize);
    }
}
//----------------------------------------------------------------------------------
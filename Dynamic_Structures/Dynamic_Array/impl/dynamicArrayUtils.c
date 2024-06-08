/**
 * @file dynamicArrayutils.c
 * @brief Implementation of the dynamic array utility operations.
 */

#include "dynamicArray.h"


int compareIntegers(const void *a, const void *b);

//----------------------------------------------------------------------------------
void clearDynamicArray(DynamicArray* da)
{
    if ((da == NULL) || (da->array == NULL))
    {
        fprintf(stderr, "Cannot insert element in array !\n");
        return;
    }

    da->size = 0;
}

//----------------------------------------------------------------------------------
int findElement(DynamicArray* da, int element)
{
    if ((da == NULL) || (da->array == NULL))
    {
        fprintf(stderr, "Cannot insert element in array !\n");
        return -1;
    }

    for (size_t i = 0; i < da->size; i++)
    {
        if (da->array[i] == element)
        {
            return i;
        }
    }

    return -1;
}

//----------------------------------------------------------------------------------
void sortDynamicArray(DynamicArray* da)
{
    if ((da == NULL) || (da->array == NULL))
    {
        fprintf(stderr, "Cannot insert element in array !\n");
        return;
    }

    if (da->size > 1) {
        qsort(da->array, da->size, sizeof(int), compareIntegers);
    }
}

//----------------------------------------------------------------------------------
int replaceElement(DynamicArray* da, int index, int newElement) {
    if ((!da) || (index < 0) || (index >= da->size)) {
        return -1;
    }
    
    int replacedElement = da->array[index];
    da->array[index] = newElement;
    return replacedElement;
}
//----------------------------------------------------------------------------------
void swapElements(DynamicArray* da, int index1, int index2) {
    if ((!da) || (index1 < 0) || (index1 >= da->size) || (index2 < 0) || (index2 >= da->size)) {
        return;
    }
    int tempNum = da->array[index1];
    da->array[index1] = da->array[index2];
    da->array[index2] = tempNum;
}
//----------------------------------------------------------------------------------
void shrinkToFit(DynamicArray* da) {
    if (!da || da->size == 0) {
        return;
    }

    da->array = (int*) realloc(da->array, da->size * sizeof(int));
    if (!da->array)
    {
        fprintf(stderr, "ERROR: Error during shrinking of the array !");
    } 
    

}
//----------------------------------------------------------------------------------
int isEmpty(DynamicArray* da) {
    if (!da) {
        return -1;
    }

    return da->size == 0 ? 1 : 0;
}
//----------------------------------------------------------------------------------
int isFull(DynamicArray* da) {
    if (!da) {
        return -1;
    }

    return da->size == da->capacity;
}
//----------------------------------------------------------------------------------
void reverseArray(DynamicArray* da) {
    if (!da || da->size == 0) {
        return;
    }
    
    for (size_t i = 0; i < da->size / 2; i++)
    {
        int temp = da->array[i];
        da->array[i] = da->array[da->size - i - 1];
        da->array[da->size - i - 1] = temp;
    }
}
//----------------------------------------------------------------------------------
void forEach(DynamicArray* da, void (*func)(int*)) {
    if (!da || !func) {
        return;
    }

    for (size_t i = 0; i < da->size; i++)
    {
        func((int*)da->array[i]);
    }
}
//----------------------------------------------------------------------------------
int compareIntegers(const void *a, const void *b) 
{
    return *(const int*)a - *(const int*)b;
}
//----------------------------------------------------------------------------------
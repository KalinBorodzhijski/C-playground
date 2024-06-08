/**
 * @file dynamic_array.c
 * @brief Implementation of the dynamic array operations.
 */

#include "dynamicArray.h"


//----------------------------------------------------------------------------------
DynamicArray* createDynamicArray(int initialCapacity)
{
    if (initialCapacity < 1) {
        fprintf(stderr, "ERROR: Invalid capacity. Capacity must be at least 1.\n");
        return NULL;
    }

    DynamicArray *result = malloc(sizeof(DynamicArray));
    if (result == NULL) {
        fprintf(stderr, "ERROR: Memory allocation for DynamicArray structure failed.\n");
        return NULL;
    }
    
    result->array = (int *) malloc(initialCapacity * sizeof(int));
    if (result->array == NULL) {
        fprintf(stderr, "ERROR: Memory allocation for array failed.\n");
        free(result);
        return NULL;
    }

    result->capacity = initialCapacity;
    result->size = 0;

    return result;

}

//----------------------------------------------------------------------------------
void destroyDynamicArray(DynamicArray* da) {
    if (da == NULL) {
        fprintf(stderr, "ERROR: Cannot destroy a NULL DynamicArray.\n");
        return;
    }

    free(da->array);
    free(da);
}
//----------------------------------------------------------------------------------
void insertElement(DynamicArray* da, int index, int element)
{
    if ((da == NULL) || (da->array == NULL) || ((index > da->size)))
    {
        fprintf(stderr, "Cannot insert element in array !\n");
        return;
    }

    if(da->capacity <= da->size)
    {
        da->array = (int*)realloc(da->array, (da->capacity + DEFAULT_REALLOC_SIZE_ELEMENTS) * sizeof(int));
        if (da->array == NULL)
        {
            fprintf(stderr, "Cannot insert element in array !\n");
            return;
        }
        da->capacity += DEFAULT_REALLOC_SIZE_ELEMENTS;
    }

    for (size_t i = index; i < da->size; i++)
    {
        da->array[i+1] = da->array[i];
    }
    da->array[index] = element;
    da->size++;
}

//----------------------------------------------------------------------------------
int removeElement(DynamicArray* da, int index) 
{
    int elementToRemove;
    if ((da == NULL) || (da->array == NULL))
    {
        fprintf(stderr, "Cannot remove element in array !\n");
        return -1;
    }

    if (index >= da->size)
    {
        fprintf(stderr, "Cannot remove element in array - Invalid index %d size of the array is %d !\n", index, da->size);
        return INDEX_OUT_OF_BOUNDS;
    }
    elementToRemove = da->array[index];
    for (size_t i = index; i < da->size - 1; i++)
    {
        da->array[i] = da->array[i+1];
    }
    da->size--;

    return elementToRemove;
}

//----------------------------------------------------------------------------------
int getElement(DynamicArray* da, int index) 
{
    if ((da == NULL) || (da->array == NULL))
    {
        fprintf(stderr, "Cannot get element in array !\n");
        return ERROR;
    }

    if (index >= da->size)
    {
        fprintf(stderr, "Cannot get element in array - Invalid index %d size of the array is %d !\n", index, da->size);
        return INDEX_OUT_OF_BOUNDS;
    }

    return da->array[index];
}

//----------------------------------------------------------------------------------
void resizeDynamicArray(DynamicArray* da, int newCapacity) 
{
    if ((da == NULL) || (da->array == NULL))
    {
        fprintf(stderr, "Cannot resize array !\n");
        return;
    }

    if(newCapacity < da->size)
    {
        fprintf(stderr, "WARNING: New capacity is lower than the size and information is lost !\n");
        da->size = newCapacity;
    }

    da->array = (int*)realloc(da->array, newCapacity * sizeof(int));
    if (da->array == NULL)
    {
        fprintf(stderr, "ERROR: Error during resizing of the array !\n");
        return;
    }

    da->capacity = newCapacity;
}

//----------------------------------------------------------------------------------
void pushBack(DynamicArray* da, int element)
{
    if ((da == NULL) || (da->array == NULL))
    {
        fprintf(stderr, "Cannot push back element in array !\n");
        return;
    }

    insertElement(da, da->size, element);
}

//----------------------------------------------------------------------------------
int popBack(DynamicArray* da)
{
    if ((da == NULL) || (da->array == NULL))
    {
        fprintf(stderr, "Cannot insert element in array !\n");
        return -1;
    }

    return removeElement(da, da->size-1);
}

//----------------------------------------------------------------------------------

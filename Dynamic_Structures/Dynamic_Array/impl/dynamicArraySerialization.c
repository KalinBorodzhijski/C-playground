/**
 * @file dynamicArraySerialization.c
 * @brief Implementation of the dynamic array serialization and deserialization functions.
 */


#include "dynamicArray.h"

int serializeDynamicArray(DynamicArray* da, const char* filename)
{
    if (da == NULL || filename == NULL) {
        fprintf(stderr, "ERROR: Null pointer provided to serializeDynamicArray.\n");
        return ERROR;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "ERROR: Unable to open file %s for writing.\n", filename);
        return ERROR;
    }

    if ((fwrite(&da->capacity, sizeof(da->capacity), 1, file) != 1) ||
        (fwrite(&da->size, sizeof(da->size), 1, file) != 1)) 
    {
        fprintf(stderr, "ERROR: Failed to write metadata to file %s.\n", filename);
        fclose(file);
        return ERROR;
    }

    if (da->size > 0) {
        if (fwrite(da->array, sizeof(da->array[0]), da->size, file) != da->size) {
            fprintf(stderr, "ERROR: Failed to write array data to file %s.\n", filename);
            fclose(file);
            return ERROR;
        }
    }

    fclose(file);
}
//--------------------------------------------------------------------
DynamicArray* deserializeDynamicArray(const char* filename)
{
    if (filename == NULL) {
        fprintf(stderr, "ERROR: Null pointer provided to deserializeDynamicArray.\n");
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "ERROR: Unable to open file %s for reading.\n", filename);
        return NULL;
    }

    
    DynamicArray* result = malloc(sizeof(DynamicArray));
    if (result == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    if (fread(&result->capacity, sizeof(result->capacity), 1, file) != 1 ||
        fread(&result->size, sizeof(result->size), 1, file) != 1) {
        fprintf(stderr, "ERROR: Failed to read metadata from file %s.\n", filename);
        free(result);
        fclose(file);
        return NULL;
    }

    result->array = (int*) malloc(result->capacity * sizeof(int));
    if (result->array == NULL) {
        fprintf(stderr, "ERROR: Array memory allocation failed.\n");
        free(result);
        fclose(file);
        return NULL;
    }

    if (result->size > 0) {
        if (fread(result->array, sizeof(result->array[0]), result->size, file) != result->size) {
            fprintf(stderr, "ERROR: Failed to read array data from file %s.\n", filename);
            free(result->array);
            free(result);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return result;

}
//--------------------------------------------------------------------
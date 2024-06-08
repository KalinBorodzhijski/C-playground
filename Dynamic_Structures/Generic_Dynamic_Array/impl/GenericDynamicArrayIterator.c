/**
 * @file GenericDynamicArrayIterator.c
 * @brief Implementation of the dynamic array iterators.
 */

#include "GenericDynamicArray.h"

Iterator begin(DynamicArray* da) {
    Iterator it;
    it.current = da->array;
    it.start = da->array;
    it.end = (char*)da->array + da->size * da->elementSize;
    it.elementSize = da->elementSize;
    return it;
}
//----------------------------------------------------------------------------------
Iterator end(DynamicArray* da) {
    Iterator it;
    it.current = (char*)da->array + da->size * da->elementSize;
    it.start = da->array;
    it.end = (char*)da->array + da->size * da->elementSize;
    it.elementSize = da->elementSize;
    return it;
}
//----------------------------------------------------------------------------------
Iterator next(Iterator it) {
    it.current = (char*)it.current + it.elementSize;
    return it;
}
//----------------------------------------------------------------------------------
Iterator prev(Iterator it) {
    it.current = (char*)it.current - it.elementSize;
    return it;
}
//----------------------------------------------------------------------------------
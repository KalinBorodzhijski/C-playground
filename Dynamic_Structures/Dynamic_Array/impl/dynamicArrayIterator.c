/**
 * @file dynamicArrayIterator.c
 * @brief Implementation of the dynamic array iterators.
 */

#include "dynamicArray.h"

Iterator begin(DynamicArray* da) {
    Iterator it = { .current = da->array, .start = da->array, .end = da->array + da->size };
    return it;
}
//---------------------------------------------------------------------

Iterator end(DynamicArray* da) {
    Iterator it = { .current = da->array + da->size, .start = da->array, .end = da->array + da->size };
    return it;
}
//---------------------------------------------------------------------
Iterator next(Iterator it) {
    if (it.current < it.end) {
        it.current++;
    }
    return it;
}
//---------------------------------------------------------------------
Iterator prev(Iterator it) {
    if (it.current > it.start) {
        it.current--;
    }
    return it;
}
//---------------------------------------------------------------------

/**
 * @file testDynamicArray.c
 * @brief Test program for the dynamic array implementation with extended functionalities.
 */

#include "dynamicArray.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ASSERT(cond, msg) if (!(cond)) { printf("FAIL: %s\n", msg); } else { printf("PASS: %s\n", msg); }

void testCreationAndDestruction();
void testInsertionsAndRemovals();
void testUtilityFunctions();
void testSerialization();
void testIterators();
void incrementElement(int *element);

int main() {
    testCreationAndDestruction();
    testInsertionsAndRemovals();
    testUtilityFunctions();
    testSerialization();
    testIterators();

    return 0;
}
//-------------------------------------------------------------
void testCreationAndDestruction()
{
    DynamicArray *da = createDynamicArray(10);
    ASSERT(da != NULL, "Create DynamicArray");
    ASSERT(da->capacity == 10, "Capacity is correct on creation");
    destroyDynamicArray(da);
    ASSERT(da, "DynamicArray destroyed");
}
//-------------------------------------------------------------
void testInsertionsAndRemovals() {
    DynamicArray *da = createDynamicArray(5);
    
    insertElement(da, 0, 100);
    ASSERT(getElement(da, 0) == 100, "Insert 100 at index 0");

    insertElement(da, 1, 200);
    ASSERT(getElement(da, 1) == 200, "Insert 200 at index 1");

    insertElement(da, 1, 150);
    ASSERT(getElement(da, 1) == 150, "Insert 150 at index 1");
    ASSERT(getElement(da, 2) == 200, "200 moved to index 2");

    resizeDynamicArray(da, 10);
    ASSERT(da->capacity == 10, "Resize array to capacity 10");

    for (int i = 3; i < 10; i++) {
        pushBack(da, i * 100);
    }
    ASSERT(da->size == 10, "Array size after multiple pushBacks");
    pushBack(da, 1100);
    ASSERT(da->capacity > 10, "Array resized automatically on pushBack");

    int lastElement = popBack(da);
    ASSERT(lastElement == 1100, "Pop back the last element 1100");
    ASSERT(da->size == 10, "Size after popBack");

    int removedElement = removeElement(da, 1);
    ASSERT(removedElement == 150, "Remove element at index 1");
    ASSERT(getElement(da, 1) == 200, "Element at index 1 is now 200");

    removeElement(da, 0);
    ASSERT(getElement(da, 0) == 200, "First element removed, first element is now 200");

    destroyDynamicArray(da);
}
//-------------------------------------------------------------
void testUtilityFunctions() {
    DynamicArray *da = createDynamicArray(5);

    ASSERT(isEmpty(da) == 1, "Array should be empty initially");
    ASSERT(isFull(da) == 0, "Array should not be full initially");

    for (int i = 0; i < 5; i++) {
        pushBack(da, i * 10);
    }

    ASSERT(isEmpty(da) == 0, "Array should not be empty after insertions");
    ASSERT(isFull(da) == 1, "Array should be full after insertions");

    ASSERT(findElement(da, 20) == 2, "Find element that exists");
    ASSERT(findElement(da, 99) == -1, "Find element that does not exist");

    replaceElement(da, 2, 25);
    ASSERT(getElement(da, 2) == 25, "Replace element at index");

    swapElements(da, 1, 3);
    ASSERT(getElement(da, 1) == 30 && getElement(da, 3) == 10, "Swap elements");

    sortDynamicArray(da);
    ASSERT(getElement(da, 0) == 0 && getElement(da, 4) == 40, "Array is sorted");

    clearDynamicArray(da);
    ASSERT(da->size == 0, "Array should be empty after clear");

    for (int i = 0; i < 5; i++) {
        pushBack(da, i); 
    }
    shrinkToFit(da);
    ASSERT(da->capacity == 5, "Capacity should match size after shrinkToFit");

    reverseArray(da);
    ASSERT(getElement(da, 0) == 4 && getElement(da, 4) == 0, "Array is reversed");

    forEach(da, incrementElement);
    ASSERT(getElement(da, 0) == 5, "forEach increments elements");

    destroyDynamicArray(da);
}
//-------------------------------------------------------------
void testSerialization()
{
    DynamicArray *da = createDynamicArray(2);
    pushBack(da, 1);
    pushBack(da, 2);
    int res = serializeDynamicArray(da, "test_save.dat");
    ASSERT(res == 0, "Serialize array");

    DynamicArray *loaded = deserializeDynamicArray("test_save.dat");
    ASSERT(loaded != NULL, "Deserialize array");
    ASSERT(getElement(loaded, 0) == 1 && getElement(loaded, 1) == 2, "Check deserialized values");

    destroyDynamicArray(da);
    destroyDynamicArray(loaded);
}
//-------------------------------------------------------------
void testIterators() {
    DynamicArray *da = createDynamicArray(5);
    for (int i = 0; i < 5; i++) {
        pushBack(da, i + 1);
    }

    Iterator it = begin(da);
    int count = 1;
    bool forwardCorrect = true;
    while (it.current != end(da).current) {
        if (*it.current != count) {
            forwardCorrect = false;
            break;
        }
        it = next(it);
        count++;
    }
    ASSERT(forwardCorrect, "Iterator forward traversal works correctly");

    it = prev(end(da));
    count = 5;
    bool backwardCorrect = true;
    while (it.current != begin(da).current) {
        if (*it.current != count) {
            backwardCorrect = false;
            break;
        }
        it = prev(it);
        count--;
    }
    ASSERT(backwardCorrect, "Iterator backward traversal works correctly");

    destroyDynamicArray(da);
}
//-------------------------------------------------------------
void incrementElement(int *element) 
{
    (*element)++;
}
//-------------------------------------------------------------
/**
 * @file testGenericDynamicArray.c
 * @brief Test program for the dynamic array implementation with extended functionalities.
 */

#include "GenericDynamicArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ASSERT(cond, msg) if (!(cond)) { printf("FAIL: %s\n", msg); } else { printf("PASS: %s\n", msg); }

typedef struct {
    char name[50];
    int age;
} Person;

void copyPerson(void* dest, const void* src) 
{
    *(Person*)dest = *(const Person*)src;
}

void destroyPerson(void* data) 
{
    // Nothing to do here for Person as no dynamic memory is used
}

int comparePerson(const void* a, const void* b) 
{
    Person* personA = (Person*)a;
    Person* personB = (Person*)b;
    int nameComparison = strcmp(personA->name, personB->name);
    if (nameComparison != 0) {
        return nameComparison;
    }
    return personA->age - personB->age;
}

void copyDouble(void* dest, const void* src) 
{
    *(double*)dest = *(const double*)src;
}

void destroyDouble(void* data) 
{
    // Nothing to do here for double
}

int compareDouble(const void* a, const void* b) 
{
    if (*(double*)a == *(double*)b) return 0;
    return *(double*)a > *(double*)b ? 1 : -1;
}

void testCreationAndDestruction();
void testInsertionsAndRemovals();
void testUtilityFunctions();
void testSerialization();
void testIterators();
void incrementPersonAge(void* element);
void incrementDoubleValue(void* element);

int main() 
{
    testCreationAndDestruction();
    testInsertionsAndRemovals();
    testUtilityFunctions();
    testSerialization();
    testIterators();

    return 0;
}

void testCreationAndDestruction() 
{
    DynamicArray *da = createDynamicArray(sizeof(Person), 10, copyPerson, destroyPerson, comparePerson);
    ASSERT(da != NULL, "Create DynamicArray for Person");
    ASSERT(da->capacity == 10, "Capacity is correct on creation");
    destroyDynamicArray(da);
    printf("PASS: DynamicArray destroyed\n");

    DynamicArray *daDouble = createDynamicArray(sizeof(double), 10, copyDouble, destroyDouble, compareDouble);
    ASSERT(daDouble != NULL, "Create DynamicArray for double");
    ASSERT(daDouble->capacity == 10, "Capacity is correct on creation");
    destroyDynamicArray(daDouble);
    printf("PASS: DynamicArray destroyed\n");
}


//-------------------------------------------------------------
void testInsertionsAndRemovals() 
{
    DynamicArray *da = createDynamicArray(sizeof(Person), 5, copyPerson, destroyPerson, comparePerson);

    Person p1 = {"Alice", 30};
    insertElement(da, 0, &p1);
    ASSERT(strcmp(((Person*)getElement(da, 0))->name, "Alice") == 0, "Insert Alice at index 0");

    Person p2 = {"Bob", 25};
    insertElement(da, 1, &p2);
    ASSERT(strcmp(((Person*)getElement(da, 1))->name, "Bob") == 0, "Insert Bob at index 1");

    Person p3 = {"Charlie", 35};
    insertElement(da, 1, &p3);
    ASSERT(strcmp(((Person*)getElement(da, 1))->name, "Charlie") == 0, "Insert Charlie at index 1");
    ASSERT(strcmp(((Person*)getElement(da, 2))->name, "Bob") == 0, "Bob moved to index 2");

    resizeDynamicArray(da, 10);
    ASSERT(da->capacity == 10, "Resize array to capacity 10");

    for (int i = 3; i < 10; i++) {
        Person p = {"Person", i * 5};
        pushBack(da, &p);
    }
    ASSERT(da->size == 10, "Array size after multiple pushBacks");

    Person p4 = {"David", 40};
    pushBack(da, &p4);
    ASSERT(da->capacity > 10, "Array resized automatically on pushBack");

    Person* lastElement = (Person*)popBack(da);
    ASSERT(strcmp(lastElement->name, "David") == 0, "Pop back the last element David");
    ASSERT(da->size == 10, "Size after popBack");

    Person removedElement;
    removeElement(da, 1, &removedElement);
    ASSERT(strcmp(removedElement.name, "Charlie") == 0, "Remove element at index 1");
    ASSERT(strcmp(((Person*)getElement(da, 1))->name, "Bob") == 0, "Element at index 1 is now Bob");

    removeElement(da, 0, &removedElement);
    ASSERT(strcmp(((Person*)getElement(da, 0))->name, "Bob") == 0, "First element removed, first element is now Bob");

    destroyDynamicArray(da);

    // Test with double
    DynamicArray *daDouble = createDynamicArray(sizeof(double), 5, copyDouble, destroyDouble, compareDouble);

    double d1 = 10.5;
    insertElement(daDouble, 0, &d1);
    ASSERT(*(double*)getElement(daDouble, 0) == 10.5, "Insert 10.5 at index 0");

    double d2 = 20.5;
    insertElement(daDouble, 1, &d2);
    ASSERT(*(double*)getElement(daDouble, 1) == 20.5, "Insert 20.5 at index 1");

    double d3 = 15.5;
    insertElement(daDouble, 1, &d3);
    ASSERT(*(double*)getElement(daDouble, 1) == 15.5, "Insert 15.5 at index 1");
    ASSERT(*(double*)getElement(daDouble, 2) == 20.5, "20.5 moved to index 2");

    resizeDynamicArray(daDouble, 10);
    ASSERT(daDouble->capacity == 10, "Resize array to capacity 10");

    for (int i = 3; i < 10; i++) {
        double d = i * 5.0;
        pushBack(daDouble, &d);
    }
    ASSERT(daDouble->size == 10, "Array size after multiple pushBacks");

    double d4 = 50.5;
    pushBack(daDouble, &d4);
    ASSERT(daDouble->capacity > 10, "Array resized automatically on pushBack");

    double* lastElementDouble = (double*)popBack(daDouble);
    ASSERT(*lastElementDouble == 50.5, "Pop back the last element 50.5");
    ASSERT(daDouble->size == 10, "Size after popBack");

    double removedElementDouble;
    removeElement(daDouble, 1, &removedElementDouble);
    ASSERT(removedElementDouble == 15.5, "Remove element at index 1");
    ASSERT(*(double*)getElement(daDouble, 1) == 20.5, "Element at index 1 is now 20.5");

    removeElement(daDouble, 0, &removedElementDouble);
    ASSERT(*(double*)getElement(daDouble, 0) == 20.5, "First element removed, first element is now 20.5");

    destroyDynamicArray(daDouble);
}

//-------------------------------------------------------------
void testUtilityFunctions() 
{
    DynamicArray *da = createDynamicArray(sizeof(Person), 5, copyPerson, destroyPerson, comparePerson);

    ASSERT(isEmpty(da) == 1, "Array should be empty initially");
    ASSERT(isFull(da) == 0, "Array should not be full initially");

    for (int i = 0; i < 5; i++) {
        Person p = {"Person", i * 10};
        pushBack(da, &p);
    }

    ASSERT(isEmpty(da) == 0, "Array should not be empty after insertions");
    ASSERT(isFull(da) == 1, "Array should be full after insertions");

    Person p = {"Person", 20};
    ASSERT(findElement(da, &p) == 2, "Find element that exists");
    Person pNotExist = {"NotExist", 99};
    ASSERT(findElement(da, &pNotExist) == -1, "Find element that does not exist");

    Person pNew = {"NewPerson", 25};
    replaceElement(da, 2, &pNew);
    ASSERT(strcmp(((Person*)getElement(da, 2))->name, "NewPerson") == 0, "Replace element at index");

    swapElements(da, 1, 3);
    ASSERT(strcmp(((Person*)getElement(da, 1))->name, "Person") == 0 && ((Person*)getElement(da, 1))->age == 30 &&
           strcmp(((Person*)getElement(da, 3))->name, "Person") == 0 && ((Person*)getElement(da, 3))->age == 10, "Swap elements");

    sortDynamicArray(da);
    ASSERT(strcmp(((Person*)getElement(da, 0))->name, "NewPerson") == 0, "Array is sorted");

    clearDynamicArray(da);
    ASSERT(da->size == 0, "Array should be empty after clear");

    for (int i = 0; i < 5; i++) {
        Person p = {"Person", i};
        pushBack(da, &p);
    }
    shrinkToFit(da);
    ASSERT(da->capacity == 5, "Capacity should match size after shrinkToFit");

    reverseArray(da);
    ASSERT(strcmp(((Person*)getElement(da, 0))->name, "Person") == 0 && ((Person*)getElement(da, 0))->age == 4, "Array is reversed");

    forEach(da, incrementPersonAge);
    ASSERT(((Person*)getElement(da, 0))->age == 5, "forEach increments elements");

    destroyDynamicArray(da);

    // Test with double
    DynamicArray *daDouble = createDynamicArray(sizeof(double), 5, copyDouble, destroyDouble, compareDouble);

    ASSERT(isEmpty(daDouble) == 1, "Array should be empty initially");
    ASSERT(isFull(daDouble) == 0, "Array should not be full initially");

    for (int i = 0; i < 5; i++) {
        double d = i * 10.0;
        pushBack(daDouble, &d);
    }

    ASSERT(isEmpty(daDouble) == 0, "Array should not be empty after insertions");
    ASSERT(isFull(daDouble) == 1, "Array should be full after insertions");

    double dExist = 20.0;
    ASSERT(findElement(daDouble, &dExist) == 2, "Find element that exists");
    double dNotExist = 99.0;
    ASSERT(findElement(daDouble, &dNotExist) == -1, "Find element that does not exist");

    double dNew = 25.0;
    replaceElement(daDouble, 2, &dNew);
    ASSERT(*(double*)getElement(daDouble, 2) == 25.0, "Replace element at index");

    swapElements(daDouble, 1, 3);
    ASSERT(*(double*)getElement(daDouble, 1) == 30.0 && *(double*)getElement(daDouble, 3) == 10.0, "Swap elements");

    sortDynamicArray(daDouble);
    ASSERT(*(double*)getElement(daDouble, 0) == 0.0 && *(double*)getElement(daDouble, 4) == 40.0, "Array is sorted");

    clearDynamicArray(daDouble);
    ASSERT(daDouble->size == 0, "Array should be empty after clear");

    for (int i = 0; i < 5; i++) {
        double d = i;
        pushBack(daDouble, &d);
    }
    shrinkToFit(daDouble);
    ASSERT(daDouble->capacity == 5, "Capacity should match size after shrinkToFit");

    reverseArray(daDouble);
    ASSERT(*(double*)getElement(daDouble, 0) == 4.0 && *(double*)getElement(daDouble, 4) == 0.0, "Array is reversed");

    forEach(daDouble, incrementDoubleValue);
    ASSERT(*(double*)getElement(daDouble, 0) == 5.0, "forEach increments elements");

    destroyDynamicArray(daDouble);
}

//-------------------------------------------------------------
void testSerialization() {
    DynamicArray *da = createDynamicArray(sizeof(Person), 2, copyPerson, destroyPerson, comparePerson);
    Person p1 = {"Alice", 30};
    Person p2 = {"Bob", 25};
    pushBack(da, &p1);
    pushBack(da, &p2);
    int res = serializeDynamicArray(da, "test_save_person.dat");
    ASSERT(res == 0, "Serialize array of Person");

    DynamicArray *loaded = deserializeDynamicArray("test_save_person.dat", sizeof(Person), copyPerson, destroyPerson, comparePerson);
    ASSERT(loaded != NULL, "Deserialize array of Person");
    ASSERT(strcmp(((Person*)getElement(loaded, 0))->name, "Alice") == 0 && ((Person*)getElement(loaded, 1))->age == 25, "Check deserialized values of Person");

    destroyDynamicArray(da);
    destroyDynamicArray(loaded);

    // Test with double
    DynamicArray *daDouble = createDynamicArray(sizeof(double), 2, copyDouble, destroyDouble, compareDouble);
    double d1 = 10.5;
    double d2 = 20.5;
    pushBack(daDouble, &d1);
    pushBack(daDouble, &d2);
    res = serializeDynamicArray(daDouble, "test_save_double.dat");
    ASSERT(res == 0, "Serialize array of double");

    DynamicArray *loadedDouble = deserializeDynamicArray("test_save_double.dat", sizeof(double), copyDouble, destroyDouble, compareDouble);
    ASSERT(loadedDouble != NULL, "Deserialize array of double");
    ASSERT(*(double*)getElement(loadedDouble, 0) == 10.5 && *(double*)getElement(loadedDouble, 1) == 20.5, "Check deserialized values of double");

    destroyDynamicArray(daDouble);
    destroyDynamicArray(loadedDouble);
}

//-------------------------------------------------------------
void testIterators() {
    DynamicArray *da = createDynamicArray(sizeof(Person), 5, copyPerson, destroyPerson, comparePerson);
    for (int i = 0; i < 5; i++) {
        Person p = {"Person", i + 1};
        pushBack(da, &p);
    }

    Iterator it = begin(da);
    int count = 1;
    bool forwardCorrect = true;
    while (it.current != end(da).current) {
        if (((Person*)it.current)->age != count) {
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
        if (((Person*)it.current)->age != count) {
            backwardCorrect = false;
            break;
        }
        it = prev(it);
        count--;
    }
    ASSERT(backwardCorrect, "Iterator backward traversal works correctly");

    destroyDynamicArray(da);

    // Test with double
    DynamicArray *daDouble = createDynamicArray(sizeof(double), 5, copyDouble, destroyDouble, compareDouble);
    for (int i = 0; i < 5; i++) {
        double d = i + 1.0;
        pushBack(daDouble, &d);
    }

    it = begin(daDouble);
    count = 1;
    forwardCorrect = true;
    while (it.current != end(daDouble).current) {
        if (*(double*)it.current != count) {
            forwardCorrect = false;
            break;
        }
        it = next(it);
        count++;
    }
    ASSERT(forwardCorrect, "Iterator forward traversal works correctly for double");

    it = prev(end(daDouble));
    count = 5;
    backwardCorrect = true;
    while (it.current != begin(daDouble).current) {
        if (*(double*)it.current != count) {
            backwardCorrect = false;
            break;
        }
        it = prev(it);
        count--;
    }
    ASSERT(backwardCorrect, "Iterator backward traversal works correctly for double");

    destroyDynamicArray(daDouble);
}

//-------------------------------------------------------------
void incrementPersonAge(void* element) 
{
    ((Person*)element)->age++;
}
//-------------------------------------------------------------
void incrementDoubleValue(void* element) 
{
    (*(double*)element)++;
}
//-------------------------------------------------------------
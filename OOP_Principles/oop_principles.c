/**
 * @file oop_principles.c
 * @brief Implementation of the MyClass class in C using Object-Oriented Programming principles.
 *
 * This file contains the implementation of the functions and methods defined in the oop_principles.h header file.
 * It provides the functionality for creating, manipulating, and destroying instances of MyClass.
 *
 * Author: Kalin Borodzhijski
 * Date: 27.06.2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "oop_principles.h"

// Private method
static void doSomethingImpl(MyClass* instance)
{
    if (instance)
    {
        printf("Doing something with data: %d\n", instance->data);
    }
}

// Constructor
MyClass* MyClass_create()
{
    MyClass* instance = (MyClass*)malloc(sizeof(MyClass));
    if (instance)
    {
        instance->data = 0;
        instance->doSomething = doSomethingImpl;
    }
    return instance;
}

// Destructor
void MyClass_destroy(MyClass* instance)
{
    if (instance)
    {
        free(instance);
    }
}

// Public method
void MyClass_doSomething(MyClass* instance)
{
    if (instance && instance->doSomething)
    {
        instance->doSomething(instance);
    }
}
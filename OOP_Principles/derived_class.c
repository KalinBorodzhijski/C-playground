/**
 * @file derived_class.c
 * @brief Implementation of the MyDerivedClass class in C using Object-Oriented Programming principles.
 *
 * This file contains the implementation of the functions and methods defined in the derived_class.h header file.
 * It demonstrates inheritance and polymorphism by extending MyClass.
 *
 * Author: Kalin Borodzhijski
 * Date: 27.06.2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "derived_class.h"
#include "oop_principles.h"

struct MyDerivedClass {
    MyClass base;
    int additionalData;
};

// Private method
static void doSomethingImpl(MyClass* instance)
{
    MyDerivedClass* derivedInstance = (MyDerivedClass*)instance;
    if (derivedInstance)
    {
        printf("Doing something with base data: %d and additional data: %d\n",
               derivedInstance->base.data, derivedInstance->additionalData);
    }
}

// Constructor
MyDerivedClass* MyDerivedClass_create()
{
    MyDerivedClass* instance = (MyDerivedClass*)malloc(sizeof(MyDerivedClass));
    if (instance)
    {
        instance->base.data = 0;
        instance->additionalData = 42;
        instance->base.doSomething = doSomethingImpl;
    }
    return instance;
}

// Destructor
void MyDerivedClass_destroy(MyDerivedClass* instance)
{
    if (instance)
    {
        free(instance);
    }
}

// Public method
void MyDerivedClass_doSomething(MyDerivedClass* instance)
{
    if (instance && instance->base.doSomething)
    {
        instance->base.doSomething((MyClass*)instance);
    }
}

/**
 * @file derived_class.h
 * @brief Definition of the MyDerivedClass class in C using Object-Oriented Programming principles.
 *
 * This file contains the definition of the MyDerivedClass struct and the declarations of the public functions and methods
 * for creating, manipulating, and destroying instances of MyDerivedClass. It extends MyClass to demonstrate inheritance
 * and polymorphism.
 *
 * Author: Kalin Borodzhijski
 * Date: 27.06.2024
 */

#ifndef DERIVED_CLASS_H
#define DERIVED_CLASS_H

#include "oop_principles.h"

typedef struct MyDerivedClass MyDerivedClass;

MyDerivedClass* MyDerivedClass_create();
void MyDerivedClass_destroy(MyDerivedClass* instance);

void MyDerivedClass_doSomething(MyDerivedClass* instance);

#endif // DERIVED_CLASS_H

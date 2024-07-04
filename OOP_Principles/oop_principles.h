/**
 * @file oop_principles.h
 * @brief Definition of the MyClass class in C using Object-Oriented Programming principles.
 *
 * This file contains the definition of the MyClass struct and the declarations of the public functions and methods
 * for creating, manipulating, and destroying instances of MyClass.

 *
 *
 * Author: Kalin Borodzhijski
 * Date: 27.06.2024
 */

#ifndef OOP_PRINCIPLES_H
#define OOP_PRINCIPLES_H

typedef struct MyClass MyClass;

struct MyClass {
    int data;
    void (*doSomething)(MyClass*);
};

MyClass* MyClass_create();
void MyClass_destroy(MyClass* instance);

void MyClass_doSomething(MyClass* instance);

#endif // OOP_PRINCIPLES_H

#include "oop_principles.h"
#include "derived_class.h"

int main() {
    MyClass* myObject = MyClass_create();
    if (myObject)
    {
        MyClass_doSomething(myObject);
        MyClass_destroy(myObject);
    }

    MyDerivedClass* myDerivedObject = MyDerivedClass_create();
    if (myDerivedObject)
    {
        MyDerivedClass_doSomething(myDerivedObject);
        MyDerivedClass_destroy(myDerivedObject);
    }

    return 0;
}

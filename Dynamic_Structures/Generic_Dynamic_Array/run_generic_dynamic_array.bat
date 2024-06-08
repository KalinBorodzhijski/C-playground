@echo off
echo Compiling the generic dynamic array project...
gcc -o testGenericDynamicArray.exe testGenericDynamicArray.c impl\GenericDynamicArray.c impl\GenericDynamicArrayIterator.c impl\GenericDynamicArraySerialization.c impl\GenericDynamicArrayUtils.c -I.

echo Running the executable...
testGenericDynamicArray.exe

echo Cleaning up...
del testGenericDynamicArray.exe

echo Done.

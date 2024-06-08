@echo off
echo Compiling the dynamic array project...
gcc -o testDynamicArray.exe testDynamicArray.c impl\dynamicArray.c impl\dynamicArrayIterator.c impl\dynamicArraySerialization.c impl\dynamicArrayUtils.c -I.

echo Running the executable...
testDynamicArray.exe

echo Cleaning up...
del testDynamicArray.exe

echo Done.

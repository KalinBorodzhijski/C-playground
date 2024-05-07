@echo off
gcc -Wall -c main.c -o main.o
gcc -Wall -c file_operations.c -o file_operations.o
gcc -Wall -c ../String_manipulation/string_local.c -o string_local.o
gcc -Wall main.o string_local.o file_operations.o -o main.exe

if %ERRORLEVEL% neq 0 (
    echo Build failed, exiting.
    exit /b %ERRORLEVEL%
)

main.exe

del /Q main.o string_local.o file_operations.o main.exe


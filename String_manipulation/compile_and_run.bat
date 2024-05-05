@echo off
gcc -Wall -c main.c -o main.o
gcc -Wall -c string_local.c -o string_local.o
gcc -Wall main.o string_local.o -o local_string_test.exe

if %ERRORLEVEL% neq 0 (
    echo Build failed, exiting.
    exit /b %ERRORLEVEL%
)

local_string_test.exe

del /Q main.o string_local.o local_string_test.exe


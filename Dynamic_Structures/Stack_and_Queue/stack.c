/*
 * stack.c
 * 
 * Implementation file for the stack data structure in C.
 * 
 * Features:
 * - Implements operations such as push, pop, top, and isEmpty.
 * - Uses a dynamic array to manage stack elements.
 * 
 * Author: Kalin Borodzhijski
 * Date: 29.06.2024
 */

#include "stack.h"

stack* createStack(int capacity)
{
    if (capacity <= 0)
    {
        fprintf(stderr, "ERROR: stack: Invalid capacity !\n");
        return NULL;
    }

    stack* result = (stack*) malloc(sizeof(stack));
    if (result == NULL)
    {
        fprintf(stderr, "ERROR: stack: Cannot allocate memory !\n");
        return NULL;
    }

    result->data = (int*) malloc(sizeof(int) * capacity);
    if (result->data == NULL)
    {
        fprintf(stderr, "ERROR: stack: Cannot allocate memory !\n");
        return NULL;
    }

    result->capacity = capacity;
    result->size = 0;
    
}

void destroyStack(stack* stackToDestroy)
{
    if (stackToDestroy  == NULL || stackToDestroy->data == NULL)
    {
        fprintf(stderr, "ERROR: stack: Invalid stack reference !\n");
        return;
    }

    free(stackToDestroy->data);
    free(stackToDestroy);
}

void push(stack* stackP, int number)
{
    if (stackP  == NULL || stackP->data == NULL)
    {
        fprintf(stderr, "ERROR: stack: Invalid stack reference !\n");
        return;
    }

    if (stackP->capacity <= stackP->size)
    {
        stackP->data = (int*) realloc(stackP->data, sizeof(int) * stackP->capacity * DEFAULT_REALLOC_SIZE);
        fprintf(stdout, "INFO: stack: Stack is reallocated !\n");
    }

    stackP->data[stackP->size++] = number;
}

int pop(stack* stackP)
{
    if (stackP  == NULL || stackP->data == NULL)
    {
        fprintf(stderr, "ERROR: stack: Invalid stack reference !\n");
        return -1;
    }

    if (stackP->size > 0)
    {
        stackP->size--;
        return stackP->data[stackP->size];
    }
    else
    {
        fprintf(stderr, "ERROR: stack: Cannot pop stack is empty !\n");
        return -1;
    }
    
}

int top(stack* stackP)
{
    if (stackP  == NULL || stackP->data == NULL)
    {
        fprintf(stderr, "ERROR: stack: Invalid stack reference !\n");
        return -1;
    }

    if (stackP->size > 0)
    {
        return stackP->data[stackP->size-1];
    }
    else
    {
        fprintf(stderr, "ERROR: stack: Cannot top stack is empty !\n");
        return -1;
    }
}

bool isEmpty(stack* stackP)
{
    if (stackP  == NULL || stackP->data == NULL)
    {
        fprintf(stderr, "ERROR: stack: Invalid stack reference !\n");
        return true;
    }

    return (stackP->size > 0) ? false : true;
}

bool isFull(stack* stackP)
{
    if (stackP  == NULL || stackP->data == NULL)
    {
        fprintf(stderr, "ERROR: stack: Invalid stack reference !\n");
        return false;
    }

    return (stackP->size == stackP->capacity) ? true : false;
}

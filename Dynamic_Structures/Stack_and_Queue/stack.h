/*
 * stack.h
 * 
 * Header file for a stack data structure implementation in C.
 * 
 * Features:
 * - Supports operations such as push, pop, pop, and isEmpty.
 * - Uses a dynamic array to manage stack elements.
 * 
 * Author: Kalin Borodzhijski
 * Date: 29.06.2024
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DEFAULT_REALLOC_SIZE 5

typedef struct 
{
    int* data;
    int capacity;
    int size;
} stack;

stack* createStack(int capacity);
void destroyStack(stack* stackToDestroy);

void push(stack* stackP, int number);
int pop(stack* stackP);
int top(stack* stackP);
bool isEmpty(stack* stackP);
bool isFull(stack* stackP);

#endif
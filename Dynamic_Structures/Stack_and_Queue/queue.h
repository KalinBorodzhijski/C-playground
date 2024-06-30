/*
 * queue.h
 * 
 * Header file for a queue data structure implementation in C.
 * 
 * Features:
 * - Supports operations such as enqueue, dequeue, peek, and isEmpty.
 * - Uses a linked list to manage queue elements.
 * 
 * Author: Kalin Borodzhijski
 * Date: 29.06.2024
 */
#ifndef QUEUE_H_
#define QUEUE_H_


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DEFAULT_REALLOC_SIZE 5

typedef struct
{
    int* data;
    int capacity;
    int size;
} queue;


queue* createQueue(int capacity);
void destroyQueue(queue* queueToDestroy);
void enqueue(queue* queueP, int number);
int dequeue(queue* queueP);
int peek(queue* queueP);
bool queueIsEmpty(queue* queueP);
bool queuesFull(queue* queueP);

#endif /* QUEUE_H_ */
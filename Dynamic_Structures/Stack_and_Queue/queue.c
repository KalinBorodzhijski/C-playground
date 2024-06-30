/*
 * queue.c
 * 
 * Implementation file for the queue data structure in C.
 * 
 * Features:
 * - Implements operations such as enqueue, dequeue, peek, isEmpty, and isFull.
 * - Uses a dynamic array to manage queue elements.
 * 
 * Author: Kalin Borodzhijski
 * Date: 29.06.2024
 */

#include "queue.h"

queue* createQueue(int capacity)
{
    if (capacity <= 0) 
    {
        fprintf(stderr, "ERROR: queue: Invalid capacity!\n");
        return NULL;
    }

    queue* result = (queue*) malloc(sizeof(queue));
    if (result == NULL) 
    {
        fprintf(stderr, "ERROR: queue: Cannot allocate memory!\n");
        return NULL;
    }

    result->data = (int*) malloc(sizeof(int) * capacity);
    if (result->data == NULL) 
    {
        fprintf(stderr, "ERROR: queue: Cannot allocate memory!\n");
        free(result);
        return NULL;
    }

    result->capacity = capacity;
    result->size = 0;

    return result;
}

void destroyQueue(queue* queueToDestroy)
{
    if (queueToDestroy == NULL || queueToDestroy->data == NULL) 
    {
        fprintf(stderr, "ERROR: queue: Invalid queue reference!\n");
        return;
    }

    free(queueToDestroy->data);
    free(queueToDestroy);
}

void enqueue(queue* queueP, int number)
{
    if (queueP == NULL || queueP->data == NULL) 
    {
        fprintf(stderr, "ERROR: queue: Invalid queue reference!\n");
        return;
    }

    if (queueP->size >= queueP->capacity) 
    {
        queueP->data = (int*) realloc(queueP->data, sizeof(int) * queueP->capacity * DEFAULT_REALLOC_SIZE);
        fprintf(stdout, "INFO: stack: Stack is reallocated !\n");
    }

    queueP->data[queueP->size++] = number;
}

int dequeue(queue* queueP)
{
    if (queueP == NULL || queueP->data == NULL) 
    {
        fprintf(stderr, "ERROR: queue: Invalid queue reference!\n");
        return -1;
    }


    if (queueP->size > 0) 
    {
        int element = queueP->data[0];

        for (int i = 0; i < queueP->size - 1; ++i) 
        {
            queueP->data[i] = queueP->data[i + 1];
        }

        queueP->size--;

        return element;
    } else 
    {
        fprintf(stderr, "ERROR: queue: Cannot dequeue, queue is empty!\n");
        return -1;
    }
}

int peek(queue* queueP)
{
    if (queueP == NULL || queueP->data == NULL) {
        fprintf(stderr, "ERROR: queue: Invalid queue reference!\n");
        return -1;
    }

    if (queueP->size > 0) 
    {
        return queueP->data[0];
    } else 
    {
        fprintf(stderr, "ERROR: queue: Cannot peek, queue is empty!\n");
        return -1;
    }
}

bool queueIsEmpty(queue* queueP)
{
    if (queueP == NULL || queueP->data == NULL) {
        fprintf(stderr, "ERROR: queue: Invalid queue reference!\n");
        return true;
    }

    return (queueP->size == 0);
}

bool queuesFull(queue* queueP)
{
    if (queueP == NULL || queueP->data == NULL) {
        fprintf(stderr, "ERROR: queue: Invalid queue reference!\n");
        return false;
    }

    return (queueP->size == queueP->capacity);
}

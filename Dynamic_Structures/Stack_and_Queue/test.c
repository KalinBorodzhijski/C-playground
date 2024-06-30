/*
 * test.c
 * 
 * A test file to verify the functionality of the stack and queue implementations.
 * 
 * Author: Kalin Borodzhijski
 * Date: 29.06.2024
 */

#include <stdio.h>
#include "stack.h"
#include "queue.h"

void test_stack_operations();
void test_queue_operations();

int main() {

    test_stack_operations();
    test_queue_operations();

    return 0;
}


void test_stack_operations() 
{

    stack* myStack = createStack(5);

    if (myStack == NULL) 
    {
        fprintf(stderr, "Failed to create stack.\n");
        return;
    }
    printf("Stack created successfully.\n");

    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);

    printf("Top element: %d\n", top(myStack));

    printf("Popped element: %d\n", pop(myStack));

    printf("Is stack empty? %s\n", isEmpty(myStack) ? "Yes" : "No");

    printf("Is stack full? %s\n", isFull(myStack) ? "Yes" : "No");

    destroyStack(myStack);
    printf("Stack destroyed.\n");

    stack* invalidStack = createStack(-1);
    if (invalidStack == NULL) 
    {
        printf("createStack with invalid capacity test passed.\n");
    }

    myStack = createStack(2);
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    printf("Top element after pushing 30: %d\n", top(myStack));

    while (!isEmpty(myStack)) 
    {
        printf("Popped element: %d\n", pop(myStack));
    }

    printf("Popped element from empty stack: %d\n", pop(myStack));

    destroyStack(myStack);
    destroyStack(invalidStack);

    myStack = createStack(3);
    push(myStack, 10);
    push(myStack, 20);
    printf("Top element after pushing 20: %d\n", top(myStack));
    printf("Popped element: %d\n", pop(myStack));
    push(myStack, 30);
    printf("Top element after pushing 30: %d\n", top(myStack));
    printf("Popped element: %d\n", pop(myStack));
    printf("Top element after popping 30: %d\n", top(myStack));
    printf("Is stack empty? %s\n", isEmpty(myStack) ? "Yes" : "No");

    destroyStack(myStack);
}

void printQueueStatus(queue* q) 
{
    printf("Queue status:\n");
    printf("Capacity: %d\n", q->capacity);
    printf("Current size: %d\n", q->size);
    printf("Elements:");
    for (int i = 0; i < q->size; ++i) {
        printf(" %d", q->data[i]);
    }
    printf("\n\n");
}

void test_queue_operations() {

    queue* q = createQueue(5);
    if (q == NULL) 
    {
        fprintf(stderr, "Failed to create queue.\n");
        return;
    }

    printf("Queue created successfully.\n");
    printQueueStatus(q);

    printf("Enqueuing elements: 10, 20, 30\n");
    enqueue(q, 10);
    printQueueStatus(q);
    enqueue(q, 20);
    printQueueStatus(q);
    enqueue(q, 30);
    printQueueStatus(q);

    printf("Dequeuing element: %d\n", dequeue(q));
    printQueueStatus(q);

    printf("Peek front element: %d\n", peek(q));
    printQueueStatus(q);

    printf("Is queue empty? %s\n", queueIsEmpty(q) ? "Yes" : "No");
    printf("Is queue full? %s\n", queuesFull(q) ? "Yes" : "No");

    printf("Enqueuing more elements to test isFull:\n");
    enqueue(q, 40);
    enqueue(q, 50);
    enqueue(q, 60);
    printQueueStatus(q);
    printf("Is queue full now? %s\n", queuesFull(q) ? "Yes" : "No");

    printf("Dequeuing all elements:\n");
    while (!queueIsEmpty(q)) 
    {
        printf("Dequeuing element: %d\n", dequeue(q));
        printQueueStatus(q);
    }

    printf("Is queue empty now? %s\n", queueIsEmpty(q) ? "Yes" : "No");

    destroyQueue(q);
    printf("Queue destroyed.\n");
}

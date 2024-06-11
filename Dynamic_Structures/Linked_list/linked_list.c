/**
 * @file linked_list.c
 * @brief Implementation of singly linked list operations.
 *
 * This file contains the definitions of the singly linked list operations
 * declared in linked_list.h.
 */

#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

tNode* createLinkedList(int data) 
{
    tNode* newNode = (tNode*) malloc(sizeof(tNode));

    if(newNode == NULL)
    {
        fprintf(stderr, "ERROR: Memory cannot be allocated !\n");
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}
//--------------------------------------------------------------------------
void deleteList(tNode** head) 
{
    tNode* currentElement = *head;
    tNode* nextElement;

    if ((head == NULL) || (*head == NULL))
    {
        fprintf(stderr, "ERROR: Invalid inputs for delete !\n");
    }
    
    currentElement = *head;
    while (currentElement)
    {
        nextElement = currentElement->next;
        free(currentElement);
        currentElement = nextElement;
    }
    
    *head = NULL;
    
}
//--------------------------------------------------------------------------
void insertAtHead(tNode** head, int data) 
{
    tNode* newElement = NULL;
    if ((head == NULL) || (*head == NULL))
    {
        fprintf(stderr, "ERROR: Invalid inputs for insert at head !\n");
    }

    newElement = (tNode*) malloc(sizeof(tNode));    
    
    if(newElement == NULL)
    {
        fprintf(stderr, "ERROR: Memory cannot be allocated !\n");
        return;
    }

    newElement->data = data;
    newElement->next = *head;
    *head = newElement;
}
//--------------------------------------------------------------------------
void insertAtTail(tNode** head, int data) 
{
    tNode* newElement = NULL;
    tNode* currentElement = *head;
    if ((head == NULL) || (*head == NULL))
    {
        fprintf(stderr, "ERROR: Invalid inputs for insert at tail !\n");
    }    
    newElement = (tNode*) malloc(sizeof(tNode));    
    
    if(newElement == NULL)
    {
        fprintf(stderr, "ERROR: Memory cannot be allocated !\n");
        return;
    }

    while (1)
    {
        if (currentElement->next == NULL)
        {
            break;
        }

        currentElement = currentElement->next;
    }

    newElement->data = data;
    newElement->next = NULL;
    currentElement->next = newElement;
    
}
//--------------------------------------------------------------------------
void deleteNode(tNode** head, int data) 
{
    tNode* previousElement = NULL;
    tNode* currentElement = *head;

    if ((head == NULL) || (*head == NULL))
    {
        fprintf(stderr, "ERROR: Invalid inputs for delete !\n");
    }

    while (currentElement != NULL)
    {
        if (currentElement->data == data)
        {
            if (previousElement == NULL)
            {
                *head = currentElement->next;
            }
            else
            {
                previousElement->next = currentElement->next;
            }

            free(currentElement);
            break;
        }
        previousElement = currentElement;
        currentElement = currentElement->next;
    }

}
//--------------------------------------------------------------------------
void printList(tNode* head) 
{
    tNode* currentElement = head;
    if (head == NULL)
    {
        fprintf(stderr, "ERROR: Invalid inputs for print !\n");
    }

    while (currentElement != NULL)
    {
        printf("%d ", currentElement->data);
        currentElement = currentElement->next;
    }
    printf("\n");
}
//--------------------------------------------------------------------------

tNode* findNode(tNode* head, int data)
{
    tNode* currentElement = head;
    tNode* foundElement = NULL;
    
    if (head == NULL)
    {
        fprintf(stderr, "ERROR: Invalid inputs for find !\n");
    }

    while (currentElement)
    {
        if (currentElement->data == data)
        {
            foundElement = currentElement;
            break;
        }
        
        currentElement = currentElement->next;
    }

    return foundElement;
}
//--------------------------------------------------------------------------

int listLength(tNode* head) 
{
    tNode* currentElement = head;
    int size = 0;
    if (head == NULL)
    {
        fprintf(stderr, "ERROR: Invalid inputs for list !\n");
    }

    while (currentElement)
    {
        size++;
        currentElement = currentElement->next;
    }

    return size;
}
//--------------------------------------------------------------------------

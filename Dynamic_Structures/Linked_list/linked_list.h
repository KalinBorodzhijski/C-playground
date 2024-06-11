/**
 * @file linked_list.h
 * @brief Header file for singly linked list operations.
 *
 * This file declares the singly linked list data structures and functions
 * for insertion, deletion, traversal, and other utility operations on the list.
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct sNode {
    int data;
    struct sNode* next;
} tNode;

tNode* createLinkedList(int data);
void insertAtHead(tNode** head, int data);
void insertAtTail(tNode** head, int data);
void deleteNode(tNode** head, int data);
void deleteList(tNode** head);
void printList(tNode* head);
tNode* findNode(tNode* head, int data);
int listLength(tNode* head);

#endif // LINKED_LIST_H

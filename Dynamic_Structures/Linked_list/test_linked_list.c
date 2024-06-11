/**
 * @file test_linked_list.c
 * @brief Test file for singly linked list operations.
 *
 * This file tests the operations defined for the singly linked list. It uses
 * a series of operations to demonstrate insertion, deletion, and traversal.
 */

#include "linked_list.h"
#include <stdio.h>

int main() {
    tNode* head = NULL;

    head = createLinkedList(1);

    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    
    printList(head);

    insertAtTail(&head, 30);
    
    printList(head);

    deleteNode(&head, 20);
    printList(head);

    tNode* found = findNode(head, 10);
    if (found != NULL) {
        printf("Node found with data: %d\n", found->data);
    } else {
        printf("Node not found.\n");
    }

    deleteList(&head);

    return 0;
}

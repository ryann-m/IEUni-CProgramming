#include "linkedHeader.h"
#include <stdlib.h>
#include <stdio.h>

// Create an empty linked list
LinkedList *linked_list_create(void) {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (!list) return NULL;
    list->head = NULL;
    return list;
}

// Insert new node after prev_node (or at head if prev_node == NULL)
int linked_list_insert(LinkedList *list, Node *prev_node, Data data) {
    if (!list) return -1;

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return -1;

    new_node->data = data;
    Node *next = prev_node ? prev_node->next : list->head;
    new_node->next = next;

    if (prev_node)
        prev_node->next = new_node;
    else
        list->head = new_node;

    return 0;
}

// Print list (used to test traversal)
void linked_list_print(LinkedList *list) {
    if (!list) return;
    Node *current = list->head;
    while (current) {
        printf("%d -> ", current->data.value);
        current = current->next;
    }
    printf("NULL\n");
}

// Generic traversal (the actual exercise)
void linked_list_traverse(LinkedList *list, LinkedListOp op) {
    if (!list || !op) return;
    Node *current = list->head;
    while (current) {
        op(&current->data);
        current = current->next;
    }
}

// Free entire list
void linked_list_free(LinkedList **list) {
    if (!list || !*list) return;
    Node *current = (*list)->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(*list);
    *list = NULL;
}
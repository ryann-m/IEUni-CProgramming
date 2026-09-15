#pragma once
#include <stddef.h>

// ---------- Type definitions ----------
typedef struct {
    int value;
} Data;

struct Node;
typedef struct Node {
    Data data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LinkedList;

// ---------- Typedef for operation ----------
typedef void (*LinkedListOp)(Data *);

// ---------- Function prototypes ----------
LinkedList *linked_list_create(void);
int linked_list_insert(LinkedList *list, Node *prev_node, Data data);
void linked_list_print(LinkedList *list);
void linked_list_traverse(LinkedList *list, LinkedListOp op);
void linked_list_free(LinkedList **list);

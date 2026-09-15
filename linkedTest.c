#include "linkedHeader.h"
#include "utest.h"
#include <stdio.h>

static void print_value(Data *data) {
    printf("%d -> ", data->value);
}

UTEST(LinkedList, TraversePrint) {
    LinkedList *list = linked_list_create();

    Data d1 = {1}, d2 = {2}, d3 = {3};
    linked_list_insert(list, NULL, d1);
    linked_list_insert(list, list->head, d2);
    linked_list_insert(list, list->head, d3);
    // list is 1 -> 3 -> 2

    printf("Expected output: 1 -> 3 -> 2 -> NULL\n");
    linked_list_traverse(list, print_value);
    printf("NULL\n");

    linked_list_free(&list);
    ASSERT_TRUE(list == NULL);
}

UTEST(LinkedList, HandlesNull) {
    linked_list_traverse(NULL, print_value);
    linked_list_traverse(NULL, NULL);
}

UTEST_MAIN();

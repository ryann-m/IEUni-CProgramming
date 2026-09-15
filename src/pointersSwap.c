/*
Description: This program uses pointers to swap the value of 2 int variables
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    if (!a || !b) return;
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("a: %d, b: %d\n", *a, *b);  // add newline
}

int main() {
    int x, y;

    printf("Choose two numbers to swap:\n");

    printf("a: ");
    scanf("%d", &x);

    printf("b: ");
    scanf("%d", &y);

    swap(&x, &y);
    return 0;
}
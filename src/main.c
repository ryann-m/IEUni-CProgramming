#include <stdio.h>
#include "name_length.h"

int main() {
    printf("This is just a prototype, calling name_length with a test name:\n");
    int len = name_length("Raul");
    printf("The length of the name is: %d\n", len);
    return 0;
}

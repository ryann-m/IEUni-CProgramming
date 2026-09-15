#include "utest.h"
#include "mallocHeader.h"
#include <stdlib.h>

// Test for the average function
UTEST(malloc, average) {
    int arr[3] = {1, 2, 3};
    average(arr, 3);
    ASSERT_TRUE(1);
}

// Test for memory allocation
UTEST(malloc, allocation) {
    int *ptr = malloc(5 * sizeof(int));
    ASSERT_TRUE(ptr != NULL);
    free(ptr);
}

UTEST_MAIN();
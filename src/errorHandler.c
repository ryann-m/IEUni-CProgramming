/*
Description: This program handles errors of division code, I utilized errno and assertions here

Date: 9.23.2025

Author: Ryann K Mack
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int vectorized_divide(int *a, int *b, int *result, int size) {
    // Error Checking
    assert(a != NULL);
    assert(b != NULL);
    assert(result != NULL);
    assert(size > 0);

    // Vectorized Divide Function (CODE)
    for (int i = 0; i < size; i++)
    {
        // Error Checking
        if(b[i] == 0) {
            fprintf(stderr, "Error: Division by zero at index %d\n", i);
            errno = EDOM; // Set domain error
            return -1;
        }

        // Vectorized Divide Function (CODE)
        result[i] = a[i] / b[i];
    }
}
int main() {
    // Main (CODE)
    int numbers[5] = {1, 2, 3, 4, 20};
    int divisors[5] = {0, 1, 2, 3, 4};
    int results[5] = {0};

    // Error Checking
    if (vectorized_divide(numbers, divisors, results, 5) != 0) {
        perror("Vectorized divide failed");
        return EXIT_FAILURE;
    }

    // Main (CODE)
    print_array(results, sizeof(results) / sizeof(results[0]));
    return EXIT_SUCCESS;
}

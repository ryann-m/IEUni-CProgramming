#include "concurrencyHeader.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 1000000;
    float* random_list = generate_random_list(size);

    double avg = average_multi_thread(random_list, size, 4);
    printf("Average of %d random floats: %.6f\n", size, avg);

    free(random_list);
    return 0;
}

#include "concurrencyHeader.h"
#include <stdlib.h>

// Generates an array of random floats between 0 and 1
float* generate_random_list(int size) {
    float* list = malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        list[i] = (float) rand() / RAND_MAX;
    }
    return list;
}

//  Helper struct for thread arguments 
typedef struct {
    float* list;
    int start;
    int end;
    double partial_sum;
} ThreadArgs;

// Function executed by each thread
static void* thread_average(void* arg) {
    ThreadArgs* args = (ThreadArgs*) arg;
    double sum = 0.0;
    for (int i = args->start; i < args->end; i++) {
        sum += args->list[i];
    }
    args->partial_sum = sum;
    return NULL;
}

//  Single-threaded version 
double average_single_thread(float* list, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += list[i];
    }
    return sum / size;
}

//  Multi-threaded version 
double average_multi_thread(float* list, int size, int num_threads) {
    if (num_threads <= 0) return 0.0;

    pthread_t threads[num_threads];
    ThreadArgs args[num_threads];

    int chunk_size = size / num_threads;
    int remainder = size % num_threads;

    int start = 0;
    for (int i = 0; i < num_threads; i++) {
        int end = start + chunk_size;
        if (i < remainder) end++; // distribute leftovers evenly
        args[i] = (ThreadArgs){ .list = list, .start = start, .end = end, .partial_sum = 0.0 };
        pthread_create(&threads[i], NULL, thread_average, &args[i]);
        start = end;
    }

    double total_sum = 0.0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += args[i].partial_sum;
    }

    return total_sum / size;
}
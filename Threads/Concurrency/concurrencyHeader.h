#pragma once
#include <pthread.h>

//  Function declarations 
float* generate_random_list(int size);
double average_single_thread(float* list, int size);
double average_multi_thread(float* list, int size, int num_threads);

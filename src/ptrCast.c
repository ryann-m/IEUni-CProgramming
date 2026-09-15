/*
Description: This program demonstrates type casting and pointer casting in C.
It converts an integer to a float and reinterprets an integer's bit pattern as a float

Date: 9.29.2025

Author: Ryann Mack
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 2;                  
    float b = (float)a;         
    float *pFloat = (float*)&a; 

    printf("The value of a as int is: %d\n", a);
    printf("The value of b as float is: %f\n", b);
    printf("The value of a reinterpreted as float is: %f\n", *pFloat);

    return 0;
}
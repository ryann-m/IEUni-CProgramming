/*
Description: This program demonstrates pointer casting in C.

Date: 9.29.2025

Author: Ryann Mack
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  int x = 0;
  double *d_ptr = (double*)&x;                 // Cast int* to float*
  printf("Value of x as double: %g\n", *d_ptr); // Dereference as double
  return 0;
}

/*Questions:

  The program prints an unexpected value because the bit pattern of an integer does not match the representation of a float or double. 
  Casting an int* to a float* (or double*) does not convert the value, it only reinterprets the memory, leading to undefined results.
*/

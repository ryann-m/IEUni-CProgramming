#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mallocLibrary.c"

int main() {
    printf("--------------------------------- Welcome to the number average and sum program! ---------------------------------\n");
    printf("------------------- Please type a number and press enter to store it into your number database. ------------------\n");
    printf("---------------------- If you would like to exit the program, please type a negative number. ---------------------\n");

    mallocIntegers(); // Stores an array dictated by user, and prints it
    return 0;
}
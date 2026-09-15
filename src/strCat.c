/*
Description: This program concatenates two strings in C.

Date: 9.29.2025

Author: Ryann Mack
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* str1 = "Hello, ";
    char* str2 = "World!";

    char strCat[50];
    
    strcpy(strCat, str1); 
    strcat(strCat, str2); 
    printf("Concatenated string: %s\n", strCat);
    return 0;
}
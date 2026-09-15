/*
Description:
    This library contains functions for the 'malloc fun' program

    'mallocInterger': Dynamically allocates memory for an array of integers based on user input
        - Takes users numbers until they type a negative numer
        - Then calls 'average' to calculate the average of the user's array, and returns the sum and average of the array
    
    'average': Takes an array of integers, calculates the sum and average of the array, and returns both values

Date: 09.30.2025

Author: Ryann Mack
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mallocHeader.h"

void average(int *arr, int length) {   
    // Error Checking
    assert(arr != NULL);                                                                      // Array is not NULL
    assert(length > 0);                                                                       // Prevent division by 0                     
    
    int sum = 0;


    for (int i = 0; i < length; i++) {
        sum += arr[i];
    }

    double average = (double)sum / length;
    printf("\nThe sum of your numbers is: %d\n", sum);
    printf("The average of your numbers is: %.2f\n", average);
    return;
}


void mallocIntegers() {           
    int capacity = MIN_MEMORY;                                                                  // Current capacity of the dynamic array
    int *arr = malloc(MIN_MEMORY * sizeof(int));                                                // Dynamic array that stores the user's array of integers
    int userInput;
    int userSize = 0;;

    // Error Checking - Checks if malloc was successful
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    while(userInput >= 0) {
        printf("Please enter a number: ");
        if(scanf(" %d", &userInput) != 1) {                                                      // Error Checking - Checks if user input is a number
            printf("Invalid input. Please enter an integer.\n");
            while(getchar() != '\n');                                                           // Clear the input buffer
            continue;
        }

        if (userInput < 0) break;

        arr[userSize] = userInput;
        userSize++;

        // Reallocates memory for a full array, and copies values into the bigger new array
        if (userSize >= capacity) {                                                            
            capacity *= 2;                                                                     // Change capacity to match the size of the new array   
            int *temp = realloc(arr, capacity * sizeof(int));                                  // Temp is the new big array, we then set the array equal to the temp (line 70), sucessfully expanding the array to fit the users needs
            
            // Error Checking - See if realloc was successful
            if (temp == NULL) {                                                                // Error Checking - Checks if realloc was successful
                printf("Memory reallocation failed\n");
                free(arr);
                return;
            }
            arr = temp;
        }
    }                                                                                          // If user input is negative, loop ends
        
    // User has types a negative number, now we print everything
    printf("You have exited the program.\nPrinting the numbers in your database...\n");
    for (int i = 0; i < userSize; i++) {                                                   
        printf("'%d' ", arr[i]);
    }

    average(arr, userSize);                                                                
    return;
}
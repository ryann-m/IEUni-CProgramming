#include <stdio.h>
#include <stdlib.h>
#include "myRectangle.h"

int main(void) {
    /* initialize so area() and grow() checks are safe before user creates a rectangle */
    Rectangle a = {0, 0};

    int choice;
    printf("Choose an option:\n1. Create Rectangle\n");
    printf("2. Edit rectangle\n");
    printf("3. Calculate Area of your Rectangle\n");
    printf("4. Grow your Rectangle\n");
    printf("5. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch(choice){
        case 1:
            printf("You chose: Create Rectangle\n");
            printf("Enter length: ");
            scanf(" %d", &a.length);
            printf("Enter width: ");
            scanf(" %d", &a.width);
            break;
        case 2:
            printf("You chose: Edit Rectangle\n");
            printf("Enter new length: ");
            scanf(" %d", &a.length);
            printf("Enter new width: ");
            scanf(" %d", &a.width);
            break;
        case 3:
            printf("You chose: Calculate Area of your Rectangle\n");
            if (a.length == 0 || a.width == 0) {
                printf("Rectangle not defined. Please create a rectangle first.\n");
                break;
            }
            printf("Area: %d\n", area(a));
            break;
        case 4:
            int dw, dl;
            printf("You chose: Grow your Rectangle\n");
            if (a.length == 0 || a.width == 0) {
                printf("Rectangle not defined. Please create a rectangle first.\n");
                break;
            }
            printf("Enter change in width: ");
            scanf(" %d", &dw);
            printf("Enter change in length: ");
            scanf(" %d", &dl);
            grow(&a, dw, dl);
            printf("New dimensions - Length: %d, Width: %d\n", a.length, a.width);
            break;
        case 5:
            printf("Exiting program.\n");
            exit(0);
            break;
        default: {
            int invalidCount = 0;
            invalidCounter(&invalidCount);
            break;
        }
            
    }
}
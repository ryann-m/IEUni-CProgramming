/*
Description: This program utilizes Unit Testing for testing a name program, where the user inputs their name, and the length is returned

Date: 9.23.2025

Author: Ryann K Mack
*/

#include "name_length.h"

int name_length(const char* name) {
    int len = 0;

    for(int i = 0; name[i] != '\0'; i++){
        if (name[i] != ' ') {
            len++;
        }
    }
    return len;
}

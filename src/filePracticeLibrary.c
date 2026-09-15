/*
Description:
    This file contains the Library of file practice main

    readBook
        - Reads the contents of the given file into a continuous array.
        - Any non-alphabetic characters are replaced with spaces.
        FileName
            - Name of the file to read
        Contents
            - Pointer that will be allocated by the function and contains the books contents
Date: 10.1.2025

Author: Ryann Mack
*/
/*
File Practice Library – Zipf’s Law assignment
Implements:
  - readBook: reads text and replaces non-letters with spaces
  - toLowerCase: converts string to lowercase
  - countWords: counts unique words and frequencies
  - writeFrequencies: outputs "rank freq word"
  - printHapax: prints words occurring once
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "filePracticeHeader.h"

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

void readBook(const char* fileName, char** contents) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", fileName);
        *contents = NULL;
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    *contents = malloc(fileSize + 1);
    if (*contents == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    int c;
    long i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (!isalpha(c)) c = ' ';
        (*contents)[i++] = (char)c;
    }
    (*contents)[i] = '\0';
    fclose(file);
}

/* helper for qsort */
int cmpWords(const void* a, const void* b) {
    const char* w1 = *(const char**)a;
    const char* w2 = *(const char**)b;
    return strcmp(w1, w2);
}

/* Count unique words and their frequencies */
void countWords(const char* book, char*** words, int** frequencies, int* nWords) {
    char* copy = strdup(book);
    if (!copy) return;

    char* token = strtok(copy, " ");
    int capacity = 10000;
    int count = 0;

    char** wordList = malloc(capacity * sizeof(char*));
    while (token != NULL) {
        if (strlen(token) > 0) {
            if (count >= capacity) {
                capacity *= 2;
                wordList = realloc(wordList, capacity * sizeof(char*));
            }
            wordList[count++] = strdup(token);
        }
        token = strtok(NULL, " ");
    }

    qsort(wordList, count, sizeof(char*), cmpWords);

    *words = malloc(count * sizeof(char*));
    *frequencies = malloc(count * sizeof(int));
    int uniqueCount = 0;

    for (int i = 0; i < count; ) {
        int freq = 1;
        int j = i + 1;
        while (j < count && strcmp(wordList[i], wordList[j]) == 0) {
            freq++;
            j++;
        }
        (*words)[uniqueCount] = strdup(wordList[i]);
        (*frequencies)[uniqueCount] = freq;
        uniqueCount++;
        i = j;
    }

    *nWords = uniqueCount;

    for (int i = 0; i < count; i++) free(wordList[i]);
    free(wordList);
    free(copy);
}

/* Output rank, frequency, word */
void writeFrequencies(const char* filename, char** words, int* frequencies, int nWords) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error creating output file: %s\n", filename);
        return;
    }

    for (int i = 0; i < nWords; i++) {
        fprintf(file, "%d %d %s\n", i + 1, frequencies[i], words[i]);
    }

    fclose(file);
}

/* Print Hapax Legomena (words occurring once) */
void printHapax(char** words, int* frequencies, int nWords) {
    int hapaxCount = 0;
    printf("\nHápax legómena (occur only once):\n");
    for (int i = 0; i < nWords; i++) {
        if (frequencies[i] == 1) {
            hapaxCount++;
            if (hapaxCount <= 10) {
                printf("%s ", words[i]);
            }
        }
    }
    printf("\nTotal hapax words: %d\n", hapaxCount);
}
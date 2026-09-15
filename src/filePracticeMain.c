#include <stdio.h>
#include <stdlib.h>
#include "filePracticeHeader.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    char* book = NULL;
    readBook(argv[1], &book);
    if (book == NULL) return 1;

    toLowerCase(book);

    printf("Preview of processed text:\n\n");
    for (int i = 0; i < 400 && book[i] != '\0'; i++) {
        putchar(book[i]);
    }
    printf("\n\n");


    char** words = NULL;
    int* frequencies = NULL;
    int nWords = 0;
    countWords(book, &words, &frequencies, &nWords);

    writeFrequencies(argv[2], words, frequencies, nWords);
    printHapax(words, frequencies, nWords);

    for (int i = 0; i < nWords; i++) free(words[i]);
    free(words);
    free(frequencies);
    free(book);

    return 0;
}
#ifndef FILEPRACTICEHEADER_H
#define FILEPRACTICEHEADER_H

void readBook(const char* fileName, char** contents);
void toLowerCase(char* str);
void countWords(const char* book, char*** words, int** frequencies, int* nWords);
void writeFrequencies(const char* filename, char** words, int* frequencies, int nWords);
void printHapax(char** words, int* frequencies, int nWords);

#endif

/*
Author: Ryann Mack

Date: 10.21.2025

Description:
        Implements two loggers (console and file) and a performTask() routine.
*/

#include "loggerHeader.h"
#include <stdio.h>
#include <stdlib.h>

// Convert enum to text label for display
static const char *getLevelName(LogLevel level) {
    switch (level) {
        case DEBUG:   return "DEBUG";
        case INFO:    return "INFO";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
        default:      return "UNKNOWN";
    }
}

// Console logger
void consoleLogger(const char *message, LogLevel level) {
    printf("[%s] %s\n", getLevelName(level), message);
}

// File logger (append mode)
void fileLogger(const char *message, LogLevel level) {
    FILE *fp = fopen("log.txt", "a");
    if (!fp) {
        fprintf(stderr, "[ERROR] Could not open log file.\n");
        return;
    }
    fprintf(fp, "[%s] %s\n", getLevelName(level), message);
    fclose(fp);
}

// Component function using provided logger
void performTask(Logger logger) {
    logger("Task started", INFO);
    logger("Working...", DEBUG);
    logger("Task completed", INFO);
}

// Demo program
int main(void) {
    printf("Using console logger:\n");
    performTask(consoleLogger);

    printf("\nUsing file logger:\n");
    performTask(fileLogger);

    return 0;
}
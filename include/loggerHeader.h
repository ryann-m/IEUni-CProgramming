#ifndef LOGGER_HEADER_H
#define LOGGER_HEADER_H

typedef enum {
    DEBUG,
    INFO,
    WARNING,
    ERROR
} LogLevel;

typedef void (*Logger)(const char *message, LogLevel level);

void performTask(Logger logger);
void consoleLogger(const char *message, LogLevel level);
void fileLogger(const char *message, LogLevel level);

#endif
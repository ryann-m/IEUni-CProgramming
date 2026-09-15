#ifndef ERROR_HEADER_H
#define ERROR_HEADER_H

typedef enum {
    MACCES,   // Permission denied
    MNOMEM,   // Out of memory
    MINVAL    // Invalid argument
} ErrorCode;

const char *getErrorMessage(ErrorCode code);

#endif

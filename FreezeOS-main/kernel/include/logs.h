#ifndef LOGS_H
#define LOGS_H

#include <stdint.h>
#include "fs.h"

typedef struct
{
    const char* file;
    const char* function;
    const char* message;
} __attribute__((packed)) log_t;

void log_init();

void ERROR(char* message);
// void WARN(char* file, char* function, char* message);
// void INFO(char* file, char* function, char* message);

#endif
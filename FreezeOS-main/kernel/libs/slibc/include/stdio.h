#include <stddef.h>

#ifndef _STDIO_H
#define _STDIO_H

#define MAX_BUFFER_SIZE 1024

void init_dynamic_mem();
void* malloc(size_t size);
void free(void* ptr);
void memset(char* ptr, char c, int count);

void puts(const char* str);
void putns(const char* str, size_t n);
void puti(int n);
void d(char* title, char* data);

void printf(const char* format, ...);
void sprintf(char* buffer, const char* format, ...);

#endif

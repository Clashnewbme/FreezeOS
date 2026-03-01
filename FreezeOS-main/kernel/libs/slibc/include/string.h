#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

// Define va_list and va_* macros
typedef char* va_list;

#define va_start(ap, last) (ap = (va_list)&last + sizeof(last))
#define va_args(ap, type) (*(type*)((ap += sizeof(type)) - sizeof(type)))
#define va_end(ap) (ap = (va_list)0);

// Standard funcitons
int strlen(const char* s);
int count_digits(int n);
void strrev(char* str);
void itoa(int num, char* str, int base);
int strcmp(const char* a, const char* b);
int strncmp(const char* a, const char* b, size_t n);
void pop(char* str);
void push(char* str, char c);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, int n);
char* strcat(char* dest, const char* src);
char* strchr(const char* str, int c);
char* strpbrk(const char* str, const char* accept);
size_t strspn(const char* str, const char* accept);
char* strtok(char* str, const char* delim);
void strsplit(char* str, char** pointers, char* delim);
void strnsplit(char* str, char** pointers, char* delim, int max);
void to_uppercase(char* str);
void to_lowercase(char* str);
void strpad(char* str, int max, char c);
char* substr(const char* src, int start, int length);
char* strstr(const char* str, const char* substr);

#endif
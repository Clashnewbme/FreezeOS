#include <disk.h>
#include <fs.h>
#include <logs.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void log_init()
{
    fz_create_file("errors.txt");
    fz_create_file("warnings.txt");
    fz_create_file("info.txt");
}

void save_log(DirEntry_t file, char* message)
{
    // Save the buffer to the log file puts(buffer);
    fz_fappend(file, message);
}

// void WARN(char* file, char* function, char* message)
// {
//     log_t log = {.file = file, .function = function, .message = message};
//     DirEntry_t log_file = find_file("warnings.txt");
//     save_log(log_file, log);
// }

void ERROR(char* message)
{
    DirEntry_t log_file = find_file("errors.txt");
    save_log(log_file, message);
}

// void INFO(char* file, char* function, char* message)
// {
//     log_t log = {.file = file, .function = function, .message = message};
//     DirEntry_t log_file = find_file("info.txt");
//     save_log(log_file, log);
// }
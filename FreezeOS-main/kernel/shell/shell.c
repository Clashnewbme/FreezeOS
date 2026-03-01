#include <console.h>
#include <fs.h>
#include <graphics.h>
#include <keyboard.h>
#include <memory.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>

static char shell_buffer[256];

void shell_init()
{
    // Clear the screen and print welcome
    keyboard_bind(&shell);
    clear_screen();
    display_header();
    puts("> ");
}

void shell(char c)
{
    if (c == '\b')
    {
        // If shell buffer is already empty then return;
        if (strlen(shell_buffer) == 0)
            return;

        pop(shell_buffer);
        cursor_back(1);
        putchar(' ');
        cursor_back(1);
    }
    else if (c == '\n')
    {
        put_nl();
        execute_command(shell_buffer);
        puts("> ");
    }
    else
    {
        push(shell_buffer, c);
        putchar(c);
    }
}

void execute_command(char* buffer)
{
    char len = strlen(buffer);
    char* command = strtok(buffer, " ");
    char* data = strtok(NULL, ">");
    char* filename = strtok(NULL, "");

    if (strcmp("help", command) == 0)
    {
        command_help();
    }
    else if (strcmp("clear", command) == 0)
    {
        clear_screen();
        display_header();
    }
    else if (strcmp("ls", command) == 0)
    {
        command_ls();
    }
    else if (strcmp("touch", command) == 0)
    {
        command_touch(data);
    }
    else if (strcmp("echo", command) == 0)
    {
        command_echo(data);
    }
    else if (strcmp("cat", command) == 0)
    {
        command_cat(data);
    }
    else if (strcmp("sizeof", command) == 0)
    {
        command_sizeof(data);
    }
    else if (len == 0)
    {
        command_empty();
    }
    else
    {
        // puts(command);
        command_unknown(command);
    }

    // Append data on file
    if (filename != NULL)
    {
        // putns(file.name, 8);
        if (*filename == '>')
        {
            filename += 2;
            DirEntry_t file = find_file(filename);
            fz_fappend(file, data);
        }
        else
        {
            ++filename;
            DirEntry_t file = find_file(filename);
            fz_fwrite(file, data);
        }
    }

    // Clear the mem
    memset(shell_buffer, 0, len);
}
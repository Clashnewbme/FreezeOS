#include <console.h>
#include <stdio.h>

void display_header()
{
    set_cursor(0, 0);
    hr();
    puts("Welcome to FreezeOS made by Shohag Ahmed.");
    hr();
    save_cursor();
    set_cursor(1, 59);
    printf("| Time : 00:00:00 ");
    reset_cursor_on_saved();
}
#ifndef CONSOLE_H
#define CONSOLE_H

void update_cursor();
void clear_screen();
void putchar(char c);
void put_nl();
void cursor_back(int count);
void hr();
int save_cursor();
void reset_cursor_on_saved();
void set_cursor(int c_row, int c_col);

#endif
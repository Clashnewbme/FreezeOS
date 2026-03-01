#ifndef SHELL_H
#define SHELL_H

void execute_command(char* buffer);
// void execute_command(char* buffer);
void command_help();
void command_ls();
void command_unknown(char* buffer);
void shell(char c);
void shell_init();
void command_touch(char* buffer);
void command_echo(char* buffer);
void command_cat(char* buffer);
void command_empty();
void command_sizeof(char* buffer);

#endif
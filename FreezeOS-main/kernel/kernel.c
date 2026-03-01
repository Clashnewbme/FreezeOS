#include <console.h>
#include <disk.h>
#include <fs.h>
#include <idt.h>
#include <keyboard.h>
#include <logs.h>
#include <memory.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <timer.h>

/**
 * @brief this kernel function is the heart of FreezeOS
 *
 */
void kernel()
{
    // Initilize memory and file system
    init_dynamic_mem();
    load_root_entries();
    load_fat();

    // Initialize shell
    shell_init();

    log_init();

    // Initialize interrupts
    idt_init();
    mask_all_irqs();
    timer_init();
    keyboard_init();
    asm volatile("sti");

    // char* t = malloc(1024);
    // sprintf(t, "File : %s, Function : %s, Message : %s", "Kernel.c", "MAIN", "FAILD to read
    // file"); puts(t);

    DirEntry_t file = find_file("errors.txt");
    // putns((char*)file.name, 8);
    // puti(file.size);
    fz_fappend(file, "Bangladesh!");

    // char* a = ">.>Hwllo world .>> go to bed";
    // char* b = ">.>";

    // a += strspn(a, b);

    // puts(a);

    // char* a = "Hello shohag.txt";
    // char* b = strtok(a, " ");
    // puts(a);
    // puts(strtok(NULL, "."));
    // puts(strtok(NULL, " "));

    // ERROR("Reading from file is failed");
    // WARN("kernel.c", "kernel_main", "Reading from file is failed");
    // INFO("kernel.c", "kernel_main", "Reading from file is failed");

    // execute_command("echo gooogle");
    // execute_command("echo gooogle > errors.txt");
    // printf("Hi this is %s. I'm %d years old", "Shohag Ahmed", 20);
}
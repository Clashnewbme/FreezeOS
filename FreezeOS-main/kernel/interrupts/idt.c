#include <idt.h>
#include <io.h>
#include <stddef.h>
#include <stdint.h>

// Constants
#define CODE_SEG 0x08
#define IDT_SIZE 256

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

idt_gate_t idt[IDT_SIZE];
idt_register_t idt_r;

// External funcitons
extern void isr1_handler();
extern void irq1_handler();

void mask_all_irqs()
{
    // Mask all IRQs on the master PIC
    outb(PIC1_DATA, 0xFF);
    // Mask all IRQs on the slave PIC
    outb(PIC2_DATA, 0xFF);
}

// Function to unmask IRQ line
void unmask_irq(uint8_t irq_line)
{
    uint8_t port;
    uint8_t value;

    if (irq_line < 8)
    {
        port = 0x21;  // Master PIC
    }
    else
    {
        port = 0xA1;  // Slave PIC
        irq_line -= 8;
    }

    value = inb(port) & ~(1 << irq_line);
    outb(port, value);
}

// Laod IDT
void load_idt()
{
    idt_r.base = (uint32_t)&idt;
    idt_r.limit = IDT_SIZE * sizeof(idt_gate_t) - 1;
    asm volatile("lidt (%0)" : : "r"(&idt_r));
}

// Set IDT gate
void set_idt_gate(int n, uint32_t handler)
{
    idt[n].low_offset = low_16(handler);
    idt[n].selector = CODE_SEG;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = high_16(handler);
}

// Remaping the pic
void pic_remap()
{
    // ICW1
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    // ICW2
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    // ICW3
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // ICW4
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // OCW1
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void set_idt_gates()
{
    set_idt_gate(32, (uint32_t)isr1_handler);
    set_idt_gate(33, (uint32_t)irq1_handler);
}

void idt_init()
{
    // Call pic remap
    pic_remap();

    // Call set idt gates
    set_idt_gates();

    // Call load idt
    load_idt();
}
#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct
{
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

#define low_16(address) (uint16_t)((address)&0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

void mask_all_irqs();
void unmask_irq(uint8_t irq_line);
void idt_init();

#endif

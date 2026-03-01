#ifndef IO_H
#define IO_H

#include <stdint.h>

// Recive a byte to an I/O port
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)  // Return value will be store in ret variable
                 : "Nd"(port));

    return ret;
}

// Send a byte to an I/O port
static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1"
                 :  // No output
                 : "a"(val), "Nd"(port));
}

// Recive a byte to an I/O port
static inline uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile("inw %1, %0"
                 : "=a"(ret)  // Return value will be store in ret variable
                 : "Nd"(port));

    return ret;
}

// Send a byte to an I/O port
static inline void outw(uint16_t port, uint16_t val)
{
    asm volatile("outw %0, %1"
                 :  // No output
                 : "a"(val), "Nd"(port));
}

#endif
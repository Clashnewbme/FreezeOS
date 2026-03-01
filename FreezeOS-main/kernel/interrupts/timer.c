#include <console.h>
#include <idt.h>
#include <io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <timer.h>

#define TIMER_IRQ 0
#define TICK_PER_SECOND 1

// RTC I/O ports
#define RTC_REGISTER_PORT 0x70
#define RTC_DATA_PORT 0x71

// RTC Register Addresses
#define RTC_SECONDS_REG 0x00
#define RTC_MINUTES_REG 0x02
#define RTC_HOURS_REG 0x04

#define PIT_CONTROL_PORT 0x43
#define PIT_CHANNEL0_PORT 0x40

#define PIT_ACCESS_MODE 0x30
#define PIT_MODE_2 0x40

// Global time variables
uint32_t seconds = 0;
uint32_t minutes = 0;
uint32_t hours = 0;

// Function to set PIT frequency
void set_pit_frequency(uint32_t frequency)
{
    uint16_t divisor = 1193180 / frequency;

    outb(PIT_CONTROL_PORT, PIT_ACCESS_MODE | PIT_MODE_2);
    outb(PIT_CHANNEL0_PORT, divisor & 0xFF);         // Send LSB
    outb(PIT_CHANNEL0_PORT, (divisor >> 8) & 0xFF);  // Send MSB
}

void timer_init()
{
    set_pit_frequency(TICK_PER_SECOND);
    unmask_irq(TIMER_IRQ);
}

void timer_handler()
{
    // Increment time counter every tick
    static uint32_t tick_count = 0;
    tick_count++;

    if (tick_count >= TICK_PER_SECOND)
    {
        read_rtc(&hours, &minutes, &seconds);
        update_display_time();
    }
}

void update_display_time()
{
    save_cursor();
    set_cursor(1, 68);

    bool is_PM = false;

    if (hours > 12)
    {
        hours -= 12;
        is_PM = true;
    }

    if (hours < 10)
        putchar('0');

    puti(hours);
    putchar(':');
    if (minutes < 10)
        putchar('0');

    puti(minutes);
    putchar(':');
    if (seconds < 10)
        putchar('0');

    puti(seconds);

    // Print day or night
    (is_PM) ? puts(" PM") : puts(" AM");

    reset_cursor_on_saved();
}

// Function to read from RTC register
uint8_t read_rtc_register(uint8_t reg)
{
    outb(RTC_REGISTER_PORT, reg);  // Select the register
    return inb(RTC_DATA_PORT);     // Read the data
}

uint8_t bcd_to_dec(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void read_rtc(uint32_t* hours, uint32_t* minutes, uint32_t* seconds)
{
    *seconds = bcd_to_dec(read_rtc_register(RTC_SECONDS_REG));
    *minutes = bcd_to_dec(read_rtc_register(RTC_MINUTES_REG));
    *hours = read_rtc_register(RTC_HOURS_REG);
}

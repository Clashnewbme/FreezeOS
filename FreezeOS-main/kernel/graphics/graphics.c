#include <graphics.h>
#include <io.h>
#include <stdint.h>

#define VGA_CTRL_PORT 0x03D4  // VGA Graphics Controller Index Register
#define VGA_DATA_PORT 0x03D5  // VGA Graphics Controller Data Register

#define VGA_MODE_13H 0x13

// Function to set VGA graphics mode 0x13
void set_vga_mode()
{
    // 1. Set the VGA CRTC registers
    // Register 0x00 to 0x07 are critical for mode 0x13
    outb(VGA_CTRL_PORT, 0x00);  // Set CRTC register index to 0x00
    outb(VGA_DATA_PORT, 0x5F);  // 1st parameter: Horizontal Display End

    outb(VGA_CTRL_PORT, 0x01);  // Set CRTC register index to 0x01
    outb(VGA_DATA_PORT, 0x4F);  // 2nd parameter: Horizontal Display End

    outb(VGA_CTRL_PORT, 0x02);  // Set CRTC register index to 0x02
    outb(VGA_DATA_PORT, 0x00);  // 3rd parameter: Start Address High

    outb(VGA_CTRL_PORT, 0x03);  // Set CRTC register index to 0x03
    outb(VGA_DATA_PORT, 0x00);  // 4th parameter: Start Address Low

    outb(VGA_CTRL_PORT, 0x04);  // Set CRTC register index to 0x04
    outb(VGA_DATA_PORT, 0x0F);  // 5th parameter: Vertical Display End

    outb(VGA_CTRL_PORT, 0x05);  // Set CRTC register index to 0x05
    outb(VGA_DATA_PORT, 0x00);  // 6th parameter: Vertical Display End

    outb(VGA_CTRL_PORT, 0x06);  // Set CRTC register index to 0x06
    outb(VGA_DATA_PORT, 0x00);  // 7th parameter: Cursor Start

    outb(VGA_CTRL_PORT, 0x07);  // Set CRTC register index to 0x07
    outb(VGA_DATA_PORT, 0x00);  // 8th parameter: Cursor End

    // 2. Set the VGA Sequencer registers
    // Register 0x00 to 0x03 are critical for mode 0x13
    outb(0x03C4, 0x00);  // Set Sequencer index to 0x00
    outb(0x03C5, 0x01);  // 1st parameter: Clocking Mode

    outb(0x03C4, 0x01);  // Set Sequencer index to 0x01
    outb(0x03C5, 0x00);  // 2nd parameter: Map Mask

    outb(0x03C4, 0x02);  // Set Sequencer index to 0x02
    outb(0x03C5, 0x00);  // 3rd parameter: Character Map Select

    outb(0x03C4, 0x03);  // Set Sequencer index to 0x03
    outb(0x03C5, 0x00);  // 4th parameter: Memory Mode

    outb(0x03C4, 0x04);  // Set Sequencer index to 0x04
    outb(0x03C5, 0x00);  // 5th parameter: Memory Mode

    // 3. Set the VGA Attribute Controller registers
    // 0x00 to 0x1F are critical for mode 0x13
    outb(0x03C0, 0x00);  // Set Attribute Controller index to 0x00
    outb(0x03C1, 0x01);  // 1st parameter: Mode Control

    outb(0x03C0, 0x01);  // Set Attribute Controller index to 0x01
    outb(0x03C1, 0x00);  // 2nd parameter: Overscan Color

    // Additional configuration for VGA attributes and registers might be needed
}
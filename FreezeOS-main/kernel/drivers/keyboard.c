#include <console.h>
#include <idt.h>
#include <io.h>
#include <keyboard.h>
#include <shell.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_IRQ 1

#define KEY_SHIFT 0x2A
#define KEY_CAPS_LOCK 0x3A

static keyboardCallback g_callback = 0;

static bool shiftPressed = false;
static bool capsLockOn = false;

// Lookup table for scancodes to ASCII characters
static char normal_key_map[128] = {
    0,    27,  '1', '2', '3',  '4', '5', '6', '7',  '8', /* 9 */
    '9',  '0', '-', '=', '\b',                           /* Backspace */
    '\t',                                                /* Tab */
    'q',  'w', 'e', 'r',                                 /* 19 */
    't',  'y', 'u', 'i', 'o',  'p', '[', ']', '\n',      /* Enter key */
    0,                                                   /* 29   - Control */
    'a',  's', 'd', 'f', 'g',  'h', 'j', 'k', 'l',  ';', /* 39 */
    '\'', '`', 0,                                        /* Left shift */
    '\\', 'z', 'x', 'c', 'v',  'b', 'n',                 /* 49 */
    'm',  ',', '.', '/', 0,                              /* Right shift */
    '*',  0,                                             /* Alt */
    ' ',                                                 /* Space bar */
    0,                                                   /* Caps lock */
    0,                                                   /* 59 - F1 key ... > */
    0,    0,   0,   0,   0,    0,   0,   0,   0,         /* < ... F10 */
    0,                                                   /* 69 - Num lock*/
    0,                                                   /* Scroll Lock */
    0,                                                   /* Home key */
    0,                                                   /* Up Arrow */
    0,                                                   /* Page Up */
    '-',  0,                                             /* Left Arrow */
    0,    0,                                             /* Right Arrow */
    '+',  0,                                             /* 79 - End key*/
    0,                                                   /* Down Arrow */
    0,                                                   /* Page Down */
    0,                                                   /* Insert Key */
    0,                                                   /* Delete Key */
    0,    0,   0,   0,                                   /* F11 Key */
    0,                                                   /* F12 Key */
    0,                                                   /* All other keys are undefined */
};

// Lookup table for scancodes to ASCII characters
static char shift_key_map[128] = {
    0,    27,  '!', '@', '#',  '$', '%', '^', '&',  '*', /* 9 */
    '(',  ')', '_', '+', '\b',                           /* Backspace */
    '\t',                                                /* Tab */
    'Q',  'W', 'E', 'R',                                 /* 19 */
    'T',  'Y', 'U', 'I', 'O',  'P', '{', '}', '\n',      /* Enter key */
    0,                                                   /* 29   - Control */
    'A',  'S', 'D', 'F', 'G',  'H', 'I', 'K', 'L',  ':', /* 39 */
    '\"', '~', 0,                                        /* Left shift */
    '|',  'Z', 'X', 'C', 'V',  'B', 'N',                 /* 49 */
    'M',  '<', '>', '?', 0,                              /* Right shift */
    '*',  0,                                             /* Alt */
    ' ',                                                 /* Space bar */
    0,                                                   /* Caps lock */
    0,                                                   /* 59 - F1 key ... > */
    0,    0,   0,   0,   0,    0,   0,   0,   0,         /* < ... F10 */
    0,                                                   /* 69 - Num lock*/
    0,                                                   /* Scroll Lock */
    0,                                                   /* Home key */
    0,                                                   /* Up Arrow */
    0,                                                   /* Page Up */
    '-',  0,                                             /* Left Arrow */
    0,    0,                                             /* Right Arrow */
    '+',  0,                                             /* 79 - End key*/
    0,                                                   /* Down Arrow */
    0,                                                   /* Page Down */
    0,                                                   /* Insert Key */
    0,                                                   /* Delete Key */
    0,    0,   0,   0,                                   /* F11 Key */
    0,                                                   /* F12 Key */
    0,                                                   /* All other keys are undefined */
};

void keyboard_bind(keyboardCallback callback)
{
    if (callback)
    {
        g_callback = callback;
    }
}

char get_char_from_scancode(uint8_t scancode)
{
    if (scancode >= 128)
        return 0;

    if ((shiftPressed && !capsLockOn) || (!shiftPressed && capsLockOn))
    {
        return shift_key_map[scancode];
    }
    else
    {
        return normal_key_map[scancode];
    }
}

void keyboard_handler()
{
    if (g_callback == NULL)
    {
        puts("Keyboard has no binding to handle characters.\n");
        return;
    }

    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    if (scancode & 0x80)
    {
        // Key release event
        switch (scancode)
        {
            case 0xAA:
            case 0xB6:
                shiftPressed = false;
                break;
        }
    }
    else
    {
        switch (scancode)
        {
            case 0x2A:
            case 0x36:
                shiftPressed = true;
                break;
            case 0x3A:
                capsLockOn = !capsLockOn;
                break;
        }

        // Key press event
        char c = get_char_from_scancode(scancode);
        if (c != 0)
        {
            g_callback(c);
        }
    }
}

void keyboard_init()
{
    // Unmask IRQ1
    unmask_irq(KEYBOARD_IRQ);
}

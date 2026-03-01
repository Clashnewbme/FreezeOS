; kernel_entry.asm
[bits 32]

section .text
; Extern functions
extern kernel
extern timer_handler
extern keyboard_handler

; Kernel entry point
global kernel_entry
kernel_entry:

    mov byte [0xb8000], 'K'
    mov byte [0xb8001], 0x2f
    mov byte [0xb8002], 'E'
    mov byte [0xb8003], 0x4f

    call kernel         ; Call the kernel

    jmp $

; isr1 handler
global isr1_handler
isr1_handler:
    cli
    pushad

    call timer_handler ; Call keyboard handler to hangle the interrupt

    mov al, 0x20    ; End of enterrupt (EOI) command code
    out 0x20, al    ; Send to master pic

    popad
    sti
    iretd

; irq1 handler
global irq1_handler
irq1_handler:
    cli
    pushad

    call keyboard_handler ; Call keyboard handler to hangle the interrupt

    mov al, 0x20    ; End of enterrupt (EOI) command code
    out 0x20, al    ; Send to master pic

    popad
    sti
    iretd
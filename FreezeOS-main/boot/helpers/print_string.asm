; print_string.asm
print_string:
    mov ah, 0x0e

.print_loop:
    lodsb
    cmp al, 0
    je .print_done
    int 0x10
    jmp .print_loop

.print_done:
    ret
    
load_fat:
    mov dl, 5
    mov si, [fat_location]
    call read_sector
    mov ax, [si]
    cmp ax, 0xfff8
    je .fat_Loaded
    jmp .faild_to_load_fat

.fat_Loaded:
    mov ah, 0x0e
    mov al, 'L'
    int 0x10
    ret

.faild_to_load_fat:
    ; Faild to load the fat
    mov ah, 0x0e
    mov al, 'F'
    int 0x10
    ret
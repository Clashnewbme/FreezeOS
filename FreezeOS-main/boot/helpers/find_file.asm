find_file:

    mov ax, [SectorsPerFAT]
    mov bx, [NumberOfFATs]
    mul bx
    mov cl, al
    add cl, [ReservedSectors]
    inc cl
    mov dl, cl

    mov si, 0x7e00
    call read_sector
    mov si, 0x7e20

    mov cx, RootEntries
find_file_loop:
    ; Check if this is the file we are looking for
    mov di, loader_name
    mov cx, 11
    repe cmpsb
    je file_found

    ; Move to next directory entry
    mov ax, 53
    add ax, cx
    add si, ax
    loop find_file_loop

file_not_found:
    mov ah, 0x0e
    mov al, 'N'
    int 0x10
    jmp $

file_found:
    ; Get first cluster
    mov ah, 0x0e
    mov al, 'X'
    int 0x10
    mov ax, [si + 15]
    ret

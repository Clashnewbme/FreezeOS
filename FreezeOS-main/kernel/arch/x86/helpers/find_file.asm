; find_file.asm

find_file:
    ; Move si to root entries address
    mov si, 0x7e20

    mov cx, RootEntries
find_file_loop:
    ; Check if this is the file we are looking for
    mov di, kernel_name
    mov cx, 11
    repe cmpsb
    je file_found

    ; Move to next directory entry
    mov ax, 53
    add ax, cx
    add si, ax
    loop find_file_loop

file_not_found:
    mov byte [0xb8000], 'N'
    mov byte [0xb8001], 0x4f
    jmp $

file_found:
    ; Get first cluster
    mov byte [0xb8000], 'X'
    mov byte [0xb8001], 0x2f
    mov eax, [si + 15]
    ret

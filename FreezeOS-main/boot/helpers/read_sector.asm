read_sector:
    ; Read sector from disk
    pusha
    mov ah, 0x02
    mov al, [SectorsPerCluster]          ; Read one sector
    mov ch, 0          ; Cylinder number
    mov cl, dl         ; Sector number
    mov dl, 0x80           ; Drive number
    mov bx, si         ; Buffer to read into
    int 0x13
    ; jc disk_error
    popa
    ret
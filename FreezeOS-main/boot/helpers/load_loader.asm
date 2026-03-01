; load_loader.asm
load_loader:
    ; Find the file from root directory
    call find_file

    ; Move the cluster number on cx register
    mov cx, ax
    mov si, loader_location

    ; Call load cluster to load all clusters of current file
    call load_cluster

    ret

load_cluster:
    ; Load the cluster data to memory
    call load_data
    push si

    ; Get next cluster number
    mov si, [fat_location]
    mov ax, 2
    mov bx, cx
    mul bx

    ; Check if cluster is last cluster
    add si, ax
    mov cx, [si]
    sub si, ax
    cmp cx, 0xffff
    je loader_loaded    ; No cluster is left to read

    ; Move the point to laod next cluster
    pop si
    add si, 2048

    ; Load cluster agin
    jmp load_cluster

load_data:
    pusha

    ; Read sectors
    call get_sector_number
    call read_sector

    popa
    ret

; Calculate the sector number
get_sector_number:
    mov al, cl
    mov bl, 4
    mul bl
    mov dl, al
    add dl, 6
    mov dh, 1
    ret

loader_loaded:
    pop si
    ret
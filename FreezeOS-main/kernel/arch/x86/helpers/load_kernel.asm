; load_kernel.asm
section .text
load_kernel:
    ; Find the file from root directory
    call find_file

    ; Move the cluster number on cx register
    mov ecx, eax
    mov esi, kernel_location

    ; Call load cluster to load all clusters of current file
    call load_cluster

    ret

load_cluster:
    call load_data
    push esi

    mov esi, fat_location
    mov eax, 2
    mov ebx, ecx
    mul ebx

    add esi, eax
    mov cx, [si]
    cmp cx, 0xffff
    ; No cluster left
    je kernel_loaded

    mov eax, ecx
    pop esi
    add esi, 2048

    jmp load_cluster
load_data:
    pusha
    mov edi, 0

    call get_sector_number
    mov ecx, ebx

.load_data_loop:
    mov ebx, esi
    call read_sector
    inc ecx
    add esi, 512

    ; Loop section
    cmp edi, 3
    je .load_data_done

    inc edi
    jmp .load_data_loop
    
.load_data_done:
    popa
    ret

kernel_loaded:
    pop esi
    ret

; Get sector number
get_sector_number:
    xor ebx, ebx
    add ebx, 4
    mul ebx
    mov ebx, eax
    add ebx, 68
    ret
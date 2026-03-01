; read_sector.asm
%define ATA_DATA_PORT           0x1F0
%define ATA_ERROR_PORT          0x1F1
%define ATA_SECTOR_COUNT        0x1F2
%define ATA_LBA_LOW             0x1F3
%define ATA_LBA_MID             0x1F4
%define ATA_LBA_HIGH            0x1F5
%define ATA_DRIVE_SELECT        0x1F6
%define ATA_COMMAND_PORT        0x1F7
%define ATA_STATUS_PORT         0x1F7
%define ATA_CMD_READ_SECTORS    0x20
%define ATA_PRIMARY_CONTROL     0x3F6

section .text
read_sector:
    pusha
    mov byte [0xb8010], 'A'
    mov byte [0xb8011], 0x2f

    mov dx, ATA_PRIMARY_CONTROL
    mov al, 0x02
    out dx, al

    ; Drive select
    mov dx, ATA_DRIVE_SELECT
    mov al, 0xE0
    out dx, al

    ; Sector count
    mov dx, ATA_SECTOR_COUNT
    mov al, 1
    out dx, al

    ; LBA low
    mov dx, ATA_LBA_LOW
    mov al, cl
    out dx, al

    ; LBA mid
    mov dx, ATA_LBA_MID
    mov al, 0
    out dx, al

    ; LBA high
    mov dx, ATA_LBA_HIGH
    mov al, 0
    out dx, al

    ; Read sectors command
    mov dx, ATA_COMMAND_PORT
    mov al, ATA_CMD_READ_SECTORS
    out dx, al

.wait_for_ready:
    mov byte [0xb8012], 'B'
    mov byte [0xb8013], 0x2f
    mov dx, ATA_STATUS_PORT
    in al, dx
    test al, 0x08
    jz .wait_for_ready

    mov ecx, 256
    mov edi, ebx

    mov dx, ATA_DATA_PORT
.read_loop:
    mov byte [0xb8014], 'C'
    mov byte [0xb8015], 0x2f
    in ax, dx
    mov [edi], ax
    add edi, 2
    loop .read_loop

    popa
    ret 

; section .bss

; kernel resb 512
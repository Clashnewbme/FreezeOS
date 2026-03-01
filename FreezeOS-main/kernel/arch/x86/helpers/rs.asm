; read_sector.asm
%define ATA_DATA_PORT         0x1F0
%define ATA_ERROR_PORT        0x0F1
%define ATA_SECTOR_COUNT      0x0F2
%define ATA_LBA_LOW           0x0F3
%define ATA_LBA_MID           0x0F4
%define ATA_LBA_HIGH          0x0F5
%define ATA_DRIVE_SELECT      0x0F6
%define ATA_COMMAND_PORT      0x0F7
%define ATA_STATUS_PORT       0x0F7
; Commands
%define ATA_CMD_READ_SECTORS  0x20

section .text
read_sector:
    pusha                    ; Save all general-purpose registers

    ; ; Load the LBA address
    ; mov eax, [LBA]
    ; and eax, 0x0FFFFFFF      ; Mask to 28 bits

    ; Select drive (master) and set LBA bits 24-27
    mov dx, ATA_DRIVE_SELECT
    mov al, 0xE0             ; Set master drive and LBA mode
    out dx, al               ; Write to the drive/head register

    ; Set the sector count (number of sectors to read)
    mov dx, ATA_SECTOR_COUNT
    mov al, 1                ; Reading 1 sector
    out dx, al               ; Write to the sector count register

    ; Set the LBA low byte
    mov dx, ATA_LBA_LOW
    mov al, byte [LBA]
    out dx, al               ; Write to the LBA low byte register

    ; Set the LBA mid byte
    mov dx, ATA_LBA_MID
    mov al, byte [LBA + 1]
    out dx, al               ; Write to the LBA mid byte register

    ; Set the LBA high byte
    mov dx, ATA_LBA_HIGH
    mov al, byte [LBA + 2]
    out dx, al               ; Write to the LBA high byte register

    ; Issue the READ SECTORS command (0x20)
    mov dx, ATA_COMMAND
    mov al, ATA_CMD_READ_SECTORS
    out dx, al               ; Write to the command register

    ; Wait for the drive to be ready (BSY flag should be 0 and DRQ flag should be 1)
.wait_for_ready:
    mov dx, ATA_STATUS
    in al, dx                ; Read the status register
    test al, 0x08            ; Check if BSY or DRQ is set
    jz .wait_for_ready       ; Loop until BSY is 0 and DRQ is 1

    ; Read the data from the data port
    mov ecx, 256              ; 256 words per sector
    mov edi, buffer           ; DI points to the buffer

.read_loop:
    mov dx, ATA_DATA
    in ax, dx                ; Read a word (2 bytes) from the data port
    stosw                    ; Store the word into the buffer
    loop .read_loop          ; Repeat until 256 words are read

    popa                     ; Restore all general-purpose registers
    ret                      ; Return from the function


section .bss
    buffer resb 512 ; Reserve 512 bytes for sector buffer

section .data
    LBA dd 80 ; Example LBA address (modify as needed)
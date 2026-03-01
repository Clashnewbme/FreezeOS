[BITS 32]
[org 0xa000]

; section .bss
; stack resb 10

section .text
kernel_kernel:
    ; Setup stack
    mov eax, 0xffff
    mov ebp, eax
    mov esp, ebp

    ; Find the kernel
    call load_kernel

    ; Jump to kernel location
    call kernel_location

    jmp $

section .data
; kernel location
fat_location       equ 0x9000
kernel_location    equ 0x100000

; kernel name
kernel_name db "KERNEL  BIN", 0

; File system data
BytesPerSector      dw 512           ; Bytes per sector
SectorsPerCluster   db 4             ; Sectors per cluster
ReservedSectors     dw 4             ; Reserved sectors
NumberOfFATs        db 2             ; Number of FATs
RootEntries         dw 512           ; Root directory entries
MediaDescriptor     db 0xF8          ; Media descriptor
SectorsPerFAT       dw 20             ; Sectors per FAT
HiddenSectors       dd 0             ; Hidden sectors

; Includes
%include "arch/x86/helpers/find_file.asm"
%include "arch/x86/helpers/load_kernel.asm"
%include "arch/x86/helpers/read_sector.asm"
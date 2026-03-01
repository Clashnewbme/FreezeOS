; boot.asm
[BITS 16]
[org 0x7c00]

; Define the BIOS Parameter Block (BPB)
jmp short start
nop
OEMLabel            db 'MSDOS5.0'    ; OEM Name
BytesPerSector      dw 512           ; Bytes per sector
SectorsPerCluster   db 4             ; Sectors per cluster
ReservedSectors     dw 4             ; Reserved sectors
NumberOfFATs        db 2             ; Number of FATs
RootEntries         dw 512           ; Root directory entries
TotalSectors        dw 20480          ; Total sectors (for 1.44MB floppy)
MediaDescriptor     db 0xF8          ; Media descriptor
SectorsPerFAT       dw 20             ; Sectors per FAT
SectorsPerTrack     dw 32            ; Sectors per track
NumberOfHeads       dw 2             ; Number of heads
HiddenSectors       dd 0             ; Hidden sectors
TotalSectorsBig     dd 0             ; Total sectors (if TotalSectors is 0)
DriveNumber         db 0             ; Drive number
Reserved1           db 0             ; Reserved
BootSignature       db 0x29          ; Extended boot signature
VolumeID            dd 0x12345678    ; Volume ID
VolumeLabel         db 'NO NAME    ' ; Volume label
FileSystemType      db 'FAT16   '    ; File system type

; loader location
fat_location        dw 0x9000
loader_location    equ 0xa000
loader_offset       dw 0xa000
; loader name
loader_name db 'LOADER  BIN', 0

; Starting point
start:
	; Load fat into memory
	call load_fat

    ; Load the loader
    call load_loader

	; Prepare for protected mode
    jmp jmp_to_pm

    ; Infinite loop
    jmp $

; Include helper files
%include "helpers/read_sector.asm"
%include "helpers/load_fat.asm"
%include "helpers/find_file.asm"
%include "helpers/load_loader.asm"
%include "helpers/print_string.asm"
%include "helpers/gdt.asm"
%include "helpers/jmp_to_pm.asm"
%include "helpers/protected_mode.asm"

; Bootloader healper and signature
times 510-($-$$) db 0   ; Fill the rest of the boot sector with zeros
dw 0xAA55               ; Boot signature

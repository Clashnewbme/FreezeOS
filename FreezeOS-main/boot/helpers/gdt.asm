; gdt.asm
; GDT descriptor
GDT_start:
	null_descriptor:
		dd 0
		dd 0
	code_descriptor:
		dw 0xffff
		dw 0
		db 0
		db 0x9a
		db 0xcf
		db 0
	data_descriptor:
		dw 0xffff
		dw 0
		db 0
		db 0x92
		db 0xcf
		db 0
GDT_end:

GDT_descriptor:
	dw GDT_end - GDT_start - 1
	dd GDT_start

CODE_SEG equ code_descriptor - GDT_start
DATA_SEG equ data_descriptor - GDT_start

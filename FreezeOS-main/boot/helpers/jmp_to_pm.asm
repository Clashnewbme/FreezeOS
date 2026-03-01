; jmp_to_pm.asm
; Prepare for protected mode
jmp_to_pm:
	cli

	lgdt [GDT_descriptor]
	mov eax, cr0
	or eax, 1
	mov cr0, eax	
	
	; Start protected mode
	jmp CODE_SEG:protected_mode
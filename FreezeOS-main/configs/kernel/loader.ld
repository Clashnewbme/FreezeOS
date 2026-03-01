ENTRY(load_kernel)
SECTIONS
{
    . = 0xa000; 
    .text :
    {
        *(.text)
    }
    .rodata :
    {
        *(.rodata)
    }
    .data :
    {
        *(.data)
    }
    .bss :
    {
        *(.bss)
    } 
}

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00080000
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00020000
}

ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        *(.ARM.exidx)
        . = ALIGN(4);
    } > FLASH

    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        __data_load__ = LOADADDR (.data);   /* ROM address of .data */
        __data_start__ = .;                 /* RAM address of .data */
        *(.data*)
        . = ALIGN(4);
        __data_end__ = .;
    } > SRAM

    .bss :
    {
        __bss_start__ = .;
        *(.bss*)
        . = ALIGN(4);
        __bss_end__ = .;
    } > SRAM

    .stack :
    {
        . = ALIGN(8);   /* initial sp should be 8-byte aligned */
        __stack_start_ = .;
        *(.stack*)
        __stack_end_ = .;
    } > SRAM
}

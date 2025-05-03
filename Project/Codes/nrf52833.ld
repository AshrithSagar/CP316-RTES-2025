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
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        *(.ARM.exidx*)
        *(.eh_frame)
        . = ALIGN(4);
    } > FLASH

    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        __etext = LOADADDR (.data);
        __data_load__ = LOADADDR (.data);
        __data_start__ = .;
        . = ALIGN(4);
        *(.data*)
        . = ALIGN(4);
        __data_end__ = .;
    } > SRAM

    .bss :
    {
        __bss_start__ = .;
        . = ALIGN(4);
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > SRAM

    .heap :
    {
        __heap_start__ = .;
        . = ALIGN(4);
        *(.heap*)
        . = ALIGN(4);
        __heap_end__ = .;
    }

    .stack :
    {
        . = ALIGN(8);   /* initial sp should be 8-byte aligned */
        __stack_start_ = .;
        *(.stack*)
        __stack_end_ = .;
    }
}

/* we are not using these symbols but sometimes these are used somewhere and
   providing linker warnings. defining dummy to prevent warning.
*/
PROVIDE(_read = _syscall_error);
PROVIDE(_write = _syscall_error);
PROVIDE(_lseek = _syscall_error);
PROVIDE(_sbrk = _syscall_error);
PROVIDE(_close = _syscall_error);
PROVIDE(_fstat = _syscall_error);
PROVIDE(_isatty = _syscall_error);
PROVIDE(_exit = _syscall_error);
PROVIDE(_abort = _syscall_error);
PROVIDE(_kill = _syscall_error);
PROVIDE(_getpid = _syscall_error);

_syscall_error = DEFINED(_syscall_error) ? _syscall_error : 0xBADDFACE;

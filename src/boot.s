section .__mbHeader
    MAGIC_NUMBER equ 0x1BADB002
    MEMINFO      equ 1 << 1
    FLAGS        equ MEMINFO | 0x0
    CHECKSUM     equ - (MAGIC_NUMBER + FLAGS)
    
    align 0x04
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM


section .text:
    global loader
    extern k_main

    loader:
        mov esp, kernel_stack + KERNEL_STACK_SIZE
        push eax
        push ebx
        call k_main

    .loop:
        jmp .loop


section .bss
    KERNEL_STACK_SIZE equ 4096
    
    align 4
    kernel_stack:
        resb KERNEL_STACK_SIZE

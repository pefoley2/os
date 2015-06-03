section .__mbHeader
    MAGIC_NUMBER equ 0x1BADB002
    FLAGS        equ 0x00
    CHECKSUM     equ - (MAGIC_NUMBER + FLAGS)
    
    align 0x04
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM


section .text:
    global loader
    extern k_main

    loader:
        mov eax, 0xFFFFFFFF
        mov esp, kernel_stack + KERNEL_STACK_SIZE
        call k_main

    .loop:
        jmp .loop


section .bss
    KERNEL_STACK_SIZE equ 4096
    
    align 4
    kernel_stack:
        resb KERNEL_STACK_SIZE

#include <multiboot.h>

#include <vga_term.h>

void k_main(multiboot_info_t *mbd, unsigned int magic) {
    term_init();
    term_putstr("Terminal initialized\n");
    term_flushbuffer();

    if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        return;
    }
    return;
}

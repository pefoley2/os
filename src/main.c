#include <multiboot.h>

#include <early_fb.h>

void k_main(multiboot_info_t *mbd, unsigned int magic) {
    k_fbclear();
    k_fbprint("Entering kernel main!\n");
    k_fbprint("Using early_fb driver\n");
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        k_fbputstring(0, 1,
                "Error: Not loaded by multiboot bootloader. Will now exit.",
                FB_RED, FB_BLACK);
        return;
    }
    return;
}

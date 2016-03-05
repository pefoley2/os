#include <console.h>
#include <kdefs.h>
#include <memory.h>

#include <multiboot.h>

#define PAGE_LIMIT 1048576
#define MAP_SIZE 262144

extern int kernel_end;

static uint32_t phys_page_map[MAP_SIZE];


static void mark_physpage_used(size_t page) {
    size_t offset = page / 32;
    uint8_t bit = page % 32;
    phys_page_map[offset] = phys_page_map[offset] & ~(1 << bit);
}

static void mark_physpage_free(size_t page) {
    size_t offset = page / 32;
    uint8_t bit = page % 32;
    phys_page_map[offset] = phys_page_map[offset] | (1 << bit);
}

static void mark_physpage_range_used(size_t start, size_t end) {
    for(size_t i = start; i < end; i++) {
        mark_physpage_used(i);
    }
}

static void mark_physpage_range_free(size_t start, size_t end) {
    for(size_t i = start; i < end; i++) {
        mark_physpage_free(i);
    }
}

static void set_max_physpage(size_t page) {
    for(size_t i = page; i < PAGE_LIMIT; i++) {
        mark_physpage_used(page);
    }
}

int check_physpage(size_t page) {
    size_t offset = page / 32;
    uint8_t bit = page % 32;
    return (phys_page_map[offset] >> bit) & 1;
}

void init_physpage_map(void) {
    for(size_t i = 0; i < MAP_SIZE; i++) {
        phys_page_map[i] = 0xFFFFFFFF;
    }
    for(size_t i = 0; i < 768; i++) {
        mark_physpage_used(i);
    }
}

void parse_mb_map(multiboot_info_t *mbd) {
    unsigned int low_mem = mbd->mem_lower;
    unsigned int high_mem = mbd->mem_upper;

    size_t highest_page = (high_mem + 1024) / 4;
    set_max_physpage(highest_page);
    if(mbd->flags & 0x20) {
        memory_map_t *mmap = (memory_map_t *)mbd->mmap_addr;
        while((unsigned long) mmap < (mbd->mmap_addr + mbd->mmap_length)) {
            if(mmap->type != 1) {
                unsigned long end_addr = mmap->base_addr_low + mmap->length_low;
                if(end_addr == 0) {
                    end_addr = end_addr - 1;
                }
                size_t page_low = mmap-> base_addr_low >> 12;
                size_t page_high = end_addr >> 12;
                kprint("Marking pages used: ");
                kprint_hex(page_low, 8);
                kprint(" - ");
                kprint_hex(page_high, 8);
                kprint("\n");
                mark_physpage_range_used(page_low, page_high);
            }
            mmap = (memory_map_t *)((unsigned long)mmap + mmap->size + sizeof(unsigned int));
        }
    }
}

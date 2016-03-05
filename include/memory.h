#ifndef _K_MEMORY_H_
#define _K_MEMORY_H_

#include <kdefs.h>

#include <multiboot.h>


int check_physpage(size_t page);
void init_physpage_map(void);
void parse_mb_map(multiboot_info_t *mbd);

#endif

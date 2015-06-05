#ifndef _KERNEL_IO_H_
#define _KERNEL_IO_H_

#include <kdefs.h>

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

void *memcpy(void *dest, void *src, uint32_t size);

#endif

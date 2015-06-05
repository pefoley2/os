#include <io.h>
#include <kdefs.h>

void *memcpy(void *dest, void *src, uint32_t size) {
    int i;
    char *ch_src = (char *) src;
    char *ch_dest = (char *) dest;
    for(i = 0; i < size; i++) {
        ch_dest[i] = ch_src[i];
    }
    return dest;
}

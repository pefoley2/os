#include "framebuffer.h"

void k_main(void) {
    k_fbclear();
    k_fbputstring(0, 0, "Entering kernel main!", FB_WHITE, FB_BLACK);
    return;
}

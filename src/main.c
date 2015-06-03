#include "framebuffer.h"

void k_main(void) {
    k_fbclear();
    k_fbputstring(0, 0, "Booty", FB_RED, FB_BLACK);
    return;
}

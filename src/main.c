char *video_mem = (char *) 0x000B8000;

void kmain(void) {
    video_mem[0] = 'A';
    video_mem[1] = 0x28;
    return;
}

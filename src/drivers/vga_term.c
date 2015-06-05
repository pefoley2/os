#include <io.h>
#include <kdefs.h>

#include "include/vga_term.h"

volatile uint16_t *fb_mem = (volatile uint16_t *) VIDEO_MEM_ADDR;

#define TERM_WIDTH 80
#define TERM_HEIGHT 25

/*
 * The buffer is used to implement scrollback
 */
#define BUFFER_HEIGHT 50
uint16_t term_buffer[TERM_WIDTH * BUFFER_HEIGHT];

uint16_t cur_x = 0;
uint16_t cur_y = 0;

/*
 * The current window row marker. Used for scrollback in the buffer.
 */
uint16_t win_y = 0;


void term_init(void) {
    term_clear();
    term_flushbuffer();
}


void term_setcell(uint16_t x, uint16_t y, char ascii, VGA_COLOR fg, VGA_COLOR bg) {
    if(x >= TERM_WIDTH || y >= TERM_HEIGHT) return;

    uint16_t attrib = (bg << 4) | (fg & 0x0F);
    uint16_t cell_val = (attrib << 8) | ascii;
    uint16_t real_y = win_y + y;

    term_buffer[(real_y * TERM_WIDTH) + x] = cell_val;
    return;
}


void term_putcharattr(char ascii, VGA_COLOR fg, VGA_COLOR bg) {
    if(ascii == '\n') {
        cur_x = 0;
        cur_y++;
    } else if(ascii == '\r') {
        cur_x = 0;
    } else {
        term_setcell(cur_x, cur_y, ascii, fg, bg);
        cur_x++;
    }
    if(cur_x >= TERM_WIDTH) {
        cur_y++;
        cur_x = 0;
    }
    if(cur_y >= TERM_HEIGHT) {
        term_scroll(1);
    }
    return;
}

void term_putchar(char ascii) {
    term_putcharattr(ascii, DEF_FG_COLOR, DEF_BG_COLOR);
    return;
}


void term_putstrattr(char *str, VGA_COLOR fg, VGA_COLOR bg) {
    char cur = *str;
    while(cur != '\0') {
        term_putcharattr(cur, fg, bg);
        cur = (*++str);
    }
}

void term_putstr(char *str) {
    term_putstrattr(str, DEF_FG_COLOR, DEF_BG_COLOR);
    return;
}


static void term_shift_buffer_one(void) {
    int i;
    for(i = BUFFER_HEIGHT; i > 0; i--) {
        uint16_t *src_line = term_buffer + (TERM_WIDTH * i);
        uint16_t *dest_line = term_buffer + (TERM_WIDTH * (i - 1));
        memcpy((void *) dest_line, (void *) src_line, TERM_WIDTH);
    }
}

static void term_shift_buffer(int shift) {
    int i;
    for(i = 0; i < shift; i++) {
        term_shift_buffer_one();
    }
}

void term_scroll(int lines) {
    win_y += lines;
    cur_y += lines;
    if(cur_y < 0) {
        cur_y = 0;
    }
    if(win_y < 0) {
        win_y = 0;
    }
    if(cur_y >= TERM_HEIGHT) {
        cur_y = TERM_HEIGHT - 1;
    }
    if(win_y > (BUFFER_HEIGHT - TERM_HEIGHT)) {
        win_y = BUFFER_HEIGHT - TERM_HEIGHT;
    }

    int shift = TERM_HEIGHT - (BUFFER_HEIGHT - win_y);
    if(shift > 0) {
        term_shift_buffer(shift);
        win_y -= shift;
    }
}


void term_flushbuffer(void) {
    uint32_t len = TERM_WIDTH * TERM_HEIGHT * 2;
    uint16_t start = win_y * TERM_WIDTH;

    memcpy((void *) fb_mem, (void *) (term_buffer + start), len);
    render_cursor();
}

void term_clear(void) {
    int x, y;
    for(x = 0; x < TERM_WIDTH; x++) {
        for(y = 0; y < TERM_HEIGHT; y++) {
            term_setcell(x, y, ' ', DEF_FG_COLOR, DEF_BG_COLOR);
        }
    }
    cur_x = 0;
    cur_y = 0;
}


void render_cursor(void) {
    uint16_t position = (cur_y * TERM_WIDTH) + cur_x;
    
    outb(CURSOR_COMMAND_PORT, CURSOR_HIGH_CMD);
    outb(CURSOR_DATA_PORT, ((position >> 8) & 0x00FF));
    outb(CURSOR_COMMAND_PORT, CURSOR_LOW_CMD);
    outb(CURSOR_DATA_PORT, position & 0x00FF);
}

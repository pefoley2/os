#ifndef _KERNEL_VGA_TERM_H_
#define _KERNEL_VGA_TERM_H_

#include <kdefs.h>

#define VIDEO_MEM_ADDR 0xB8000

#define CURSOR_COMMAND_PORT 0x3D4
#define CURSOR_DATA_PORT    0x3D5
#define CURSOR_HIGH_CMD     14
#define CURSOR_LOW_CMD      15

extern volatile uint16_t *fb_mem;

enum VGA_TEXT_COLORS {
    VGA_BLACK = 0,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_LGREY,
    VGA_DGREY,
    VGA_LBLUE,
    VGA_LGREEN,
    VGA_LCYAN,
    VGA_LRED,
    VGA_LMAGENTA,
    VGA_LBROWN,
    VGA_WHITE
};
typedef enum VGA_TEXT_COLORS VGA_COLOR;


/*
 * Default terminal colors
 */
#define DEF_BG_COLOR VGA_BLACK
#define DEF_FG_COLOR VGA_WHITE

void term_init(void);

/*
 *  Sets cell at x and y to the desired character and attributes
 *  x and y are defined in terms of the visible terminal, not the buffer
 */
void term_setcell(uint16_t x, uint16_t y, char ascii, VGA_COLOR fg, VGA_COLOR bg);


void term_putcharattr(char ascii, VGA_COLOR fg, VGA_COLOR bg);
void term_putchar(char ascii);


void term_putstrattr(char *str, VGA_COLOR fg, VGA_COLOR bg);
void term_putstr(char *str);


void term_scroll(int lines);


void term_flushbuffer(void);
void term_clear(void);


void render_cursor(void);

#endif

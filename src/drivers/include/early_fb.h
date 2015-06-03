#ifndef _KERNEL_FB_H_
#define _KERNEL_FB_H_

#define VIDEO_MEM_ADDR 0x000B8000

extern char *fb_mem;

enum FB_COLORS {
    FB_BLACK = 0,
    FB_BLUE,
    FB_GREEN,
    FB_CYAN,
    FB_RED,
    FB_MAGENTA,
    FB_BROWN,
    FB_LGREY,
    FB_DGREY,
    FB_LBLUE,
    FB_LGREEN,
    FB_LCYAN,
    FB_LRED,
    FB_LMAGENTA,
    FB_LBROWN,
    FB_WHITE
};
typedef enum FB_COLORS FB_COLOR;

#define FB_BG_COLOR FB_BLACK
#define FB_FG_COLOR FB_WHITE


void k_fbwritecell(unsigned int cell, char ascii, FB_COLOR fg, FB_COLOR bg);

/*
 *
 * Writes character at (zero indexed) row and column with the
 * given foreground and background color
 * 
 * The screen is 80 columns by 25 rows
 * The function will silently fail if x > 79 and/or y > 24
 *
 */

void k_fbputchar(char x, char y, char ascii, FB_COLOR fg, FB_COLOR bg);

void k_fbputstring(char x, char y, char *string, FB_COLOR fg, FB_COLOR bg);

void k_fbprintc(char ch);

void k_fbprint(char *string);

void k_fbputall(char ascii, FB_COLOR fg, FB_COLOR bg);

void k_fbclear(void);

#endif

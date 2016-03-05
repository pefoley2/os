#ifndef _K_CONSOLE_H_
#define _K_CONSOLE_H_

struct console_struct {
    void (*writec)(char);
    char (*readc)(void);
};

void init_early_console(void);

void kprint(char *string);

void kprint_hex(unsigned int value, int width);
void kprint_dec(unsigned int value, int width);

#endif

#include "string.h"

unsigned int k_strlen(char *string) {
    unsigned int len;
    for(len = 0; *(string++) != '\0'; len++);
    return len;
}

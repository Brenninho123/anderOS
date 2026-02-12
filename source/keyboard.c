#include "keyboard.h"
#include <stdint.h>

#define KEYBOARD_STATUS 0x64
#define KEYBOARD_DATA   0x60

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

char get_key() {
    while (!(inb(KEYBOARD_STATUS) & 1));
    return inb(KEYBOARD_DATA);
}
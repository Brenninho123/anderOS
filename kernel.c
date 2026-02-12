#include <stdint.h>

#define VIDEO_MEMORY 0xB8000
#define KEYBOARD_STATUS 0x64
#define KEYBOARD_DATA 0x60

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void print(const char* str, int color) {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    for (int i = 0; str[i] != '\0'; i++) {
        video[i*2] = str[i];
        video[i*2+1] = color;
    }
}

char get_key() {
    while (!(inb(KEYBOARD_STATUS) & 1));
    return inb(KEYBOARD_DATA);
}

void kernel_main() {
    print("Welcome to anderOS kernel!", 0x0F);

    while (1) {
        char c = get_key();
        volatile char* video = (volatile char*)VIDEO_MEMORY;
        video[80*2] = c;   // prints typed key in first column of second line
        video[80*2+1] = 0x0F;
    }
}
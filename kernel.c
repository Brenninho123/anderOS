#include <stdint.h>

// --- Video memory ---
#define VIDEO_MEMORY 0xB8000
#define MAX_COLS 80
#define MAX_ROWS 25

// --- Keyboard ports ---
#define KEYBOARD_STATUS 0x64
#define KEYBOARD_DATA   0x60

// --- Inline assembly para porta ---
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// --- Video helpers ---
void print(const char* str, int color) {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    static int row = 0;
    static int col = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            row++;
            col = 0;
            continue;
        }
        video[(row*MAX_COLS + col)*2] = str[i];
        video[(row*MAX_COLS + col)*2 + 1] = color;
        col++;
        if (col >= MAX_COLS) { col = 0; row++; }
        if (row >= MAX_ROWS) { row = 0; } // simples scroll
    }
}

// --- Clear screen ---
void clear_screen() {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    for (int i = 0; i < MAX_COLS*MAX_ROWS*2; i++) video[i] = 0;
}

// --- Execute command ---
void execute_command(const char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        print("Commands: help, clear\n", 0x0F);
    } else if (strcmp(cmd, "clear") == 0) {
        clear_screen();
    } else {
        print("Unknown command\n", 0x0F);
    }
}

// --- Read key ---
char get_key() {
    while (!(inb(KEYBOARD_STATUS) & 1));
    return inb(KEYBOARD_DATA);
}

// --- Simple strcmp ---
int strcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i]) i++;
    return s1[i] - s2[i];
}

// --- Kernel main ---
void kernel_main() {
    clear_screen();
    print("Welcome to anderOS!\nType 'help' for commands.\n> ", 0x0F);

    char buffer[128];
    int index = 0;

    while (1) {
        char c = get_key();

        if (c == 0x1C) { // Enter
            buffer[index] = '\0';
            print("\n", 0x0F);
            execute_command(buffer);
            print("> ", 0x0F);
            index = 0;
        } else if (c == 0x0E) { // Backspace
            if (index > 0) {
                index--;
                volatile char* video = (volatile char*)VIDEO_MEMORY;
                int pos = (MAX_COLS + index)*2; // simplificado
                video[pos] = ' ';
            }
        } else {
            buffer[index++] = c;
            volatile char* video = (volatile char*)VIDEO_MEMORY;
            int pos = (MAX_COLS*2 + index - 1)*2; // simplificado
            video[pos] = c;
            video[pos+1] = 0x0F;
        }
    }
}
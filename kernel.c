#include <stdint.h>

#define VIDEO_MEMORY 0xB8000
#define MAX_COLS 80
#define MAX_ROWS 25
#define KEYBOARD_STATUS 0x64
#define KEYBOARD_DATA   0x60

// --- Inline assembly ---
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// --- Video helpers ---
void clear_screen() {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    for (int i = 0; i < MAX_COLS*MAX_ROWS*2; i++) video[i] = 0;
}

// --- Print char at row, col ---
void print_char(char c, int color, int row, int col) {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    if (row < MAX_ROWS && col < MAX_COLS) {
        video[(row*MAX_COLS + col)*2] = c;
        video[(row*MAX_COLS + col)*2 + 1] = color;
    }
}

// --- Scroll screen up 1 line ---
void scroll() {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    for (int row = 1; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            video[((row-1)*MAX_COLS + col)*2] = video[(row*MAX_COLS + col)*2];
            video[((row-1)*MAX_COLS + col)*2 + 1] = video[(row*MAX_COLS + col)*2 + 1];
        }
    }
    // Clear last row
    for (int col = 0; col < MAX_COLS; col++) {
        video[((MAX_ROWS-1)*MAX_COLS + col)*2] = ' ';
        video[((MAX_ROWS-1)*MAX_COLS + col)*2 + 1] = 0x0F;
    }
}

// --- Print string with auto-scroll ---
void print(const char* str, int color) {
    static int row = 6; // abaixo do logo
    static int col = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            row++;
            col = 0;
            if (row >= MAX_ROWS) { scroll(); row = MAX_ROWS-1; }
            continue;
        }
        print_char(str[i], color, row, col);
        col++;
        if (col >= MAX_COLS) { col = 0; row++; }
        if (row >= MAX_ROWS) { scroll(); row = MAX_ROWS-1; }
    }
}

// --- Simple strcmp ---
int strcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i]) i++;
    return s1[i] - s2[i];
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

// --- Draw logo ---
void draw_logo() {
    const char* logo[] = {
        "  _   _       _             ____  ",
        " | | | | __ _| | _____     / ___| ",
        " | |_| |/ _` | |/ / _ \\   | |     ",
        " |  _  | (_| |   <  __/   | |___  ",
        " |_| |_|\\__,_|_|\\_\\___|    \\____| ",
        ""
    };
    int color = 0x0A; // green
    for (int i = 0; i < 6; i++) {
        print(logo[i], color);
    }
}

// --- Kernel main ---
void kernel_main() {
    clear_screen();
    draw_logo();
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
                int row = MAX_ROWS-1;
                int col = index;
                print_char(' ', 0x0F, row, col);
            }
        } else {
            buffer[index++] = c;
            int row = MAX_ROWS-1;
            int col = index-1;
            print_char(c, 0x0F, row, col);
        }
    }
}
#include "utils.h"
#include <stdint.h>

#define VIDEO_MEMORY 0xB8000
#define MAX_COLS 80
#define MAX_ROWS 25

void print_char(char c, int color, int row, int col) {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    if (row < MAX_ROWS && col < MAX_COLS) {
        video[(row*MAX_COLS + col)*2] = c;
        video[(row*MAX_COLS + col)*2 + 1] = color;
    }
}

void print(const char* str, int color) {
    static int row = 6; // below logo
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

void clear_screen() {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    for (int i = 0; i < MAX_COLS*MAX_ROWS*2; i++) video[i] = 0;
}

void scroll() {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    for (int row = 1; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            video[((row-1)*MAX_COLS + col)*2] = video[(row*MAX_COLS + col)*2];
            video[((row-1)*MAX_COLS + col)*2 + 1] = video[(row*MAX_COLS + col)*2 + 1];
        }
    }
    // clear last row
    for (int col = 0; col < MAX_COLS; col++) {
        video[((MAX_ROWS-1)*MAX_COLS + col)*2] = ' ';
        video[((MAX_ROWS-1)*MAX_COLS + col)*2 + 1] = 0x0F;
    }
}

int strcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i]) i++;
    return s1[i] - s2[i];
}
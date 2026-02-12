#include "utils.h"
#include "keyboard.h"
#include "logo.h"
#include "terminal.h"

#define BUFFER_SIZE 128

// Entry do kernel em 32-bit
void kernel_main() {
    clear_screen();
    draw_logo();
    print("Welcome to anderOS Protected Mode!\nType 'help' for commands.\n> ", 0x0F);

    char buffer[BUFFER_SIZE];
    int index = 0;

    while (1) {
        char c = get_key();

        if (c == 0x1C) { // Enter
            buffer[index] = '\0';
            print("\n", 0x0F);
            execute_command(buffer);
            print("> ", 0x0F);
            index = 0;
        } 
        else if (c == 0x0E) { // Backspace
            if (index > 0) {
                index--;
                int row = MAX_ROWS-1;
                int col = index;
                print_char(' ', 0x0F, row, col);
            }
        } 
        else if (c >= 32 && c <= 126) { // ASCII imprimível
            if (index < BUFFER_SIZE-1) {
                buffer[index++] = c;
                int row = MAX_ROWS-1;
                int col = index-1;
                print_char(c, 0x0F, row, col);
            }
        }

        if (index >= MAX_COLS) {
            scroll();
            index = 0;
        }
    }
}
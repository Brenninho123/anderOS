#include "utils.h"
#include "keyboard.h"
#include "logo.h"
#include "terminal.h"

// Kernel principal
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
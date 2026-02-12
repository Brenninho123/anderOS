#include "utils.h"
#include "keyboard.h"
#include "logo.h"
#include "terminal.h"

#define BUFFER_SIZE 128

void kernel_main() {
    // Limpa a tela e desenha logo
    clear_screen();
    draw_logo();
    print("Welcome to anderOS!\nType 'help' for commands.\n> ", 0x0F);

    char buffer[BUFFER_SIZE];
    int index = 0;

    while (1) {
        char c = get_key();

        if (c == 0x1C) { // Enter
            buffer[index] = '\0';           // Finaliza string
            print("\n", 0x0F);             // Nova linha
            execute_command(buffer);        // Executa comando
            print("> ", 0x0F);             // Novo prompt
            index = 0;                      // Reset buffer
        } 
        else if (c == 0x0E) { // Backspace
            if (index > 0) {
                index--;
                int row = MAX_ROWS - 1;    // linha de input
                int col = index;
                print_char(' ', 0x0F, row, col); // apaga caracter
            }
        } 
        else if (c >= 32 && c <= 126) { // caracteres imprimíveis
            if (index < BUFFER_SIZE - 1) {
                buffer[index++] = c;
                int row = MAX_ROWS - 1;
                int col = index - 1;
                print_char(c, 0x0F, row, col);
            }
        }

        // Scroll automático quando a linha de input ultrapassa
        if (index >= MAX_COLS) {
            scroll();
            index = 0;
        }
    }
}
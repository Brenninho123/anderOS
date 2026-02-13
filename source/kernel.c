#include "utils.h"
#include "keyboard.h"
#include "terminal.h"
#include "logo.h"

#include "os/system.h"
#include "os/memory.h"
#include "os/io.h"

#define KERNEL_COLOR 0x0F

// Buffer de entrada do terminal
static char input_buffer[256];
static int input_pos = 0;

/* ===============================
   Inicialização básica do kernel
================================*/
void kernel_init() {
    clear_screen();

    print_color("Booting anderOS 32-bit...\n", KERNEL_COLOR);
    os_delay(50);

    show_logo();
    print("\n", KERNEL_COLOR);

    os_print_info();
    print("\nType 'help' to see commands.\n\n", KERNEL_COLOR);

    print("> ", KERNEL_COLOR);
}

/* ===============================
   Processamento de teclado
================================*/
void handle_keyboard() {
    char c = keyboard_getchar();

    if (!c)
        return;

    // Enter
    if (c == '\n') {
        print("\n", KERNEL_COLOR);

        input_buffer[input_pos] = '\0';
        execute_command(input_buffer);

        // Reset buffer
        input_pos = 0;
        memset(input_buffer, 0, sizeof(input_buffer));

        print("> ", KERNEL_COLOR);
        return;
    }

    // Backspace
    if (c == '\b') {
        if (input_pos > 0) {
            input_pos--;
            print("\b \b", KERNEL_COLOR);
        }
        return;
    }

    // Caracter normal
    if (input_pos < sizeof(input_buffer) - 1) {
        input_buffer[input_pos++] = c;
        char s[2] = {c, 0};
        print(s, KERNEL_COLOR);
    }
}

/* ===============================
   Loop principal do kernel
================================*/
void kernel_main() {
    kernel_init();

    while (1) {
        handle_keyboard();

        // Pequeno delay para evitar uso 100% da CPU
        os_delay(1);
    }
}
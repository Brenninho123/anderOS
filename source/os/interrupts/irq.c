#include "irq.h"
#include "../io.h"
#include "../../keyboard.h"
#include "../../terminal.h"

void irq_keyboard_handler() {
    char c = keyboard_getchar();
    if (c)
        terminal_input(c);

    outb(0x20, 0x20); // EOI
}

static int tick = 0;

void irq_timer_handler() {
    tick++;
    outb(0x20, 0x20); // EOI
}
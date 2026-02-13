[bits 32]

global isr0
global irq0
global irq1

extern irq_timer_handler
extern irq_keyboard_handler

isr0:
    iretd

irq0:
    cli
    call irq_timer_handler
    sti
    iretd

irq1:
    cli
    call irq_keyboard_handler
    sti
    iretd
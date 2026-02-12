#include "system.h"
#include "utils.h"

void os_reboot() {
    print("Rebooting...\n", 0x0F);
    __asm__ volatile (
        "mov al, 0xFE\n"
        "out 0x64, al\n"
    );
}

void os_print_info() {
    print("anderOS - Custom 32-bit OS\n", 0x0F);
    print("Author: Brenninho123\n", 0x0F);
    print("Terminal & Protected Mode active\n", 0x0F);
}

void os_delay(int ms) {
    for (volatile int i = 0; i < ms * 1000; i++);
}
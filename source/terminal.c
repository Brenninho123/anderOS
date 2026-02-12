#include "terminal.h"
#include "utils.h"

// Versão atual do anderOS
#define OS_VERSION "anderOS 0.1"

void execute_command(const char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        print("Commands: help, clear, version, reboot, info\n", 0x0F);
    } 
    else if (strcmp(cmd, "clear") == 0) {
        clear_screen();
    } 
    else if (strcmp(cmd, "version") == 0) {
        print("anderOS version: ", 0x0F);
        print(OS_VERSION, 0x0F);
        print("\n", 0x0F);
    } 
    else if (strcmp(cmd, "reboot") == 0) {
        print("Rebooting...\n", 0x0F);
        // Reboot usando porta 0x64
        __asm__ volatile (
            "mov al, 0xFE\n"
            "out 0x64, al\n"
        );
    } 
    else if (strcmp(cmd, "info") == 0) {
        print("anderOS - Custom 32-bit OS\n", 0x0F);
        print("Simple terminal + keyboard support\n", 0x0F);
        print("Author: Brenninho123\n", 0x0F);
    } 
    else {
        print("Unknown command\n", 0x0F);
    }
}
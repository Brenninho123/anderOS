#include "terminal.h"
#include "utils.h"

void execute_command(const char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        print("Commands: help, clear\n", 0x0F);
    } else if (strcmp(cmd, "clear") == 0) {
        clear_screen();
    } else {
        print("Unknown command\n", 0x0F);
    }
}
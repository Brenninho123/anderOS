#include "logo.h"
#include "utils.h"

void draw_logo() {
    const char* logo[] = {
        "  _   _       _             ____  ",
        " | | | | __ _| | _____     / ___| ",
        " | |_| |/ _` | |/ / _ \\   | |     ",
        " |  _  | (_| |   <  __/   | |___  ",
        " |_| |_|\\__,_|_|\\_\\___|    \\____| ",
        ""
    };
    int color = 0x0A; // green
    for (int i = 0; i < 6; i++) {
        print(logo[i], color);
    }
}
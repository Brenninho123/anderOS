void kernel_main() {
    char* video = (char*) 0xB8000;

    const char* text = "Welcome to anderOS kernel!";
    
    for (int i = 0; text[i] != '\0'; i++) {
        video[i * 2] = text[i];      // character
        video[i * 2 + 1] = 0x0F;     // color (white)
    }

    while (1) {
        // Infinite loop keeps OS running
    }
}
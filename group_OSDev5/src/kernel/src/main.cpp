#include <system.h>

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}
void clear_screen() {
    char* vidmem = (char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vidmem[i] = ' ';
        vidmem[i+1] = 0x0f; // black background, white foreground
    }
}

void print(const char* str) {
    char* vidmem = (char*)0xb8000;
    int i = 0;
    while (str[i] != '\0') {
        vidmem[i * 2] = str[i];
        vidmem[i * 2 + 1] = 0x0f; // Set color attribute to white on blue
        i++;
    }
}

void kernel_main()
{

    clear_screen();
    print("Hello, world");

}
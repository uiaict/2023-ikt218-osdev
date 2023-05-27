
#include "system.h"

// Define entry point in asm to prevent C++ mangling

extern "C"{
    void kernel_main();
}

void kernel_main()
{
int a = 900000;


int b = 100;
a = b;

int v = 5;
*((int*)0xb8000)=0x07690748;

}

// Set the color you want to use for the text
    //uint8_t color = 0x0F; // White text on black background

    // Write "Hello, World!" to the screen
    //const char *str = "Hello, World!";
   // for (size_t i = 0; str[i] != '\0'; ++i) {
//vga_putc(str[i], color, i, 0);
    

    // Halt the CPU
    //for (;;) {
    //    __asm__("hlt");
    //}
//}
